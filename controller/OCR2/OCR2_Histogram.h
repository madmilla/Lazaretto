#pragma once
#include "ImageLib.h"
#include <string>

//! Histogram class
//
//! This class can be used to create a Histogram from a given image
//!
//! Team: OCR2
//! Author(s): Rick Koster & Matthijs Veldhuizen
//! Version: 1.0

#define COLOR_HISTOGRAM_LENGTH 256

namespace OCR2 {

	class Histogram {
	public:
		//! Constructor
		//
		//! /param Length length of the Histogram
		Histogram(int Length = COLOR_HISTOGRAM_LENGTH);
		//! Destructor
		~Histogram();

		//! Save as .csv file
		//
		//! This function will save the Histogram value's as a comma seperated file
		//! /param FileName name used to save the file
		void Save(const std::string & FileName);

		//! Creates a grayval Color Histogram from an RGB Image
		//
		//! /param Img the image used to create a color histogram
		void CreateColorHistogram(const ImageLib::ImageRGB & Img);

		//! Creates a Vertical Histogram from a Binary Image
		//
		//! /param Img the image used to create a vertical histogram
		void CreateVerticalHistogram(const ImageLib::ImageGray & Img);

		//! Creates a Horizontal Histogram from a Binary Image
		//
		//! /param Img the image used to create a horizontal histogram
		void CreateHorizontalHistogram(const ImageLib::ImageGray & Img);

		//! /return float value of the lowest value stored within
		float MinValue();

		//! /return float value of the highest value stored within
		float MaxValue();

		//! /return int value of Histogram length
		inline int Length() const { return _Length; }

		//! Operator[]
		//
		//! Used to reach the Histogram values float f = Histogram[index]
		//!
		//! /param index Index of Histogram
		//! /return float value found on given index
		inline float operator[] (int index) const {
			if (index < 0 || index > _Length) throw std::out_of_range("Invalid Index");
			return _Histogram[index];
		}

		//! Operator[]
		//
		//! Used to reach the Histogram values Histogram[index] = float f
		//!
		//! /param index Index of Histogram
		//! /return float value found on given index
		inline float & operator[] (int index) {
			if (index < 0 || index > _Length) throw std::out_of_range("Invalid Index");
			return _Histogram[index];
		}

	private:
		//! Histogram Value's
		std::vector<float> _Histogram;
		//! Histogram Length
		int _Length;

		//! Resets the Values
		//
		//! This method will put all the Histogram value's on 0
		inline void ResetValues();
	};

}