#include "OCR2_HistogramOCR.h"

using namespace OCR2;

#define DEFAULT_MARGE		.15f
#define MARGE_INCREMENT		.01f
#define MAX_OCR_ITERATIONS	10

HistogramOCR::HistogramOCR() { }
HistogramOCR::~HistogramOCR() { }

char HistogramOCR::Apply(const ImageLib::ImageGray & Img) {
	Histogram VerticalHistogram = Histogram(Img.width());
	VerticalHistogram.CreateVerticalHistogram(Img);
	//VerticalHistogram.Save("Vertical");

	Histogram HorizontalHistogram = Histogram(Img.height());
	HorizontalHistogram.CreateHorizontalHistogram(Img);
	//HorizontalHistogram.Save("Horizontal");

	//Get 5 Average value's
	int HistMarge = Img.width() / 5;

	Averages Average;
	for (int i = 0; i < 5; i++) {
		Average.Vertical[i] = 0.0f;
		Average.Horizontal[i] = 0.0f;
	}

	for (int i = 0; i < 5; i++) {

		for (int q = HistMarge * i; q < HistMarge * (i + 1); q++) {
			try {
				Average.Vertical[i] += VerticalHistogram[q];
				Average.Horizontal[i] += HorizontalHistogram[q];
			}
			catch (std::out_of_range) { }
		}

		Average.Vertical[i] /= HistMarge;
		Average.Horizontal[i] /= HistMarge;
	}

	// Compare value's
	char ResultChar;
	for (int i = 0; i < MAX_OCR_ITERATIONS; i++) {
		ResultChar = CheckCharacters(Average, DEFAULT_MARGE + (i * MARGE_INCREMENT));
		
		if (ResultChar != '#')
			break;
	}

	return ResultChar;
}

inline char HistogramOCR::CheckCharacters(const Averages Average, float Marge) {
	if (CompareAverages(Average, PerfectChar0, Marge))
		return '0';

	else if (CompareAverages(Average, PerfectChar1, Marge))
		return '1';

	else if (CompareAverages(Average, PerfectChar2, Marge))
		return '2';

	else if (CompareAverages(Average, PerfectChar3, Marge))
		return '3';

	else if (CompareAverages(Average, PerfectChar4, Marge))
		return '4';

	else if (CompareAverages(Average, PerfectChar5, Marge))
		return '5';

	else if (CompareAverages(Average, PerfectChar6, Marge))
		return '6';

	else if (CompareAverages(Average, PerfectChar7, Marge))
		return '7';

	else if (CompareAverages(Average, PerfectChar8, Marge))
		return '8';

	else if (CompareAverages(Average, PerfectChar9, Marge))
		return '9';

	else if (CompareAverages(Average, PerfectCharA, Marge))
		return 'A';

	else if (CompareAverages(Average, PerfectCharB, Marge))
		return 'B';

	else if (CompareAverages(Average, PerfectCharC, Marge))
		return 'C';

	else if (CompareAverages(Average, PerfectCharD, Marge))
		return 'D';

	else if (CompareAverages(Average, PerfectCharE, Marge))
		return 'E';

	else if (CompareAverages(Average, PerfectCharF, Marge))
		return 'F';

	else if (CompareAverages(Average, PerfectCharG, Marge))
		return 'G';

	else if (CompareAverages(Average, PerfectCharH, Marge))
		return 'H';

	else if (CompareAverages(Average, PerfectCharI, Marge))
		return 'I';

	else if (CompareAverages(Average, PerfectCharJ, Marge))
		return 'J';

	else if (CompareAverages(Average, PerfectCharK, Marge))
		return 'K';

	else if (CompareAverages(Average, PerfectCharL, Marge))
		return 'L';

	else if (CompareAverages(Average, PerfectCharM, Marge))
		return 'M';

	else if (CompareAverages(Average, PerfectCharN, Marge))
		return 'N';

	else if (CompareAverages(Average, PerfectCharO, Marge))
		return 'O';

	else if (CompareAverages(Average, PerfectCharP, Marge))
		return 'P';

	else if (CompareAverages(Average, PerfectCharQ, Marge))
		return 'Q';

	else if (CompareAverages(Average, PerfectCharR, Marge))
		return 'R';

	else if (CompareAverages(Average, PerfectCharS, Marge))
		return 'S';

	else if (CompareAverages(Average, PerfectCharT, Marge))
		return 'T';

	else if (CompareAverages(Average, PerfectCharU, Marge))
		return 'U';

	else if (CompareAverages(Average, PerfectCharV, Marge))
		return 'V';

	else if (CompareAverages(Average, PerfectCharW, Marge))
		return 'W';

	else if (CompareAverages(Average, PerfectCharX, Marge))
		return 'X';

	else if (CompareAverages(Average, PerfectCharY, Marge))
		return 'Y';

	else if (CompareAverages(Average, PerfectCharZ, Marge))
		return 'Z';

	else if (CompareAverages(Average, PerfectCharDash1, Marge) ||
			 CompareAverages(Average, PerfectCharDash2, Marge))
		return '-';

	else
		return '#';
}

inline bool HistogramOCR::CompareAverages(const Averages & current, const PerfectAverages & perfect, float Marge) {
	bool b = true;

	for (int i = 0; i < 5; i++) {
		if (!(current.Horizontal[i] >= (perfect.Horizontal[i] - Marge) && current.Horizontal[i] <= (perfect.Horizontal[i] + Marge))) b = false;
		if (!(current.Vertical[i] >= (perfect.Vertical[i] - Marge) && current.Vertical[i] <= (perfect.Vertical[i] + Marge))) b = false;
	}

	return b;
}
