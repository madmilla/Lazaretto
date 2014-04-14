#include "Example.h"

	// File: Example.cpp
	// @Author Lars Veenendaal 1633223
	// 0.1 - Skeleton setup

using namespace ImageLib;
using namespace std;

int Example::do_it(char * filename){
	unique_ptr<ImageRGB> img;
	try{ img = loadImg(filename); }
	catch (...){ throw testExceptions("IMAGE_NOT_FOUND"); return(0); }
		int width = img->width();
		for (int w = 0; w < img->width(); w++){
			for (int h = 0; h < img->height(); h++){
				img->at(w, h).red = 255;
				img->at(w, h).green = 0;
				img->at(w, h).blue = 0;
			}
		}
		saveImg(*img, "test.jpg");
}
int Example::addToTen(int p1, int p2){
	// Only postives
	// Returning value max value is 10;
	if (p1 < 0){ throw testExceptions("P1_OVER_ALLOWED_VALUE"); };
	if (p2 < 0){ throw testExceptions("P2_OVER_ALLOWED_VALUE"); };
	int temp = p1 + p2;
	if (temp > 10){ throw testExceptions("TEMP_OVER_ALLOWED_VALUE"); }
	return temp;
}