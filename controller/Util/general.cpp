#include "../Util/general.h"

	// File: general.cpp
	// @Author Lars Veenendaal 1633223
	// 0.2 - Refactor & comments
	// 0.1 - Skeleton setup

using namespace ImageLib;
using namespace std;

void General::Input_Control(std::string filename){
	unique_ptr<ImageRGB> img;
	load_image(filename);	 // is the file loadable
	//check_filetype(filename);	// Do we accept the filetype (jpg, png, 
	minimum_resolution(loadImg(filename)); // Is it bigger than the defined 'unacceptable resolution' -640x480
}
/*void General::load_image(char * filename){
	unique_ptr<ImageRGB> img;
	try { img = loadImg(filename); }
	catch (...)
	{
		throw GeneralExceptions("IMAGE_NOT_FOUND");
	}
}*/
void General::load_image(std::string filename) {
	// I cant fix the debugmode in the library of CImg. 
	// So i cant keep remove the the ugly error.

	try {
		loadImg(filename);
	}
	catch (...)
	{
		throw GeneralExceptions("IMAGE_NOT_FOUND");
	}
	//return *image;
}

void General::check_filetype(std::string filename){
	size_t lastdot = filename.find_last_of(".");
	std::string extension = filename.substr(lastdot);
	cout << extension << "--" << (extension.compare(".jpg")) << endl;
	//NPOS = is a static member constant value with the greatest possible value for an element of type size_t.
	
	if (lastdot == std::string::npos){
		throw GeneralExceptions("IMAGE_FILETYPE_NOT_ALLOWED");
	}
	// Extension checking if they are not allowed throw filetype error.
	if ((extension.compare(".jpg") != 0) && (extension.compare(".png") != 0) && (extension.compare(".bmp") != 0)){
		throw GeneralExceptions("IMAGE_FILETYPE_NOT_ALLOWED");
	}
}

void General::minimum_resolution(unique_ptr<ImageRGB> img){
	//unique_ptr<IMAGERGB> img = load_image(filename);
	if (img->width() < 640 || img->height() < 480){
		throw GeneralExceptions("IMAGE_RESOLUTION_TOO_SMALL");
	}

}
