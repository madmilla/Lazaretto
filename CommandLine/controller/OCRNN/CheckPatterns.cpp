/////////////////////////////////////////////////////////// 
//														 //	
//	Class: CheckPatterns.cpp 						  	 // 
//													  	 //
//	Auther's: 										  	 //
//	Thomas                    						  	 //
//  Kevin                                             	 //
//  Mitchell                                          	 //
//  Wouter                                             	 //
//	                                                   	 //
//	Date:                                              	 //
//	3-4-14'                                            	 //
//	                                                   	 //
//	Version:                                           	 //
//	V0.1.                                              	 //
//                                                       //
//	Description:                                         //
//	The CheckPatterns class consist of varius algorithm  //
//	to check numbers and characters on there paterns.    //
//                                                       //
///////////////////////////////////////////////////////////                                      

#include "CheckPatterns.h"

CheckPatterns::CheckPatterns()
{
	//bt = new BaseTimer();
}

CheckPatterns::~CheckPatterns()
{
	//delete bt;
}

// =======================================================================================

/**
* checkBlackWhiteTransisitionVertical will look for transisiton in an ImageGray on the Vertical axis. These transitions are made from
* black to white or white to black. If a transisition is detected a counter will be increased.
*
* @param  sourceImage
* @param  percentage
* @return
*/

double CheckPatterns::countBlackPixelsPerRowHorizontal(const ImageGray &sourceImage, int percentage)
{
	//bt->reset();
	//bt->start();

	if (percentage > 100)
	{
		percentage = 100;
	}
	else if (percentage < 0)
	{
		percentage = 0;
	}

	//int y = (int)(sourceImage.height() / 100.0 * percentage);
	int y = Extensions::getValueFromPercentage(sourceImage.height(), percentage);
	//int y = Extensions::getPercentage(percentage, sourceImage.height());
	int blackPixels = 0;

	auto end_ptr = sourceImage.data(0, y + 1);

	for (auto pxl_ptr = sourceImage.data(0, y); pxl_ptr < end_ptr; pxl_ptr++) {
		blackPixels += (int)(*pxl_ptr < thresholdValue);
	}

	//bt->stop();
	//std::cout << "Time for the countBlackPixelsPerRowHorizontal function: " << //bt->elapsedMicroSeconds() << " Microseconds (" << //bt->elapsedMilliSeconds() << "ms)" << std::endl;

	//return blackPixels;
	//return (int)(blackPixels / (double)(sourceImage.width()) * 100);
	//std::cout << "blackpixels: " << blackPixels << " sourceImg Width: " << sourceImage.width() << " percentage: " << Extensions::getPercentage(blackPixels, sourceImage.width()) << std::endl;
	return Extensions::getWeightFromPercentage(Extensions::getPercentage(blackPixels, sourceImage.width()));
}

/**
* checkBlackWhiteTransisitionVertical will look for transisiton in an ImageGray on the Vertical axis. These transitions are made from
* black to white or white to black. If a transisition is detected a counter will be increased.
*
* @param  sourceImage
* @param  percentage
* @return
*/

double CheckPatterns::countBlackPixelsPerLineVertical(const ImageGray &sourceImage, int percentage)
{
	//bt->reset();
	//bt->start();

	if (percentage > 100)
	{
		percentage = 100;
	}
	else if (percentage < 0)
	{
		percentage = 0;
	}

	//int x = (int)(sourceImage.width() / 100.0 * percentage);
	int x = Extensions::getValueFromPercentage(sourceImage.width(), percentage);
	int blackPixels = 0;

	auto end_ptr = sourceImage.data(x, sourceImage.height());

	for (auto pxl_ptr = sourceImage.data(x, 0); pxl_ptr < end_ptr; pxl_ptr += sourceImage.width())
	{
		blackPixels += (int)(*pxl_ptr < thresholdValue);
	}

	//bt->stop();
	//std::cout << "Time for the countBlackPixelsPerLineVertical function: " << //bt->elapsedMicroSeconds() << " Microseconds (" << //bt->elapsedMilliSeconds() << "ms)" << std::endl;

	//return blackPixels;
	//return (int)(blackPixels / (double)(sourceImage.height()) * 100);
	return Extensions::getWeightFromPercentage(Extensions::getPercentage(blackPixels, sourceImage.height()));
}

// =======================================================================================

/**
* countBlackWhiteTransisitionHorizontal will look for transisiton in an ImageGray on the horizontal axis. These transitions are made from
* black to white or white to black. If a transisition is detected a counter will be increased.
*
* @param  sourceImage
* @param  percentage
* @return
*/

