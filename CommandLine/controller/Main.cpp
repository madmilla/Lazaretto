#define OCR true				// true = OCR1, false = OCR2
#define OUTPUT_IMAGES false
#define TEST_RUN false			// Leave true unless this is the UI.

#include <memory>
#include <exception>
#include <string>
#include <utility>

#include "ImageLib.h"

//UTIL
#include "Util/general.h"
#include "Util/stopwatch.h"
#include "Exceptions/allExceptions.h"

//Classes
#include "Localization/localization.h"
#include "Shadow_Lighting/shadow_lighting.h"
#include "Rotation/imageCorrection.h"

#include "OCR1/OCRPatternMatching.h"
#include "OCR1/SplitLicensePlate.h"

#include "OCR2/FileData.h"
#include "OCR2/OpticalCharacterRecognition2.h"

#include "OCRNN/NeuralNetworkOCR.h"

	// File: Main.cpp
	// @Author Lars Veenendaal 1633223
	// 0.6.7 -	NN Updated,
	//			Localisation Updated, 
	//			Shadow and Lighting Updated, 
	//			Checking for -1 values to hopefully quash those Violations.
	//			Clock (UI) now return valid times.	// 0.6.6 - Implemented various commented code sections, Solved another Access Violation caused by invalid Vector handling.
	// 0.6.5 -	Access Violations fix. Added a new Shadow solving algorithm.
	// 0.6.4 -	NN reimplementation.
	// 0.6.3 -	ShadowTest replaced, Fix pointer mishap which cause a access violation.
	// 0.6.2 -	ImageTransform Acces Violation fix, RemoveLight Acces Violation fix, Added Multi licenseplate support.
	// 0.6.1 -	Minor refactoring, added debugging values.
	// 0.6 -	Implementation of NN and added a function for when localization cant find a plate.
	// 0.5 -	Implementation of OCR 1 & OCR 2.
	// 0.4 -	Implementation Rotation & Cleaned up code and file structure.
	// 0.3 -	Implementation Localization & Shadow and lighting.
	// 0.2 -	General testing added.
	// 0.1 -	Skeleton setup.

using namespace ImageLib;
using namespace std;

