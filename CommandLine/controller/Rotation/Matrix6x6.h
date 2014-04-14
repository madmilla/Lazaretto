/**
* \class Matrix6x6
* \brief Class used for calculating the inverse of a 6x6 matrix.
*
*
* \author Jelmer Bootsma, Olaf van der Kruk
* \version 2
* \date $Date: 2014/04/07 14:16:20 $
*/
#include <ostream>
#pragma once


namespace ImageCorrection {
	class Matrix6x6
	{
	public:
		//! Constructor, takes three coordinates of the license plate as integers, in (x,y).
		/*!
		\param x1 an integer argument representing the X-coordinate of the top left corner.
		\param y1 an integer argument representing the Y-coordinate of the top left corner.
		\param x2 an integer argument representing the X-coordinate of the bottom left corner.
		\param y2 an integer argument representing the Y-coordinate of the bottom left corner.
		\param x3 an integer argument representing the X-coordinate of the bottom right corner.
		\param y3 an integer argument representing the Y-coordinate of the bottom right corner.
		*/
		Matrix6x6(int x1, int y1, int x2, int y2, int x3, int y3);

		//! Calculates the inversematrix of the provided 6x6matrix.
		void Matrix6x6::calculateInverse();

		//! Calculates the transformation matrix based on the inversematrix and the target coordinates.
		/*! This function takes 6 arguments, being the three coordinates representing the three target-coordinates for mapping the new image.
		\param x1 an integer argument representing the X-coordinate of the top left corner.
		\param y1 an integer argument representing the Y-coordinate of the top left corner.
		\param x2 an integer argument representing the X-coordinate of the bottom left corner.
		\param y2 an integer argument representing the Y-coordinate of the bottom left corner.
		\param x3 an integer argument representing the X-coordinate of the bottom right corner.
		\param y3 an integer argument representing the Y-coordinate of the bottom right corner.
		\return The array with 9 coefficients that make up the transformation needed
		*/
		float* Matrix6x6::calculateCoeff(int x1, int y1, int x2, int y2, int x3, int y3);
		//! Default deconstructor.
		~Matrix6x6(void);
	};
}