double CheckPatterns::countBlackWhiteTransisitionHorizontal(const ImageGray &sourceImage, int percentage)
{
	//bt->reset();
	//bt->start();

	//int y = (int)(sourceImage.height() / 100.0 * percentage);
	int y = Extensions::getValueFromPercentage(sourceImage.height(), percentage);
	int pixelCounter = 0;
	// set oldpixel to 1 because white is 1 and every ImageGray starts with white
	int oldPixel = 1;

	auto end_ptr = sourceImage.data(0, y + 1);

	bool oldpixel = 1;

	for (auto pxl_ptr = sourceImage.data(0, y); pxl_ptr < end_ptr; pxl_ptr++) {
		bool currentPixel = (*pxl_ptr > thresholdValue);

		pixelCounter += (int)(currentPixel != oldPixel);
		oldPixel = currentPixel;
	}

	//bt->stop();
	//std::cout << "Time for the checkBlackWhiteTransision function: " << //bt->elapsedMicroSeconds() << " Microseconds (" << //bt->elapsedMilliSeconds() << "ms)" << std::endl;
	//return pixelCounter;
	return Extensions::getWeightFromPercentage(Extensions::getPercentage(pixelCounter, percentage));
}

/**
* checkBlackWhiteTransisitionVertical will look for transisiton in an ImageGray on the Vertical axis. These transitions are made from
* black to white or white to black. If a transisition is detected a counter will be increased.
*
* @param  sourceImage
* @param  percentage
* @return
*/

double CheckPatterns::countBlackWhiteTransisitionVertical(const ImageGray &sourceImage, int percentage)
{
	//bt->reset();
	//bt->start();
	int x = Extensions::getValueFromPercentage(sourceImage.width(), percentage);
	int pixelCounter = 0;
	// set oldpixel to 1 because white is 1 and every ImageGray starts with white
	int oldPixel = 1;

	auto end_ptr = sourceImage.data(x, sourceImage.height());

	bool oldpixel = 1;

	for (auto pxl_ptr = sourceImage.data(x, 0); pxl_ptr < end_ptr; pxl_ptr += sourceImage.width()) {
		bool currentPixel = (*pxl_ptr > thresholdValue);

		pixelCounter += (int)(currentPixel != oldPixel);
		oldPixel = currentPixel;
	}

	//bt->stop();
	//std::cout << "Time for the checkBlackWhiteTransision function: " << //bt->elapsedMicroSeconds() << " Microseconds (" << //bt->elapsedMilliSeconds() << "ms)" << std::endl;
	//return pixelCounter;
	return Extensions::getWeightFromPercentage(Extensions::getPercentage(pixelCounter, percentage));
}

// =======================================================================================

double CheckPatterns::checkSymmetryHorizontal(const ImageGray &sourceImage, bool boundingBox)
{
	//bt->reset();
	//bt->start();
	int numberOfBlackPixels = 0, symmetricBlackPixels = 0;
	//double percentageSymmetric;
	if (boundingBox)
	{
		int x1 = this->findLeftBlackPixel(sourceImage);
		int x2 = this->findRightBlackPixel(sourceImage);
		int y1 = this->findTopBlackPixel(sourceImage);
		int y2 = this->findBottomBlackPixel(sourceImage);
		for (int y = y2; y >= y1; y--)
		{
			for (int x = x2; x >= ((x2 - x1) / 2); x--)
			{
				if (*(sourceImage.data(x, y)) < thresholdValue)
				{
					numberOfBlackPixels++;
					if (*(sourceImage.data(sourceImage.width() - x, y)) < thresholdValue)
					{
						symmetricBlackPixels++;
					}
				}
			}
		}
	}
	else
	{
		for (int y = 0; y < sourceImage.height(); y++)
		{
			auto left_ptr = sourceImage.data(0, y);

			for (int offset = sourceImage.width() - 1; offset > 0; offset -= 2)
			{
				bool leftBlack = *left_ptr < thresholdValue;
				bool rightBlack = *(left_ptr + offset) < thresholdValue;
				//numberOfBlackPixels += leftBlack;
				bool bothBlack = leftBlack == rightBlack;
				symmetricBlackPixels += (int)bothBlack;

				left_ptr++;
			}
		}
	}
	//percentageSymmetric = ((double)symmetricBlackPixels / (double)numberOfBlackPixels)*100.0;
	//bt->stop();
	//std::cout << "Time for the checkSymmetryHorizontal function: " << //bt->elapsedMicroSeconds() << " Microseconds (" << //bt->elapsedMilliSeconds() << "ms)" << std::endl;
	//return (int)percentageSymmetric;
	return Extensions::getWeightFromPercentage(Extensions::getPercentage(symmetricBlackPixels, sourceImage.size()));
}

