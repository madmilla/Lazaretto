#pragma once
#include "ImageLib.h"
#include "OCR2_Histogram.h"
#include "OCR2_HistogramOCR_References.h"

//! HistogramOCR class
//
//! This class implements an Optical Character Recognition algorithm using value's
//! taken from the Horizontal and Vertical Histogram.
//!
//! This class will generate the Histogram's, devide them in 5 pieces, get the average value's
//! from those pieces and compare those value's with value's gained from a best-case scenario image.
//!
//! pros:
//! - fast recognition
//! - most characters not found by this algorithm can be found fast with IntersecionOCR
//!
//! cons:
//! - doesn't have an incredible succesrate
//! - has a problem with character '1' (character only needs a little difference to change the histogram drastically)
//
//! Team: OCR2
//! Author(s): Rick Koster
//! Version: 1.0
//!

namespace OCR2 {

	class HistogramOCR {
	public:
		//! Constructor
		HistogramOCR();
		//! Destructor
		~HistogramOCR();

		//! Apply HistogramOCR
		//
		//! This function will make sure that the giving image containing a character will be
		//! read and returned as a single character value.
		//
		//! /param Img binairy image containing a character
		//! /return char value representing the recognized character from image
		char Apply(const ImageLib::ImageGray & Img);

	private:
		//! Structure containing Average value's from Horizontal and Vertical histogram
		struct Averages {
			std::array<float, 5> Vertical;
			std::array<float, 5> Horizontal;
		};

		//! Check for character
		//
		//! This function will check with the value's with each character
		//
		//! /param Averages Average value's created from given image (Apply method)
		//! /param float Marge used for the check's
		//! /return char Character found during checks
		inline char CheckCharacters(const Averages Average, float Marge);

		//! Compares Average value's
		//
		//! Compares Average value's with perfect value's using a given marge
		//
		//! /param Averages average value's found
		//! /param PerfectAverages average values of best-case scenario
		//! /param float Marge used while comparing
		//! /return bool true if value's are close to each other using marge param
		inline bool CompareAverages(const Averages & current, const PerfectAverages & perfect, float Marge);
	};

}