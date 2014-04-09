#pragma once
#include <vector>
#include <array>

namespace ImageLib 
{
	class Image
	{
	private:
		const unsigned int width_;
		const unsigned int height_;
	protected:
		std::vector<unsigned char> data_;
		Image(unsigned int width, unsigned int height, int numChannels);
		Image(unsigned int width, unsigned int height, int numChannels, const std::vector<unsigned char> & data);
		Image(unsigned int width, unsigned int height, int numChannels, const unsigned char * data);

	public:
		virtual ~Image() {};

		typedef std::vector<unsigned char>::iterator iterator;
		typedef std::vector<unsigned char>::const_iterator const_iterator;

		/**
		The width of the image
		*/
		inline unsigned int width() const { return width_; }
		/**
		The height of the image
		*/
		inline unsigned int height() const { return height_; }
		/**
		The size in bytes of the imagedata
		*/
		inline size_t size() const { return data_.size(); }

		/**
		The amount of channels an image has
		*/
		virtual int channels() const = 0;

		/**
		Returns an iterator to the beginning
		*/
		iterator begin() { return data_.begin(); }
		/**
		Returns a const iterator to the beginning
		*/
		const_iterator begin() const { return data_.begin(); }
		const_iterator cbegin() const { return data_.cbegin(); }

		/**
		Returns an iterator to the end
		*/
		iterator end() { return data_.end(); }
		/**
		Returns a const iterator to the end
		*/
		const_iterator end() const { return data_.end(); }
		const_iterator cend() const { return data_.cend(); }
	};
}