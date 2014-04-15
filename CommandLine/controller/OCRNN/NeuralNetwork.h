#pragma once
#include <iostream>
#include "NeuronLayer.h"

#include <vector>

class NeuralNetwork
{
public:
	// Construct a network where every vector value is the number of nodes of that layer
	NeuralNetwork(const std::vector<unsigned int> topology);
	// Construct a network based on a previously exported network
	NeuralNetwork(const std::string &importFile);
	~NeuralNetwork();
	// Feed input values through the network
	void feedForward(const std::vector<double> &input);
	// Train the network by adjusting neuron weights using desired target output values
	void backPropagate(const std::vector<double> &target);
	// Return the current output values
	const std::vector<double>& getOutput() const;
	// Export the network topology and weights to a .txt file
	void exportNetwork(const std::string filename) const;
	// Returns the amount of layers in this network
	unsigned int num_layers() const { return static_cast<unsigned int>(layers.size()); }

private:
	std::vector<NeuronLayer> layers;
};

