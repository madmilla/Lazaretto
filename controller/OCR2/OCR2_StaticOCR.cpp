#include "OCR2_StaticOCR.h"
#include "OCR2_ImageResizer.h"

using namespace OCR2;

#define marge 12.0f
#define MAX_ITERATIONS 15
#define extra_marge .2f

StaticOCR::StaticOCR() {

}

char StaticOCR::Apply(const ImageLib::ImageGray & Img) {
	ImageLib::ImageGray Image = ImageResizer::ScaleTo(Img, 60);
	//ImageLib::saveImg(Image, "Resized.bmp");

	int imageWidth = Image.width();
	int imageHeight = Image.height();
	int blockHeight = imageHeight / 3;
	int blockWidth = imageWidth / 3;
	float pixelCount = 0;
	//Loop through all the percentage blocks of the image.
	for (int blockY = 0; blockY < 3; blockY++) {
		for (int blockX = 0; blockX < 3; blockX++) {
			//Loop trough a single block
			for (int imageY = blockHeight * blockY; imageY < blockHeight * (blockY + 1); imageY++) {
				for (int imageX = blockWidth * blockX; imageX < blockWidth * (blockX + 1); imageX++) {
					//Check wether the pixelvalue is black.
					if (Image.at(imageX, imageY) < 80) {
						//If so increase the pixelcount
						pixelCount++;
					}
				}
			}
			//Calculate the percentage and store it in the blockpercentage array.
			percentages[blockX + (blockY * 3)] = (pixelCount / (blockHeight * blockWidth) * 100);
			pixelCount = 0;
		}
	}

	char c;
	for (int i = 0; i < MAX_ITERATIONS; i++) {
		c = compareAllBlocks(marge + (i * extra_marge));

		if (c != '#')
			break;
	}

	return c;

}

bool StaticOCR::compareWithBlock(std::array<float, 9> block, float mrg) {
	char count = 0;
	//Loop through all the blocks
	for (int i = 0; i < block.size(); i++) {
		//Check wether the percentages in the blocks are the same or almost the same.
		if ((percentages[i] >= (block[i] - mrg)) && (percentages[i] <= (block[i] + mrg))) {
			//If so increase count.
			count++;
		}
	}
	//If count equals 9 then all blocks are the same and true is returned.
	if (count == 9) {
		return true;
	} else{
		return false;
	}
}

char StaticOCR::compareAllBlocks(float mrg) {

	if (compareWithBlock(ZERO, mrg)) {
		return '0';
	}
	else if (compareWithBlock(ONE, mrg)) {
		return '1';
	}
	else if (compareWithBlock(TWO, mrg)) {
		return '2';
	}
	else if (compareWithBlock(THREE, mrg)) {
		return '3';
	}
	else if (compareWithBlock(FOUR, mrg)) {
		return '4';
	}
	else if (compareWithBlock(FIVE, mrg)) {
		return '5';
	}
	else if (compareWithBlock(SIX, mrg)) {
		return '6';
	}
	else if (compareWithBlock(SEVEN, mrg)) {
		return '7';
	}
	else if (compareWithBlock(EIGHT, mrg)) {
		return '8';
	}
	else if (compareWithBlock(NINE, mrg)) {
		return '9';
	}
	else if (compareWithBlock(A, mrg)) {
		return 'A';
	}
	else if (compareWithBlock(B, mrg)) {
		return 'B';
	}
	else if (compareWithBlock(C, mrg)) {
		return 'C';
	}
	else if (compareWithBlock(D, mrg)) {
		return 'D';
	}
	else if (compareWithBlock(E, mrg)) {
		return 'E';
	}
	else if (compareWithBlock(F, mrg)) {
		return 'F';
	}
	else if (compareWithBlock(G, mrg)) {
		return 'G';
	}
	else if (compareWithBlock(H, mrg)) {
		return 'H';
	}
	else if (compareWithBlock(I, mrg)) {
		return 'I';
	}
	else if (compareWithBlock(J, mrg)) {
		return 'J';
	}
	else if (compareWithBlock(K, mrg)) {
		return 'K';
	}
	else if (compareWithBlock(L, mrg)) {
		return 'L';
	}
	else if (compareWithBlock(M, mrg)) {
		return 'M';
	}
	else if (compareWithBlock(N, mrg)) {
		return 'N';
	}
	else if (compareWithBlock(O, mrg)) {
		return 'O';
	}
	else if (compareWithBlock(P, mrg)) {
		return 'P';
	}
	else if (compareWithBlock(Q, mrg)) {
		return 'Q';
	}
	else if (compareWithBlock(R, mrg)) {
		return 'R';
	}
	else if (compareWithBlock(S, mrg)) {
		return 'S';
	}
	else if (compareWithBlock(T, mrg)) {
		return 'T';
	}
	else if (compareWithBlock(U, mrg)) {
		return 'U';
	}
	else if (compareWithBlock(V, mrg)) {
		return 'V';
	}
	else if (compareWithBlock(W, mrg)) {
		return 'W';
	}
	else if (compareWithBlock(X, mrg)) {
		return 'X';
	}
	else if (compareWithBlock(Y, mrg)) {
		return 'Y';
	}
	else if (compareWithBlock(Z, mrg)) {
		return 'Z';
	}
	else if (compareWithBlock(DASH1, mrg) || compareWithBlock(DASH2, mrg)) {
		return '-';
	}
	else {
		return '#';
	}
}

StaticOCR::~StaticOCR() {

}