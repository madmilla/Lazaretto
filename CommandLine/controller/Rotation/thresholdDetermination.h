#include <cmath>
#include <fstream>
#include <array>
#include <numeric>
#include <ImageLoader.h>
#include <memory>

using namespace ImageLib;

#pragma once
/**
*\file tresholdDetermination.h
*
*\brief deze library bevat de tresholdDetermination klasse
*
* \class tresholdDetermination
*
* \brief deze klasse maakt het mogelijk om een afbeelding in binair zwart wit om te zetten.
*
* \author Olaf van der Kruk
* \author Benjamin Meulenberg
*
* \version 1.5
*
* \date 2014/4/3
*/

namespace ImageCorrection {
	class thresholdDetermination{

	private:
		int meanCorners, meanAllOthers, tOld, tNew;

	public:
		/** \brief maakt een tresholdDetermination object aan
		* \param c het ImageRGB object
		*/
		thresholdDetermination(){}

		/** \brief conversie functie zet de afbeelding om naar binair zwart wit
		* \return void
		*/
		std::unique_ptr<ImageGray> convert(const ImageRGB& img);

		/** \brief geeft de pixel grijswaarde (intensiteit) op die positie
		* \param x de x positie
		* \param y de y positie
		* \return unsigned int de grijswaarde
		*/
		inline unsigned int getIntensity(unsigned int pixel) {
			return (unsigned int)std::floor(0.11f * (pixel & 0xFF) + 0.59f * ((pixel >> 8) & 0xFF) + 0.30f * (pixel >> 16));
		}
		inline unsigned int convertToHex(unsigned char R, unsigned char G, unsigned char B){
			return ((unsigned int)R << 16) + ((unsigned int)G << 8) + ((unsigned int)B);
		}


	};
}