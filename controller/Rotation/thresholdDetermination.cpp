#include "../Rotation/thresholdDetermination.h"
#include <iostream>

using namespace ImageCorrection;

std::unique_ptr<ImageGray> thresholdDetermination::convert(const ImageRGB& img){
	std::unique_ptr<ImageGray> returnImage = std::make_unique<ImageGray>(img.width(), img.height());
	meanCorners = (getIntensity(convertToHex(img.at(0, 0).red, img.at(0, 0).green, img.at(0, 0).blue)) + getIntensity(convertToHex(img.at(img.width() - 1, 0).red, img.at(img.width() - 1, 0).green, img.at(img.width() - 1, 0).blue)) + getIntensity(convertToHex(img.at(0, img.height() - 1).red, img.at(0, img.height() - 1).green, img.at(0, img.height() - 1).blue))) + getIntensity(convertToHex(img.at(img.width() - 1, img.height() - 1).red, img.at(img.width() - 1, img.height() - 1).green, img.at(img.width() - 1, img.height() - 1).blue)) / 4;
	meanAllOthers = 0;

	for (int h = 0; h < img.height(); ++h) {
		for (int w = 0; w < img.width(); ++w) {

			if (!((w == 0 && h == 0) || (w == img.width() - 1 && h == 0) || (w == 0 && h == img.height() - 1) || (w == img.width() - 1 && h == img.height() - 1))) {
				meanAllOthers += getIntensity(convertToHex(img.at(w, h).red, img.at(w, h).green, img.at(w, h).blue));
			}

		}
	}

	meanAllOthers /= ((img.width()*img.height()) - 4);

	tOld = 0;
	tNew = (meanCorners + meanAllOthers) / 2;


	unsigned int u1count = 0, u2count = 0;

	while (tNew != tOld) {

		meanAllOthers = 0;
		meanCorners = 0;
		for (int h = 0; h < img.height(); ++h) {
			for (int w = 0; w < img.width(); ++w) {


				if (getIntensity(convertToHex(img.at(w, h).red, img.at(w, h).green, img.at(w, h).blue)) < tNew){
					meanCorners += getIntensity(convertToHex(img.at(w, h).red, img.at(w, h).green, img.at(w, h).blue));
					u1count++;
				}
				else if (getIntensity(convertToHex(img.at(w, h).red, img.at(w, h).green, img.at(w, h).blue)) >= tNew){
					meanAllOthers += getIntensity(convertToHex(img.at(w, h).red, img.at(w, h).green, img.at(w, h).blue));
					u2count++;
				}

			}
		}

		meanCorners /= u1count;
		meanAllOthers /= u2count;
		u1count = 0;
		u2count = 0;
		tOld = tNew;
		tNew = (meanCorners + meanAllOthers) / 2;

	}

	for (int h = 0; h < returnImage->height(); ++h) {
		for (int w = 0; w < returnImage->width(); ++w) {

			if (getIntensity(convertToHex(img.at(w, h).red, img.at(w, h).green, img.at(w, h).blue)) < tNew){
				returnImage->at(w, h) = 0;
			}
			else if (getIntensity(convertToHex(img.at(w, h).red, img.at(w, h).green, img.at(w, h).blue)) >= tNew){
				returnImage->at(w, h) = 255;
			}

		}
	}

	return returnImage;

}