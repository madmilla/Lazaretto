#pragma once
#include "Image.h"

namespace ImageLib 
{
	enum class Channel
	{
		Red = 0,
		Green = 1,
		Blue = 2
	};

	template<typename T>
	struct Rgb
	{
		T red;
		T green;
		T blue;

		inline Rgb(T r, T g, T b)
			: red(r), green(g), blue(b) {}
	};

	class ImageRGB : public Image
	{
	private:
		size_t channelsize;
	public:
		/**
		Create empty image
		@param width Width of the new image
		@param height Height of the new image
		*/
		ImageRGB(unsigned int width, unsigned int height)
			: Image(width, height, 3), channelsize(width * height) {}
		/**
		Create new image containing the data in the vector
		@param width Width of the new image
		@param height Height of the new image
		@param data Data for new image
		*/
		ImageRGB(unsigned int width, unsigned int height, const std::vector<unsigned char> & data)
			: Image(width, height, 3, data), channelsize(width * height) {}
		/**
		Create new image containing the data in the 
		@param width Width of the new image
		@param height Height of the new image
		@param data Data for new image
		*/
		ImageRGB(unsigned int width, unsigned int height, const unsigned char * data)
			: Image(width, height, 3, data), channelsize(width * height) {}

		ImageRGB(const std::string & filename)
			: Image(filename, 3) {}

		/**
		Rgb struct containing references to each channel
		*/
		typedef Rgb<unsigned char &> reference;
		/**
		const Rgb struct containing const references to each channel
		*/
		typedef const Rgb<const unsigned char &> const_reference;

		/**
		Rgb struct containing pointers to the channel
		*/
		typedef Rgb<unsigned char *> pointer;
		/**
		const Rgb struct containing const pointers to each channel
		*/
		typedef const Rgb<const unsigned char *> const_pointer;

		int channels() const { return 3; }

		/**
		Get pointer to pixel at (x,y) in specified channel
		*/
		unsigned char * data(unsigned int x, unsigned int y, Channel channel)
		{
			return data_.data() + x + (y * width()) + ((int)channel * channelsize);
		}
		/**
		Get const pointer to pixel at (x,y) in specified channel
		*/
		const unsigned char * data(unsigned int x, unsigned int y, Channel channel) const
		{
			return data_.data() + x + (y * width()) + ((int)channel * channelsize);
		}

		/**
		Get struct of pointers to each channel at (x, y)
		@return [red *, green *, blue *]
		*/
		pointer data(unsigned int x = 0, unsigned int y = 0)
		{
			auto ptr_red = data(x, y, Channel::Red);
			auto ptr_green = ptr_red + channelsize;
			auto ptr_blue = ptr_green + channelsize;

			return ImageRGB::pointer(ptr_red, ptr_green, ptr_blue);
		}
		/**
		Get struct of const pointers to each channel at (x, y)
		@return [red *, green *, blue *]
		*/
		const_pointer data(unsigned int x = 0, unsigned int y = 0) const
		{
			auto ptr_red = data(x, y, Channel::Red);
			auto ptr_green = ptr_red + channelsize;
			auto ptr_blue = ptr_green + channelsize;

			return ImageRGB::const_pointer(ptr_red, ptr_green, ptr_blue);
		}

		/**
		Get struct of references to pixel at (x,y)
		*/
		reference at(unsigned int x = 0, unsigned int y = 0)
		{
			auto ptrs = data(x, y);

			return ImageRGB::reference(*ptrs.red, *ptrs.green, *ptrs.blue);
		}
		/**
		Get struct of references to pixel at (x,y)
		*/
		const_reference at(unsigned int x = 0, unsigned int y = 0) const
		{
			auto ptrs = data(x, y);

			return ImageRGB::const_reference(*ptrs.red, *ptrs.green, *ptrs.blue);
		}

		/**
		Get reference to pixel at (x,y), in the specified channel
		*/
		unsigned char & at(unsigned int x, unsigned int y, Channel channel)
		{
			auto ptr = data(x, y, channel);

			return *ptr;
		}
		/**
		Get const reference to pixel at (x,y), in the specified channel
		*/
		const unsigned char & at(unsigned int x, unsigned int y, Channel channel) const
		{
			auto ptr = data(x, y, channel);

			return *ptr;
		}
	};

	/**
	@example Examples.cpp


	*/
}