/*
*
*	Author: Mike Schaap
*/


//#include "stdafx.h"
#include "../Localization/BlobCheck.h"

BlobCheck::BlobCheck() {}

BlobCheck::~BlobCheck() {}

std::vector<Blob> BlobCheck::CheckIfBlobIsLicensePlate(std::vector<Blob> &blobobjects, std::vector< std::vector<int> > blobMap) {

	std::vector<Blob> validBlobs;
	//check if blob of possible licenseplate
	for (std::vector<Blob>::iterator it = blobobjects.begin(); it != blobobjects.end(); ++it) {
		double ratio = it->getRatio();
		if (ratio >= 2.1 && ratio <= 5.5) {
			int edgeCounter = 0;
			int lastBlobId = 0;


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
				validBlobs.insert(validBlobs.end(), *it);
		}
	}

	//std::cout << "validBlobs: " << validBlobs.size() << std::endl;

	for (std::vector<Blob>::iterator it = validBlobs.begin(); it != validBlobs.end(); it++) {

		int blobId = it->getId();
		int h = it->getHeight();

		bool labelFound = false;

		int cornerTLY = -1;
		int cornerTLX = -1;

		int cornerTRY = -1;
		int cornerTRX = -1;

		int cornerBLY = -1;
		int cornerBLX = -1;

		int cornerBRY = -1;
		int cornerBRX = -1;


		int minFlatRate = 2;

		int lastY = -1;
		int flatCnt = 0;

		int smallY = it->getSmallestY();
		int smallX = it->getSmallestX();

		int bigY = it->getBiggestY();
		int bigX = it->getBiggestX();

		int halfX = smallX + ((bigX - smallX) / 2);
		int halfY = smallY + ((bigY - smallY) / 2);

		//Top Left
		for (int x = halfX; x > smallX; x--) {
			for (int y = smallY; y < bigY && labelFound == false; y++) {
				//We found the label we are looking for. 
				if (blobMap[y][x] == blobId) {
					labelFound = true;
					if (lastY == -1) lastY = y;
					if (y == lastY) {
						flatCnt++;
						if (flatCnt >= minFlatRate && y < halfY) {
							cornerTLY = y;
							cornerTLX = x;
						}
					}
					else {
						flatCnt = 0;
					}
					lastY = y;
				}
			}
			labelFound = false;
		}

		flatCnt = 0;
		lastY = -1;

		//Top right
		for (int x = halfX; x < bigX; x++) {
			for (int y = smallY; y < bigY && labelFound == false; y++) {
				//We found the label we are looking for. 
				if (blobMap[y][x] == blobId) {
					labelFound = true;
					if (lastY == -1) lastY = y;
					if (y == lastY) {
						flatCnt++;
						if (flatCnt >= minFlatRate && y < halfY) {
							cornerTRY = y;
							cornerTRX = x;
						}
					}
					else {
						flatCnt = 0;
					}
					lastY = y;
				}
			}
			labelFound = false;
		}

		flatCnt = 0;
		lastY = -1;

		// Bot left
		for (int x = halfX; x > smallX; x--) {
			for (int y = bigY; y > smallY && labelFound == false; y--) {
				//We found the label we are looking for. 
				if (blobMap[y][x] == blobId) {
					labelFound = true;
					if (lastY == -1) lastY = y;
					if (y == lastY) {
						flatCnt++;
						if (flatCnt >= minFlatRate && y > halfY) {
							cornerBLY = y;
							cornerBLX = x;
						}
					}
					else {
						flatCnt = 0;
					}
					lastY = y;
				}
			}
			labelFound = false;
		}

		flatCnt = 0;
		lastY = -1;

		//Bot right
		for (int x = halfX; x < bigX; x++) {
			for (int y = bigY; y > smallY && labelFound == false; y--) {
				//We found the label we are looking for. 
				if (blobMap[y][x] == blobId) {
					labelFound = true;
					if (lastY == -1) lastY = y;
					if (y == lastY) {
						flatCnt++;
						if (flatCnt >= minFlatRate && y > halfY) {
							cornerBRY = y;
							cornerBRX = x;
						}
					}
					else {
						flatCnt = 0;
					}
					lastY = y;
				}
			}
			labelFound = false;
		}

		std::vector<int> cornerPoints(8);
		cornerPoints[0] = cornerTLX;
		cornerPoints[1] = cornerTLY;
		cornerPoints[2] = cornerTRX;
		cornerPoints[3] = cornerTRY;
		cornerPoints[4] = cornerBLX;
		cornerPoints[5] = cornerBLY;
		cornerPoints[6] = cornerBRX;
		cornerPoints[7] = cornerBRY;

		it->setCornerPoints(cornerPoints);

	}

	return validBlobs;
}
