// Arthur van der Weiden

#ifndef SHADOW_TEST
#define SHADOW_TEST

#include <ImageLoader.h>
#define YELLOWGRAY 60

using namespace ImageLib;

class ShadowTest{

private:
	int TotalPixels;
	int LicensePlateHeight;
	int LicensePlateWidth;
	int TopBigY, TopSmallY, BottomBigY, BottomSmallY;
	int DarkestFoundPixel = 0;

	int darkestFoundPixelR;
	int darkestFoundPixelG;
	int darkestFoundPixelB;

	float Percentage;
	int ShadowPixels = 0;

public:
	//! Constructor
	//! 
	//! Constructs an object of the ShadowTest type
	ShadowTest(){ darkestFoundPixelR = 0; darkestFoundPixelG = 0; darkestFoundPixelB = 0; }

	//! Shadow_Detection
	//! @param img, TopLeftX, TopLeftY, TopRightX, TopRightY, BottomLeftX, BottomLeftY, BottomRightX, BottomRightY, the image and coordinates within which will be tested
	//!
	//! Detects whether an image has shadow in it.
	//! The image will be tested within the coordinates passed through the parameters.
	bool Shadow_Detection(std::shared_ptr<ImageRGB> img, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY);

	//! getDarkestFoundPixel
	//!
	//! Returns the darkest found pixel
	inline int getDarkestFoundPixel(){
		return DarkestFoundPixel;
	}

	//! getDarkestFoundPixelR
	//!
	//! Returns the darkest found pixel (Red Channel)
	inline int getDarkestFoundPixelR(){
		return darkestFoundPixelR;
	}

	//! getDarkestFoundPixelG
	//!
	//! Returns the darkest found pixel (Green Channel)
	inline int getDarkestFoundPixelG(){
		return darkestFoundPixelG;
	}

	//! getDarkestFoundPixel`B
	//!
	//! Returns the darkest found pixel (Blue Channel)
	inline int getDarkestFoundPixelB(){
		return darkestFoundPixelB;
	}

	//! setDarkestFoundPixel
	//! @param value the new value for the darkest found pixel
	//! 
	//! Sets the darkest found pixel to the value passed through the parameter
	inline void setDarkestFoundPixel(int value);
};
#endif