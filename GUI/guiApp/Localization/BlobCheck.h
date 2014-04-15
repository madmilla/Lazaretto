/**
*	File: BlobCheck.h
*	Author(s): Mike Schaap, Chanan van Ooijen, Bryan baan
*	Version: 1.0
*/

#ifndef BlobCheck_H
#define BlobCheck_H

#include <iostream>
#include <vector>
#include <ImageLib.h>
#include "../Localization/Blob.h"


/**
*	class for checking is a blob can be considered as a license plate
*/
class BlobCheck {
private:

public:
	/**
	*	Constructor
	*/
	BlobCheck();

	/**
	*	Deconstructor
	*/
	~BlobCheck();

	/**
	*	Return a vector list of blobs which are considered to be a license plate
	*	[in] blobobjects, vector list with all blobs
	*	[in] blobMap, image Map with blob id's
	*/
	std::vector<Blob> CheckIfBlobIsLicensePlate(std::vector<Blob> &blobobjects, std::vector< std::vector<int> > blobMap);
};

#endif