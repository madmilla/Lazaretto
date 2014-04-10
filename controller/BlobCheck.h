/*
*
*	Author: Mike Schaap
*/

#ifndef BlobCheck_H
#define BlobCheck_H

#include <iostream>
#include <vector>
#include <ImageLib.h>
#include "Blob.h"



class BlobCheck {
private:

public:
	BlobCheck();
	~BlobCheck();
	std::vector<Blob> CheckIfBlobIsLicensePlate(std::vector<Blob> &blobobjects, std::vector< std::vector<int> > blobMap);
};

#endif