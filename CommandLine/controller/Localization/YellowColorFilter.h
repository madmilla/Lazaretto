#ifndef YELLOWCOLORFILTER_H
#define YELLOWCOLORFILTER_H

#include <ImageRGB.h>
#include <math.h>

using namespace ImageLib;

class YellowColorFilter {
public:
	void filterImage(ImageRGB & image);

	// Function to convert a RGB value to HSV format.
	// Source: http://en.literateprograms.org/RGB_to_HSV_color_space_conversion_%28C%29
	static void RGB2HSV(float r, float g, float b, float & h, float & s, float & v);
};

#endif