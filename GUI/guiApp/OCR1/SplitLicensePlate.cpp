#include "SplitLicensePlate.h"
#include "ImageGray.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <memory.h>
#define MINIMAL_CHARACTER_WIDTH 5

using namespace ImageLib;

SplitLicensePlate::SplitLicensePlate(ImageGray& img) : image(img)
{
	//image = std::move(img);
	width = img.width();
	height = img.height();
	imageSurface = width * height;
}

inline void SplitLicensePlate::RemoveLicenseplateBorder() {
	unsigned int heightLimit = image.height() / 2;
	unsigned int widthLimit = image.width() / 2;
	unsigned int leastPixels = 99999;
	unsigned int leastYTop = 0;
	for (unsigned int y = 0; y < heightLimit; y++) {
		unsigned int count = 0;
		for (unsigned int x = 0; x < image.width(); x++) {
			if (image.at(x, y) == 0)
				count++;
		}
		if (count < leastPixels)
		{
			leastPixels = count;
			leastYTop = y;
		}
	}
	leastPixels = 99999;
	unsigned int leastYBottom = 0;
	for (unsigned int y = image.height() - 1; y > heightLimit; y--) {
		unsigned int count = 0;
		for (unsigned int x = 0; x < image.width(); x++) {
			if (image.at(x, y) == 0)
				count++;
		}
		if (count < leastPixels)
		{
			leastPixels = count;
			leastYBottom = y;
		}
	}
	//clean top and bottom stripe
	for (unsigned int y = 0; y < leastYTop; y++) {
		for (unsigned int x = 0; x < image.width(); x++) {
			image.at(x, y) = 255;
		}
	}
	for (unsigned int y = image.height() - 1; y > leastYBottom; y--) {
		for (unsigned int x = 0; x < image.width(); x++) {
			image.at(x, y) = 255;
		}
	}
	leastPixels = 99999;
	unsigned int leastXLeft = 0;
	for (unsigned int x = 0; x < widthLimit; x++) {
		unsigned int count = 0;
		for (unsigned int y = 0; y < image.height(); y++) {
			if (image.at(x, y) == 0)
				count++;
		}
		if (count < leastPixels)
		{
			leastPixels = count;
			leastXLeft = x;
		}
	}
	leastPixels = 99999;
	unsigned int leastXRight = 0;
	for (unsigned int x = image.width() - 1; x > widthLimit; x--) {
		unsigned int count = 0;
		for (unsigned int y = 0; y < image.height(); y++) {
			if (image.at(x, y) == 0)
				count++;
		}
		if (count < leastPixels)
		{
			leastPixels = count;
			leastXRight = x;
		}
	}
	//clean left and right stripe
	for (unsigned int x = 0; x < leastXLeft; x++) {
		for (unsigned int y = 0; y < image.height(); y++) {
			image.at(x, y) = 255;
		}
	}
	for (unsigned int x = image.width() - 1; x > leastXRight; x--) {
		for (unsigned int y = 0; y < image.height(); y++) {
			image.at(x, y) = 255;
		}
	}
}

