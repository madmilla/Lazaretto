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