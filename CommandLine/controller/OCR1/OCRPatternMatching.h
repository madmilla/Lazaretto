#pragma once
#include "ImageGray.h"
#include <memory>
#define NUMBER_OF_CHARACTERS 37
#define FIND_CHAR_PERCENTAGE 99
#define	CHAR_INDEX_SIZE	26
#define LAST_FOUND_STRIPE 0
#define	LAST_FOUND_LETTER 1
#define	LAST_FOUND_NUMBER 2
#define Q_INDEX 16
#define O_INDEX 14
#define ASCII_CONVERT_LETTER 65
#define ASCII_CONVERT_NUMBER 21
#define ASCII_CONVERT_STRIPE 19

using namespace ImageLib;

//! class OCRPatternMatching
//
//! @authors Rick van der Paauw, Marco Knol, Melvin van den Berg and Michael Pieneman
//! This class uses Pattern Matching to determine which character is inserted. 
class OCRPatternMatching
{
private:
	const std::string font_directory = "images/font/";
	//! @var lastDetection stores the previous detected character.
	unsigned char lastDetection;
	//! @var referenceImages stores the samples of all the font characters. 
	std::vector<ImageGray> referenceImages;
	//! Resample
	//
	//! @param input contains the input grayImage.
	//! @param newWidth is the width of the new grayImage.
	//! @param newHeight is the height of new grayImage.
	//! This function resamples the input grayImage to a new grayImage with the given width and height. 
	inline ImageGray Resample(ImageGray& input, short newWidth, short newHeight);
	//! Recognize
	//
	//! @param character is the imageGray with the character that has to be detected (recognized).
	//! This function recognizes the character out of the image. 
	inline unsigned char Recognize(ImageGray& character);
public:
	//! Constructor OCR Pattern Matching
	//
	//! Constructs an object of OCR Pattern Matching.
	OCRPatternMatching();
	//! Recognize License Plate 
	//
	//! Recognizes the total license plate. 
	std::string RecognizeLicenseplate(std::vector<ImageGray>& chars);
};

