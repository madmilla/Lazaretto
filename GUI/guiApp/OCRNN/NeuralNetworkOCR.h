#pragma once
#include <string>
#include "ImageLib.h"
#include "NeuralNetwork.h"
#include "CheckPatterns.h"

class NeuralNetworkOCR
{
private:
	NeuralNetwork neural_network;
	CheckPatterns patterns;

	std::vector<double> getInputsFromImage(const ImageLib::ImageGray & img);
	char outputToChar(const std::vector<double> output);

public:
	NeuralNetworkOCR();
	//~NeuralNetworkOCR();

	std::string recognise(const std::vector<ImageGray> &images);
};
