#define OCR true				// true = OCR1, false = OCR2
#define OUTPUT_IMAGES true
#define TEST_RUN false			// this is the UI there is no test run.

// Lazaretto Controller
#include "controller.h"


// File: controller.cpp
// @Author Lars Veenendaal 1633223
// 0.6.3 - Additional optimalization removed cout's and timekeeping inside of the controller.
// 0.6.2 - ImageTransform Acces Violation fix, RemoveLight Access Violation fix, Added Multi licenseplate support.
// 0.6.1 - Minor refactoring, added debugging values.
// 0.6 - Implementation of NN and added a function for when localization cant find a plate.
// 0.5 - Implementation of OCR 1 & OCR 2.
// 0.4 - Implementation Rotation & Cleaned up code and file structure.
// 0.3 - Implementation Localization & Shadow and lighting.
// 0.2 - General testing added.
// 0.1 - Skeleton setup.


using namespace ImageLib;
using namespace std;


string Controller::Find_licenseplate(string filename){

	char *file = new char[filename.length() + 1];
	strcpy(file, filename.c_str());
	// Needed Defines
	shared_ptr<ImageRGB> img;
	General gen;
	Shadow_Lighting snl;
	vector<Blob> possibleBlobs;
	string Licence = "";

	// General
	try{
		gen.Input_Control(filename); // Run checks for existance of the file, filetype and size.
	}
	catch (GeneralExceptions &gE){ cout << "Something happened" << endl; } // If something happens here kill the program.
	catch (std::bad_alloc &gE){ cerr << "Out of memory." << endl; }
	//General checks done:

	img = loadImg(filename);	// if all is well this work fine now.

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
		possibleBlobs = bd.Invoke(input, minBlobSize);
		
		for (vector<Blob>::iterator it = possibleBlobs.begin(); it != possibleBlobs.end(); ++it) {
			if (OUTPUT_IMAGES){ saveImg(input, "results/lokalisatie[" + to_string(Plates_found) + "].jpg"); }
			Plates_found++;
		}
		if (possibleBlobs.size() <= 0) {
			throw LocalizationExceptions("LICENSE_NOT_FOUND");
		}
		
	}
	catch (LocalizationExceptions &lE){
		cout << "RetryWithImprovedImage()" << endl;
		if (RetryWithImprovedImage(img, possibleBlobs) == 1){
			cout << "Retry Failed";
			return "No license plate found.";
		}
	}
	//Localization done:
	
	Plates_found = 0;
	for (vector<Blob>::iterator it = possibleBlobs.begin(); it != possibleBlobs.end(); ++it) {
		
		// Shadow & Lighting
		shared_ptr<ImageRGB> snl_img = img;
		try{
			vector<int> t = possibleBlobs[Plates_found].getCornerPoints();
			snl.checkForDefects(snl_img, t[0], t[1], t[2], t[3], t[4], t[5], t[6], t[7]);
			if (OUTPUT_IMAGES){ saveImg(*snl_img, "results/snl["+ to_string(Plates_found)+"].jpg"); }

		}
		catch (ShadowExceptions sE){	/* Shadow manages found things internally. */ }
		//Shadow and lighting done:


		// Rotation 'n warping
		shared_ptr<ImageRGB> rnw_img_rgb = img;
		shared_ptr<ImageGray> rnw_result;

		try{
			// Gets the img.
			vector<int> t = possibleBlobs[Plates_found].getCornerPoints();
			float tmpCoord[8] = { t[0], t[1], t[2], t[3], t[4], t[5], t[6], t[7] };
			ImageCorrection::imageCorrection Correction = ImageCorrection::imageCorrection(tmpCoord);
			rnw_result = Correction.correct(*snl_img.get());
			// Rotates and fixes up the image and cut out the plate.
			if (OUTPUT_IMAGES){ saveImg(*rnw_result, "results/RNW[" + to_string(Plates_found) + "].jpg"); }

		}
		catch (DistortExceptions &lE){ cout << "RNW ERROR" << endl; } //No exceptions defined by RNW
		//Rotation done:


		// OCR 
		//SegmentedImages Characters;
		std::vector<ImageGray> Characters;
		try{
			/*//Finds some letters*/
			if (OCR){
				//OCR
				OCRPatternMatching matching;
				SplitLicensePlate* makeSplit = new SplitLicensePlate(*rnw_result);
				Characters = makeSplit->SplitImage();

				//char recognition starts here
				Licence = Licence + to_string(Plates_found) + ": " + matching.RecognizeLicenseplate(Characters) + "\r\n";
				//cout << "LICENSE PLATE: " << Licence << std::endl;
					//kenteken = "results/" + to_string(nr) + "/OCR1-" + string(kenteken);
				//	const char * plaat = kenteken.c_str();
				//	fopen(kenteken.c_str(), "wb");
				delete makeSplit;
			}
			else {
				//ORC 2
				//Controller lines:
				OpticalCharacterRecognition2 OCR2 = OpticalCharacterRecognition2();
				Characters = OCR2.SegmentateImage(*rnw_result);
				Licence = Licence + to_string(Plates_found) + ": " + OCR2.ReadLicencePlate(Characters) + "\r\n";
				//Send back the found letters.*/
			}
		}
		catch (const std::exception& ex) { cout << ex.what() << endl; }
		catch (DistortExceptions &lE){ cout << "OCR ERROR" << endl; }  //No exceptions defined by both OCR's

		// Print out found character.
		for (int i = 0; i < 8 && OUTPUT_IMAGES; i++){
			if (Characters[i].size() != 10){
				break;
			}
			saveImg(Characters[i], "results/Characters[" + to_string(i) + "].jpg");
		}
		//Controller finished:

		// OCRNN
		// I have not recieved any updates since 11-04-14. - Lars
		//	try{
		//	cout << "OCRNN" << endl;
		//	NeuralNetworkOCR ocr("OCR.txt");
		//	for (int i = 0; i < 8; i++) {
		//		auto result = ocr.convert(Characters[i]);
		//		saveImg(Characters[i], "Characters[" + to_string(i) + "].jpg");
		//		//	std::cout << "target output nodes: " << ocr.char_to_output(Characters[i].getChar()) << std::endl;
		//		std::cout << "output char: " << result.first << std::endl;
		//		std::cout << "output nodes: " << ocr.output_nodes() << std::endl;
		//		std::cout << "output char: " << result.first << "-" << result.second << std::endl;
		//	}
		//}
		//catch (const std::exception& ex){
		//
		//}
		Plates_found++;
	}

	//OCRNN finished:
	return Licence;
}

