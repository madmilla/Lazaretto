// I need this line in the library... to stop the controller from tossing salads everytime he cant load an image.
	#define cimg_debug 0    
#include <memory>
#include <exception>
#include <string>
#include <utility>

#include "ImageLib.h"
#include "OCRNN/NeuralNetwork.h"
#include "OCRNN/CheckPatterns.h"
#include "OCRNN/ImageList.h"

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
//#include "ImageList.h"

	// File: Main.cpp
	// @Author Lars Veenendaal 1633223
	// 0.5 - Implementation of OCR 1 & OCR 2.
	// 0.4 - Implementation Rotation & Cleaned up code and file structure.
	// 0.3 - Implementation Localization & Shadow and lighting.
	// 0.2 - General testing added.
	// 0.1 - Skeleton setup.

using namespace ImageLib;
using namespace std;
std::ostream& operator<< (std::ostream& stream, const std::vector<double>& fs)
{
	stream << '[';

	for (int i = 0; i < fs.size() - 1; i++) {
		stream << fs[i] << ',';
	}

	stream << fs.back() << ']';

	return stream;
}

int plan_B(shared_ptr<ImageRGB> img, vector<Blob> &possibleBlobs){
	// Plan B:
	// Localisation cant find the license plate
	// So shadow and lighting tries to fix the entire image.
	// Then feeds it back to localisation.
	// If all goes well localisation will succes then if not.
	// Stop searching for the license plate which probably wont be there.
	vector<Blob> possibleBlobs2;
	cout << "Localization couldn't find a licenseplate returning it to shadow.";
	// Shadow & Lighting
	Shadow_Lighting snl;
	shared_ptr<ImageRGB> snl_img = img;
	
	cout << "Shadow and lighting done: ";
	try{
	//	vector<int> t = possibleBlobs[0].getCornerPoints();
		snl.checkForDefects(snl_img, 0, 0, img->width(), 0, 0, img->height(), img->width(), img->height());
		saveImg(*snl_img, "loc_fail_snl.jpg");
	}
	catch (ShadowExceptions sE){
		// Shadow manages found things internally.
	}
	cout << "Shadow and lighting done: ";
	// Lokalisatie
	try{
		//Gets the img.
		cout << "TEST BRYAN" << endl;
		YellowColorFilter ycf;
		cout << "TEST BRYAN" << endl;
		BlobDetection bd;
			cout << "TEST BRYAN" << endl;
		ImageRGB input = *img;
		cout << "TEST BRYAN" << endl;
		ycf.filterImage(input);
		int minBlobSize = (input.width() * input.height()) * 0.0015;
		cout << "TEST BRYAN" << endl;
		possibleBlobs = bd.Invoke(input, minBlobSize);
		saveImg(input, "loc_fail_lokalisatie.jpg");
		if (possibleBlobs.size() <= 0) {
			throw LocalizationExceptions("LICENSE_NOT_FOUND");
		}
	}
	catch (LocalizationExceptions &lE){ cout << "STILL FAILED" << endl; return 1; }
	return 0;
}
void Plan_A(char * filename, int nr = 0){

	// Needed Defines
	shared_ptr<ImageRGB> img;
	General gen;
	vector<Blob> possibleBlobs;
	// General
	try{
		gen.Input_Control(filename); // Run checks for existance of the file, filetype and size.
	}
	catch (GeneralExceptions &gE){ cout << "Something happened" << endl; } // If something happens here kill the program.
	catch (std::bad_alloc &gE){ cerr << "Out of memory." << endl; }

	cout << "General checks done: " << endl;
	img = loadImg(filename); // if all is well this work fine now.

	Stopwatch timeKeeper; // Moraalistisch starten we de klok zodra de afbeelding is ingeladen? of zodra de order geplaatst is?

	// Lokalisatie
	try{
		//Gets the img.
		YellowColorFilter ycf;
		BlobDetection bd;
		BlobCheck bc;
		ImageRGB input = *img;
		ycf.filterImage(input);
		int minBlobSize = (input.width() * input.height()) * 0.0015;
		possibleBlobs = bd.Invoke(input, minBlobSize);
		saveImg(input, "results/" + to_string(nr) +  "/lokalisatie.jpg");
		if (possibleBlobs.size() <= 0) {
			throw LocalizationExceptions("LICENSE_NOT_FOUND");
		}
	}
	catch (LocalizationExceptions &lE){
		cout << "PLAN B" << endl;
		if (plan_B(img, possibleBlobs) == 1){
			cout << "PLAN B Failed";
			return;
		}
	}
	cout << "Localization done: ";
	timeKeeper.printTimePast();

	// Shadow & Lighting
	Shadow_Lighting snl;
	shared_ptr<ImageRGB> snl_img = img;
	try{
		vector<int> t = possibleBlobs[0].getCornerPoints();
		snl.checkForDefects(snl_img, t[0], t[1], t[2], t[3], t[4], t[5], t[6], t[7]);
		saveImg(*snl_img, "results/" + to_string(nr) + "/snl.jpg");
	}
	catch (ShadowExceptions sE){
		// Shadow manages found things internally.
	}
	cout << "Shadow and lighting done: ";
	timeKeeper.printTimePast();

	// Rotation 'n warping
	shared_ptr<ImageRGB> rnw_img_rgb = img;
	shared_ptr<ImageGray> rnw_result;

	try{
		// Gets the img.
		cout << "RNW" << snl_img->height() << endl;
		vector<int> t = possibleBlobs[0].getCornerPoints();
		float tmpCoord[8] = { t[0], t[1], t[2], t[3], t[4], t[5], t[6], t[7] };
		ImageCorrection::imageCorrection Correction = ImageCorrection::imageCorrection(tmpCoord);
		rnw_result = Correction.correct(*snl_img.get());
		// Rotates and fixes up the image and cut out the plate.
		saveImg(*rnw_result, "results/" + to_string(nr) + "/RNW.jpg");
	}
	catch (DistortExceptions &lE){ cout << "RNW ERROR" << endl; }
	cout << "Rotation done: ";
	timeKeeper.printTimePast();


	// OCR 
	//SegmentedImages Characters;
	std::vector<ImageGray> Characters;
	try{
		/*//Finds some letters*/
		/*
		cout << "OCR" << endl;
		OCRPatternMatching matching;
		std::cout << "Start recognition of " << filename << std::endl;
		SplitLicensePlate* makeSplit = new SplitLicensePlate(*rnw_result);
		characters = makeSplit->SplitImage();
		
		//char recognition starts here
		std::string kenteken = matching.RecognizeLicenseplate(characters);
		std::cout << "LICENSE PLATE: " << kenteken << std::endl;
		kenteken = "results/" + to_string(nr) + "/OCR1-"  + string(kenteken);
	//	const char * plaat = kenteken.c_str();
		fopen(kenteken.c_str(), "wb");
		delete makeSplit;
		*/
		//ORC 2
		cout << "OCR2" << endl;
		//Controller lines:
		OpticalCharacterRecognition2 OCR2 = OpticalCharacterRecognition2();
		Characters = OCR2.SegmentateImage(*rnw_result);

		std::string Licence = OCR2.ReadLicencePlate(Characters);
		Licence = "results/" + to_string(nr) + "/OCR2-" + string(Licence);
		//	const char * plaat = kenteken.c_str();
		fopen(Licence.c_str(), "wb");
		cout << Licence << endl;
		//Send back the found letters.*/

	}
	catch (const std::exception& ex) {
		cout << ex.what() << endl;
	}
	catch (DistortExceptions &lE){ cout << "OCR ERROR" << endl; }
	for (int i = 0; i < 8; i++){
		if (Characters[i].size() != 10){
			break;
		}
		saveImg(Characters[i], "results/"+to_string(nr)+"/Characters[" + to_string(i) + "].jpg");
	}
	cout << "Controller finished: ";
	timeKeeper.printTimePast();

	// OCRNN
	try{
	/*	cout << "OCRNN" << characters.size() << endl;
		NeuralNetworkOCR ocr("OCR.txt");
		for (int i = 0; i < 8; i++) {
			auto result = ocr.convert(characters[i]);
			saveImg(characters[i], "Characters[" + to_string(i) + "].jpg");
			//	std::cout << "target output nodes: " << ocr.char_to_output(Characters[i].getChar()) << std::endl;
			std::cout << "output char: " << result.first << std::endl;
			std::cout << "output nodes: " << ocr.output_nodes() << std::endl;
			std::cout << "output char: " << result.first << "-" << result.second << std::endl;
		} */
	}
	catch (const std::exception& ex){

	}
	cout << "OCRNN finished: ";
	timeKeeper.printTimePast();
}


int main(int argc, char* argv[]){

	//char * filename = (argv[1] == NULL) ? "" : argv[1];
	char * filename = "8.jpg";
	
	char * filenames[] = { "images/license_plate_1.jpg", "images/license_plate_2.jpg", "images/license_plate_3.jpg",
		"images/license_plate_4.jpg", "images/license_plate_5.jpg", "images/license_plate_6.jpg", "images/license_plate_7.jpg", 
		"images/license_plate_8.jpg", "images/license_plate_9.jpg", "images/license_plate_10.jpg", "images/license_plate_11.jpg", 
		"images/license_plate_ex_1.jpg", "images/license_plate_ex_2.jpg", "images/license_plate_ex_3.jpg", 
		"images/license_plate_ex_4.png", "images/license_plate_ex_5.jpg" };
	for (int i = 0; i < 16; i++){
		Plan_A(filenames[i], i);
	}
	
	system("pause");
}