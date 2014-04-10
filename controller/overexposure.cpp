#include "OverExposure.h"
#include <iostream>

// @Author Jeroen Huisen


void OverExposure::M(){
	//based on http://www->comp->nus->edu->sg/~tsim/documents/cvpr2010-final-reduced->pdf
	//The implementation isn't done so it will not produce usefull results->
	for (int y = 0; y < image->height(); y++){
		for (int x = 0; x < image->width(); x++){
			int Li = *image->data(x, y, Channel::Red);//Lightness of the pixel with coordinates x and y
			int Ci = pow((*image->data(x, y, Channel::Green) * *image->data(x, y, Channel::Blue)), 2);
			float m = 0.5*(tanh(1.0 / 60.0*((Li - 80.0) + (40 - Ci))) + 1); //formula, see link 3->1
			*editedImage->data(x, y, Channel::Red) = m * 255;
			*editedImage->data(x, y, Channel::Green) = m * 255;
			*editedImage->data(x, y, Channel::Blue) = m * 255;
		}
	}
}

void OverExposure::ThresholdFunction(int threshold){
	for (int y = 0; y < image->height(); y++){
		for (int x = 0; x < image->width(); x++){
			int Li = *image->data(x, y, Channel::Red);//get the lightness value
			if (Li > threshold){ //checks if higher, when higher pixel becomes white->
				*editedImage->data(x, y, Channel::Red) = 255;
				*editedImage->data(x, y, Channel::Green) = 255;
				*editedImage->data(x, y, Channel::Blue) = 255;
			}
			else{
				//if lower pixel becomes black
				*editedImage->data(x, y, Channel::Red) = 0;
				*editedImage->data(x, y, Channel::Green) = 0;
				*editedImage->data(x, y, Channel::Blue) = 0;
			}
		}
	}

	//editedImage->SaveImage("testOverExposureThreshold->bmp");
}

void OverExposure::ThresholdRepair(int threshold, int power, int xmin, int ymin, int xmax, int ymax){
	for (int y = ymin; y < ymax; y++){
		for (int x = xmin; x < xmax; x++){
			int Li = *image->data(x, y, Channel::Red);
			if (Li > threshold){ //if higher than threshold lower lightness of pixel
				*editedImage->data(x, y, Channel::Red) = Li - power; //Not a complete repair but will lower the lightness
				//*editedImage->Data(x, y, 0) = 0; //this is overexposed show->
				*editedImage->data(x, y, Channel::Green) = *image->data(x, y, Channel::Green);//just copy image channels
				*editedImage->data(x, y, Channel::Blue) = *image->data(x, y, Channel::Blue);
			}
			else if (Li > threshold - power){ //if its lower than threshold but higher than edited ligthness is changed into->
				//This makes sure its not higher than edited lightness value->
				*editedImage->data(x, y, Channel::Red) = Li - (Li - (threshold - power));
				*editedImage->data(x, y, Channel::Green) = *image->data(x, y, Channel::Green);//just copy image channels
				*editedImage->data(x, y, Channel::Blue) = *image->data(x, y, Channel::Blue);
			}
			else{//In anyother case keep the default lightness
				*editedImage->data(x, y, Channel::Red) = Li;
				*editedImage->data(x, y, Channel::Green) = *image->data(x, y, Channel::Green);//just copy image channels
				*editedImage->data(x, y, Channel::Blue) = *image->data(x, y, Channel::Blue);
			}
		}
	}

	//editedImage->SaveImage("testOverExposureThresholdRepair->bmp");
}

void OverExposure::ThresholdRepair(int threshold, int power){
	for (int y = 0; y < image->height(); y++){
		for (int x = 0; x < image->width(); x++){
			int Li = *image->data(x, y, Channel::Red);
			if (Li > threshold){ //if higher than threshold lower lightness of pixel
				*editedImage->data(x, y, Channel::Red) = Li - power; //Not a complete repair but will lower the lightness
				//*editedImage->Data(x, y, 0) = 0; //this is overexposed show->
				*editedImage->data(x, y, Channel::Green) = *image->data(x, y, Channel::Green);//just copy image channels
				*editedImage->data(x, y, Channel::Blue) = *image->data(x, y, Channel::Blue);
			}
			else if (Li > threshold - power){ //if its lower than threshold but higher than edited ligthness is changed into->
				//This makes sure its not higher than edited lightness value->
				*editedImage->data(x, y, Channel::Red) = Li - (Li - (threshold - power));
				*editedImage->data(x, y, Channel::Green) = *image->data(x, y, Channel::Green);//just copy image channels
				*editedImage->data(x, y, Channel::Blue) = *image->data(x, y, Channel::Blue);
			}
			else{//In anyother case keep the default lightness
				*editedImage->data(x, y, Channel::Red) = Li;
				*editedImage->data(x, y, Channel::Green) = *image->data(x, y, Channel::Green);//just copy image channels
				*editedImage->data(x, y, Channel::Blue) = *image->data(x, y, Channel::Blue);
			}
		}
	}

	//editedImage->SaveImage("testOverExposureThresholdRepair->bmp");
}

