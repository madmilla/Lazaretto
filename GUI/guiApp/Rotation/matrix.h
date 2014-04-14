/**
* \class Matrix
* \brief Class used for calculating the inverse of a 3x3 matrix.
*	This class is used to perform some basic matrix operations: Multiply and Inverse.
*
* \author Olaf van der Kruk, Ben Meulenberg
* \version 1
* \date $Date: 2014/04/07 14:16:20 $
*/

#pragma once
#include <iostream>

using namespace std;

namespace ImageCorrection {
	class matrix {

	private:

		float returnArray[3], returnMatrix[9];

	public:
		//! Default Constructor.
		matrix(void);
		//! Default Deconstructor.
		~matrix(void);

		//! Calculates a new matrix by multiplying a provided matrix with a (1,3) matrix, and stores it in a provided target array.
		/*!
		\param matrixArray The Matrix used to multiply, provided as a float[9] array.
		\param x Integer representing the X-coefficient
		\param y Integer representing the Y-coefficient
		\param w Integer representing the W-coefficient
		*/
		void calcMatrix(float *matrixArray, int x, int y, int w, float *target);

		//! Calculates a new matrix by multiplying two provided 3x3 matrices.
		/*!
		\param matrixArray The Matrix used to multiply, provided as a float[9] array.
		\param a The first array as a float[9] array.
		\param b The second array as a float[9] array.
		\return The resulting matrix as a float[9] array.
		*/
		float *getMultMatrix(float *a, float *b);

		//! Calculates the inverse matrix of a provided 3x3 matrix.
		/*!
		\param matrixArray The Matrix used to multiply, provided as a float[9] array.
		\param a The provided array as a float[9] array.
		\return The resulting matrix as a float[9] array.
		*/
		float *getInverseMatrix(float *givenMatrix);

	};
}