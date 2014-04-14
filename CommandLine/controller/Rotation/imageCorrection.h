#include <iostream>
#include <fstream>
#include <array>
#include <numeric>
#include <ImageLib.h>
#include <memory>
#include <string.h>

#include "../Rotation/imageTransform.h"
#include "../Rotation/thresholdDetermination.h"
#include "../Rotation/calcHorizonLine.h"
#include "../Rotation/matrix.h"
#include "../Rotation/Matrix6x6.h"

using namespace ImageLib;
using namespace std;

#pragma once

namespace ImageCorrection {
	class imageCorrection
	{
	private:
		float* coordinates;
	public:
		imageCorrection(float *coords) :coordinates(coords){}
		~imageCorrection(){}
		std::unique_ptr<ImageGray> correct(const ImageRGB& img);
	};
}
