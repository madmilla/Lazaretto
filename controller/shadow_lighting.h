#ifndef Shadow_Lighting_H
#define Shadow_Lighting_H
#include <memory>
#include <ImageLoader.h>
#include "shadowExceptions.h"

// File: shadow_lighting.h
// @Author Lars Veenendaal 1633223
// 0.1 - Skeleton setup
/*
	Still holds nothing.
*/
using namespace ImageLib;
using namespace std;

class Shadow_Lighting{
private:
public:
	void checkForDefects(ImageRGB *, int i);
	void ApplyShadowFiltering();
	void ApplyLightingFiltering();
};

#endif

