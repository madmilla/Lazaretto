#include "../Rotation/matrix.h"

using namespace ImageCorrection;

matrix::matrix(void) {
}

matrix::~matrix(void) {
}

void matrix::calcMatrix(float *givenMatrix, int x, int y, int w, float *target) {

	float newX = (x*givenMatrix[0]) + (y*givenMatrix[1]) + (w*givenMatrix[2]);
	float newY = (x*givenMatrix[3]) + (y*givenMatrix[4]) + (w*givenMatrix[5]);
	float newW = (x*givenMatrix[6]) + (y*givenMatrix[7]) + (w*givenMatrix[8]);

	target[0] = ((newX / newW));
	target[1] = ((newY / newW));
	//target[2] = newW;

}
float *matrix::getMultMatrix(float *a, float *b){

	//http://stackoverflow.com/questions/5670596/multiplying-two-3x3-matrices-in-c

	int i, j, k;
	int count = 0;
	float een[3][3], ander[3][3];
	float terug[3][3] = { 0 };


	for (i = 0; i<3; ++i) {
		for (j = 0; j<3; ++j) {
			een[i][j] = a[count++];
		}
	}
	count = 0;
	for (i = 0; i<3; ++i) {
		for (j = 0; j<3; ++j) {
			ander[i][j] = b[count++];
		}
	}
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			for (k = 0; k < 3; k++)
			{
				terug[i][j] += een[i][k] * ander[k][j];
			}
		}
	}
	count = 0;
	//cout<<"multiplied matrix"<<endl;
	for (i = 0; i<3; ++i) {
		for (j = 0; j<3; ++j) {
			//cout<<terug[i][j]<<"\t";
			returnMatrix[count++] = terug[i][j];
		}
		//cout<<endl;
	}
	return returnMatrix;
}

float *matrix::getInverseMatrix(float *givenMatrix) {

	//http://www.wikihow.com/Inverse-a-3X3-Matrix
	//code to calculate inverse matrix "stolen" from: http://forgetcode.com/C/1781-Inverse-Matrix-of-3x3

	float calcMatrix[3][3], determinant = 0;
	int i, j, count = 0;
	/*
	cout << "givenMatrix is:" << endl;
	for (i=0; i<9; ++i) {

	//cout << givenMatrix[i] << "\t";

	if ((i != 0) && ((i+1)%3 == 0)) {
	cout << endl;
	}

	}
	*/
	for (i = 0; i<3; ++i) {
		for (j = 0; j<3; ++j) {
			calcMatrix[i][j] = givenMatrix[count++];
		}
	}

	for (i = 0; i<3; ++i) {
		determinant += (calcMatrix[0][i] * (calcMatrix[1][(i + 1) % 3] * calcMatrix[2][(i + 2) % 3] - calcMatrix[1][(i + 2) % 3] * calcMatrix[2][(i + 1) % 3]));
	}

	//cout << "Determinant: " << determinant << endl;

	if (determinant != 0) {

		count = 0;

		//cout << "Inverse of givenMatrix is:" << endl;
		for (i = 0; i<3; ++i) {
			for (j = 0; j<3; ++j) {
				returnMatrix[count++] = ((calcMatrix[(j + 1) % 3][(i + 1) % 3] * calcMatrix[(j + 2) % 3][(i + 2) % 3]) - (calcMatrix[(j + 1) % 3][(i + 2) % 3] * calcMatrix[(j + 2) % 3][(i + 1) % 3])) / determinant;
				//cout << returnMatrix[count-1] << "\t";
			}
			//cout << endl;
		}

		return returnMatrix;

	}
	else {
		//cout << "The givenMatrix has no inverse.." << endl;

		return returnMatrix;
	}
}