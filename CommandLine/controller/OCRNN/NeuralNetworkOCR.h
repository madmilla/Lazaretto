#pragma once
#include <string>
#include <utility>

#include "ImageLib.h"
#include "NeuralNetwork.h"
#include "CheckPatterns.h"
#include "ImageList.h"

using namespace ImageLib;

class NeuralNetworkOCR
{
private:
	NeuralNetwork neural_network;
	CheckPatterns patterns;

public:
	NeuralNetworkOCR();
	NeuralNetworkOCR(const std::string & importFile);
	~NeuralNetworkOCR();

	std::pair<char, double> convert(const ImageGray & img);
	void train(const ImageList & images, int passes);

	const std::vector<double> & output_nodes() const;

	char output_to_char(const std::vector<double> & v);
	std::vector<double> char_to_output(char c);
	std::vector<double> img_to_input(const ImageGray & img);

	void export(std::string filename) const;
};