int RetryWithImprovedImage(shared_ptr<ImageRGB> img, vector<Blob> &possibleBlobs){
	// Plan B:
	// Localisation cant find the license plate
	// So shadow and lighting tries to fix the entire image.
	// Then feeds it back to localisation.
	// If all goes well localisation will succes then if not.
	// Stop searching for the license plate which probably wont be there.
	cout << "Localization couldn't find a licenseplate returning it to shadow." << endl;
	// Shadow & Lighting
	Shadow_Lighting snl;
	shared_ptr<ImageRGB> snl_img = img;
	
	try{
	//	vector<int> t = possibleBlobs[0].getCornerPoints();
		snl.checkForDefects(snl_img, 0, 0, img->width(), 0, 0, img->height(), img->width(), img->height());
		saveImg(*snl_img, "loc_fail_snl.jpg");
	}
	catch (ShadowExceptions sE){
		// Shadow manages found things internally.
	}
	cout << "Shadow and lighting done: " << endl;
	// Lokalisatie
	try{
		//Gets the img.
		YellowColorFilter ycf;
		BlobDetection bd;
		ImageRGB input = *snl_img;
		ycf.filterImage(input);
		int minBlobSize = (input.width() * input.height()) * 0.0015;
		possibleBlobs = bd.Invoke(input, 255, minBlobSize);
		saveImg(input, "loc_fail_lokalisatie.jpg");
		if (possibleBlobs.size() <= 0) {
			throw LocalizationExceptions("LICENSE_NOT_FOUND");
		}
	}
	catch (LocalizationExceptions &lE){ return 1; /* Retrying did not help go back */}
	return 0;
}
void Find_licenseplate(char * filename, int nr = 0){

	// Needed Defines
	shared_ptr<ImageRGB> img;
	General gen;
	Shadow_Lighting snl;
	vector<Blob> possibleBlobs;
	string License = "";

	// General
	try{
		gen.Input_Control(filename); // Run checks for existance of the file, filetype and size.
	}
	catch (GeneralExceptions &gE){ cout << "Something happened" << endl; } // If something happens here kill the program.
	catch (std::bad_alloc &gE){ cerr << "Out of memory." << endl; }
	cout << "General checks done: " << endl;

	img = loadImg(filename);	// if all is well this work fine now.
	Stopwatch timeKeeper;		// Moraalistisch starten we de klok zodra de afbeelding is ingeladen? of zodra de order geplaatst is?

	int Plates_found = 0;
	// Lokalisatie
	try{
		//Gets the img.
		YellowColorFilter ycf;
		BlobDetection bd;
		BlobCheck bc;
		ImageRGB input = *img;
		ycf.filterImage(input);
		int minBlobSize = (input.width() * input.height()) * 0.0015;
		possibleBlobs = bd.Invoke(input, 255, minBlobSize);

		for (vector<Blob>::iterator it = possibleBlobs.begin(); it != possibleBlobs.end(); ++it) {
			if (OUTPUT_IMAGES){ saveImg(input, "results/" + to_string(nr) + "/lokalisatie[" + to_string(Plates_found) + "].jpg"); }
		}
		if (possibleBlobs.size() <= 0) {
			throw LocalizationExceptions("LICENSE_NOT_FOUND");
		}
	}
	catch (LocalizationExceptions &lE){
		cout << "RetryWithImprovedImage()" << endl;
		if (RetryWithImprovedImage(img, possibleBlobs) == 1){
			cout << "Retry Failed";
			return;
		}
	}
	cout << "Localization done: ";
	timeKeeper.printTimePast();

	Plates_found = 0;
	for (vector<Blob>::iterator it = possibleBlobs.begin(); it != possibleBlobs.end(); ++it) {

		// Shadow & Lighting
		shared_ptr<ImageRGB> snl_img = img;
		try{
			vector<int> t = possibleBlobs[Plates_found].getCornerPoints();
			snl.checkForDefects(snl_img, t[0], t[1], t[2], t[3], t[4], t[5], t[6], t[7]);
			if (OUTPUT_IMAGES){ saveImg(*snl_img, "results/" + to_string(nr) + "/snl.jpg"); }

		}
		catch (ShadowExceptions sE){	/* Shadow manages found things internally. */ }
		cout << "Shadow and lighting done: ";
		timeKeeper.printTimePast();


		// Rotation 'n warping
		shared_ptr<ImageRGB> rnw_img_rgb = img;
		shared_ptr<ImageGray> rnw_result;

		try{
			// Gets the img.
			cout << "RNW" << snl_img->height() << endl;
			vector<int> t = possibleBlobs[Plates_found].getCornerPoints();
			float tmpCoord[8] = { t[0], t[1], t[2], t[3], t[4], t[5], t[6], t[7] };
			ImageCorrection::imageCorrection Correction = ImageCorrection::imageCorrection(tmpCoord);
			rnw_result = Correction.correct(*snl_img.get());
			// Rotates and fixes up the image and cut out the plate.
			if (OUTPUT_IMAGES){ saveImg(*rnw_result, "results/" + to_string(nr) + "/RNW.jpg"); }

		}
		catch (DistortExceptions &lE){ cout << "RNW ERROR" << endl; } //No exceptions defined by RNW
		cout << "Rotation done: ";
		timeKeeper.printTimePast();


		// OCR 
		//SegmentedImages Characters;
		std::vector<ImageGray> Characters;
		try{
			/*//Finds some letters*/
			if (OCR){
				cout << "OCR" << endl;
				OCRPatternMatching matching;
				std::cout << "Start recognition of " << filename << std::endl;
				SplitLicensePlate* makeSplit = new SplitLicensePlate(*rnw_result);
				Characters = makeSplit->SplitImage();

				//char recognition starts here
				License = matching.RecognizeLicenseplate(Characters);
				cout << Plates_found << ": " << License << endl;
				delete makeSplit;
			}
			else {
				//ORC 2
				cout << "OCR2" << endl;
				//Controller lines:
				OpticalCharacterRecognition2 OCR2 = OpticalCharacterRecognition2();
				Characters = OCR2.SegmentateImage(*rnw_result);

				License = OCR2.ReadLicencePlate(Characters);
				cout << Plates_found << ": " << License << endl;
				//Send back the found letters.*/
			}
		}
		catch (const std::exception& ex) { cout << ex.what() << endl; }
		catch (DistortExceptions &lE){ cout << "OCR ERROR" << endl; }  //No exceptions defined by both OCR's

		// Print out found character.
		for (int i = 0; i < 8 && OUTPUT_IMAGES; i++){
			if (Characters.size() != 10){
				break;
			}
			saveImg(Characters[i], "results/" + to_string(nr) + "/Characters[" + to_string(i) + "].jpg");
		}
		cout << "Controller finished: " << endl;
		timeKeeper.printTimePast();

		Plates_found++;
	
		try{
			//OCRNN;
			NeuralNetworkOCR ocr;
			cout << "NN: " << ocr.recognise(Characters) << endl;
		}
		catch (const std::exception& ex){

		}
		cout << "OCRNN finished: " << endl;
	}
		timeKeeper.printTimePast();

}


int main(int argc, char* argv[]){

	if (TEST_RUN){
		char * filenames[] = { "images/license_plate_1.jpg", "images/license_plate_2.jpg", "images/license_plate_3.jpg",
			"images/license_plate_4.jpg", "images/license_plate_5.jpg", "images/license_plate_6.jpg", "images/license_plate_7.jpg", 
			"images/license_plate_8.jpg", "images/license_plate_9.jpg", "images/license_plate_10.jpg", "images/license_plate_11.jpg", 
			"images/license_plate_ex_1.jpg", "images/license_plate_ex_2.jpg", "images/license_plate_ex_3.jpg", 
			"images/license_plate_ex_4.png", "images/license_plate_ex_5.jpg" };
		for (int i = 0; i < 16; i++){
			Find_licenseplate(filenames[i], i);
		}
	}else{
		char * filename = (argv[1] == NULL) ? "" : argv[1];
		if (filename == "" || strlen(filename) == 0){
			cout << "This application requires a image path as parameter to function." << endl;
		}
		else{
			Find_licenseplate(filename);
		}

	}




	 system("pause");
}

//UTIL for debugging

std::ostream& operator<< (std::ostream& stream, const std::vector<double>& fs){
	stream << '[';
	for (int i = 0; i < fs.size() - 1; i++) {
		stream << fs[i] << ',';
	}
	stream << fs.back() << ']';
	return stream;
}