int Controller::RetryWithImprovedImage(shared_ptr<ImageRGB> img, vector<Blob> &possibleBlobs){
	// Plan B:
	// Localisation cant find the license plate
	// So shadow and lighting tries to fix the entire image.
	// Then feeds it back to localisation.
	// If all goes well localisation will succes then if not.
	// Stop searching for the license plate which probably wont be there.
	//Localization couldn't find a licenseplate returning it to shadow.
	// Shadow & Lighting
	Shadow_Lighting snl;
	shared_ptr<ImageRGB> snl_img = img;

	try{
		//	vector<int> t = possibleBlobs[0].getCornerPoints();
		snl.checkForDefects(snl_img, 0, 0, img->width(), 0, 0, img->height(), img->width(), img->height());
		if (OUTPUT_IMAGES){ saveImg(*snl_img, "loc_fail_snl.jpg"); }
	}
	catch (ShadowExceptions sE){
		// Shadow manages found things internally.
	}
	//Shadow and lighting done:
	// Lokalisatie
	try{
		//Gets the img.
		YellowColorFilter ycf;
		BlobDetection bd;
		ImageRGB input = *snl_img;
		ycf.filterImage(input);
		int minBlobSize = (input.width() * input.height()) * 0.0015;
		possibleBlobs = bd.Invoke(input, minBlobSize);
		if (OUTPUT_IMAGES){ saveImg(input, "loc_fail_lokalisatie.jpg"); }
		if (possibleBlobs.size() <= 0) {
			throw LocalizationExceptions("LICENSE_NOT_FOUND");
		}
	}
	catch (LocalizationExceptions &lE){ return 1; /* Retrying did not help go back */ }
	return 0;
}