double CheckPatterns::checkSymmetryVertical(const ImageGray &sourceImage, bool boundingBox)
{
	//bt->reset();
	//bt->start();
	int numberOfBlackPixels = 0, symmetricBlackPixels = 0;
	//double percentageSymmetric;
	if (boundingBox)
	{
		int x1 = this->findLeftBlackPixel(sourceImage);
		int x2 = this->findRightBlackPixel(sourceImage);
		int y1 = this->findTopBlackPixel(sourceImage);
		int y2 = this->findBottomBlackPixel(sourceImage);
		for (int y = y2; y >= ((y2 - y1) / 2); y--)
		{
			for (int x = x2; x >= x1; x--)
			{
				if (*(sourceImage.data(x, y)) < thresholdValue)
				{
					numberOfBlackPixels++;
					if (*(sourceImage.data(x, sourceImage.height() - y)) < thresholdValue)
					{
						symmetricBlackPixels++;
					}
				}
			}
		}
	}
	else
	{
		for (int x = 0; x < sourceImage.width(); x++)
		{
			auto top_ptr = sourceImage.data(x, 0);

			for (int offset = sourceImage.height() - 1; offset > 0; offset -= 2)
			{
				bool topBlack = *top_ptr < thresholdValue;
				bool bottomBlack = *(top_ptr + offset) < thresholdValue;
				//numberOfBlackPixels += topBlack;
				bool bothBlack = topBlack == bottomBlack;
				symmetricBlackPixels += (int)bothBlack;

				top_ptr += sourceImage.width();
			}
		}
	}
	//percentageSymmetric = ((double)symmetricBlackPixels / (double)numberOfBlackPixels)*100.0;
	//bt->stop();
	//std::cout << "Time for the checkSymmetryVertical function: " << //bt->elapsedMicroSeconds() << " Microseconds (" << //bt->elapsedMilliSeconds() << "ms)" << std::endl;
	//return (int)percentageSymmetric;
	return Extensions::getWeightFromPercentage(Extensions::getPercentage(symmetricBlackPixels, sourceImage.size()));
}

int CheckPatterns::findLeftBlackPixel(const ImageGray &sourceImage)
{
	int xValue = sourceImage.width();
	for (int y = sourceImage.height(); y >= 0; y--)
	{
		for (int x = 0; x <= (sourceImage.width() / 2); x++)
		{
			if (*(sourceImage.data(x, y)) < thresholdValue)
			{
				if (x <= xValue){
					xValue = x;
					x = 0;
					y--;
				}
			}
		}
	}
	return xValue;
}

int CheckPatterns::findRightBlackPixel(const ImageGray &sourceImage)
{
	int xValue = 0;
	for (int y = sourceImage.height(); y >= 0; y--)
	{
		for (int x = sourceImage.width(); x >= (sourceImage.width() / 2); x--)
		{
			if (*(sourceImage.data(x, y)) < thresholdValue)
			{
				if (x >= xValue)
				{
					xValue = x;
					x = sourceImage.width();
					y--;
				}
			}
		}
	}
	return xValue;
}

int CheckPatterns::findTopBlackPixel(const ImageGray &sourceImage)
{
	int yValue = sourceImage.height();
	for (int x = sourceImage.width(); x >= 0; x--)
	{
		for (int y = (sourceImage.height() / 2); y <= sourceImage.height(); y++)
		{
			if (*(sourceImage.data(x, y)) < thresholdValue)
			{
				if (y <= yValue)
				{
					yValue = y;
					x--;
					y = 0;
				}
			}
		}
	}
	return yValue;
}

int CheckPatterns::findBottomBlackPixel(const ImageGray &sourceImage)
{
	int yValue = 0;
	for (int x = sourceImage.width(); x >= 0; x--)
	{
		for (int y = sourceImage.height(); y >= (sourceImage.height() / 2); y--)
		{
			if (*(sourceImage.data(x, y)) < thresholdValue)
			{
				if (y >= yValue)
				{
					yValue = y;
					x--;
					y = 0;
				}
			}
		}
	}
	return yValue;
};