std::vector<ImageGray> SplitLicensePlate::SplitImage()
{
	RemoveLicenseplateBorder();
	std::vector<ImageGray> splitimage;

	const int findArea = 20;/////// 8 karakters + 12 vlekkeen op het kenteken die los van de characters zitten is er mogelijk voor worst case.
	int borderLeft[findArea];
	int borderRight[findArea];
	short countL = 0, countR = 0, areaFound = 0, above = 0, under = 0;
	csvVertical();
	for (short i = 1; i < height; i++){
		if (csvDataV[i] == 0){
			continue;
		}
		else{
			if (csvDataV[i - 1] == 0) // vergelijking met de pixel ervoor.
			{
				above = i;
				continue;
			}
			else if (i + 1 < height){
				if (csvDataV[i + 1] == 0){
					under = i;
					break;
				}
			}
		}
	}
	csvHorizontal();
	for (short i = 0; i < width; i++){
		if (csvDataH[i] == 0) {
			continue;
		}
		if (i == 0) // eerste run
		{
			borderLeft[countL] = i;
			countL++;
		}
		else {
			
			if (i < (width - 1)) { //not last index
				if (csvDataH[i - 1] == 0 && csvDataH[i + 1] != 0) { // vergelijking met de pixel ervoor. zorg dat het niet 1 pixel breed is (ruis)
					borderLeft[countL] = i;
					countL++;
					continue;
				}
				else if (csvDataH[i + 1] == 0 && csvDataH[i - 1] != 0) { // vergelijking met de pixel erna
					borderRight[countR] = i + 1;
					countR++;
					areaFound++;
				}
			}

		}
	}
	for (int z = 0; z < areaFound; z++){
		if (under == 0)
			under = image.height() - 1;
		int splitWidth = borderRight[z] - borderLeft[z];
		//check character width
		if (splitWidth <= MINIMAL_CHARACTER_WIDTH)
			continue;
		int splitHeight = under - above;
		int shiftUp = 0;
		//int shiftHeight = under;
		//slice more white spaces in top and bottom of the character
		for (int j = above; j < under; j++){
			bool blackFound = false;
			for (int i = borderLeft[z]; i < borderRight[z]; i++){
				blackFound = image.at(i, j) == 0 ? true : false;
				if (blackFound) 
					break;
			}
			if (blackFound)
			{
				if (shiftUp == 0)
					shiftUp = j - above;
			}
			/*else {
				if (shiftUp != 0) {	
					//black was already found at least one time. Now only white detected. This means we found white under the char
					shiftHeight = j;
					break;
				}
			}*/
		}
		//slicing corrected
		ImageGray character = ImageGray(splitWidth, (splitHeight - shiftUp));//(shiftHeight - above - shiftUp));
		for (int j = (above + shiftUp); j < under; j++){ //shiftHeight
			for (int i = borderLeft[z]; i < borderRight[z]; i++){
				int xSplit = (i - borderLeft[z]);
				int ySplit = (j - (above + shiftUp));
				unsigned char& pixel = character.at(xSplit, ySplit);
				pixel = image.at(i, j);
			}
		}
		splitimage.push_back(character);
	}
	return splitimage;
}

void SplitLicensePlate::WriteCSV(int x, int y)
{
	std::ofstream CSVWriter;
	if (x == 0 && y == 0){
		std::string path = "C:\\Images\\Split_Histogram.csv";
		CSVWriter.open(path);
		for (int i = 0; i < width; i++)
		{
			int normalized = ((int)csvDataH[i]);
			CSVWriter << i << ";" << normalized << "\n";
		}
		CSVWriter.close();
	}
	else if (x == 1){
		std::string path = "C:\\Images\\horizontal_histogram";
		path += std::to_string(y);
		path += ".csv";
		CSVWriter.open(path);
		for (int i = 0; i < width; i++)
		{
			float normalized = ((float)csvDataH[i]);
			CSVWriter << i << ";" << normalized << "\n";
		}
		CSVWriter.close();
	}
	else if (x == 2){
		std::string path = "C:\\Images\\vertical_histogram";
		path += std::to_string(y);
		path += ".csv";
		CSVWriter.open(path);
		for (int i = 0; i < height; i++)
		{
			float normalized = ((float)csvDataV[i]);
			CSVWriter << i << ";" << normalized << "\n";
		}
		CSVWriter.close();
	}
}

std::vector<int> SplitLicensePlate::csvHorizontal(){
	csvDataH = std::vector<int>(width);
	for (int i = 0; i < width; i++){
		csvDataH[i] = 0;
	}
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			unsigned char whiteOrBlack = image.at(i, j);
			if (whiteOrBlack == 0){
				csvDataH[i] += 1;
			}
		}
	}
	return csvDataH;
}

std::vector<int> SplitLicensePlate::csvVertical(){
	csvDataV = std::vector<int>(height);
	for (int i = 0; i < height; i++){
		csvDataV[i] = 0;
	}
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			unsigned char whiteOrBlack = image.at(j, i);
			if (whiteOrBlack == 0){
				csvDataV[i] += 1;
			}
		}
	}
	return csvDataV;
}
