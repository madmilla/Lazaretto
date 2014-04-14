#include "RemoveLight.h"

RemoveLight::RemoveLight(){

}

void RemoveLight::CornerPointsValues(shared_ptr<ImageRGB> image, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY){
	int meanRTopL = 0;
	int meanGTopL = 0;
	int meanBTopL = 0;

	int offset = (BottomLeftY - TopLeftY) / 10;
	for (int y = TopLeftY + offset; y < TopLeftY + offset + 3; y++){
		auto samples = image->data(TopLeftX + offset, y);
		for (int x = TopLeftX + offset; x < TopLeftX + offset + 3; x++){
			meanRTopL += *samples.red;
			meanGTopL += *samples.green;
			meanBTopL += *samples.blue;
			samples.red++;
			samples.green++;
			samples.blue++;
		}
	}
	meanRTopL /= 9;
	meanGTopL /= 9;
	meanBTopL /= 9;

	int meanRBottomL = 0;
	int meanGBottomL = 0;
	int meanBBottomL = 0;

	for (int y = BottomLeftY - offset; y > BottomLeftY - offset - 3; y--){
		auto samples = image->data(BottomLeftX + offset, y);
		for (int x = BottomLeftX + offset; x < BottomLeftX + offset + 3; x++){
			meanRBottomL += *samples.red;
			meanGBottomL += *samples.green;
			meanBBottomL += *samples.blue;
			samples.red++;
			samples.green++;
			samples.blue++;
		}
	}
	meanRBottomL /= 9;
	meanGBottomL /= 9;
	meanBBottomL /= 9;



	int meanRTopR = 0;
	int meanGTopR = 0;
	int meanBTopR = 0;

	offset = (BottomRightY - TopRightY) / 10;

	for (int y = TopRightY + offset; y < TopRightY+ offset + 3; y++){
		auto samples = image->data(TopRightX - offset, y);
		for (int x = TopRightX - offset; x > TopRightX - offset - 3; x--){
			meanRTopR += *samples.red;
			meanGTopR += *samples.green;
			meanBTopR += *samples.blue;
			samples.red--;
			samples.green--;
			samples.blue--;
		}
	}
	meanRTopR /= 9;
	meanGTopR /= 9;
	meanBTopR /= 9;


	int meanRBottomR = 0;
	int meanGBottomR = 0;
	int meanBBottomR = 0;

	for (int y = BottomRightY - offset; y > BottomRightY - offset - 3; y--){
		auto samples = image->data(BottomRightX - offset, y);
		for (int x = BottomRightX - offset; x > BottomRightX - offset - 3; x--){
			meanRBottomR += *samples.red;
			meanGBottomR += *samples.green;
			meanBBottomR += *samples.blue;
			samples.red--;
			samples.green--;
			samples.blue--;
		}
	}
	meanRBottomR /= 9;
	meanGBottomR /= 9;
	meanBBottomR /= 9;


	//float Rx = (float)*rgb_ptrs.red / 255;
	//float Gx = (float)*rgb_ptrs.green / 255;
	//float Bx = (float)*rgb_ptrs.blue / 255;
	//float test = max(Rx, Gx);
	//float K = 1 - max(test, Bx);
	//float Y = (1 - Bx - K) / (1 - K);

	int meanR = (meanRBottomL + meanRBottomR + meanRTopL + meanRTopR) / 4;
	int meanG = (meanGBottomL + meanGBottomR + meanGTopL + meanGTopR) / 4;
	int meanB = (meanBBottomL + meanBBottomR + meanBTopL + meanBTopR) / 4;

	float meanRx = (float)meanR / 255;
	float meanGx = (float)meanG / 255;
	float meanBx = (float)meanB / 255;

	cout << "meanR: " << meanR << "\n";
	cout << "meanG: " << meanG << "\n";
	cout << "meanB: " << meanB << "\n";


	float test = max(meanRx, meanGx);
	meanK = 1 - max(test, meanBx);
	meanC = (1 - meanRx - meanK) / (1 - meanK);
	meanM = (1 - meanGx - meanK) / (1 - meanK);
	meanY = (1 - meanBx - meanK) / (1 - meanK);
	cout << "meanY :" << meanY << "\n";
	cout << "meanK :" << meanK << "\n";
	if (meanK < 0.1){
		meanK = 0.1;
	}
}

void RemoveLight::ApplyShadowFiltering(shared_ptr<ImageRGB> image, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY){
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

			float Rx = (float)*rgb_ptrs.red / 255;
			float Gx = (float)*rgb_ptrs.green / 255;
			float Bx = (float)*rgb_ptrs.blue / 255;

			float test = max(Rx, Gx);
			float K = 1 - max(test, Bx);
			float C = (1 - Rx - K) / (1 - K);
			float M = (1 - Gx - K) / (1 - K);
			float Y = (1 - Bx - K) / (1 - K);

			// if (K > meanK + meanK/10 && K < meanK + meanK/4*3 && Y > meanY - meanY / 10){//works decent but should be tweaked a little
			if (K > meanK + meanK / 10 && K < meanK + 0.3 - meanK / 3 && Y > meanY - 0.1){
				C = 1; 
				M = 0;
				Y = 0;	 
				K = 0;
			}

			else if (Y < 0.1 && K > 0.05 && K < meanK && M < 0.1 && C < 0.1){ //overexposure gray letter 
				C = 0;
				M = 0;
				Y = 0;
				K = 1;
			}

			//these if statements below will almost scale all pixels black or yellow works pretty well
			else if (K > meanK + meanK / 4){ //make black -> was black
				C = 0;
				M = 0;
				Y = 0;
				K = 1;
			}
			else if (Y > meanY - meanY / 2){ //make white -> was yellow
				C = 0;
				M = 0;
				Y = 0;
				K = 0;
			}
			 
			*rgb_ptrs.red = 255 * (1 - C) * (1 - K);
			*rgb_ptrs.green = 255 * (1 - M) * (1 - K);
			*rgb_ptrs.blue = 255 * (1 - Y) * (1 - K);
		}
	}
}