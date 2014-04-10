#ifndef FILTER_H
#define FILTER_H
#include <iostream>
#include <ImageLoader.h>
#include <memory>

// File: shadow_lighting.h
// @Author Jeroen Huisen
// @Author Lars Veenendaal 1633223
// 
// 0.2 - Implementation to controller.
// 0.1 - original setup.

/*
Still holds nothing.
*/

using namespace std;
using namespace ImageLib;

class Filter{
protected:
	std::shared_ptr<ImageRGB> editedImage;
	std::shared_ptr<ImageRGB> image;
public:
	//Constructor
	Filter(ImageRGB rgb_img);
	//Return image
	std::shared_ptr<ImageRGB> getImage();
	//Return editedImage
	std::shared_ptr<ImageRGB> getEditedImage();
	//Copy data from image to editedImage
	void Copy();
};
#endif