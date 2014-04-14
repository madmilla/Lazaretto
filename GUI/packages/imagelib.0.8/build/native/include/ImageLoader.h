#pragma once
#include <string>
#include <memory>
#include "ImageGray.h"
#include "ImageRGB.h"

namespace ImageLib
{
	/**
	Load an RGB image from file
	@throws runtime_error Throws a runtime error if the loaded image is not RGB
	@returns A unique pointer to the loaded image
	*/
	std::unique_ptr<ImageRGB> loadImg(std::string filename);

	void saveImg(const ImageGray & img, const std::string filename);
	void saveImg(const ImageRGB & img, const std::string filename);
}