#include "../Rotation/imageCorrection.h"

using namespace ImageCorrection;

std::unique_ptr<ImageGray> imageCorrection::correct(const ImageRGB& img){
	////START BUILDING MATRIX////
	float theMatrix[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
	float * oldCoordinates = coordinates;

	float gayCoordinates[3];
	CalcHorizonLine(oldCoordinates, gayCoordinates);

	theMatrix[6] = gayCoordinates[0];
	theMatrix[7] = gayCoordinates[1];
	theMatrix[8] = gayCoordinates[2];

	//cout << "Werkt met: " << theMatrix[6] << " " << theMatrix[7] << " " << theMatrix[8] << endl;
	////END BUILDING MATRIX////

	////START NEW COORDINATES////
	float newCoordinates[8];
	float tempCoordinates[2];
	matrix m;
	for (int i = 0; i<8; i += 2) {
		m.calcMatrix(theMatrix, (int)oldCoordinates[i], (int)oldCoordinates[i + 1], 1, tempCoordinates);
		newCoordinates[i] = tempCoordinates[0];
		newCoordinates[i + 1] = tempCoordinates[1];
		//cout << "Resultaat: " << tempCoordinates[0] << " " << tempCoordinates[1] << endl;
	}
	////END NEW COORDINATES////

	Matrix6x6 m6 = Matrix6x6((int)newCoordinates[0], (int)newCoordinates[1], (int)newCoordinates[4], (int)newCoordinates[5], (int)newCoordinates[6], (int)newCoordinates[7]);
	m6.calculateInverse();
	float * theCoefs = m6.calculateCoeff(0, 0, 0, 110, 520, 110);

	float *resultMatrix = m.getMultMatrix(theCoefs, theMatrix);

	imageTransform k = imageTransform(resultMatrix);
	auto newImage = k.convert(img);
	thresholdDetermination t = thresholdDetermination();
	auto treshold = t.convert(*newImage);
	return treshold;

}