#pragma once
#include <string>
#include <memory>
#include <utility>

#include "ImageLib.h"

using namespace ImageLib;

struct ImageData
{
	std::string filename;
	ImageGray image;

	ImageData(std::string fln, ImageGray img) 
	: filename(fln), image(img) {

	}

	char getChar() const {
		char c = filename.front();
		return (c > 96 && c < 123) ? c - 32 : c;
	}
};

class ImageList
{
private:
	const std::string image_dir;
	std::vector<ImageData> images;

	std::vector<std::string> getFilelist(const std::string & searchkey);
public:
	ImageList(const std::string & image_dir);
	~ImageList();

	const ImageData & operator [] (int id) const;

	const ImageData & getRandom() const;

	size_t numImages() const
	{
		return images.size();
	}
};

