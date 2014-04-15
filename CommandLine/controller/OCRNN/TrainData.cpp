/* Created By Stefan Hulspas
* Using some of the code from Simon Voordouw, Kevin Bosman and Harmen Klink
* 04-13-2014 version 0.2
* Cleaned up code
* Added Comments
* Added Functionallity for final product
*/
#include "TrainData.h"
#include <iostream>

TrainData::TrainData(std::string img_dir)
{
	std::srand(time(0));
	auto img_files = getFilelist(img_dir + "\\*.jpg");
	for (auto & file_name : img_files) {
		images.emplace_back(file_name, ImageLib::ImageGray(img_dir + "\\" + file_name));
	}
}

TrainData::~TrainData()
{
}

std::vector<std::string> TrainData::getFilelist(const std::string & searchkey)
{
	WIN32_FIND_DATA fd;
	HANDLE h = FindFirstFile(searchkey.c_str(), &fd);

	if (h == INVALID_HANDLE_VALUE) {
		return{}; // no files found
	}

	std::vector<std::string> ret_list;

	while (1) {
		ret_list.emplace_back(fd.cFileName);

		if (FindNextFile(h, &fd) == FALSE)
			break;
	}
	return ret_list;
}

const ImageData & TrainData::operator [] (unsigned int id) const
{
	return images[id];
}

const ImageData & TrainData::getRandom() const
{
	int id = (rand() * (int)(images.size() - 1) / RAND_MAX);
	return images[id];
}

size_t TrainData::testDataSize() const
{
	return images.size();
}

const std::vector<unsigned int> TrainData::getTopology() {
	return{ INPUT, HIDDEN, OUTPUT };
}

std::vector<double> TrainData::getInput(unsigned int testDataID)
{
	const ImageLib::ImageGray & img = images[testDataID].image;

	return getInputForImage(img);
}

std::vector<double> TrainData::getInputForImage(const ImageLib::ImageGray & img)
{
	std::vector<double> input{
		patterns.countBlackPixelsPerRowHorizontal(img, 10),
		patterns.countBlackPixelsPerRowHorizontal(img, 20),
		patterns.countBlackPixelsPerRowHorizontal(img, 30),
		patterns.countBlackPixelsPerRowHorizontal(img, 40),
		patterns.countBlackPixelsPerRowHorizontal(img, 50),
		patterns.countBlackPixelsPerRowHorizontal(img, 60),
		patterns.countBlackPixelsPerRowHorizontal(img, 70),
		patterns.countBlackPixelsPerRowHorizontal(img, 80),
		patterns.countBlackPixelsPerRowHorizontal(img, 90),

		patterns.countBlackPixelsPerLineVertical(img, 10),
		patterns.countBlackPixelsPerLineVertical(img, 20),
		patterns.countBlackPixelsPerLineVertical(img, 30),
		patterns.countBlackPixelsPerLineVertical(img, 40),
		patterns.countBlackPixelsPerLineVertical(img, 50),
		patterns.countBlackPixelsPerLineVertical(img, 60),
		patterns.countBlackPixelsPerLineVertical(img, 70),
		patterns.countBlackPixelsPerLineVertical(img, 80),
		patterns.countBlackPixelsPerLineVertical(img, 90),

		patterns.checkSymmetryVertical(img),
		patterns.checkSymmetryHorizontal(img),

		patterns.countBlackWhiteTransisitionHorizontal(img, 10),
		patterns.countBlackWhiteTransisitionHorizontal(img, 25),
		patterns.countBlackWhiteTransisitionHorizontal(img, 40),
		patterns.countBlackWhiteTransisitionHorizontal(img, 50),
		patterns.countBlackWhiteTransisitionHorizontal(img, 60),
		patterns.countBlackWhiteTransisitionHorizontal(img, 75),
		patterns.countBlackWhiteTransisitionHorizontal(img, 90),

		patterns.countBlackWhiteTransisitionVertical(img, 10),
		patterns.countBlackWhiteTransisitionVertical(img, 25),
		patterns.countBlackWhiteTransisitionVertical(img, 40),
		patterns.countBlackWhiteTransisitionVertical(img, 50),
		patterns.countBlackWhiteTransisitionVertical(img, 60),
		patterns.countBlackWhiteTransisitionVertical(img, 75),
		patterns.countBlackWhiteTransisitionVertical(img, 90),

		patterns.firstEdgeLocationLeft(img, 10),
		patterns.firstEdgeLocationLeft(img, 25),
		patterns.firstEdgeLocationLeft(img, 40),
		patterns.firstEdgeLocationLeft(img, 50),
		patterns.firstEdgeLocationLeft(img, 60),
		patterns.firstEdgeLocationLeft(img, 75),
		patterns.firstEdgeLocationLeft(img, 90),

		patterns.firstEdgeLocationRight(img, 10),
		patterns.firstEdgeLocationRight(img, 25),
		patterns.firstEdgeLocationRight(img, 40),
		patterns.firstEdgeLocationRight(img, 50),
		patterns.firstEdgeLocationRight(img, 60),
		patterns.firstEdgeLocationRight(img, 75),
		patterns.firstEdgeLocationRight(img, 90),

		patterns.firstEdgeLocationTop(img, 10),
		patterns.firstEdgeLocationTop(img, 25),
		patterns.firstEdgeLocationTop(img, 40),
		patterns.firstEdgeLocationTop(img, 50),
		patterns.firstEdgeLocationTop(img, 60),
		patterns.firstEdgeLocationTop(img, 75),
		patterns.firstEdgeLocationTop(img, 90),

		patterns.firstEdgeLocationBottom(img, 10),
		patterns.firstEdgeLocationBottom(img, 25),
		patterns.firstEdgeLocationBottom(img, 40),
		patterns.firstEdgeLocationBottom(img, 50),
		patterns.firstEdgeLocationBottom(img, 60),
		patterns.firstEdgeLocationBottom(img, 75),
		patterns.firstEdgeLocationBottom(img, 90) };

	return input;
}

// Main author: Harmen Klink
std::vector<double> TrainData::getTargetOutput(unsigned int testDataID)
{
	std::vector<double> output(36, -1.0f);

	unsigned char c = images[testDataID].getChar();

	if (c >= 47 && c < 58) {
		output[c - 48] = 1.0; // Numbers 0-9 in indices 0-9
	}
	else if (c > 64 && c < 91) {
		output[c - 55] = 1.0; // Characters A-Z in indices 10-35
	}
	else if (c > 96 && c < 123) {
		output[c - 87] = 1.0;
	}
	else if (c == '-') {
		output[36];
	}
	return output;
}

unsigned int TrainData::getNumOutputs() {
	return OUTPUT;
}

void TrainData::print(unsigned int testDataID, std::vector<double> output, unsigned int highestR, std::vector<double> target, unsigned int highestT) {
	char out = highestR < 10 ? '0' + highestR : 'A' + (highestR - 10);
	if (out > 'Z') out = '-';
	std::cout << "target char: " << images[testDataID].getChar() << "   id: " << highestT << std::endl;
	std::cout << "output char: " << out << "   id: " << highestR << std::endl;
	std::cout << "results: ";
	for (int i = 0; i < output.size(); i++) {
		std::cout << " " << output[i];
	}
	std::cout << std::endl << "targets: ";
	for (int i = 0; i < target.size(); i++) {
		std::cout << " " << target[i];
	}
	std::cout << "------------------------" << std::endl;
}