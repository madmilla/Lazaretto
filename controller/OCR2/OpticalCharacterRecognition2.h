#pragma once
#include <string>
#include "OCR2_Segmentation.h"

#include "OCR2_HistogramOCR.h"
#include "OCR2_StaticOCR.h"
#include "OCR2_TicTacToeOCR.h"
#include "OCR2_IntersectionOCR.h"
#include "OCR2_StaticOCR2.h"

//! StaticOCR class
//
//! This class can be used to apply a static OCR algorithm on a given image
//! of a character. It will divide the image in 9 block and calculates the
//! percentage of black pixels in the block. It will then compare them with the
//! percentages per block per character given in StaticOCR_References.h
//!
//! Team: OCR2
//! Author(s): Matthijs Veldhuizen & Rick Koster
//! Version: 1.0

class OpticalCharacterRecognition2 {
public:
	//! Constructor
	OpticalCharacterRecognition2() {};
	//! Destructor
	~OpticalCharacterRecognition2() {};

	//! Segmentate Image
	//
	//! This method will segmentate the given image and return it as a vector of images
	//
	//! /param Source ImageGray object
	//! /return std::vector<ImageLib::ImageGray> containing segmented images
	SegmentedImages SegmentateImage(const ImageLib::ImageGray & Source);

	//! Segmentate Image
	//
	//! This method will convert the Image to an ImageGray object and segmentate the image
	//! and return it as a vector of ImageGray objects
	//
	//! /param Source ImageRGB object
	//! /return std::vector<ImageLib::ImageGray> containing segmented images
	SegmentedImages SegmentateImage(const ImageLib::ImageRGB & Source);

	//! Read Licence plate from segmented images
	//
	//! will read all the characters in the segmented images
	//
	//! /param segmented images
	//! /return string value of licence
	std::string ReadLicencePlate(const SegmentedImages & Source);

	//! Read Licence plate from image
	//
	//! will first segmentate the image and then read each character
	//
	//! /param Source image (licence plate)
	//! /return string value of licence
	std::string ReadLicencePlate(const ImageLib::ImageGray & Source);

	//! Read Character
	//
	//! Will read a character from the given image
	//
	//! /param Source image (single character)
	//! /return char value representing the image
	char ReadCharacter(const ImageLib::ImageGray & Source);

	//! Run Test
	//
	//! Will run a test on all OCR algorithm's printing the results
	//
	//! /param Source image (licence plate)
	void RunTest(const ImageLib::ImageGray & Source);

private:
	inline std::string ReadStaticOCRLicence(const SegmentedImages & Source);
	inline std::string ReadHistogramOCRLicence(const SegmentedImages & Source);
	inline std::string ReadTicTacToeOCRLicence(const SegmentedImages & Source);
	inline std::string ReadIntersectionOCRLicence(const SegmentedImages & Source);
	inline std::string ReadStaticOCR2Licence(const SegmentedImages & Source);

	std::unique_ptr<ImageLib::ImageGray> GrayScale(const ImageLib::ImageRGB & rgb_img);
};

