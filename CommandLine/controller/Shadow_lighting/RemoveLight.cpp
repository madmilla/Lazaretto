#include "RemoveLight.h"

RemoveLight::RemoveLight(){
	//default init values
	float meanRx = 0;
	float meanGx = 0;
	float meanBx = 0;

	float meanC = 0; 
	float meanM = 0;
	float meanY = 0;
	float meanK = 0;
}

void RemoveLight::CornerPointsValues(shared_ptr<ImageRGB> image, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY){
	

	//Default init, mean red, green and blue will be saved in these varibles
	int meanRTopL = 0; 
	int meanGTopL = 0;
	int meanBTopL = 0;

	int offset = (BottomLeftY - TopLeftY) / 10; //10% distance from sides
	for (int y = TopLeftY + offset; y < TopLeftY + offset + 3; y++){
		for (int x = TopLeftX + offset; x < TopLeftX + offset + 3; x++){
			auto samples = image->data(x, y); //get pointer to pixel
			//prevent possible bugs with pointers
			int samplesRed = *samples.red;
			int samplesGreen = *samples.green;
			int samplesBlue = *samples.blue;
			meanRTopL += samplesRed; //get red value and add all values
			meanGTopL += samplesGreen;//get green value and add all values
			meanBTopL += samplesBlue;//get blue value and add all values
		}
	}
	meanRTopL /= 9; //9 samples are taken from the left top corner now the values should be divided by 9 so we get the mean value
	meanGTopL /= 9;
	meanBTopL /= 9;

	int meanRBottomL = 0;
	int meanGBottomL = 0;
	int meanBBottomL = 0;

	for (int y = BottomLeftY - offset; y > BottomLeftY - offset - 3; y--){
		for (int x = BottomLeftX + offset; x < BottomLeftX + offset + 3; x++){
			auto samples = image->data(x, y); //get pointer to pixel
			//prevent possible bugs with pointers
			int samplesRed = *samples.red;
			int samplesGreen = *samples.green;
			int samplesBlue = *samples.blue;
			meanRTopL += samplesRed; //get red value and add all values
			meanGTopL += samplesGreen;//get green value and add all values
			meanBTopL += samplesBlue;//get blue value and add all values
		}
	}
	meanRBottomL /= 9; //9 samples are taken from the left bottom corner now the values should be divided by 9 so we get the mean value
	meanGBottomL /= 9;
	meanBBottomL /= 9;



	int meanRTopR = 0;
	int meanGTopR = 0;
	int meanBTopR = 0;

	offset = (BottomRightY - TopRightY) / 10;

	for (int y = TopRightY + offset; y < TopRightY+ offset + 3; y++){
		for (int x = TopRightX - offset; x > TopRightX - offset - 3; x--){
			auto samples = image->data(x, y); //get pointer to pixel
			//prevent possible bugs with pointers
			int samplesRed = *samples.red;
			int samplesGreen = *samples.green;
			int samplesBlue = *samples.blue;
			meanRTopL += samplesRed; //get red value and add all values
			meanGTopL += samplesGreen;//get green value and add all values
			meanBTopL += samplesBlue;//get blue value and add all values
		}
	}
	meanRTopR /= 9; // 9 samples are taken from the right top corner now the values should be divided by 9 so we get the mean value
	meanGTopR /= 9;
	meanBTopR /= 9;


	int meanRBottomR = 0;
	int meanGBottomR = 0;
	int meanBBottomR = 0;

	for (int y = BottomRightY - offset; y > BottomRightY - offset - 3; y--){
		auto samples = image->data(BottomRightX - offset, y);
		for (int x = BottomRightX - offset; x > BottomRightX - offset - 3; x--){
			auto samples = image->data(x, y); //get pointer to pixel
			//prevent possible bugs with pointers
			int samplesRed = *samples.red;
			int samplesGreen = *samples.green;
			int samplesBlue = *samples.blue;
			meanRTopL += samplesRed; //get red value and add all values
			meanGTopL += samplesGreen;//get green value and add all values
			meanBTopL += samplesBlue;//get blue value and add all values
		}
	}
	meanRBottomR /= 9; // 9 samples are taken from the right bottom corner now the values should be divided by 9 so we get the mean value
	meanGBottomR /= 9;
	meanBBottomR /= 9;

	int meanR = (meanRBottomL + meanRBottomR + meanRTopL + meanRTopR) / 4; //of every corner the mean is taken and divide by 4 so 1 mean value stays pro channel
	int meanG = (meanGBottomL + meanGBottomR + meanGTopL + meanGTopR) / 4;
	int meanB = (meanBBottomL + meanBBottomR + meanBTopL + meanBTopR) / 4;

	//Calc rgb to cmyk
	//http://www.rapidtables.com/convert/color/rgb-to-cmyk.htm
	meanRx = (float)meanR / 255;
	meanGx = (float)meanG / 255;
	meanBx = (float)meanB / 255;

	float test = max(meanRx, meanGx);
	meanK = 1 - max(test, meanBx);
	meanC = (1 - meanRx - meanK) / (1 - meanK);
	meanM = (1 - meanGx - meanK) / (1 - meanK);
	meanY = (1 - meanBx - meanK) / (1 - meanK);

	//low K value will be highered for following calculations
	if (meanK < 0.1){
		meanK = 0.1;
	}
}

