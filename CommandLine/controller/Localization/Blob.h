/**
*	File: Blob.h
*	Author(s): Mike Schaap, Chanan van Ooijen, Bryan baan
*	Version: 1.0
*/

#ifndef Blob_H
#define Blob_H

#include <vector>
#include <math.h> 


/**
*	Blob class used for storing blob properties
*/
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

	/**
	*	Used for resize function in vector.
	*	DO NOT USE! No setters available
	*/
	Blob();

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
	Blob(int id, int mass, int minY, int maxY, int minX, int maxX);

	/**
	*	Deconstructor
	*/
	~Blob();

	/**
	*	Gets the blob ID
	*/
	int getId(){ return _id; };

	/**
	*	Gets the ground surface of the boundingBox
	*/
	int getBoundingBoxGroundSurface(){ return (getBoundingBoxWidth() * getBoundingBoxHeight()); };

	/**
	*	Gets the ground surface of the blob
	*/
	int getBlobGroundSurface(){ return getBlobWidth() * getBlobHeight(); };

	/**
	*	Gets the Bounding box ratio
	*/
	double getBoundingBoxRatio(){ return (double((getBoundingBoxWidth() + 1)) / double((getBoundingBoxHeight() + 1))); };

	/**
	*	Gets the ratio of the blob
	*	See .cpp file
	*/
	double getBlobRatio();

	/*
	* Gets the mass(amount of pixels) of the blob
	*/
	int getMass(){ return _pixelCount; };

	/**
	*	Gets the width of the bounding box
	*/
	int getBoundingBoxWidth(){ return (_biggestX - _smallestX); };

	/**
	*	Gets the height of the bounding box
	*/
	int getBoundingBoxHeight(){ return (_biggestY - _smallestY); };

	/**
	*	Gets the width of the actual blob
	*	See .cpp file
	*/
	int getBlobWidth();

	/**
	*	Gets the height of the actual blob
	*	See .cpp file
	*/
	int getBlobHeight();

	/**
	*	Gets the smallest Y
	*/
	int getSmallestY() { return _smallestY; };

	/**
	*	Gets the biggest Y
	*/
	int getBiggestY() { return _biggestY; };

	/**
	*	Gets the smallest X
	*/
	int getSmallestX() { return _smallestX; };

	/**
	*	Gets the biggest X
	*/
	int getBiggestX() { return _biggestX; };

	/**
	*	Sets the cornerpoints for the blob
	*/
	void setCornerPoints(std::vector<int> points) { _cornerPoints = points; };

	/**
	*	Gets the cornerpoints for the blob
	*/
	std::vector<int> getCornerPoints(){ return _cornerPoints; };

	/**
	*	Find cornerPoints
	*/
	void findCornerPoints(std::vector< std::vector<int> > blobMap);

};

#endif