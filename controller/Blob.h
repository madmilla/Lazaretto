/*
*
*	Author: Mike Schaap
*/

#ifndef Blob_H
#define Blob_H

#include <vector>

class Blob {

private:
	int _id;
	int _pixelCount;
	int _smallestY;
	int _biggestY;

	int _smallestX;
	int _biggestX;

	std::vector<int> _cornerPoints;

public:
	Blob(int id, int mass, int minY, int maxY, int minX, int maxX);

	int getGroundSurface(){ return (getWidth() * getHeight()); };
	double getRatio(){ return (double((getWidth() + 1)) / double((getHeight() + 1))); };
	int getMass(){ return _pixelCount; };

	int getWidth(){ return (_biggestX - _smallestX); };
	int getHeight(){ return (_biggestY - _smallestY); };

	int getSmallestY() { return _smallestY; };
	int getSmallestX() { return _smallestX; };

	int getBiggestY() { return _biggestY; };
	int getBiggestX() { return _biggestX; };

	int getId(){ return _id; };

	void setCornerPoints(std::vector<int> points) { _cornerPoints = points; };
	std::vector<int> getCornerPoints(){ return _cornerPoints; };

};

#endif