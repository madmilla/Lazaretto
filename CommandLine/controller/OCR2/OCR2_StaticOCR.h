#pragma 
#include "ImageLib.h"
#include "OCR2_StaticOCR_References.h"

//! StaticOCR class
//
//! This class can be used to apply a static OCR algorithm on a given image
//! of a character. It will divide the image in 9 block and calculates the
//! percentage of black pixels in the block. It will then compare them with the
//! percentages per block per character given in StaticOCR_References.h
//!
//! Team: OCR2
//! Author(s): Pim te Slaa
//! Version: 1.0

namespace OCR2 {

	class StaticOCR {
	public:
		//! Constructor
		StaticOCR();
		//! Destructor
		~StaticOCR();

		//! Apply the character recognition algorithm
		//
		//! This function will apply the OCR altorithm on the given image of a character.
		//! First it builds up 9 blocks. In each block the percentage of black pixels is calculated
		//! After the percentage blocks are build they are compared to the static blocks given in
		//! StaticOCR_References.h. It will compare the two blocks and give back the correct character.
		//! /param Image of the character
		//! /return The character which is displayed in the source image.
		char Apply(const ImageLib::ImageGray & Img);

	private:
		//! Array containing the 9 calculated percentage blocks.
		std::array<float, 9> percentages;

		//! Compare the blocks with the reference blocks
		//
		//! This function compares a block with the calculated percentage block
		//! of the image.
		//! /param Array which represents the blocks.
		//! /param Float to add extra marge to the comparison.
		//! /return Boolean which states if the two blocks are the same or not.
		bool compareWithBlock(std::array<float, 9> block, float mrg);

		//! Compare the calculated percentage block with all reference blocks.
		//
		//! This function compares all of the reference blocks with the percentage block of the image
		//! /param Float to add extra marge to the comparison.
		//! /return The character that is found in the comparison of the blocks.
		char compareAllBlocks(float marge);
	};

}