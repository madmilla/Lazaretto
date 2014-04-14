#include "OCR2_IntersectionOCR.h"
#include "OCR2_ImageResizer.h"

using namespace OCR2;

#define LINECOUNT 5
#define THRESHOLD 127

IntersectionOCR::IntersectionOCR() {
	for (int i = 1; i <= LINECOUNT; i++) {
		IndexesH[i - 1] = i * 10;
		IndexesV[i - 1] = i * 10;
	}
}

IntersectionOCR::~IntersectionOCR() { }

char IntersectionOCR::Apply(const ImageLib::ImageGray & Image) {
	ImageLib::ImageGray Img = ImageResizer::ScaleTo(Image, 60);

	// Reset Value's
	ResetIntersections();

	// Check intersections
	CheckHorizontalIntersections(Img);
	CheckVerticalIntersections(Img);

	// Compare
	char c = CheckCharacters();

	return c;
}

inline char IntersectionOCR::CheckCharacters() {
	if (CompareIntersections(Intersections0))
		return '0';

	if (CompareIntersections(Intersections1))
		return '1';

	if (CompareIntersections(Intersections2))
		return '2';

	if (CompareIntersections(Intersections3))
		return '3';

	if (CompareIntersections(Intersections4))
		return '4';

	if (CompareIntersections(Intersections5))
		return '5';

	if (CompareIntersections(Intersections6))
		return '6';

	if (CompareIntersections(Intersections7))
		return '7';

	if (CompareIntersections(Intersections8))
		return '8';

	if (CompareIntersections(Intersections9))
		return '9';

	if (CompareIntersections(IntersectionsA))
		return 'A';

	if (CompareIntersections(IntersectionsB))
		return 'B';

	if (CompareIntersections(IntersectionsC))
		return 'C';

	if (CompareIntersections(IntersectionsD))
		return 'D';

	if (CompareIntersections(IntersectionsE))
		return 'E';

	if (CompareIntersections(IntersectionsF))
		return 'F';

	if (CompareIntersections(IntersectionsG))
		return 'G';

	if (CompareIntersections(IntersectionsH))
		return 'H';

	if (CompareIntersections(IntersectionsI))
		return 'I';

	if (CompareIntersections(IntersectionsJ))
		return 'J';

	if (CompareIntersections(IntersectionsK))
		return 'K';

	if (CompareIntersections(IntersectionsL))
		return 'L';

	if (CompareIntersections(IntersectionsM))
		return 'M';

	if (CompareIntersections(IntersectionsN))
		return 'N';

	if (CompareIntersections(IntersectionsO))
		return 'O';

	if (CompareIntersections(IntersectionsP))
		return 'P';

	if (CompareIntersections(IntersectionsQ))
		return 'Q';

	if (CompareIntersections(IntersectionsR))
		return 'R';

	if (CompareIntersections(IntersectionsS))
		return 'S';

	if (CompareIntersections(IntersectionsT))
		return 'T';

	if (CompareIntersections(IntersectionsU))
		return 'U';

	if (CompareIntersections(IntersectionsV))
		return 'V';

	if (CompareIntersections(IntersectionsW))
		return 'W';

	if (CompareIntersections(IntersectionsX))
		return 'X';

	if (CompareIntersections(IntersectionsY))
		return 'Y';

	if (CompareIntersections(IntersectionsZ))
		return 'Z';

	return '#';
}

inline bool IntersectionOCR::CompareIntersections(const ReferenceIntersections & Reference) {
	bool b = true;

	for (int i = 0; i < LINECOUNT; i++) {
		if (Intersections.HorizontalIntersections[i] != Reference.HorizontalIntersections[i]) b = false;
		if (Intersections.VerticalIntersections[i] != Reference.VerticalIntersections[i]) b = false;
	}

	return b;
}

inline void IntersectionOCR::CheckHorizontalIntersections(const ImageLib::ImageGray & Img) {
	bool CurrentlyWhite;
	int counter;
	
	for (int i = 0; i < LINECOUNT; i++) {
		CurrentlyWhite = true;
		counter = 0;

		for (int x = 0; x < Img.width(); x++) {
			unsigned char PixelValue = Img.at(x, IndexesH[i]);

			if (PixelValue > THRESHOLD && !CurrentlyWhite) {
				counter++;

				if (counter > 3) {
					CurrentlyWhite = true;
					counter = 0;
				}
			}
			else if (PixelValue < THRESHOLD && CurrentlyWhite) {
				counter++;

				if (counter > 3) {
					Intersections.HorizontalIntersections[i]++;
					CurrentlyWhite = false;
					counter = 0;
				}
			}

		}
	}
}

inline void IntersectionOCR::CheckVerticalIntersections(const ImageLib::ImageGray & Img) {
	bool CurrentlyWhite;
	int counter;

	for (int i = 0; i < LINECOUNT; i++) {
		CurrentlyWhite = true;
		counter = 0;

		for (int y = 0; y < Img.height(); y++) {
			unsigned char PixelValue = Img.at(IndexesV[i], y);

			if (PixelValue > THRESHOLD && !CurrentlyWhite) {
				counter++;

				if (counter > 3) {
					CurrentlyWhite = true;
					counter = 0;
				}
			}
			else if (PixelValue < THRESHOLD && CurrentlyWhite) {
				counter++;

				if (counter > 3) {
					Intersections.VerticalIntersections[i]++;
					CurrentlyWhite = false;
					counter = 0;
				}
			}

		}
	}
}

inline void IntersectionOCR::ResetIntersections() {
	for (int i = 0; i < LINECOUNT; i++) {
		Intersections.HorizontalIntersections[i] = 0;
		Intersections.VerticalIntersections[i] = 0;
	}
}

