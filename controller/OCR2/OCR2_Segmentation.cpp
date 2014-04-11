#include "OCR2_Segmentation.h"
#include "OCR2_Histogram.h"

using namespace OCR2;

#define MARGE .09f

typedef std::vector<unsigned char>::iterator iterator;

Segmentation::Segmentation() { }
Segmentation::~Segmentation() { }

SegmentedImages Segmentation::Apply(const ImageLib::ImageGray & Img) {
	XIndexes IndexX = GetXIndexes(Img);
	YIndexes IndexY = GetYIndexes(Img);

	return CreateImages(Img, IndexX, IndexY);
}

inline Segmentation::XIndexes Segmentation::GetXIndexes(const ImageLib::ImageGray & Img) {
	Histogram VerticalHistogram(Img.width());
	VerticalHistogram.CreateVerticalHistogram(Img);
	//VerticalHistogram.Save("VerticalHistogram");
	 
	XIndexes Indexes;
	bool LookingForX1 = true;
	float MinValueX = VerticalHistogram.MinValue() + MARGE;

	for (int i = 0; i < VerticalHistogram.Length(); i++) {
		if (VerticalHistogram[i] > MinValueX && LookingForX1) {
			
			// Filter left side of licence plate (NL)
			//if (i < (Img.width() / 10))
			//	continue;

			Indexes.X1.push_back(i);
			LookingForX1 = false;
		}
		else if (VerticalHistogram[i] < MinValueX && !LookingForX1) {
			Indexes.X2.push_back(i);
			LookingForX1 = true;
		}
	}

	if (Indexes.X2.size() < Indexes.X1.size())
		Indexes.X2.push_back(Img.width());

	return Indexes;
}

inline Segmentation::YIndexes Segmentation::GetYIndexes(const ImageLib::ImageGray & Img) {
	Histogram HorizontalHistogram(Img.height());
	HorizontalHistogram.CreateHorizontalHistogram(Img);
	//HorizontalHistogram.Save("HorizontalHistogram");

	YIndexes Indexes;
	bool LookingForY1 = true;
	float MinValueY = HorizontalHistogram.MinValue() + MARGE;

	for (int i = 0; i < HorizontalHistogram.Length(); i++) {
		if (HorizontalHistogram[i] > MinValueY && LookingForY1) {
			Indexes.Y1.push_back(i);
			LookingForY1 = false;
		}
		else if (HorizontalHistogram[i] < MinValueY && !LookingForY1) {
			Indexes.Y2.push_back(i);
			LookingForY1 = true;
		}
	}

	if (Indexes.Y1.size() == 0) Indexes.Y1.push_back(0);
	if (Indexes.Y2.size() == 0) Indexes.Y2.push_back(Img.height());

	if (Indexes.Y2.size() < Indexes.Y1.size())
		Indexes.Y2.push_back(Img.height());

	return Indexes;
}

inline SegmentedImages Segmentation::CreateImages(const ImageLib::ImageGray & Img, const Segmentation::XIndexes & IndexX, const Segmentation::YIndexes & IndexY) {
	int NewWidth = 0;
	int NewHeight = 0;

	int HeightIndex;
	for (int i = 0; i < IndexY.Y1.size(); i++) {
		if (NewHeight < (IndexY.Y2[i] - IndexY.Y1[i])) {
			NewHeight = IndexY.Y2[i] - IndexY.Y1[i];
			HeightIndex = i;
		}
	}

	SegmentedImages Images;
	int CharacterCount = IndexX.X1.size();
	int ImageIndex = 0;
	for (int i = 0; i < CharacterCount; i++) {
		NewWidth = IndexX.X2[i] - IndexX.X1[i];

		if (NewWidth < (Img.width() / 41))
			continue;
		
		Images.push_back(ImageLib::ImageGray(NewWidth, NewHeight));

		for (int y = 0; y < NewHeight; y++)
		for (int x = 0; x < NewWidth; x++)
			Images[ImageIndex].at(x, y) = Img.at(x + IndexX.X1[i], y + IndexY.Y1[HeightIndex]);

		ImageIndex++;
	}

	return Images;
}