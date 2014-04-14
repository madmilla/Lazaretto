#include "OpticalCharacterRecognition2.h"
#include <iostream>

using namespace OCR2;

SegmentedImages OpticalCharacterRecognition2::SegmentateImage(const ImageLib::ImageGray & Source) {
	return Segmentation().Apply(Source);
}

SegmentedImages OpticalCharacterRecognition2::SegmentateImage(const ImageLib::ImageRGB & Source) {
	ImageLib::ImageGray GrayImage = *GrayScale(Source).get();

	return Segmentation().Apply(GrayImage);
}

std::string OpticalCharacterRecognition2::ReadLicencePlate(const SegmentedImages & Source) {
	std::string Licence;
	for (int i = 0; i < Source.size(); i++) {
		Licence += ReadCharacter(Source[i]);
	}
	return Licence;
}

std::string OpticalCharacterRecognition2::ReadLicencePlate(const ImageLib::ImageGray & Source) {
	//std::cout << "\n  Segmenting Characters" << std::endl;

	SegmentedImages Characters = Segmentation().Apply(Source);

	//std::cout << "\n    Found " << Characters.size() << " Characters" << std::endl;

	//for (int i = 0; i < Characters.size(); i++) {
	//	ImageLib::saveImg(Characters[i], file->GetFileName() + "[" + std::to_string(i + 1) + "].bmp" );
	//}

	//std::cout << "\n  Reading Characters" << std::endl;
	//std::cout << "\n    StaticOCR + HistogramOCR + IntersectionOCR:" << std::endl;

	std::string Licence = ReadLicencePlate(Characters);

	//std::cout << "    Read: " << Licence << std::endl;

	return Licence;
}

char OpticalCharacterRecognition2::ReadCharacter(const ImageLib::ImageGray & Source) {
	char c;

	c = StaticOCR().Apply(Source);

	if (c == '#')
		c = HistogramOCR().Apply(Source);

	if (c == '#')
		c = StaticOCR2().Apply(Source);

	return c;
}

void OpticalCharacterRecognition2::RunTest(const ImageLib::ImageGray & Source) {
	//Timer t = Timer();

	std::cout << "\n  Segmenting Characters" << std::endl;

	//t.Start();
	SegmentedImages Characters = Segmentation().Apply(Source);
	//t.Stop();

	//for (int i = 0; i < Characters.size(); i++) {
	//	ImageLib::saveImg(Characters[i], "Segmentation[" + std::to_string(i) + "].bmp");
	//}

	std::cout << "\n    Found " << Characters.size() << " Characters" << std::endl;
	//std::cout << "    Took: " << t.ElapsedMilliSeconds() << "ms" << std::endl;

	std::cout << "\n  Reading Characters" << std::endl;
	ReadStaticOCRLicence(Characters);
	ReadHistogramOCRLicence(Characters);
	ReadTicTacToeOCRLicence(Characters);
	ReadIntersectionOCRLicence(Characters);
	ReadStaticOCR2Licence(Characters);
}

inline std::string OpticalCharacterRecognition2::ReadStaticOCRLicence(const SegmentedImages & Source) {
	//Timer t = Timer();

	std::cout << "\n    StaticOCR:" << std::endl;
	//t.Start();
	StaticOCR OCR; std::string License("");
	for (unsigned int i = 0; i < Source.size(); i++) {
		License += OCR.Apply(Source[i]);
	}
	//t.Stop();
	std::cout << "    Read: " << License << std::endl;
	//std::cout << "    Took: " << t.ElapsedMilliSeconds() << "ms" << std::endl;

	return License;
}

inline std::string OpticalCharacterRecognition2::ReadHistogramOCRLicence(const SegmentedImages & Source) {
	//Timer t = Timer();

	std::cout << "\n    HistogramOCR:" << std::endl;
	//t.Start();
	HistogramOCR OCR; std::string License("");
	for (unsigned int i = 0; i < Source.size(); i++) {
		License += OCR.Apply(Source[i]);
	}
	//t.Stop();
	std::cout << "    Read: " << License << std::endl;
	//std::cout << "    Took: " << t.ElapsedMilliSeconds() << "ms" << std::endl;

	return License;
}

inline std::string OpticalCharacterRecognition2::ReadTicTacToeOCRLicence(const SegmentedImages & Source) {
	//Timer t = Timer();

	std::cout << "\n    TicTacToeOCR:" << std::endl;
	//t.Start();
	TicTacToeOCR OCR; std::string License("");
	for (unsigned int i = 0; i < Source.size(); i++) {
		License += OCR.Apply(Source[i]);
	}
	//t.Stop();
	std::cout << "    Read: " << License << std::endl;
	//std::cout << "    Took: " << t.ElapsedMilliSeconds() << "ms" << std::endl;

	return License;
}

inline std::string OpticalCharacterRecognition2::ReadIntersectionOCRLicence(const SegmentedImages & Source) {
	//Timer t = Timer();

	std::cout << "\n    IntersectionOCR:" << std::endl;
	//t.Start();
	IntersectionOCR OCR; std::string License("");
	for (unsigned int i = 0; i < Source.size(); i++) {
		License += OCR.Apply(Source[i]);
	}
	//t.Stop();
	std::cout << "    Read: " << License << std::endl;
	//std::cout << "    Took: " << t.ElapsedMilliSeconds() << "ms" << std::endl;

	return License;
}

inline std::string OpticalCharacterRecognition2::ReadStaticOCR2Licence(const SegmentedImages & Source) {
	//Timer t = Timer();

	std::cout << "\n    StaticOCR2:" << std::endl;
	//t.Start();
	StaticOCR2 OCR; std::string License("");
	for (unsigned int i = 0; i < Source.size(); i++) {
		License += OCR.Apply(Source[i]);
	}
	//t.Stop();
	std::cout << "    Read: " << License << std::endl;
	//std::cout << "    Took: " << t.ElapsedMilliSeconds() << "ms" << std::endl;

	return License;
}

std::unique_ptr<ImageLib::ImageGray> OpticalCharacterRecognition2::GrayScale(const ImageLib::ImageRGB & rgb_img) {
	auto gray_img = std::make_unique<ImageLib::ImageGray>(rgb_img.width(), rgb_img.height());

	// get pointers to each channel of rgb image
	auto rgb_ptrs = rgb_img.data();

	// iterate through new image
	for (std::vector<unsigned char>::iterator itr = gray_img->begin(); itr != gray_img->end(); itr++) {
		*itr = ((*rgb_ptrs.red) + (*rgb_ptrs.blue) + (*rgb_ptrs.green)) / 3;

		rgb_ptrs.red++;
		rgb_ptrs.green++;
		rgb_ptrs.blue++;
	}

	return gray_img;
}