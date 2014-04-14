#pragma once
#include "ImageLib.h"
#include "OCR2_IntersectionOCR_References.h"

//! IntersectionOCR class
//
//! This class implements an Optical Character Recognition algorithm using 
//! lines drawn over the Image, these lines will have an amount of intersections with a
//! character that can be used to find out which character is on the Image
//!
//! This algorithm will use 5 horizontal and 5 vertical lines to count intersections with.
//!
//! pros:
//! - Algorithm takes 1ms
//! - Able to find most characters that HistogramOCR could not find (best used together)
//!
//! cons:
//! - Does not work for reading a T / L / Z (T and L will become a 1, Z will become a 2)
//! - High chance to fail on alot of characters
//! - Not relyable on its own
//
//! Team: OCR2
//! Author(s): Rick Koster & Matthijs Uit den Bogaard
//! Version: 1.0
//!

namespace OCR2 {

	class IntersectionOCR {
	public:
		//! Constructor
		IntersectionOCR();
		//! Deconstructor
		~IntersectionOCR();

		//! Apply InsertionOCR
		//
		//! This function will make sure that the given Image containing a single character will be
		//! read and returned as it's char value.
		//
		//! /param Img binary image containing a single character
		//! /return char value representing the character read
		char Apply(const ImageLib::ImageGray & Img);

	private:
		//! Array with 5 y indexes of the horizontal lines
		std::array<int, 5> IndexesH;
		//! Array with 5 x indexes of the vertical lines
		std::array<int, 5> IndexesV;

		//! Struct used to save the ammount of intersection by each line applied
		//! on the image.
		struct IntersectionCount {
			std::array<int, 5> HorizontalIntersections;
			std::array<int, 5> VerticalIntersections;
		} Intersections;

		//! Check Intersections on Horizontal lines
		//
		//! /param Img binary Image containing a single character
		inline void CheckHorizontalIntersections(const ImageLib::ImageGray & Img);

		//! Check Intersections on Vertical lines
		//
		//! /param Img binary Image containing a single character
		inline void CheckVerticalIntersections(const ImageLib::ImageGray & Img);

		//! Check for characters
		//
		//! This method will check each character and see if the intersections found correspondent
		//! with values stored from best-case scenario's
		//
		//! /return char value representing the character read from the Image 
		inline char CheckCharacters();

		//! Compare Intersections
		//
		//! This method will be used to compare the intersections stored within with the given reference
		//! Intersection value's
		//
		//! /param ReferenceIntersections intersections used as reference to compare with
		//! /return bool value telling if the intersections equal the reference
		inline bool CompareIntersections(const ReferenceIntersections & Reference);

		//! Reset Intersection Value's
		//
		//! This method will put all the Intersection value's stored witin on 0
		inline void ResetIntersections();
	};

}