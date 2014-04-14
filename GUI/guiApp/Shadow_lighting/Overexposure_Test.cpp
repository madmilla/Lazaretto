// Hendrik Cornelisse

#include "Overexposure_Test.h"

#include <iostream>

using namespace ImageLib;
using namespace std;

int TotalPixels = 0;
int Overexposed_pixels = 0;
int BigY, SmallY;
int sum = 0;
int tempRed = 0;
int tempGreen = 0;
int tempBlue = 0;
int count_Pixels = 0;
int average_Red, average_Green, average_Blue;
int temp_Red_Black, temp_Blue_Black;
float percentage = 0;
bool count_Pix = false;

Overexposure_Test::Overexposure_Test(){
	
}

bool Overexposure_Test::Overexposure_Detection(shared_ptr<ImageRGB> img, int Top_Left_X, int Top_Left_Y, int Top_Right_X, int Top_Right_Y, int Bottom_Left_X, int Bottom_Left_Y, int Bottom_Right_X, int Bottom_Right_Y){

	//! Making a bounding box with the coordinates of the license plate.
	//! check what the smalles top corner is.
	if (Top_Left_Y < Top_Right_Y){
		SmallY = Top_Left_Y;
	}
	else{
		SmallY = Top_Right_Y;
	}
	
	//! Check what the biggest bottom cornet is. 
	if (Bottom_Left_Y > Bottom_Right_Y){
		BigY = Bottom_Left_Y;
	}
	else{
		BigY = Bottom_Right_Y;
	}

	TotalPixels = (Bottom_Right_X - Top_Left_X) * (BigY - SmallY);

	//!1 for loop is for the height of the license plate and the other is for the width of the license plate

	for (int y = SmallY + 5; y < BigY - 5; y++){
		for (int x = Top_Left_X + 5; x < Bottom_Right_X - 5; x++){
			int xGradient = *img->data(x - 1, y + 1).blue + *img->data(x - 1, y).blue * 2 + *img->data(x - 1, y - 1).blue - *img->data(x + 1, y + 1).blue - *img->data(x + 1, y).blue * 2 - *img->data(x + 1, y - 1).blue;
			int yGradient = *img->data(x - 1, y - 1).blue + *img->data(x, y - 1).blue * 2 + *img->data(x + 1, y - 1).blue - *img->data(x + 1, y + 1).blue - *img->data(x, y + 1).blue * 2 - *img->data(x - 1, y + 1).blue;

			sum = abs(xGradient) + abs(yGradient);
			
			if (sum >= 255){
				percentage = ((float)Overexposed_pixels / (float)TotalPixels) * 100;

				if (percentage >= 1){
					return true;
				}
				
				for (int h = y - 5; h < y + 5; h++){
					for (int w = x - 5; w < x + 5; w++){
						if ((*img->data(w, h).red > 210) && (*img->data(w, h).green > 210) && (*img->data(w, h).blue > 210)){
							if (count_Pix == false){
								Overexposed_pixels++;
								count_Pix = true;
							}	
						}
					}
				}
			}
			count_Pix = false;
		}
	}
	return false;
}

void Overexposure_Test::Overexposure_Removal(shared_ptr<ImageRGB> img, int Top_Left_X, int Top_Left_Y, int Top_Right_X, int Top_Right_Y, int Bottom_Left_X, int Bottom_Left_Y, int Bottom_Right_X, int Bottom_Right_Y){
	
	//! Making a bounding box with the coordinates of the license plate.
	//! check what the smalles top corner is.
	if (Top_Left_Y < Top_Right_Y){
		SmallY = Top_Left_Y;
	}
	else{
		SmallY = Top_Right_Y;
	}

	//! Check what the biggest bottom cornet is.
	if (Bottom_Left_Y > Bottom_Right_Y){
		BigY = Bottom_Left_Y;
	}
	else{
		BigY = Bottom_Right_Y;
	}

	//!1 for loop is for the height of the license plate and the other is for the width of the license plate
	for (int y = SmallY + 5; y < BigY - 5; y++){
		for (int x = Top_Left_X + 5; x < Bottom_Right_X - 5; x++){
			int xGradient = *img->data(x - 1, y + 1).blue + *img->data(x - 1, y).blue * 2 + *img->data(x - 1, y - 1).blue - *img->data(x + 1, y + 1).blue - *img->data(x + 1, y).blue * 2 - *img->data(x + 1, y - 1).blue;
			int yGradient = *img->data(x - 1, y - 1).blue + *img->data(x, y - 1).blue * 2 + *img->data(x + 1, y - 1).blue - *img->data(x + 1, y + 1).blue - *img->data(x, y + 1).blue * 2 - *img->data(x - 1, y + 1).blue;

			sum = abs(xGradient) + abs(yGradient);

			if (sum >= 255){
				for (int h = y - 5; h < y + 5; h++){
					for (int w = x - 5; w < x + 5; w++){
							if (*img->data(w, h).green < *img->data(w, h).red){
								temp_Red_Black = *img->data(w, h).red - *img->data(w, h).green;
							}
							else{
								temp_Red_Black = *img->data(w, h).green - *img->data(w, h).red;
							}

							if (*img->data(w, h).blue < *img->data(w, h).green){
								temp_Blue_Black = *img->data(w, h).green - *img->data(w, h).blue;
							}
							else{
								temp_Blue_Black = *img->data(w, h).blue - *img->data(w, h).green;
							}

							if ((temp_Red_Black < 30) && (temp_Blue_Black < 30) && (*img->data(w, h).red <= 244)){
								img->at(w, h).red = 0;
								img->at(w, h).green = 0;
								img->at(w, h).blue = 0;
							}
			
							if ((*img->data(w, h).red >= 185) && (*img->data(w, h).green >= 185) && (*img->data(w, h).blue <= 50)){
								tempRed	+= *img->data(w, h).red;
								tempGreen += *img->data(w, h).green;
								tempBlue += *img->data(w, h).blue;
								count_Pixels++;
						}
					}
				}

				if (count_Pixels != 0){
					average_Red = tempRed / count_Pixels;
					average_Green = tempGreen / count_Pixels;
					average_Blue = tempBlue / count_Pixels;

					for (int h = y - 5; h < y + 5; h++){
						for (int w = x - 5; w < x + 5; w++){
							if ((*img->data(x, y).red > 210) && (*img->data(w, h).green > 210) && (*img->data(w, h).blue > 210)){
								img->at(w, h).red = average_Red;
								img->at(w, h).green = average_Green;
								img->at(w, h).blue = average_Blue;
							}
						}
					}
					average_Red = 0;
					average_Green = 0;
					average_Blue = 0;
					tempRed = 0;
					tempGreen = 0;
					tempBlue = 0;
					count_Pixels = 0;
				}
			}
		}
	}
	saveImg(*img, "test.jpg");
}
