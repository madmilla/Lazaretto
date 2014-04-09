#include <ImageLoader.h>
#include "GeneralExceptions.h"

	// File: general.h
	// @Author Lars Veenendaal 1633223
	// 0.2 - comments
	// 0.1 - Skeleton setup
	/*
		The general class checks for defect of the input file.
		Wether the image can actually find and load.
		If the filetype is accepted: JPG, PNG, BMP.
		Check for resolution size.
	*/
using namespace ImageLib;
using namespace std;

class General{
private:
public:
	void Input_Control(std::string filename);
	void load_image(std::string filename);
	void check_filetype(std::string filename);
	void minimum_resolution(unique_ptr<ImageRGB> img);

};