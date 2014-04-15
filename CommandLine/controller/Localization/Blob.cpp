/**
*	File: Blob.cpp
*	Author(s): Mike Schaap, Chanan van Ooijen, Bryan baan
*	Version: 1.0
*/

#include "../Localization/Blob.h"

Blob::Blob() {

}

/**
*	Constructor for Blob.
*	Takes following arguments:
*	[in] id , used to identify blob
*	[in] mass, amount of pixels belonging to the blob
*	[in] minY, smallest Y value 
*	[in] maxY, biggest Y value
*	[in] minX, smallest X value
*	[in] maxXm biggest X value
*/
Blob::Blob(int id, int mass, int minY, int maxY, int minX, int maxX)  {
	_id = id;
	_pixelCount = mass;
	_smallestX = minX;
	_biggestX = maxX;
	_smallestY = minY;
	_biggestY = maxY;
}

Blob::~Blob() {
}

/**
*	Gets the blob height
*/
int Blob::getBlobHeight() {
	if (_cornerPoints.size() == 0) return -1;
	else {
		return (_cornerPoints[5] - _cornerPoints[1]);
	}
}

/**
*	Gets the average blob width of the topHypotenuse and botHypotenuse
*/
int Blob::getBlobWidth() {
	int topHypotenuse = -1;
	int botHypotenuse = -1;
	//Calculate width of the top side
	if (_cornerPoints[1] == _cornerPoints[3])
	{
		topHypotenuse = _cornerPoints[3] - _cornerPoints[1];
	}
	else {
		int opposite = -1;
		int adjacent = _cornerPoints[2] - _cornerPoints[0];
		if (_cornerPoints[1] < _cornerPoints[3]) opposite = _cornerPoints[3] - _cornerPoints[1];
		else if (_cornerPoints[1] > _cornerPoints[3]) opposite = _cornerPoints[1] - _cornerPoints[3];
		topHypotenuse = (int)sqrt(pow(opposite, 2) + pow(adjacent, 2));
	}

	//Calculate width of the bot side
	if (_cornerPoints[5] == _cornerPoints[7])
	{
		botHypotenuse = _cornerPoints[5] - _cornerPoints[7];
	}
	else
	{
		int opposite = -1;
		int adjacent = _cornerPoints[6] - _cornerPoints[4];
		if (_cornerPoints[5] < _cornerPoints[7]) opposite = _cornerPoints[7] - _cornerPoints[5];
		else if (_cornerPoints[5] > _cornerPoints[7]) opposite = _cornerPoints[5] - _cornerPoints[7];
		botHypotenuse = (int)sqrt(pow(opposite, 2) + pow(adjacent, 2));
	}
	if (topHypotenuse > -1 && botHypotenuse > -1) return ((topHypotenuse + botHypotenuse) / 2);
	else return -1;
}

/**
*	Gets the ratio of the actual blob size
*/
double Blob::getBlobRatio() {
	if (getBlobHeight() == 0){
		return (double)getBlobWidth();
	}
	return (double)(getBlobWidth() / getBlobHeight());
};

/**
*	Find the cornerPoints
*/
void Blob::findCornerPoints(std::vector< std::vector<int> > blobMap) {
	int h = getBoundingBoxHeight();

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

	int smallY = getSmallestY();
	int smallX = getSmallestX();

	int bigY = getBiggestY();
	int bigX = getBiggestX();

	int halfX = smallX + ((bigX - smallX) / 2);
	int halfY = smallY + ((bigY - smallY) / 2);

	//Top Left
	for (int x = halfX; x > smallX; x--) {
		for (int y = smallY; y < bigY && labelFound == false; y++) {
			//We found the label we are looking for. 
			if (blobMap[y][x] == _id) {
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
			if (blobMap[y][x] == _id) {
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
			if (blobMap[y][x] == _id) {
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
			if (blobMap[y][x] == _id) {
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

	_cornerPoints = cornerPoints;
}