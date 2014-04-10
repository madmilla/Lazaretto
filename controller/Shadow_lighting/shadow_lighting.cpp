#include "../Shadow_lighting/shadow_lighting.h"

// File: shadow_lighting.h
// @Author Lars Veenendaal 1633223
// @Author Arthur van der Weiden
// @Author Jeroen Huisen
// 0.3- Migration of Jeroen seperated tests for detecting shadows.
// 0.2 - Migration of Arthurs seperated tests for detecting shadows.
// 0.1 - Skeleton setup
/*
Still holds nothing.
*/
using namespace ImageLib;
using namespace std;


void Shadow_Lighting::checkForDefects(ImageRGB img, int i){
	if (Overexposure_Detection(img, 1796, 1518, 2562, 1447, 1815, 1692, 2580, 1630) == true){
		ApplyLightingFiltering(img);
	}
	if (Shadow_Detection(img, 1796, 1518, 2562, 1447, 1815, 1692, 2580, 1630) == true){
		ApplyShadowFiltering(img);
	}
}
void Shadow_Lighting::ApplyShadowFiltering(ImageRGB img){
	cout << "shadow\n";
	ColorSpace cs(img);
	cs.Copy();
	cs.ToLAB(1796, 1447, 2580, 1692);
	OverExposure oe(*cs.getEditedImage());
	oe.Copy();
	//oe.ThresholdRepairOpposite(20, 60, 90, 1796, 1447, 2580, 1692);
	ColorSpace cs2(*oe.getEditedImage());
	cs2.Copy();
	cs2.ToRGB(1796, 1447, 2580, 1692);
	ImageRGB output(*cs2.getEditedImage());
//	saveImg(output, "output2.jpg");
}
void Shadow_Lighting::ApplyLightingFiltering(ImageRGB img){
	cout << "overexposure\n";
	ColorSpace cs(img);
	cs.Copy();
	cs.ToLAB(1796, 1447, 2580, 1692);
	OverExposure oe(*cs.getEditedImage());
	oe.Copy();
	oe.ThresholdRepair(90, 20, 1796, 1447, 2580, 1692);
	ColorSpace cs2(*oe.getEditedImage());
	cs2.Copy();
	cs2.ToRGB(1796, 1447, 2580, 1692);
	ImageRGB output(*cs2.getEditedImage());
//	saveImg(output, "output1.jpg");
}

bool Shadow_Lighting::Shadow_Detection(ImageRGB img, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY,
	int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY){

	int TopBigY, TopSmallY, BottomBigY, BottomSmallY;

	if (TopLeftY < TopRightY){
		TopBigY = TopRightY;
		TopSmallY = TopLeftY;
	}
	else {
		TopBigY = TopLeftY;
		TopSmallY = TopRightY;
	}
	if (BottomLeftY < BottomRightY){
		BottomBigY = BottomRightY;
		BottomSmallY = BottomLeftY;
	}
	else {
		BottomBigY = BottomLeftY;
		BottomSmallY = BottomRightY;
	}

	int LicensePlateWidth = BottomRightX;
	int LicensePlateHeight = BottomBigY - TopSmallY;

	int TotalPixels = LicensePlateHeight * LicensePlateWidth;
	float percentage;
	int ShadowPixels = 0;
	auto rgb_ptrs = img.data(TopLeftX + 1, TopLeftY + 1);
	auto Grayval = (*rgb_ptrs.red * 0.21) + (*rgb_ptrs.blue * 0.71) + (*rgb_ptrs.green * 0.07);
	auto Darkest = Grayval;
	setDarkestFoundPixel(Darkest);
	for (int x = TopLeftX + 1; x <= LicensePlateWidth; x++){
		for (int y = TopSmallY + 1; y <= BottomBigY; y++){
			Grayval = (*rgb_ptrs.red * 0.21) + (*rgb_ptrs.blue * 0.71) + (*rgb_ptrs.green * 0.07);
			if ((int)Grayval < (int)Darkest){
				Darkest = Grayval;
				setDarkestFoundPixel(Darkest);
			}
		}
	}

	for (int x = TopLeftX + 1; x <= LicensePlateWidth; x++){
		for (int y = TopSmallY + 1; y <= BottomBigY; y++){
			Grayval = (*rgb_ptrs.red * 0.21) + (*rgb_ptrs.blue * 0.71) + (*rgb_ptrs.green * 0.07);

			rgb_ptrs.red++;
			rgb_ptrs.blue++;
			rgb_ptrs.green++;

			if ((rgb_ptrs.blue > rgb_ptrs.green && rgb_ptrs.blue > rgb_ptrs.red) && (Grayval >= Darkest && Grayval <= YELLOWGRAY)){
				ShadowPixels++;
			}
			percentage = ((float)ShadowPixels / (float)TotalPixels) * 100;
			if (percentage > 2.0f){
				FoundShadow = true;
			}
		}
	}
	return FoundShadow;
}

void Shadow_Lighting::setDarkestFoundPixel(int value){
	DarkestFoundPixel = value;
}

int Shadow_Lighting::getDarkestFoundPixel(){
	return DarkestFoundPixel;
}

bool Shadow_Lighting::Overexposure_Detection(ImageRGB img, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY){
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
	for (int y = SmallY + 5; y < BigY - 5; y++){
		for (int x = TopLeftX + 5; x < BottomRightX - 5; x++){
			int xGradient = *img.data(x - 1, y + 1).blue + *img.data(x - 1, y).blue * 2 + *img.data(x - 1, y - 1).blue - *img.data(x + 1, y + 1).blue - *img.data(x + 1, y).blue * 2 - *img.data(x + 1, y - 1).blue;
			int yGradient = *img.data(x - 1, y - 1).blue + *img.data(x, y - 1).blue * 2 + *img.data(x + 1, y - 1).blue - *img.data(x + 1, y + 1).blue - *img.data(x, y + 1).blue * 2 - *img.data(x - 1, y + 1).blue;

			sum = abs(xGradient) + abs(yGradient);

			if (sum > 255){
				sum = 255;
			}
			else if (sum < 0){
				sum = 0;
			}

			if (sum >= 255){
				percentage = ((float)Overexposed_pixels / (float)TotalPixels) * 100;

				if (percentage >= 1){
					return true;
				}
				for (int h = y - 10; h < y + 10; h++){
					for (int w = x - 10; w < x + 10; w++){
						if ((*img.data(w, h).blue > 210) && (*img.data(w, h).green > 200) && (*img.data(w, h).red > 200)){
							Overexposed_pixels++;
						}
					}
				}
			}
		}
	}
	return false;
}

