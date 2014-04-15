/*!
*	@author		Jeroen Huisen
*	@version	0.9 14-4-2014
*	@project	Themaopdracht 7, license plate recognition
*	@brief		This class will remove overexposure and shadows from an image.
*
*				To do this there should be taken samples, this is done in CornerPointsValues
*				When these samples are taken, they will be used to determinate if something is overexposed or a shadow or just normal light
*				If overexposure is found it will be repaired automaticly, the same goes for shadows.
*/

#include <imageloader.h> //Image library
#include <iostream> //debugging

using namespace ImageLib;
using namespace std;

class RemoveLight{
private:
	float meanRx; //mean red value of the samples / 255
	float meanGx; //mean green value of the samples / 255
	float meanBx; //mean blue value of the samples / 255

	float meanC; //mean cyan value of the samples
	float meanM; //mean magenta value of the samples
	float meanY; //mean yellow value of the samples
	float meanK; //mean key value of the samples
public:
	//!Constructor
	//!
	RemoveLight();

	//!Take samples from the licenseplate
	//!
	//!This function will take sample values in each corner of the licenseplate. 
	//!The samples aren't taken from the corners directly but from height, 10% more in the image.
	//!The samples are 9 pro corner.
	//!These samples are saved in meanRx, meanGx, meanBx and also in meanC, meanM, meanY and meanK.
	//!These samples are taken from @param image, which is a shared_ptr to the input image.
	//!The coordinates of the licenseplate are used as input using the @params, TopLeftX, TopLeftY, TopRightX, TopRightY, BottomLeftX, BottomLeftY, BottomRightX and BottomRightY.
	void CornerPointsValues(shared_ptr<ImageRGB> image, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY);
	
	//!Remove overexposure (and shadows)
	//!
	//!This function will remove as much overexposure as possible.
	//!To do this there should be first taken sample values which is done in the function CornerPointsValues.
	//!These samples are used to determinate if something is yellow, the license plate or something is black, the letters on the license plate.
	//!These samples are also used to determinate if something is overexposed, than this will be repaired if possible.
	//!The input images is @param image, which is a shared_ptr to the input image.
	//!The coordinates of the licenseplate are used as input using the @params, TopLeftX, TopLeftY, TopRightX, TopRightY, BottomLeftX, BottomLeftY, BottomRightX and BottomRightY.
	void ApplyLightingFiltering(shared_ptr<ImageRGB> image, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY);

	//!Remove shadows (and overexposure)
	//!
	//!This function will remove as much shadows as possible.
	//!To do this there should be first taken sample values which is done in the function CornerPointsValues.
	//!These samples are used to determinate if something is yellow, the license plate or something is black, the letters on the license plate.
	//!These samples are also used to determinate if something is a shadow, than this will be repaired if possible.
	//!The input images is @param image, which is a shared_ptr to the input image.
	//!The coordinates of the licenseplate are used as input using the @params, TopLeftX, TopLeftY, TopRightX, TopRightY, BottomLeftX, BottomLeftY, BottomRightX and BottomRightY.
	void ApplyShadowFiltering(shared_ptr<ImageRGB> image, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY, int darkestPixelR, int darkestPixelG, int darkestPixelB);
};