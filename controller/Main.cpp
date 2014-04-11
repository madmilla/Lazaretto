// I need this line in the library... to stop the controller from tossing salads everytime he cant load an image.
	#define cimg_debug 0    
#include <memory>
#include <exception>

//UTIL
#include "Util/general.h"
#include "Util/stopwatch.h"
#include "Exceptions/allExceptions.h"

//Classes
#include "Localization/localization.h"
#include "Shadow_Lighting/shadow_lighting.h"
#include "Rotation/imageCorrection.h"

#include "OCR2/FileData.h"
#include "OCR2/OpticalCharacterRecognition2.h"

	// File: Main.cpp
	// @Author Lars Veenendaal 1633223
	// 0.4 - Implementation Rotation & Cleaned up code and file structure.
	// 0.3 - Implementation Localization & Shadow
	// 0.2 - General testing added.
	// 0.1 - Skeleton setup.

using namespace ImageLib;
using namespace std;

int main(int argc, char* argv[]){

	//char * filename = (argv[1] == NULL) ? "" : argv[1];
	char * filename = "8.jpg";
	// Needed Defines
	shared_ptr<ImageRGB> img;
	General gen;
	vector<Blob> possibleBlobs;
	// General
	try{
		gen.Input_Control(filename); // Run checks for existance of the file, filetype and size.
	}
	catch (GeneralExceptions &gE){ return 0; } // If something happens here kill the program.
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
		saveImg(input, "lokalisatie.jpg");
	}
	catch (LocalizationExceptions &lE){ cout << "LOC ERROR" << endl; }

	cout << "Localization done: ";
	timeKeeper.printTimePast();

	// Shadow & Lighting
	//Shadow_Lighting snl;
	//shared_ptr<ImageRGB> snl_img = img;
	//ImageRGB snl_img_rgb = *img;
	try{
	//	snl.checkForDefects(snl_img_rgb,2);
	//	saveImg(snl_img_rgb, "snl.jpg");
	} 
	catch (ShadowExceptions sE){
		if (sE.GetError() == "SHADOW"){
			cout << "WHOOOP" << endl;
			//	snl.ApplyShadowFiltering();
		}
		if (sE.GetError() == "OVEREXPOSED"){
			cout << "WHOOOP" << endl;
			//	snl.ApplyShadowFiltering();
		}
	}

	cout << "Shadow and lighting done: ";
	timeKeeper.printTimePast();
	vector<int> t = possibleBlobs[0].getCornerPoints();
	cout << "LT X " << t[0] << " y " << t[1] << endl;
	cout << "RT X " << t[2] << " y " << t[3] << endl;
	cout << "LB X " << t[4] << " y " << t[5] << endl;
	cout << "RB X " << t[6] << " y " << t[7] << endl;

	// Rotation 'n warping
	shared_ptr<ImageRGB> rnw_img_rgb = img;
	shared_ptr<ImageGray> rnw_result;

	try{
		// Gets the img.
		cout << "RNW" << endl;
		float tmpCoord[8] = { t[0], t[1], t[2], t[3], t[4], t[5], t[6], t[7] };
		ImageCorrection::imageCorrection Correction = ImageCorrection::imageCorrection(tmpCoord);
		rnw_result = Correction.correct(*rnw_img_rgb.get());
		// Rotates and fixes up the image and cut out the plate.
		saveImg(*rnw_result, "RNW.jpg");
	}
	catch (DistortExceptions &lE){ cout << "RNW ERROR" << endl; }
	cout << "Rotation done: ";
	timeKeeper.printTimePast();




	// OCR 
	try{
		//Finds some letters
		cout << "OCR" << endl;


		/* Controller lines: */
	//	OpticalCharacterRecognition2 OCR2 = OpticalCharacterRecognition2();
	//	SegmentedImages Characters = OCR2.SegmentateImage(*rnw_result);
	//	std::string Licence = OCR2.ReadLicencePlate(Characters);
		/*
		ImageGray _Image = *rnw_result;
		OpticalCharacterRecognition2 OCR2 = OpticalCharacterRecognition2();
		SegmentedImages Characters = OCR2.SegmentateImage(_Image);
		std::string Licence = OCR2.ReadLicencePlate(Characters);
		*/
		//Send back the found letters.
	}
	catch (DistortExceptions &lE){ cout << "OCR ERROR" << endl; }

	cout << "Controller finished: ";
	timeKeeper.printTimePast();

}