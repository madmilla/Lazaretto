#include "../Rotation/Matrix6x6.h"
#include <ostream>
#include <iostream>
#include <iomanip>

using namespace ImageCorrection;

//! Matrix used to store the coordinates of the license plate in the original image
float matrix[6][6] = { { 0, 0, 1, 0, 0, 0 },
{ 0, 0, 1, 0, 0, 0 },
{ 0, 0, 1, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 1 },
{ 0, 0, 0, 0, 0, 1 },
{ 0, 0, 0, 0, 0, 1 } };

//! Matrix used to store the inverse matrix that is calculated by the calculateInverse()-method.
float imatrix[6][6] = { { 0, 0, 1, 0, 0, 0 },
{ 0, 0, 1, 0, 0, 0 },
{ 0, 0, 1, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 1 },
{ 0, 0, 0, 0, 0, 1 },
{ 0, 0, 0, 0, 0, 1 } };



//! Matrix used to store the coefficients for the transformation matrix. The last three values are always 0,0,1 .
float returnMatrix[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 1 };


Matrix6x6::Matrix6x6(int x1, int y1, int x2, int y2, int x3, int y3)
{
	/*
	{{x1,y1, 1, 0, 0, 0},
	{x2,y2, 1, 0, 0, 0},
	{x3,y3, 1, 0, 0, 0},
	{ 0, 0, 0,x1,y1, 1},
	{ 0, 0, 0,x2,y2, 1},
	{ 0, 0, 0,x3,y3, 1}}
	*/
	matrix[0][0] = (float)x1;
	matrix[0][1] = (float)y1;
	matrix[1][0] = (float)x2;
	matrix[1][1] = (float)y2;
	matrix[2][0] = (float)x3;
	matrix[2][1] = (float)y3;

	matrix[3][3] = (float)x1;
	matrix[3][4] = (float)y1;
	matrix[4][3] = (float)x2;
	matrix[4][4] = (float)y2;
	matrix[5][3] = (float)x3;
	matrix[5][4] = (float)y3;

}

void Matrix6x6::calculateInverse(){

	/*
	The Matrix is stored in the following way:	https://www.wolframalpha.com/input/?i=%7B%7Ba%2Cb%2C1%2C0%2C0%2C0%7D%2C+%7Bc%2Cd%2C1%2C0%2C0%2C0%7D%2C+%7Be%2Cf%2C1%2C0%2C0%2C0%7D%2C+%7B0%2C0%2C0%2Ca%2Cb%2C1%7D%2C+%7B0%2C0%2C0%2Cc%2Cd%2C1%7D%2C+%7B0%2C0%2C0%2Ce%2Cf%2C1%7D%7D
	{{a,b,1,0,0,0},
	{c,d,1,0,0,0},
	{e,f,1,0,0,0},
	{0,0,0,a,b,1},
	{0,0,0,c,d,1},
	{0,0,0,e,f,1}}
	*/
	float a = matrix[0][0];
	float b = matrix[0][1];

	float c = matrix[1][0];
	float d = matrix[1][1];

	float e = matrix[2][0];
	float f = matrix[2][1];

	//std::cout << a << "\t"<< b<< "\t" << c<< "\t" << d<< "\t" << e<< "\t" << f << "\n"; // << "\t"
	//std::cout <<(f-d)/(b*(c-e)+d*e-c*f+a*(f-d));
	imatrix[0][0] = (f - d) / (b*(c - e) + d*e - c*f + a*(f - d));
	imatrix[0][1] = (b - f) / (b*c - f*c - a*d - b*e + d*e + a*f);
	imatrix[0][2] = (b - d) / (-d*e + b*(e - c) + a*(d - f) + c*f);

	imatrix[1][0] = (c - e) / (b*c - f*c - a*d - b*e + d*e + a*f);
	imatrix[1][1] = (a - e) / (-d*e + b*(e - c) + a*(d - f) + c*f);
	imatrix[1][2] = (a - c) / (b*c - f*c - a*d - b*e + d*e + a*f);

	imatrix[2][0] = (d*c - c*f) / (b*c - f*c - a*d - b*e + d*e + a*f);
	imatrix[2][1] = (b*e - a*f) / (-d*e + b*(e - c) + a*(d - f) + c*f);
	imatrix[2][2] = (b*c - a*d) / (b*c - f*c - a*d - b*e + d*e + a*f);

	imatrix[3][3] = imatrix[0][0];
	imatrix[3][4] = imatrix[0][1];
	imatrix[3][5] = imatrix[0][2];

	imatrix[4][3] = imatrix[1][0];
	imatrix[4][4] = imatrix[1][1];
	imatrix[4][5] = imatrix[1][2];

	imatrix[5][3] = imatrix[2][0];
	imatrix[5][4] = imatrix[2][1];
	imatrix[5][5] = imatrix[2][2];

	/*
	for(int i = 0; i<6;i++){
	for(int ii =0 ; ii<6;ii++){
	std::cout << imatrix[i][ii] << "\t";//<<"imatrix["<<i<<"]["<<ii<<"] = "
	}
	std::cout << "\n";
	}
	*/


}

float *Matrix6x6::calculateCoeff(int x1, int y1, int x2, int y2, int x3, int y3){
	returnMatrix[0] = imatrix[0][0] * (float)x1 + imatrix[0][1] * (float)x2 + imatrix[0][2] * (float)x3;
	returnMatrix[1] = imatrix[1][0] * (float)x1 + imatrix[1][1] * (float)x2 + imatrix[1][2] * (float)x3;
	returnMatrix[2] = imatrix[2][0] * (float)x1 + imatrix[2][1] * (float)x2 + imatrix[2][2] * (float)x3;
	returnMatrix[3] = imatrix[3][3] * (float)y1 + imatrix[3][4] * (float)y2 + imatrix[3][5] * (float)y3;
	returnMatrix[4] = imatrix[4][3] * (float)y1 + imatrix[4][4] * (float)y2 + imatrix[4][5] * (float)y3;
	returnMatrix[5] = imatrix[5][3] * (float)y1 + imatrix[5][4] * (float)y2 + imatrix[5][5] * (float)y3;
	return returnMatrix;
}

Matrix6x6::~Matrix6x6(void)
{
}