double CheckPatterns::firstEdgeLocationLeft(const ImageGray & sourceImage, int percentage)
{
	int y = Extensions::getValueFromPercentage(sourceImage.height(), percentage);
	// set oldpixel to 1 because white is 1 and every ImageGray starts with white
	auto end_ptr = sourceImage.data(sourceImage.width(), y);

	bool oldpixel = 1;
	int x = 0;

	for (auto pxl_ptr = sourceImage.data(0, y); pxl_ptr < end_ptr; pxl_ptr++) {
		bool currentPixel = (*pxl_ptr > thresholdValue);

		if (oldpixel != currentPixel) {
			return Extensions::getWeightFromPercentage(Extensions::getPercentage(y, sourceImage.width()));
		}
		
		oldpixel = currentPixel;
		x++;
	}

	return 1.0;
}

double CheckPatterns::firstEdgeLocationRight(const ImageGray & sourceImage, int percentage)
{
	int y = Extensions::getValueFromPercentage(sourceImage.height(), percentage);
	// set oldpixel to 1 because white is 1 and every ImageGray starts with white
	auto end_ptr = sourceImage.data(0, y);

	bool oldpixel = 1;
	int x = sourceImage.width() - 1;

	for (auto pxl_ptr = sourceImage.data(sourceImage.width() - 1, y); pxl_ptr >= end_ptr; pxl_ptr--) {
		bool currentPixel = (*pxl_ptr > thresholdValue);

		if (oldpixel != currentPixel) {
			return Extensions::getWeightFromPercentage(Extensions::getPercentage(y, sourceImage.width()));
		}

		oldpixel = currentPixel;
		x--;
	}

	return 1.0;
}

double CheckPatterns::firstEdgeLocationTop(const ImageGray & sourceImage, int percentage)
{
	int x = Extensions::getValueFromPercentage(sourceImage.width(), percentage);
	// set oldpixel to 1 because white is 1 and every ImageGray starts with white
	auto end_ptr = sourceImage.data(x, sourceImage.height() - 1);

	bool oldpixel = 1;
	int y = 0;

	for (auto pxl_ptr = sourceImage.data(x, 0); pxl_ptr >= end_ptr; pxl_ptr += sourceImage.width()) {
		bool currentPixel = (*pxl_ptr > thresholdValue);

		if (oldpixel != currentPixel) {
			return Extensions::getWeightFromPercentage(Extensions::getPercentage(y, sourceImage.width()));
		}

		oldpixel = currentPixel;
		y++;
	}

	return 1.0;
}

double CheckPatterns::firstEdgeLocationBottom(const ImageGray & sourceImage, int percentage)
{
	int x = Extensions::getValueFromPercentage(sourceImage.width(), percentage);
	// set oldpixel to 1 because white is 1 and every ImageGray starts with white
	auto end_ptr = sourceImage.data(x, 0);

	bool oldpixel = 1;
	int y = sourceImage.height() - 1;

	for (auto pxl_ptr = sourceImage.data(x, sourceImage.height() - 1); pxl_ptr >= end_ptr; pxl_ptr -= sourceImage.width()) {
		bool currentPixel = (*pxl_ptr > thresholdValue);

		if (oldpixel != currentPixel) {
			return Extensions::getWeightFromPercentage(Extensions::getPercentage(y, sourceImage.width()));
		}

		oldpixel = currentPixel;
		y--;
	}

	return 1.0;
}

double CheckPatterns::percentageBlack(const ImageGray & sourceImage, int xleft, int ytop, int xright, int ybottom)
{
	std::pair<int, int> topleft = {
		Extensions::getValueFromPercentage(sourceImage.width(), xleft),
		Extensions::getValueFromPercentage(sourceImage.height(), ytop),
	};

	std::pair<int, int> bottomright = {
		Extensions::getValueFromPercentage(sourceImage.width(), xright),
		Extensions::getValueFromPercentage(sourceImage.height(), ybottom),
	};

	std::pair<int, int> size = {
		bottomright.first - topleft.first,
		bottomright.second - topleft.second
	};

	unsigned int numBlack = 0;

	auto pxl_ptr = sourceImage.data(topleft.first, topleft.second);

	for (int y = size.second; y > 0; --y) {
		for (int x = size.first; x > 0; --x) {
			numBlack += *pxl_ptr > thresholdValue;
			pxl_ptr++;
		}
		pxl_ptr += sourceImage.width() - size.first;
	}

	return Extensions::getWeightFromPercentage(Extensions::getPercentage(numBlack, size.first * size.second));
}