#include "../Rotation/imageTransform.h"
#include <iostream>
#include <math.h>
#include "matrix.h"

using namespace ImageCorrection;

std::unique_ptr<ImageRGB> imageTransform::convert(const ImageRGB& oldImage) {
	std::unique_ptr<ImageRGB> returnImage = std::make_unique<ImageRGB>(460, 110);

	matrix m;

	float *inverse = m.getInverseMatrix(theMatrix);

	float a0 = inverse[0];
	float a1 = inverse[1];
	float a2 = inverse[2];
	float b0 = inverse[3];
	float b1 = inverse[4];
	float b2 = inverse[5];
	float c0 = inverse[6];
	float c1 = inverse[7];
	float c2 = inverse[8];

#define PT_IN_IMAGE(x,y) (x >= 0 && x < oldImage.width() && y >= 0 && y < oldImage.height())
	for (int h = 0; h < returnImage->height(); ++h) {
		for (int w = 0; w < returnImage->width(); ++w) {
			float x = (a0*w) + (a1*h) + a2;
			float y = (b0*w) + (b1*h) + b2;
			float w1 = (c0*w) + (c1*h) + c2;

			x /= w1;
			y /= w1;

			if (PT_IN_IMAGE(w, h)){
				float x0 = floor(x);
				float x1 = ceil(x);
				float y0 = floor(y);
				float y1 = ceil(y);
				float deltaX = (x - x0);
				float deltaY = (y - y0);

				float p = oldImage.at((int)x0 + .5, (int)y0 + .5).red + (oldImage.at((int)x1 + .5, (int)y0 + .5).red - oldImage.at((int)x0 + .5, (int)y0 + .5).red) * deltaX;
				float q = oldImage.at((int)x0 + .5, (int)y1 + .5).red + (oldImage.at((int)x1 + .5, (int)y1 + .5).red - oldImage.at((int)x0 + .5, (int)y1 + .5).red) * deltaX;
				returnImage->at(w, h).red = (int)(p + ((q - p)*deltaY));

				p = oldImage.at((int)x0 + .5, (int)y0 + .5).green + (oldImage.at((int)x1 + .5, (int)y0 + .5).green - oldImage.at((int)x0 + .5, (int)y0 + .5).green) * deltaX;
				q = oldImage.at((int)x0 + .5, (int)y1 + .5).green + (oldImage.at((int)x1 + .5, (int)y1 + .5).green - oldImage.at((int)x0 + .5, (int)y1 + .5).green) * deltaX;
				returnImage->at(w, h).green = (int)(p + ((q - p)*deltaY));

				p = oldImage.at((int)x0 + .5, (int)y0 + .5).blue + (oldImage.at((int)x1 + .5, (int)y0 + .5).blue - oldImage.at((int)x0 + .5, (int)y0 + .5).blue) * deltaX;
				q = oldImage.at((int)x0 + .5, (int)y1 + .5).blue + (oldImage.at((int)x1 + .5, (int)y1 + .5).blue - oldImage.at((int)x0 + .5, (int)y1 + .5).blue) * deltaX;
				returnImage->at(w, h).blue = (int)(p + ((q - p)*deltaY));

			}

		}
	}

	return returnImage;
}