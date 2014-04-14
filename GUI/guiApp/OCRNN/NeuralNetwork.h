#pragma once
#include <iostream>
#include "NeuronLayer.h"

#include <vector>

class NeuralNetwork
{
public:
	NeuralNetwork(const std::vector<unsigned int> topology);
	NeuralNetwork(const std::string &importFile);
	~NeuralNetwork();
	void feedForward(const std::vector<double> &input);
	void backPropagate(const std::vector<double> &target);
	const std::vector<double>& getOutput() const;
	void exportNetwork(const std::string filename) const;

	unsigned int num_layers() const { return static_cast<unsigned int>(layers.size()); }

private:
	std::vector<NeuronLayer> layers;
	double network_error;
};

