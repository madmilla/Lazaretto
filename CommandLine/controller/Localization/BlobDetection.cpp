/**
*	File: BlobDetection.cpp
*	Author(s): Mike Schaap
*	Version: 1.0
*/

#include "../Localization/BlobDetection.h"


/**
*	Constructor
*/
BlobDetection::BlobDetection() {

}

/*
*	Deconstructor
*/
BlobDetection::~BlobDetection() {
}

std::vector<Blob> BlobDetection::Invoke(ImageLib::ImageRGB & image,int foregroundValue, int minBlobSize) {

	//Get the image height
	int height = image.height();

	//Get the image width
	int width = image.width();

	std::vector<int> blobRows;

	std::vector< std::vector<int> > labelMap(height, std::vector<int>(width));

	std::vector<int> labelTable((height * width * 2), 0);

	//Remember on which lines we found a (part) blob, so we don't have to check every line again.
	bool blobFoundOnRow = false;

	//Maximum amount of labels an image can containt. this is a estimation.
	int maxLabels = height * width / 2;

	//We start labeling at 1. 0 means no label. (black(background) pixel)
	int labelIndex = 1;

	//used to find the labels of the surrounding pixels
	int labelA, labelB, labelC, labelD;

	int maxIntValue = std::numeric_limits<int>::max();

	//smallest neighboor label found. We use a huge value so we know for sure our if works
	int smallestLabel = maxIntValue;

	//We don't want to check the edge(1px), since not all the surrounding pixels are there.
	int tmpHeight = height - 1;
	int tmpWidth = width - 1;

	//Check every pixel for color, if color is white check surrounding pixels if they already have a label. If a neighbour (or more) has a label, assign the lowest label
	// to the current pixel
	for (int y = 1; y < tmpHeight; y++)
	{
		for (int x = 1; x < tmpWidth; x++)
		{
			//Only check blue. Saves time and if blue = 0 it's black, if blue is 255 it's white. Simple as that
			if (image.at(x, y).red == foregroundValue)
			{
				if (blobFoundOnRow == false) blobFoundOnRow = true;
				labelA = labelMap[y][x - 1];
				labelB = labelMap[y - 1][x - 1];
				labelC = labelMap[y - 1][x];
				labelD = labelMap[y - 1][x + 1];

				smallestLabel = maxIntValue;

				if (labelA != 0 && labelA < smallestLabel) smallestLabel = labelA;
				if (labelB != 0 && labelB < smallestLabel) smallestLabel = labelB;
				if (labelC != 0 && labelC < smallestLabel) smallestLabel = labelC;
				if (labelD != 0 && labelD < smallestLabel) smallestLabel = labelD;

				if (smallestLabel == maxIntValue)
				{
					//No neighbours found
					labelMap[y][x] = labelIndex;
					labelTable[labelIndex] = labelIndex;
					labelIndex++;
				}
				else
				{
					//Found atleast one neighbour label
					labelMap[y][x] = smallestLabel;
					if (labelA > smallestLabel) labelTable[labelA] = smallestLabel;
					if (labelB > smallestLabel) labelTable[labelB] = smallestLabel;
					if (labelC > smallestLabel) labelTable[labelC] = smallestLabel;
					if (labelD > smallestLabel) labelTable[labelD] = smallestLabel;

				}
			}
		}
		//found blob on row
		if (blobFoundOnRow == true) {
			blobFoundOnRow = false;
			blobRows.insert(blobRows.end(), y);
		}
	}

	std::vector<int> labelToBlob(labelIndex, 0);

	int blobCount = 0;
	int tmp1;
	for (int i = 0; i < labelIndex; i++) {
		if (labelTable[i] != i) {
			tmp1 = labelTable[i];
			while (labelTable[tmp1] != tmp1) {
				tmp1 = labelTable[tmp1];
			}
			labelToBlob[i] = labelToBlob[tmp1];
			labelTable[i] = tmp1;
		}
		else {
			labelToBlob[i] = blobCount++;
		}
	}

	std::vector< std::vector<int> > blobMap(height, std::vector<int>(width));

	//Changed all merged labels to the lowest one
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			blobMap[y][x] = labelToBlob[labelMap[y][x]];
		}
	}

	std::vector< std::vector<int> > blobsBuffer(blobCount, std::vector<int>(6));

	int originalLabel = 0;
	int blobId = 0;

	//Find smallest Y,X and biggest Y,X for each blob
	for (std::vector<int>::iterator it = blobRows.begin(); it != blobRows.end(); it++) {
		for (int x = 0; x < width; x++) {
			originalLabel = labelMap[*it][x];
			if (originalLabel > 0) {
				blobId = labelToBlob[originalLabel];
				blobsBuffer[blobId][0] = blobId;
				blobsBuffer[blobId][1]++;
				//Since we don't use the outer row the x or y should never be 0
				if (x < blobsBuffer[blobId][4] || blobsBuffer[blobId][4] == 0) blobsBuffer[blobId][4] = x;
				if (x > blobsBuffer[blobId][5]) blobsBuffer[blobId][5] = x;
				//Since we don't use the outer row the x or y should never be 0
				if (*it < blobsBuffer[blobId][2] || blobsBuffer[blobId][2] == 0) blobsBuffer[blobId][2] = *it;
				if (*it > blobsBuffer[blobId][3]) blobsBuffer[blobId][3] = *it;
			}
		}
	}

	std::vector<Blob> blobs;

	//Check if blobs are bigger than the minimum blob size, else do not add them to the new list
	for (int i = 0; i < blobCount; i++) {
		if (blobsBuffer[i][1] > minBlobSize) {
			blobs.insert(blobs.end(), Blob(blobsBuffer[i][0], blobsBuffer[i][1], blobsBuffer[i][2], blobsBuffer[i][3], blobsBuffer[i][4], blobsBuffer[i][5]));
		}
	}

	std::vector<Blob> licensePlates = _bc.CheckIfBlobIsLicensePlate(blobs, blobMap);

	return licensePlates;
}