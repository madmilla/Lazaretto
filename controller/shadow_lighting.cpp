#include "shadow_lighting.h"

// File: shadow_lighting.h
// @Author Lars Veenendaal 1633223
// 0.1 - Skeleton setup
/*
Still holds nothing.
*/
using namespace ImageLib;
using namespace std;


void Shadow_Lighting::checkForDefects(ImageRGB * img, int i){
	cout << "SNL " << img->height() << "X" << img->width() << endl;
	if (i == 2){
		throw ShadowExceptions("OVEREXPOSED");
	}
	else if (i == 1){
		throw ShadowExceptions("SHADOW");
	}
	else{
		throw ShadowExceptions("NOTHING");
	}
}
void Shadow_Lighting::ApplyShadowFiltering(){
	cout << "SHADOW FOUND AND FIXXED" << endl;
}
void Shadow_Lighting::ApplyLightingFiltering(){
	cout << "OVEREXPOSED FOUND AND FIXXED" << endl;
}

