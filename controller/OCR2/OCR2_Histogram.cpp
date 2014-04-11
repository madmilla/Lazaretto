#include "OCR2_Histogram.h"
#include <fstream>

using namespace OCR2;

// create type's for clearer code
typedef unsigned char Byte;
typedef ImageLib::Rgb<const Byte &> ConstPixelRef;
typedef std::vector<Byte>::const_iterator const_iterator;

// threshold used when creating horizontal / vertical histogram
#define THRESHOLD 127

Histogram::Histogram(int Length) {
	if (Length < 0) _Length = 0;
	else _Length = Length;

	_Histogram = new float[_Length];
	ResetValues();
}

Histogram::~Histogram() {
	delete[] _Histogram;
}

void Histogram::Save(const std::string & FileName) {
	std::ofstream HistogramStream(FileName + ".csv");

	for (int i = 0; i < _Length; i++)
		HistogramStream << i << ", " << _Histogram[i] << std::endl;

	HistogramStream.close();
}

void Histogram::CreateColorHistogram(const ImageLib::ImageRGB & Img) {
	ResetValues();

	int GrayVal;
	for (unsigned int x = 0; x < Img.width(); x++) {
		for (unsigned int y = 0; y < Img.height(); y++) {
			ConstPixelRef Pix = Img.at(x, y);
			GrayVal = (int)(
				(.2126f * Pix.red) +
				(.7152f * Pix.green) +
				(.0722f * Pix.blue));

			_Histogram[GrayVal]++;
		}
	}

	for (int i = 0; i < _Length; i++)
		_Histogram[i] /= Img.size();
}

void Histogram::CreateVerticalHistogram(const ImageLib::ImageGray & Img) {
	ResetValues();
	
	int Height = Img.height();
	int Width = Img.width();

	int counter = 0;
	for (const_iterator itr = Img.cbegin(); itr != Img.cend(); itr++, counter++)
		if ((*itr) < THRESHOLD) _Histogram[counter % Width]++;

	for (int i = 0; i < _Length; i++)
		_Histogram[i] /= (float)Height;

}

void Histogram::CreateHorizontalHistogram(const ImageLib::ImageGray & Img) {
	ResetValues();

	int Height = Img.height();
	int Width = Img.width();

	int NextLine = Width;
	int CollumnCounter = 0;

	int counter = 0;
	for (const_iterator itr = Img.cbegin(); itr != Img.cend(); itr++, counter++) {
		if ((counter % Width) == 0) CollumnCounter++;

		if ((*itr) < THRESHOLD) _Histogram[CollumnCounter]++;
	}

	for (int i = 0; i < _Length; i++)
		_Histogram[i] /= (float)Width;
}

float Histogram::MinValue() {
	float Value = 1.0f;

	for (int i = 0; i < _Length; i++)
		if (_Histogram[i] < Value) Value = _Histogram[i];

	return Value;
}

float Histogram::MaxValue() {
	float Value = 0.0f;

	for (int i = 0; i < _Length; i++)
		if (_Histogram[i] > Value) Value = _Histogram[i];

	return Value;
}

inline void Histogram::ResetValues() {
	for (int i = 0; i < _Length; i++) _Histogram[i] = 0;
}