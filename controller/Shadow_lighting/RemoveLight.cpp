#include "RemoveLight.h"

RemoveLight::RemoveLight(){

}

void RemoveLight::ApplyLightingFiltering(shared_ptr<ImageRGB> image, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY){
	/*int meanRTopL = 0;
	int meanGTopL = 0;
	int meanBTopL = 0;


	for (int y = TopLeftY; y < TopLeftY + 3; y++){
	auto samples = image->data(TopLeftX, y);
	for (int x = TopLeftX; x < TopLeftX + 3; x++){
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

	int meanRTopR = 0;
	int meanGTopR = 0;
	int meanBTopR = 0;


	for (int y = TopRightY; y < TopLeftY + 3; y++){
	auto samples = image->data(TopRightX, y);
	for (int x = TopRightX; x < TopLeftX + 3; x++){
	meanRTopL += *samples.red;
	meanGTopL += *samples.green;
	meanBTopL += *samples.blue;
	samples.red--;
	samples.green--;
	samples.blue--;
	}
	}
	meanRTopR /= 9;
	meanGTopR /= 9;
	meanBTopR /= 9;

	int meanRBottomL = 0;
	int meanGBottomL = 0;
	int meanBBottomL = 0;

	for (int y = BottomLeftY; y > BottomLeftY - 3; y--){
	auto samples = image->data(BottomLeftX,y);
	for (int x = BottomLeftX; x < BottomLeftX + 3; x++){
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

	int meanRBottomR = 0;
	int meanGBottomR = 0;
	int meanBBottomR = 0;

	for (int y = BottomRightY; y > BottomRightY - 3; y--){
	auto samples = image->data(BottomRightX, y);
	for (int x = BottomRightX; x < BottomRightX + 3; x++){
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
	*/

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
			/*if (Y < 0.5){
			Y = 1;
			}*/
			/*if (Y > 0.5 && K < 0.5){
			Y = 1;
			K = 0;
			*/
			if (Y  < blackLastYValue + 0.1 && K > 0.3){
				blackLastYValue = Y;
				blackLastKValue = K;
				C = 0;
				M = 0;
				Y = 0;
				K = 1;
			}
			/*else if (K < yellowLastKValue + 0.3 && Y > yellowLastYValue - 0.1){
				yellowLastYValue = Y;
				yellowLastKValue = K;
				C = 0;
				M = 0;
				Y = 0;
				K = 0;
			}*/
			else if (K < 0.1 && Y > 0.1){ //geel
				yellowLastYValue = Y;
				yellowLastKValue = K;
				C = 0;
				M = 0;
				Y = 1;
				K = 0;
			}
			else if (K < 0.05 && Y < 0.1 && C < 0.1 && M < 0.1){ //wit
				C = 0;
				M = 0;
				Y = 1;
				K = 0;
			}
			else if (Y < 0.2){ //zwart
				blackLastKValue = K;
				blackLastYValue = Y;
				C = 0;
				M = 0;
				Y = 0;
				K = 1;
			}

			*rgb_ptrs.red = 255 * (1 - C) * (1 - K);
			*rgb_ptrs.green = 255 * (1 - M) * (1 - K);
			*rgb_ptrs.blue = 255 * (1 - Y) * (1 - K);
		}
	}
}