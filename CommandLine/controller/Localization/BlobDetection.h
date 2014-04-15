/**
*	File: BlobDetection.h
*	Author(s): Mike Schaap
*	Version: 1.0
*/

#ifndef BlobDetection_H
#define BlobDetection_H

#include "../Localization/Blob.h"
#include "../Localization/BlobCheck.h"

#include <string>
#include <iostream>
#include <list>
#include <ImageLib.h>
#include <limits>

/**
*	Class used for detecting and labelings blob in an black/white image
*/
class BlobDetection {
private:

	/**
	*	Class to check and filter blobs
	*/
	BlobCheck _bc;

public:
	/**
	*	Constructor
	*/
	BlobDetection();

	/**
	*	Deconstructor
	*/
	~BlobDetection();

	/**
	*	Returns list of all the found blobs
	*/
	std::vector<Blob> Invoke(ImageLib::ImageRGB & image, int foregroundValue, int minBlobSize);
};

#endif