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
		ImageGray(unsigned int width, unsigned int height);
		/**
		Create new image containing the data in the vector
		@param width Width of the new image
		@param height Height of the new image
		@param data Data for new image
		*/
		ImageGray(unsigned int width, unsigned int height, const std::vector<unsigned char> & data);
		/**
		Create new image containing the data in the
		@param width Width of the new image
		@param height Height of the new image
		@param data Data for new image
		*/
		ImageGray(unsigned int width, unsigned int height, const unsigned char * data);

		int channels() const { return 1; }

		/**
		Get pointer to pixel at (x,y)
		*/
		unsigned char * data(unsigned int x = 0, unsigned int y = 0);
		/**
		Get const pointer to pixel at (x,y)
		*/
		const unsigned char * data(unsigned int x = 0, unsigned int y = 0) const;

		/**
		Get reference to pixel at (x,y)
		*/
		unsigned char & at(unsigned int x, unsigned int y);
		/**
		Get const reference to pixel at (x,y)
		*/
		const unsigned char & at(unsigned int x, unsigned int y) const;
	};
}