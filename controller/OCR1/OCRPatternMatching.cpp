#include "OCRPatternMatching.h"
#include "ImageLoader.h"
#include <iostream>
#include <iomanip>

inline ImageGray OCRPatternMatching::Resample(ImageGray& input, short newWidth, short newHeight)
{
	// Get a new buffer to interpolate into
	ImageGray newData = ImageGray(newWidth, newHeight);

	float scaleWidth = (float)newWidth / (float)input.width();
	float scaleHeight = (float)newHeight / (float)input.height();

	for (short cy = 0; cy < newHeight; cy++)
	{
		for (short cx = 0; cx < newWidth; cx++)
		{
			newData.at(cx, cy) = input.at((unsigned int)(cx / scaleWidth), (unsigned int)(cy / scaleHeight));
		}
	}
	return newData;
}


OCRPatternMatching::OCRPatternMatching()
{
	lastDetection = LAST_FOUND_STRIPE;
	//referenceImages = std::vector<ImageGray>(NUMBER_OF_CHARACTERS);
	for (unsigned char i = 0; i < NUMBER_OF_CHARACTERS; i++) {
		std::unique_ptr<ImageRGB> rgb = loadImg(font_directory + std::to_string(i) + ".png");
		ImageGray gray = ImageGray(rgb->width(), rgb->height());
		for (unsigned int x = 0; x < rgb->width(); x++) {
			for (unsigned int y = 0; y < rgb->height(); y++) {
				gray.at(x,y) = (unsigned char)((int)(rgb->at(x, y, Channel::Red) + rgb->at(x, y, Channel::Green) + rgb->at(x, y, Channel::Blue)) / 3);
			}
		}
		referenceImages.push_back(gray);
	}
}

std::string OCRPatternMatching::RecognizeLicenseplate(std::vector<ImageGray>& chars) {
	lastDetection = LAST_FOUND_STRIPE;
	std::string kenteken;
	unsigned char number = 0;
	for (ImageGray &character : chars) {
		unsigned char recognizedCharacter = Recognize(character);
		if (number == 0 && recognizedCharacter == '-'){
			std::cout << std::endl;
			continue;
		}
		else if (number > 7 && recognizedCharacter == '-'){
			std::cout << std::endl;
			break;
		}
		std::cout << recognizedCharacter << std::endl;
		if (kenteken.length() > 0) {
			unsigned char prevChar = kenteken.at(kenteken.length() - 1);
			if (prevChar >= '0' && prevChar <= '9' && recognizedCharacter >= 'A' && recognizedCharacter <= 'Z' && recognizedCharacter != 'O' && recognizedCharacter != 'Q')
			{
				//previous is a number and current is a letter (not O or Q).
				unsigned char recheck = Recognize(chars[number - 1]);
				if (recheck != prevChar) {
					kenteken.erase(kenteken.size() - 1, 1);
					kenteken += recheck;
					std::cout << recheck << std::endl;
				}
			}
		}
		kenteken += recognizedCharacter;
		++number;
	}
	return kenteken;
}


inline unsigned char OCRPatternMatching::Recognize(ImageGray& character) {
	float score[NUMBER_OF_CHARACTERS] = { };
	unsigned short index = 0;
	for (ImageGray& sample : referenceImages) {
		ImageGray resized = Resample(character, sample.width(), sample.height());
		//resized input image has the same size as our sample from here
		for (unsigned short h = 0; h < sample.height(); h++) {
			for (unsigned short w = 0; w < sample.width(); w++) {
				if (sample.at(w, h) == resized.at(w, h)) {
					score[index] += 1;
				}
				/*else {
					score[index] -= 2;
				}*/
			}
		}
		score[index] = (float)score[index] / (resized.width() * resized.height()) * 100; //percentage
		if (score[index] > FIND_CHAR_PERCENTAGE)
			break;
		//score[index] = score[index] / (resized.width() * resized.height());
		++index;
	}
	short highestIndex = 0;
	float highestValue = 0;
	for (unsigned char i = 0; i < NUMBER_OF_CHARACTERS; i++) {
		if (score[i] > highestValue) {
			highestValue = score[i];
			highestIndex = i;
		}
	}

	unsigned char charIndex;
	if (highestIndex < CHAR_INDEX_SIZE) {
		//letter
		charIndex = highestIndex + ASCII_CONVERT_LETTER;
	}
	else if (highestIndex == CHAR_INDEX_SIZE) {
		//-
		charIndex = highestIndex + ASCII_CONVERT_STRIPE;
	}
	else {
		//number
		charIndex = highestIndex + ASCII_CONVERT_NUMBER;
	}
	char output = (charIndex & 0xff);
	if (output == '-')
		lastDetection = LAST_FOUND_STRIPE;
	else {
		if (highestIndex < CHAR_INDEX_SIZE && lastDetection == LAST_FOUND_NUMBER && (output == 'O' || output == 'Q')) {
			//found letter O or Q and our last detection was number
			//not possible
			output = '0';
		}
		else if (highestIndex > CHAR_INDEX_SIZE && lastDetection == LAST_FOUND_LETTER && output == '0') {
			//found number 0 and our last detection was letter
			//not possible
			if (score[O_INDEX] > score[Q_INDEX]) 
				output = 'O';
			else 
				output = 'Q';
		}
		else if (highestIndex < CHAR_INDEX_SIZE && lastDetection == LAST_FOUND_NUMBER && output == 'S') {
			//found letter S and our last detection was number
			//not possible
			output = '5';
		}
		else if (highestIndex > CHAR_INDEX_SIZE && lastDetection == LAST_FOUND_LETTER && output == '5') {
			//found number 5 and our last detection was letter
			//not possible
			output = 'S';
		}
		else if (highestIndex < CHAR_INDEX_SIZE && lastDetection == LAST_FOUND_NUMBER && output == 'B') {
			//found letter B and our last detection was number
			//not possible
			output = '8';
		}
		else if (highestIndex > CHAR_INDEX_SIZE && lastDetection == LAST_FOUND_LETTER && output == '8') {
			//found number 8 and our last detection was letter
			//not possible
			output = 'B';

		}
		else if (highestIndex < CHAR_INDEX_SIZE && lastDetection == LAST_FOUND_NUMBER && output == 'I') {
			//found letter I and our last detection was number
			//not possible
			output = '1';
		}
		else if (highestIndex > CHAR_INDEX_SIZE && lastDetection == LAST_FOUND_LETTER && output == '1') {
			//found number 1 and our last detection was letter
			//not possible
			output = 'I';
		}
		else {
			if (highestIndex < CHAR_INDEX_SIZE) {
				//set last found to letter
				lastDetection = LAST_FOUND_LETTER;
			}
			else {
				//set last found to number
				lastDetection = LAST_FOUND_NUMBER;
			}
		}
	}
	std::cout << std::setprecision(4) <<std::fixed << highestValue << "%\t";
	return output;
}