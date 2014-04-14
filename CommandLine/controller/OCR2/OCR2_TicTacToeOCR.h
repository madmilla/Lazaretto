#pragma once
#include "ImageLib.h"

//! TicTacToe class
//
//! This algoritm is based on the bord game tic tac toe.
//! To make this algoritm work I print a tic tac toe field with 9 crossings over the character (this is bigger then the normal board).
//! By checking the crossings of this field I can narrow down the possibility's of characters to a maximum of 3 with one or two simpel is it possible to find the character
//!
//
//! Team: OCR2
//! Author(s): Matthijs Uit den Bogaard
//! Version: 1.0

namespace OCR2 {

class TicTacToeOCR {
public:
	//! Constructor
	TicTacToeOCR();
	//! Constructor
	//
	//! /param Int The interger containing the left border
	//! /param Int The interger containing the right border
	//! /param Int The interger containing the upper border
	//! /param Int The interger containing the under border
	TicTacToeOCR(int l, int r, int u, int d);
	//! Destructor
	~TicTacToeOCR();

	//! Apply TicTacToeOCR
	//
	//! This function contains the Switch statement that contains all the numbers that equal a character
	//
	//! /param Img binairy Image containing the character
	//! /return char value representing the character on the image
	char Apply(const ImageLib::ImageGray & Img, bool recheck = false);

	//! Learn
	//!
	//! This function writes the information found on the picture to a text file together with the given character
	//
	//! /param Img binairy Image containing the character
	void Learn(const ImageLib::ImageGray & source, char c = 0);

	//! Set the left border
	//
	//! /param Int The interger containing the left border
	inline void setLeft(int l) { left = l; }

	//! Set the right border
	//
	//! /param Int The interger containing the right border
	inline void setRight(int r) { right = r; }

	//! Set the upper border
	//
	//! /param Int The interger containing the upper border
	inline void setUp(int u) { up = u; }

	//! Set the under border
	//
	//! /param Int The interger containing the under border
	inline void setDown(int d) { down = d; }

private:
	//! These intergers are the border around the character
	int left, right, up, down;

	//! Check
	//!
	//! This function checks all the 9 points on the character
	inline short check(const ImageLib::ImageGray & source);
};

}