#ifndef Shadow_Lighting_H
#define Shadow_Lighting_H
#define YELLOWGRAY 60
#include <memory>
#include <ImageLoader.h>
#include "../Exceptions/shadowExceptions.h"
#include "../Shadow_lighting/RemoveLight.h"
#include "../Shadow_lighting/Overexposure_Test.h"
#include "../Shadow_lighting/ShadowTest.h"

// File: shadow_lighting.h
// @Author Lars Veenendaal 1633223
// @Author Arthur van der Weiden
// 0.2 - Migration of tests,
// 0.1 - Skeleton setup
/*
	Still holds nothing.
*/
using namespace ImageLib;
using namespace std;

class Shadow_Lighting{
private:

public:
	void checkForDefects(shared_ptr<ImageRGB> img, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY);
};
#endif