void RemoveLight::ApplyShadowFiltering(shared_ptr<ImageRGB> image, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY, int darkestPixelR, int darkestPixelG, int darkestPixelB){
	CornerPointsValues(image, TopLeftX, TopLeftY, TopRightX, TopRightY, BottomLeftX, BottomLeftY, BottomRightX, BottomRightY); //make samples
	
	//some easy (and a bit ugly) max and min to make a bounding box
	int tempA = max(TopLeftX, TopRightX);
	int tempB = max(BottomLeftX, BottomRightX);
	int xmax = max(tempA, tempB);
	tempA = min(TopLeftX, TopRightX);
	tempB = min(BottomLeftX, BottomRightX);
	int xmin = min(tempA, tempB);

	tempA = max(TopLeftY, TopRightY);
	tempB = max(BottomLeftY, BottomRightY);
	int ymax = max(tempA, tempB);
	tempA = min(TopLeftY, TopRightY);
	tempB = min(BottomLeftY, BottomRightY);
	int ymin = min(tempA, tempB);


	for (int y = ymin; y < ymax; y++){
		int yellowLastYValue = 0;
		int yellowLastKValue = 0;
		int blackLastYValue = 0;
		int blackLastKValue = 0;
		for (int x = xmin; x < xmax; x++){
			auto rgb_ptrs = image->data(x, y); //get pointer to pixel
			if (x == -1 || y == -1){
				continue;
			}
			float rgb_ptrs_red = *rgb_ptrs.red;
			float rgb_ptrs_green = *rgb_ptrs.green;
			float rgb_ptrs_blue = *rgb_ptrs.blue;
			
			//calc rgb to cmyk 
			//http://www.rapidtables.com/convert/color/rgb-to-cmyk.htm
			float Rx = rgb_ptrs_red / 255;
			float Gx = rgb_ptrs_green / 255;
			float Bx = rgb_ptrs_blue / 255;

			float test = max(Rx, Gx);
			float K = 1 - max(test, Bx);
			float C = (1 - Rx - K) / (1 - K);
			float M = (1 - Gx - K) / (1 - K);
			float Y = (1 - Bx - K) / (1 - K);

			//If (else) statements which determinates if something should be yellow or black
			if (K > meanK + meanK / 10 && K < meanK + 0.3 - meanK / 3 && Y > meanY - 0.1){ //shadow detection
				//yellow
				C = 0;
				M = 0;
				Y = 1;
				K = 0;
			}

			else if (Y < 0.1 && K > 0.05 && M < 0.2 && C < 0.2){ //overexposure gray letter to black letter
				//black
				C = 0;
				M = 0;
				Y = 0;
				K = 1;
			}
			else if (K < 0.2 && M < 0.2 && C < 0.2){// white, overexposure to yellow
				//yellow
				C = 0;
				M = 0;
				Y = 1;
				K = 0;
			}

			//these if statements below will almost scale all pixels black or yellow
			else if (K > meanK + 0.2 - meanK / 5){ //make black used to be black
				//black
				C = 0;
				M = 0;
				Y = 0;
				K = 1;
			}
			else if (Y > meanY - meanY / 2){ //make yellow used to be yellow
				//yellow
				C = 0;
				M = 0;
				Y = 1;
				K = 0;
			}
			 
			//cmyk to rgb
			//http://www.rapidtables.com/convert/color/cmyk-to-rgb.htm
			*rgb_ptrs.red = 255 * (1 - C) * (1 - K);
			*rgb_ptrs.green = 255 * (1 - M) * (1 - K);
			*rgb_ptrs.blue = 255 * (1 - Y) * (1 - K);
		}
	}
}

