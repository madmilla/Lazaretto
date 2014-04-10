
#include "../Localization/YellowColorFilter.h"

void YellowColorFilter::filterImage(ImageRGB & image) {
	// Image size;
	int width = image.width();
	int height = image.height();

	// For every pixel in the image
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			// Get the RGB values
			Rgb<unsigned char &> pixelRGB = image.at(x, y);

			// To save the Hue, Saturation and Value
			float hue, saturation, value;

			// Convert RGB to HSV.
			RGB2HSV(pixelRGB.red, pixelRGB.green, pixelRGB.blue, hue, saturation, value);

			// If the color is yellow.
			if (hue >= 25 && hue <= 60 && saturation >= 0.60) {
				// If the color is within our yellow range, make the output pixel white.
				pixelRGB.red = 255;
				pixelRGB.green = 255;
				pixelRGB.blue = 255;
			}
			else {
				// Else make the pixel black.
				pixelRGB.red = 0;
				pixelRGB.green = 0;
				pixelRGB.blue = 0;
			}
		}
	}
}

// Function to convert a RGB value to HSV format.
// Source: http://en.literateprograms.org/RGB_to_HSV_color_space_conversion_%28C%29
void YellowColorFilter::RGB2HSV(float r, float g, float b, float & h, float & s, float & v)
{
	float min, max, delta;

	// Find the minimum RGB value.
	min = r < g ? r : g;
	min = min  < b ? min : b;

	// Find the maximum RGB value.
	max = r > g ? r : g;
	max = max  > b ? max : b;

	// Set the Value.
	v = max;

	// Calculate Saturtation.
	delta = max - min;
	if (max > 0.0) {
		s = (delta / max);
	}
	else {
		s = 0.0;
		h = NAN;
		return;
	}

	// Calculate Hue.
	if (r >= max) {
		// between yellow & magenta.
		h = (g - b) / delta;
	}
	else {
		if (g >= max) {
			// between cyan & yellow.
			h = 2.0f + (b - r) / delta;
		}
		else {
			// between magenta & cyan.
			h = 4.0f + (r - g) / delta;
		}
	}

	// Degrees.
	h *= 60.0;

	if (h < 0.0) {
		h += 360.0;
	}
}