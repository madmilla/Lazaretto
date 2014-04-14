// Arthur van der Weiden

#include "ShadowTest.h"

bool ShadowTest::Shadow_Detection(std::shared_ptr<ImageRGB> img, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY,
								int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY){


	//! Bounding Box
	//! 
	//! These if statements calculates the bounding box of the license plate.
	//! The shadow check will be in the bounding box.
	if (TopLeftY < TopRightY){
		TopBigY = TopRightY;
		TopSmallY = TopLeftY;
	}else {
		TopBigY = TopLeftY;
		TopSmallY = TopRightY;
	}
	if (BottomLeftY < BottomRightY){
		BottomBigY = BottomRightY;
		BottomSmallY = BottomLeftY;
	}else {
		BottomBigY = BottomLeftY;
		BottomSmallY = BottomRightY;
	}

	//! Some needed variables
	//!
	//! Set the needed variables to the right values.
	LicensePlateWidth = BottomRightX;
	LicensePlateHeight = BottomBigY - TopSmallY;

	TotalPixels = LicensePlateHeight * LicensePlateWidth;
	ShadowPixels = 0;
	auto rgb_ptrs = img->data(TopLeftX + 1, TopLeftY + 1);

	int rgb_ptr_red = *rgb_ptrs.red;
	int rgb_ptr_green = *rgb_ptrs.green;
	int rgb_ptr_blue = *rgb_ptrs.blue;

	double Grayval = (rgb_ptr_red * 0.21) + (rgb_ptr_blue * 0.71) + (rgb_ptr_green * 0.07);
	auto Darkest = Grayval;
	setDarkestFoundPixel(Darkest);
	
	//! Darkest pixel
	//!
	//! To find the bottom threshold for the shadow detection,
	//! the algorithm loops through the picture in search of the darkest pixel.
	for (int x = TopLeftX + 1; x <= LicensePlateWidth; x++){
		for (int y = TopSmallY + 1; y <= BottomBigY; y++){
			Grayval = (rgb_ptr_red * 0.21) + (rgb_ptr_blue * 0.71) + (rgb_ptr_green * 0.07);

			if ((int)Grayval < (int)Darkest){
				Darkest = Grayval;
				setDarkestFoundPixel(Darkest);
				darkestFoundPixelR = *rgb_ptrs.red;
				darkestFoundPixelG = *rgb_ptrs.green;
				darkestFoundPixelB = *rgb_ptrs.blue;
			}
		}
	}
	//! Shadow search
	//! 
	//! When a pixel is considered as a shadowpixel, a counter will be added.
	//! When a percentage of 2% shadow pixels is reached the function will return true, else it will return false.
	for (int x = TopLeftX + 1; x <= LicensePlateWidth; x++){
		for (int y = TopSmallY + 1; y <= BottomBigY; y++){
			Grayval = (rgb_ptr_red * 0.21) + (rgb_ptr_blue * 0.71) + (rgb_ptr_green * 0.07);

			rgb_ptr_red++;
			rgb_ptr_blue++;
			rgb_ptr_green++;
			
			if (((rgb_ptr_blue > rgb_ptr_green) && (rgb_ptr_blue > rgb_ptr_red)) && (Grayval >= Darkest && Grayval <= YELLOWGRAY)){
				ShadowPixels++;
			}
			Percentage = ((float)ShadowPixels / (float)TotalPixels) * 100;
			if (Percentage > 2.0f){	
				return true;
			}
		}
	}
	return false;
	
}
void ShadowTest::setDarkestFoundPixel(int value){
	DarkestFoundPixel = value;
}