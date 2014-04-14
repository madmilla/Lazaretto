/*
*
*	Author: Mike Schaap
*/

//#include "stdafx.h"
#include "../Localization/Blob.h"

Blob::Blob(int id, int mass, int minY, int maxY, int minX, int maxX)  {
	_id = id;
	_pixelCount = mass;
	_smallestX = minX;
	_biggestX = maxX;
	_smallestY = minY;
	_biggestY = maxY;
}

double Blob::getRealRatio() {
	//if (_cornerPoints.size() <= 0){
	//	throw std::exception("No corner points found!");
	//}
	// _cornerPoints[0] & 2 = width;
	// _cornerPoints[1] & 4 = height;
	double width = _cornerPoints[2] - _cornerPoints[0];
	double height = _cornerPoints[5] - _cornerPoints[1];
	if (height == 0){
		return (double)width;
	}
	else{
		return (double)(width / height);
	}
	//	return (double((width + 1)) / double((height + 1)));
};