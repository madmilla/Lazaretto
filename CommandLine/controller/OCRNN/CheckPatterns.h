#pragma once
//#include "ImageGray.h"
#include "ImageLib.h"
//#include "exectimer.h"
#include "Extensions.h"

using namespace ImageLib;

class CheckPatterns {
private:
	// Define the timer var
	//BaseTimer* bt;

	// Define a constant variable that will help check for color values.
	// In this case i've used it to check wether a pixel would be 
	// black (value < thresholdValue) or white (value > thresholdValue)
	const int thresholdValue = 127;

	// Maximum number that can be returned with any character.
	// This value wil act as upper limit of the +1 / -1 range in BlackWhiteTransition
	const int maxNumberOfLines = 6;
public:
	// Simple constructor, this just defines the existance of the BaseTimer object.
	CheckPatterns();
	// Destructor, destroys the BaseTimer object.
	~CheckPatterns();

	// =======================================================================================

	// PixPerLine - Kevin Bosman

	// This function checks how much pixels in one height line are black and returns the
	// normalized percentage in the range of +1 / -1.
	// 
	// ImageGray &sourceImage takes a reference to an ImageGray object
	// int percentage specifies the percentage of the height line in a range from 0 - 100%
	double countBlackPixelsPerRowHorizontal(const ImageGray &sourceImage, int percentage);

	// This function checks how much pixels in one width line are black and returns the
	// normalized percentage in the range of +1 / -1.
	// 
	// ImageGray &sourceImage takes a reference to an ImageGray object
	// int percentage specifies the percentage of the width line in a range from 0 - 100%
	double countBlackPixelsPerLineVertical(const ImageGray &sourceImage, int percentage);

	// =======================================================================================

	// BlackWhiteTransition - Wouter Veen
	double countBlackWhiteTransisitionVertical(const ImageGray &sourceImage, int percentage);
	double countBlackWhiteTransisitionHorizontal(const ImageGray &sourceImage, int percentage);

	// =======================================================================================
	// CheckSymmetry - Thomas Kok

	// This function checks whether there is symmetry present in an ImageGray, with the mirror
	// line drawn horizontally. This might be interpreted as vertical symmetry.
	// The first argument is the actual ImageGray to be used. The second argument 
	// is for the check whether the bounding box should be used. More on the bounding box
	// below.
	// This function returns a percentage.
	double checkSymmetryHorizontal(const ImageGray &sourceImage, bool boundingBox = 0);

	// This function checks whether there is symmetry present in an ImageGray, with the mirror
	// line drawn vertically. This might be interpreted as horizontal symmetry.
	// The first argument is the actual ImageGray to be used. The second argument 
	// is for the check whether a bounding box should be used. More on the bounding box 
	// below.
	// This function returns a percentage.
	double checkSymmetryVertical(const ImageGray &sourceImage, bool boundingBox = 0);

	// The following four functions are used for calculating values used as a bounding box.
	// The bounding box is nothing more than the most left and right value of actual character
	// data, ergo the x value of where the first usefull information starts
	// The same is done for the highest en lowest actual character data. The data is in this
	// case a black pixel.
	// This principe is illustrated below
	// 
	// xxxxxxxxxxxxxxxxxxxxxxx
	// xxxxyyyxxxxxxxxyyyxxxxx
	// xxxl   xxxxxxxx   rxxxx
	// xxxl   xxxxxxxx   rxxxx
	// xxxl   xxxxxxxx   rxxxx
	// xxxl              rxxxx
	// xxxl   xxxxxxxx   rxxxx
	// xxxl   xxxxxxxx   rxxxx
	// xxxl   xxxxxxxx   rxxxx
	// xxxxzzzxxxxxxxxzzzxxxxx
	// xxxxxxxxxxxxxxxxxxxxxxx
	// 
	// Here the 'y' is the highest an actual data pixel gets, 'z' the lowest.
	// The 'l' denotes the most left pixel, and 'r' the most right.
	// If these values are fed in the abovementioned functions, all the 'x' 
	// pixels won't be checked.
	int findLeftBlackPixel(const ImageGray &sourceImage);
	int findRightBlackPixel(const ImageGray &sourceImage);
	int findTopBlackPixel(const ImageGray &sourceImage);
	int findBottomBlackPixel(const ImageGray &sourceImage);

	double firstEdgeLocationLeft(const ImageGray & sourceImage, int percentage);
	double firstEdgeLocationRight(const ImageGray & sourceImage, int percentage);
	double firstEdgeLocationTop(const ImageGray & sourceImage, int percentage);
	double firstEdgeLocationBottom(const ImageGray & sourceImage, int percentage);

	double percentageBlack(const ImageGray & sourceImage, int xleft, int ytop, int xright, int ybottom);
};

