/* Created By Stefan Hulspas
* Using some of the code from Simon Voordouw and Kevin Bosman
* 04-13-2014 version 0.2
* Cleaned up code
* Added Comments
* Added Functionallity for final product
*/
#pragma once
#include <string>
#include <ctime>
#include <vector>
#include <windows.h>
#include <ImageLib.h>
#include "CheckPatterns.h"

#define INPUT 62
#define HIDDEN 60
#define OUTPUT 37

struct ImageData
{
	std::string filename;
	ImageLib::ImageGray image;
	ImageData(std::string fln, ImageLib::ImageGray img)
		: filename(fln), image(img) {}

	char getChar() const {
		char c = filename.front();
		return (c > 96 && c < 123) ? c - 32 : c;
	}
};

class TrainData
{
private:
	//List of test data images
	std::vector<ImageData> images;
	//All possible patters
	CheckPatterns patterns;
	//Left over operator from Simon Voordouw
	//Not really needed as noone but this class should be able to acces the images
	const ImageData & operator [] (unsigned int id) const;
	//Left over method from Simon Voordouw
	//Not needed as random is created in the trainers
	const ImageData & getRandom() const;
	//Method to get all the possible images in the directory
	std::vector<std::string> getFilelist(const std::string & searchkey);
public:
	//Constructor taking the directory of all the test images
	TrainData(std::string img_dir);
	//Method to get Topology of the NN to sync inputsize and outputsize
	const std::vector<unsigned int> getTopology();
	//Method to give the number of images to the trainer should he need it
	size_t testDataSize() const;
	//Method to create the correct input for the given testdata ID
	std::vector<double> getInput(unsigned int testDataID);
	//Method to create the correct input for a custom image which can be put into the trainer
	std::vector<double> getInputForImage(const ImageLib::ImageGray & image);
	//Method to create the correct output for the given testdata ID
	std::vector<double> getTargetOutput(unsigned int i);
	//Get number of outputs
	unsigned int getNumOutputs();
	//Method to print data from the NN
	//Because the trainer doesn't know what hes putting in the NN or whats supposed to come out
	void print(unsigned int testDataID, std::vector<double> output, unsigned int highestR, std::vector<double> target, unsigned int highestT);
	//Method to get the file name of the image with the testdataID
	inline std::string getFileName(unsigned int testDataID){ return images[testDataID].filename; };
	~TrainData();
};

