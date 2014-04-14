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
	float Percentage;
	int ShadowPixels = 0;

public:

	ShadowTest(){}
	bool Shadow_Detection(std::shared_ptr<ImageRGB> img, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY);
	
	inline int getDarkestFoundPixel(){
		return DarkestFoundPixel;
	}

	inline void setDarkestFoundPixel(int value);
};
#endif