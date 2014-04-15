/**
*	File: BlobCheck.cpp
*	Author(s): Mike Schaap, Chanan van Ooijen, Bryan baan
*	Version: 1.0
*/

#include "../Localization/BlobCheck.h"

/**
*	Constructor
*/
BlobCheck::BlobCheck() {}

/**
*	Deconstructor
*/
BlobCheck::~BlobCheck() {}

/**
*	Return a vector list of blobs which are considered to be a license plate
*	[in] blobobjects, vector list with all blobs
*	[in] blobMap, image Map with blob id's
*/
std::vector<Blob> BlobCheck::CheckIfBlobIsLicensePlate(std::vector<Blob> &blobobjects, std::vector< std::vector<int> > blobMap) {

	//List which will contain all possible license plate blobs 
	std::vector<Blob> filteredBlobs;

	//first check cornerPoints
	for (std::vector<Blob>::iterator it = blobobjects.begin(); it != blobobjects.end(); it++) {
		//Start with finding the cornerPoints 
		it->findCornerPoints(blobMap);

		double ratio = it->getBlobRatio();
		int edgeCounter = 0;
		int lastBlobId = 0;

		//The blob is within the ratio of a licenseplate
		if (ratio >= 2 && ratio <= 5.5) {
			
			int smallY = it->getSmallestY();
			int smallX = it->getSmallestX();

			int bigY = it->getBiggestY();
			int bigX = it->getBiggestX();

			int y = ((bigY - smallY) / 2) + smallY;

			for (int x = smallX; x < bigX; x++){
				if (blobMap[y][x] != lastBlobId){
					edgeCounter++;
					lastBlobId = blobMap[y][x];
				}
			}
			if (edgeCounter >= 5)
				filteredBlobs.insert(filteredBlobs.end(), *it);
		}
	}
	return filteredBlobs;
}
