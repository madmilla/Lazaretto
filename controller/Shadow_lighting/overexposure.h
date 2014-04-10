/*
Lars Veenendaal 
Version: 0.2	8-4-2014
Conversion for the controller and slight modifications.

Jeroen Huisen - Schaduw & Belichting
Version: 0.1	7-4-2014
Summary:		This class will remove overexposure
Description:	This class will detect overexposure and will remove the overexposure on this image.
How this works is simple, the constructor should be called and image should be in LAB colorspace.
L channel from 0 to 100, other channels does not matter.
The function thresholdrepair should be called after the class is created.
When this function is called the Lightness channel will be scanned for a to high lightness value.
After a to high value is found, this will be replaced by a lower value.
A to high value is the value which is given as param to the function thresholdrepair.
*/

#ifndef OVEREXPOSURE_H
#define OVEREXPOSURE_H
#include "Filter.h"		//Filter class is used for having 2 images 1 as input (image) and 1 as output(editedImage)
#include <math.h>		//Used for the pow function

class OverExposure : public Filter{
private:
public:
	//Constructor OverExposure
	//
	//Img is the input image, on this image the overexposure will be "removed".
	//Img should have the first channel (0) as L range from 0 till 100
	OverExposure(ImageRGB img) :Filter(img){}

	//Repair image overexposure
	//
	//This is an alternative way to adjust lightness this doesnt work yet as it should.
	void M();

	//Threshold image
	//
	//This function will threshold the image and not repair it. 
	//The image will be thresholded with the threshold param.
	//This function will only be used for testing purposes
	void ThresholdFunction(int threshold);

	//Repair using threshold
	//
	//This function will detect if a value is higher than the threshold.
	//When a value is higher this will be repaired. 
	//This makes sure the lightness will get lower, a high lightness will mean it is overexposed.
	void ThresholdRepair(int threshold, int power);
	void ThresholdRepair(int threshold, int power, int xmin, int ymin, int xmax, int ymax);


	void ThresholdRepairOpposite(int threshold);
};
#endif