void RemoveLight::ApplyLightingFiltering(shared_ptr<ImageRGB> image, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY){
	CornerPointsValues(image, TopLeftX, TopLeftY, TopRightX, TopRightY, BottomLeftX, BottomLeftY, BottomRightX, BottomRightY);
	//some easy and ugly max and min

	int tempA = max(TopLeftX, TopRightX);
	int tempB = max(BottomLeftX, BottomRightX);
	int xmax = max(tempA, tempB);
	tempA = min(TopLeftX, TopRightX);
	tempB = min(BottomLeftX, BottomRightX);
	int xmin = min(tempA, tempB);

	tempA = max(TopLeftY, TopRightY);
	tempB = max(BottomLeftY, BottomRightY);
	int ymax = max(tempA, tempB);
	tempA = min(TopLeftY, TopRightY);
	tempB = min(BottomLeftY, BottomRightY);
	int ymin = min(tempA, tempB);


	for (int y = ymin; y < ymax; y++){
		int yellowLastYValue = 0;
		int yellowLastKValue = 0;
		int blackLastYValue = 0;
		int blackLastKValue = 0;
		for (int x = xmin; x < xmax; x++){
			auto rgb_ptrs = image->data(x, y);
			if (x == -1 || y == -1){
				continue; // Skip als hij -1 is !!! - Lars misschien handig om hier op te checken?
			}
			float rgb_ptrs_red = *rgb_ptrs.red; 
			float rgb_ptrs_green = *rgb_ptrs.green;
			float rgb_ptrs_blue = *rgb_ptrs.blue;

			float Rx = rgb_ptrs_red / 255;
			float Gx = rgb_ptrs_green / 255;
			float Bx = rgb_ptrs_blue / 255;

			float test = max(Rx, Gx);
			float K = 1 - max(test, Bx);
			float C = (1 - Rx - K) / (1 - K);
			float M = (1 - Gx - K) / (1 - K);
			float Y = (1 - Bx - K) / (1 - K);

			// if (K > meanK + meanK/10 && K < meanK + meanK/4*3 && Y > meanY - meanY / 10){//works decent but should be tweaked a little
			if (K > meanK + meanK / 10 && K < meanK + 0.3 - meanK / 3 && Y > meanY - 0.1){
				C = 0;
				M = 0;
				Y = 1;
				K = 0;
			}

			/*else if (K > meanK  && K < Y && Y > meanY + 0.2 - meanY / 5 && M < Y &&  C < Y){
			C = 0;
			M = 1;
			Y = 0;
			K = 0;
			}*/
			else if (Y < 0.1 && K > 0.05 && M < 0.2 && C < 0.2){ //overexposure gray letter 
				C = 0;
				M = 0;
				Y = 0;
				K = 1;
			}
			else if (K < 0.2 && M < 0.2 && C < 0.2){// white?
				C = 0;
				M = 0;
				Y = 1;
				K = 0;
			}
			/*else if (Rx < meanRx && Gx < meanGx && Rx > darkestPixelR / 255 + 0.2 - darkestPixelR / 5 && Gx > darkestPixelG / 255 + 0.2 - darkestPixelG / 5){
			C = 0;
			M = 1;
			Y = 0;
			K = 0;
			}*/

			//these if statements below will almost scale all pixels black or yellow works pretty well
			else if (K > meanK + 0.2 - meanK / 5){ //make black -> was black
				C = 0;
				M = 0;
				Y = 0;
				K = 1;
			}
			else if (Y > meanY - meanY / 2){ //make white -> was yellow
				C = 0;
				M = 0;
				Y = 1;
				K = 0;
			}

			*rgb_ptrs.red = 255 * (1 - C) * (1 - K);
			*rgb_ptrs.green = 255 * (1 - M) * (1 - K);
			*rgb_ptrs.blue = 255 * (1 - Y) * (1 - K);
		}
	}
}