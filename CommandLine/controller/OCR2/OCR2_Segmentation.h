#pragma once
#include "ImageLib.h"

//! Segmentation class
//
//! This class implements multiple methods which together are used for a segementation
//! algorithm. This segmentation algorithm will segmentate the different character from
//! an image containing a character sequence. Using histograms the different character are
//! found and seperated into different images.
//!
//! Team: OCR2
//! Author(s): Rick Koster & Pim te Slaa
//! Version: 1.0
//!

typedef std::vector<ImageLib::ImageGray> SegmentedImages;

namespace OCR2 {

	class Segmentation {
	public:
		//! Constructor
		Segmentation();
		//!Destructor
		~Segmentation();

		//! Apply
		//!
		//! This method is the main method in from the class. It will apply the segmentation
		//! method onto an image. The first thing it does is getting the Y indexes and the X indexes
		//! from all the characters using the GetXIndexes and GetYIndexes methods. With those indexes
		//! it will start creating the segmentated images from all characters with the CreateImages
		//! method.
		//
		//! /param Img binairy image containing the character sequence.
		//! /return ImageLib::ImageGray vector containing the different images from the characters.
		SegmentedImages Apply(const ImageLib::ImageGray & Img);

	private:
		//! A struct containing two vectors which containg the different X indexes of the characters.
		struct XIndexes {
			std::vector<int> X1;
			std::vector<int> X2;
		};

		//! A struct containing two vectors which contain the different Y indexes of the characters.
		struct YIndexes {
			std::vector<int> Y1;
			std::vector<int> Y2;
		};

		//! GetXIndexes
		//!
		//! This method will get all the X indexes of the characters in the image. This is done by
		//! using the verticalhistogram of the source image.
		//
		//! /param Img binairy image containing the character sequence.
		//! /return The filled XIndexes struct containing all the X indexes of the characters.
		inline XIndexes GetXIndexes(const ImageLib::ImageGray & Img);

		//! GetYIndexes
		//!
		//! This method will get all the Y indexes of all the characters in the image. This is done by
		//! using the horizontalhistrogram of the source image.
		//
		//! /param Img binairy image containing the character sequence.
		//! /return The filled YIndexes struct containing the two Y indexes of the characters.
		inline YIndexes GetYIndexes(const ImageLib::ImageGray & Img);

		//! CreateImages
		//!
		//! This method will create all the segmentated images of the characters in the source image.
		//! It will use the source image to locate all the characters based on the Xindexes and the YIndexes.
		//! Then it will cut out the data between those indexes and put them in a new seperate image. All the
		//! images are then collected in the segementatedImages vector.
		//!
		//! /param Img binairy image containing the character sequence
		//! /param XIndexes The struct containing all the X indexes of the characters.
		//! /param YIndexes The struct containing the two Y indexes of the characters.
		//! /return A vector containing all the segmentated character images.
		inline SegmentedImages CreateImages(const ImageLib::ImageGray & Img, const XIndexes & IndexX, const YIndexes & IndexY);
	};

}