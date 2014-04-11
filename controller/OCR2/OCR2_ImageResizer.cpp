#include "OCR2_ImageResizer.h"

using namespace OCR2;

ImageLib::ImageGray ImageResizer::ScaleTo(const ImageLib::ImageGray & Image, int Size) {
	ImageLib::ImageGray ReturnImage = ImageLib::ImageGray(Size, Size);
	ImageLib::ImageGray SourceImage = PutImageIn1x1Ratio(Image);

	float Scale = (float)SourceImage.width() / (float)Size;

	for (int y = 0; y < Size; y++)
	for (int x = 0; x < Size; x++) {

		int oldX = (int)(round(Scale * (float)x + 0.0f  * (float)y));
		int oldY = (int)(round(0.0f  * (float)x + Scale * (float)y));

		if (oldX >= 0 && oldX < SourceImage.width() && oldY >= 0 && oldY < SourceImage.height())
			ReturnImage.at(x, y) = SourceImage.at(oldX, oldY);
		else
			ReturnImage.at(x, y) = 150;
	}

	return ReturnImage;
}

ImageLib::ImageGray ImageResizer::PutImageIn1x1Ratio(const ImageLib::ImageGray & Image) {
	int OldSize;
	int Size;

	if (Image.width() < Image.height()) {
		Size = Image.height();
		OldSize = Image.width();

		ImageLib::ImageGray ReturnImage = ImageLib::ImageGray(Size, Size);
		VerticalPadding(Image, ReturnImage);

		return ReturnImage;
	}
	else {
		Size = Image.width();
		OldSize = Image.height();

		ImageLib::ImageGray ReturnImage = ImageLib::ImageGray(Size, Size);
		HorizontalPadding(Image, ReturnImage);

		return ReturnImage;
	}
}

void ImageResizer::VerticalPadding(const ImageLib::ImageGray & Source, ImageLib::ImageGray & Destination) {
	int Size = Destination.width();
	int OldSize = Source.width();
	
	int Padding = (Size - OldSize) / 2;

	for (int y = 0; y < Size; y++)
	for (int x = 0; x < Padding; x++)
		Destination.at(x, y) = 255;

	for (int y = 0; y < Size; y++)
	for (int x = Padding; x < OldSize + Padding; x++)
		Destination.at(x, y) = Source.at(x - Padding, y);

	int adPadding = Padding * 2;
	if (((Size - OldSize) % 2) != 0) {
		adPadding += 1;
	}

	for (int y = 0; y < Size; y++)
	for (int x = OldSize + Padding; x < OldSize + adPadding; x++)
		Destination.at(x, y) = 255;
}

void ImageResizer::HorizontalPadding(const ImageLib::ImageGray & Source, ImageLib::ImageGray & Destination) {
	int Size = Destination.height();
	int OldSize = Source.height();

	int Padding = (Size - OldSize) / 2;

	for (int y = 0; y < Padding; y++)
	for (int x = 0; x < Size; x++)
		Destination.at(x, y) = 255;

	for (int y = Padding; y < OldSize + Padding; y++)
	for (int x = 0; x < Size; x++)
		Destination.at(x, y) = Source.at(x - Padding, y);

	int adPadding = Padding * 2;
	if (((Size - OldSize) % 2) != 0) {
		adPadding += 1;
	}

	for (int y = OldSize + Padding; y < OldSize + adPadding; y++)
	for (int x = 0; x < OldSize; x++)
		Destination.at(x, y) = 255;
}