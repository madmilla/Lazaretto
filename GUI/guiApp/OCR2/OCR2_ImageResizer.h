#pragma once
#include "ImageLib.h"

//! Image Resizer class
//
//! This class can be used to put resize Images
//!
//! Team: OCR2
//! Author(s): Rick Koster & Pim te Slaa
//! Version: 1.0

namespace OCR2 {

	class ImageResizer {
	public:
		//! Scale ImageGray
		//
		//! This method will convert an ImageGray Object to a given Size (Size * Size)
		//! 
		//! /param Image const Image object that needs to be converted
		//! /param Size int value of the new width and height
		//! /return ImageGray new resized imagegray object
		static ImageLib::ImageGray ScaleTo(const ImageLib::ImageGray & Image, int Size);

		//! Put Image in 1x1 Ratio
		//
		//! This method will put an image in 1:1 width:height ratio (20x30 = 30x30; 560x 340 = 560x560)
		//! The unknown pixel's will be filled with white padding, the old image will be put in the middle
		//!
		//! /param Image const Image object that will be put in 1:1 ratio
		//! /return ImageGray new resized imagegray object
		static ImageLib::ImageGray PutImageIn1x1Ratio(const ImageLib::ImageGray & Image);

	private:
		static void VerticalPadding(const ImageLib::ImageGray & Source, ImageLib::ImageGray & Destination);
		static void HorizontalPadding(const ImageLib::ImageGray & Source, ImageLib::ImageGray & Destination);
	};

}