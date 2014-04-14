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


void Shadow_Lighting::checkForDefects(shared_ptr<ImageRGB> img, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY){
	Overexposure_Test ot;
	RemoveLight rl;
	if (ot.Overexposure_Detection(img, TopLeftX, TopLeftY, TopRightX, TopRightY, BottomLeftX, BottomLeftY, BottomRightX, BottomRightY) == true){
		cout << "Overexposure\n";
		rl.ApplyLightingFiltering(img, TopLeftX, TopLeftY, TopRightX, TopRightY, BottomLeftX, BottomLeftY, BottomRightX, BottomRightY);
	}
	ShadowTest st;
	if (st.Shadow_Detection(img, TopLeftX, TopLeftY, TopRightX, TopRightY, BottomLeftX, BottomLeftY, BottomRightX, BottomRightY) == true){
		cout << "Shadow\n";
		rl.ApplyShadowFiltering(img, TopLeftX, TopLeftY, TopRightX, TopRightY, BottomLeftX, BottomLeftY, BottomRightX, BottomRightY);
	}
}

