/*
	Autor: Jeroen Huisen
	Summary:
	Version:


*/


#include <ImageLoader.h>
#include <iostream> //debugging

using namespace ImageLib;
using namespace std;

class RemoveLight{
private:
	float meanRx;
	float meanGx;
	float meanBx;

	float meanC;
	float meanM;
	float meanY;
	float meanK;
public:
	//Constructor
	RemoveLight();

	//!Take samples from the licenseplate
	//!
	//!This function will take sample values in each corner of the licenseplate. 
	//!These samples are saved in meanRx, meanGx, meanBx and also in meanC, meanM, meanY and meanK.
	//!These samples are taken from image, which is a shared_ptr to the input image.
	//!The coordinates of the licenseplate are used as input using the params, TopLeftX, TopLeftY, TopRightX, TopRightY, BottomLeftX, BottomLeftY, BottomRightX and BottomRightY.
	void CornerPointsValues(shared_ptr<ImageRGB> image, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY);

	//!
	void ApplyLightingFiltering(shared_ptr<ImageRGB> image, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY);
	void ApplyShadowFiltering(shared_ptr<ImageRGB> image, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY, int darkestPixelR, int darkestPixelG, int darkestPixelB);
	//	ApplyLightingFiltering(image, TopLeftX, TopLeftY, TopRightX, TopRightY, BottomLeftX, BottomLeftY, BottomRightX, BottomRightY);
	//}
};