/*
*
*	Author: Mike Schaap
*/

#ifndef BlobDetection_H
#define BlobDetection_H

#include "../Localization/Blob.h"
#include "Image.h"
#include "../Localization/BlobCheck.h"

#include <string>
#include <iostream>
#include <list>
#include <ImageLib.h>

class BlobDetection {
private:
public:
	BlobDetection();
	std::vector<Blob> Invoke(ImageLib::ImageRGB & image, int minBlobSize);
};

#endif