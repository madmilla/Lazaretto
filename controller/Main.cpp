// I need this line in the library... to stop the controller from tossing salads everytime he cant load an image.
	#define cimg_debug 0    
#include <memory>
#include <exception>
#include "general.h"
#include "shadow_lighting.h"
#include "stopwatch.h"
#include "allExceptions.h"

	// File: Main.cpp
	// @Author Lars Veenendaal 1633223
	// 0.3 - Test implementation.
	// 0.2 - General testing added.
	// 0.1 - Skeleton setup.

using namespace ImageLib;
using namespace std;

int main(int argc, char* argv[]){

	char * filename = (argv[1] == NULL) ? "" : argv[1];

	// Needed Defines
	shared_ptr<ImageRGB> img;
	General gen;
	Stopwatch timeKeeper; // Moraalistisch starten we de klok zodra de afbeelding is ingeladen? of zodra de order geplaatst is?
	
	// General
	try{
		gen.Input_Control(filename); // Run checks for existance of the file, filetype and size.
	}
	catch (GeneralExceptions &gE){ return 0; } // If something happens here kill the program.
	catch (std::bad_alloc &gE){ cerr << "Out of memory." << endl; }

	cout << "General checks done: ";
	img = loadImg(filename); // if all is well this work fine now.

	timeKeeper.printTimePast();



	// Lokalisatie
	try{
		//Gets the img.
		cout << "LOC" << endl;

		//Gives back the licenseplate corners.
	}
	catch (LocalizationExceptions &lE){ cout << "LOC ERROR" << endl; }

	cout << "Localization done: ";
	timeKeeper.printTimePast();



	// Shadow & Lighting
	Shadow_Lighting snl;
	shared_ptr<ImageRGB> snl_img = img;
	ImageRGB snl_img_rgb(*img);
	try{
		// Get the img.
		snl.checkForDefects(snl_img_rgb, 1);
		// Gives back the original image or a modified version.
	} 
	catch (ShadowExceptions sE){
		if (sE.GetError() == "SHADOW"){
			snl.ApplyShadowFiltering();
		}
		if (sE.GetError() == "OVEREXPOSED"){
			snl.ApplyLightingFiltering();
		}
	}
	cout << "Shadow and lighting done: ";
	timeKeeper.printTimePast();



	// Rotation 'n warping
	try{
		// Gets the img.
		cout << "RNW" << endl;
		// Rotates and fixes up the image and cut out the plate.
	}
	catch (DistortExceptions &lE){ cout << "RNW ERROR" << endl; }
	cout << "Rotation done: ";
	timeKeeper.printTimePast();




	// OCR 
	try{
		//Finds some letters
		cout << "OCR" << endl;
		//Send back the found letters.
	}
	catch (DistortExceptions &lE){ cout << "OCR ERROR" << endl; }

	cout << "Controller finished: ";
	timeKeeper.printTimePast();

}