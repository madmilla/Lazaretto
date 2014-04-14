#include "Overexposure_Test.h"

#include <iostream>
#include <ImageLoader.h>

using namespace ImageLib;
using namespace std;

int TotalPixels = 0;
int Overexposed_pixels = 0;
float percentage = 0;
int sum = 0;
int tempRed = 0;
int tempGreen = 0;
int tempBlue = 0;
int BigY, SmallY;
int temp_aantal = 0;
int red, green, blue;
int tempRed2, tempBlue2;
bool tel = false;

Overexposure_Test::Overexposure_Test(){
	
}

bool Overexposure_Test::Overexposure_Detection(shared_ptr<ImageRGB> img, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY){
	if (TopLeftY < TopRightY){
		SmallY = TopLeftY;
	}
	else{
		SmallY = TopRightY;
	}
	
	if (BottomLeftY > BottomRightY){
		BigY = BottomLeftY;
	}
	else{
		BigY = BottomRightY;
	}

	TotalPixels = (BottomRightX - TopLeftX) * (BigY - SmallY);
	for (int y = SmallY + 10; y < BigY - 10; y++){
		for (int x = TopLeftX + 10; x < BottomRightX - 10; x++){
			int xGradient = *img->data(x - 1, y + 1).blue + *img->data(x - 1, y).blue * 2 + *img->data(x - 1, y - 1).blue - *img->data(x + 1, y + 1).blue - *img->data(x + 1, y).blue* 2 - *img->data(x + 1, y - 1).blue;
			int yGradient = *img->data(x - 1, y - 1).blue + *img->data(x, y - 1).blue * 2 + *img->data(x + 1, y - 1).blue - *img->data(x + 1, y + 1).blue - *img->data(x, y + 1).blue* 2 - *img->data(x - 1, y + 1).blue;
			
			sum = abs(xGradient) + abs(yGradient);

			/*if (sum > 255){
				sum = 255;
			}
			else if (sum < 0){
				sum = 0;
			}*/

			if (sum >= 255){
				percentage = ((float)Overexposed_pixels / (float)TotalPixels) * 100;
				
				if (percentage >= 1){
					return true;
				}
				for (int h = y - 10; h < y + 10; h++){
					for (int w = x - 10; w < x + 10; w++){
						if ((*img->data(w, h).red > 210) && (*img->data(w, h).green > 210) && (*img->data(w, h).blue > 210)){
							if (tel == false){
								Overexposed_pixels++;
								tel = true;
							}
							
							/*img->at(x, y).red = 255;
							img->at(x, y).green = 0;
							img->at(x, y).blue = 0;*/
						}
					}
				}
				tel = false;
			}	
			/*img->at(x, y).red = 255;
			img->at(x, y).green = 0;
			img->at(x, y).blue = 0;*/
		}
	}
	//saveImg(*img, "test.jpg");
	//cout << TotalPixels << '\n';
	//cout << Overexposed_pixels << '\n';
	//cout << percentage << '\n';
	return false;
}

void Overexposure_Test::Overexposure_Removal(shared_ptr<ImageRGB> img, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY){
	if (TopLeftY < TopRightY){
		SmallY = TopLeftY;
	}
	else{
		SmallY = TopRightY;
	}

	if (BottomLeftY > BottomRightY){
		BigY = BottomLeftY;
	}
	else{
		BigY = BottomRightY;
	}

	for (int y = SmallY + 5; y < BigY - 5; y++){
		for (int x = TopLeftX + 5; x < BottomRightX - 5; x++){
			int xGradient = *img->data(x - 1, y + 1).blue + *img->data(x - 1, y).blue * 2 + *img->data(x - 1, y - 1).blue - *img->data(x + 1, y + 1).blue - *img->data(x + 1, y).blue * 2 - *img->data(x + 1, y - 1).blue;
			int yGradient = *img->data(x - 1, y - 1).blue + *img->data(x, y - 1).blue * 2 + *img->data(x + 1, y - 1).blue - *img->data(x + 1, y + 1).blue - *img->data(x, y + 1).blue * 2 - *img->data(x - 1, y + 1).blue;

			sum = abs(xGradient) + abs(yGradient);

			if (sum > 255){
				sum = 255;
			}
			else if (sum < 0){
				sum = 0;
			}

			if (sum >= 255){
				for (int h = y - 5; h < y + 5; h++){
					for (int w = x - 5; w < x + 5; w++){
							if (*img->data(w, h).green < *img->data(w, h).red){
								tempRed2 = *img->data(w, h).red - *img->data(w, h).green;
							}
							else{
								tempRed2 = *img->data(w, h).green - *img->data(w, h).red;
							}

							if (*img->data(w, h).blue < *img->data(w, h).green){
								tempBlue2 = *img->data(w, h).green - *img->data(w, h).blue;
							}
							else{
								tempBlue2 = *img->data(w, h).blue - *img->data(w, h).green;
							}

							if ((tempRed2 < 30) && (tempBlue2 < 30) && (*img->data(w, h).red <= 244)){
								img->at(w, h).red = 0;
								img->at(w, h).green = 0;
								img->at(w, h).blue = 0;
							}
			
							if ((*img->data(w, h).red >= 185) && (*img->data(w, h).green >= 185) && (*img->data(w, h).blue <= 50)){
								tempRed += *img->data(w, h).red;
								tempGreen += *img->data(w, h).green;
								tempBlue += *img->data(w, h).blue;
								temp_aantal++;
						}
					}
				}

				if (temp_aantal != 0){
					red = tempRed / temp_aantal;
					green = tempGreen / temp_aantal;
					blue = tempBlue / temp_aantal;

					for (int h = y - 5; h < y + 5; h++){
						for (int w = x - 5; w < x + 5; w++){
							if ((*img->data(w, h).red > 210) && (*img->data(w, h).green > 210) && (*img->data(w, h).blue > 210)){
								img->at(w, h).red = red;
								img->at(w, h).green = green;
								img->at(w, h).blue = blue;
							}
						}
					}
					red = 0;
					green = 0;
					blue = 0;
					tempRed = 0;
					tempGreen = 0;
					tempBlue = 0;
					temp_aantal = 0;
				}
			}
		}
	}
	saveImg(*img, "test.jpg");
}