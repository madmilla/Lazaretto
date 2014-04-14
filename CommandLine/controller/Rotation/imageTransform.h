#include <cmath>
#include <fstream>
#include <array>
#include <numeric>
#include <ImageLoader.h>
#include <memory>


using namespace ImageLib;

#pragma once

//#define PT_IN_IMAGE(x,y) (x >= 0 && x < getWidth() && y >= 0 && y < getHeight())

namespace ImageCorrection {
	class imageTransform  {

	private:
		float *theMatrix;
		int interpolation;
		unsigned char returnPixel;

	public:
		imageTransform(float matrix[]){
			theMatrix = matrix;
		};

		std::unique_ptr<ImageRGB> convert(const ImageRGB& img);
		/*
		inline unsigned char& getPixelColor(int x, int y, int shift) {
		if (x >= 0 && x < (int)width() && y >= 0 && y < (int)copy.height()){
		switch (shift){
		case 16:
		returnPixel = copy.at(x, y).red;
		break;
		case 8:
		returnPixel = copy.at(x, y).green;
		break;
		case 0:
		returnPixel = copy.at(x, y).blue;
		break;
		}
		}
		return returnPixel;
		}*/
	};

	struct corner {
		int x;
		int y;
	};
}
