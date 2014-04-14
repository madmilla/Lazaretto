#pragma once
#include "Image.h"

namespace ImageLib 
{
	class ImageGray : public Image
	{
	public:
		/**
		Create empty image
		@param width Width of the new image
		@param height Height of the new image
		*/
		ImageGray(unsigned int width, unsigned int height)
			: Image(width, height, 1){}
		/**
		Create new image containing the data in the vector
		@param width Width of the new image
		@param height Height of the new image
		@param data Data for new image
		*/
		ImageGray(unsigned int width, unsigned int height, const std::vector<unsigned char> & data)
			: Image(width, height, 1, data) {}
		/**
		Create new image containing the data in the
		@param width Width of the new image
		@param height Height of the new image
		@param data Data for new image
		*/
		ImageGray(unsigned int width, unsigned int height, const unsigned char * data)
			: Image(width, height, 1, data) {}


		ImageGray(const std::string & filename) : Image(filename, 1) {}


		int channels() const { return 1; }

		/**
		Get pointer to pixel at (x,y)
		*/
		unsigned char * data(unsigned int x = 0, unsigned int y = 0)
		{
				return data_.data() + x + y * width();
		}
		/**
		Get const pointer to pixel at (x,y)
		*/
		const unsigned char * data(unsigned int x = 0, unsigned int y = 0) const
		{
			return data_.data() + x + y * width();
		}

		/**
		Get reference to pixel at (x,y)
		*/
		unsigned char & at(unsigned int x, unsigned int y)
		{
			return *(data_.data() + x + y * width());
		}
		/**
		Get const reference to pixel at (x,y)
		*/
		const unsigned char & at(unsigned int x, unsigned int y) const
		{
			return *(data_.data() + x + y * width());
		}
	};
}