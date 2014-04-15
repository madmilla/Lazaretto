#pragma once
#include <vector>


struct NeuronLayer
{
friend class NeuralNetwork;
 
public:
	NeuronLayer(unsigned int size, unsigned int connections_per_neuron, bool biasnode = false);
	~NeuronLayer();

	const bool biasnode;
	std::vector<double> output_values;
	std::vector<double> gradients;
	std::vector<std::vector<double>> weights;

private:
	// Returns the number of nodes in this layer
	unsigned int num_nodes() const { return static_cast<unsigned int>(output_values.size()); }
	// Returns the number of "mutable" nodes in this layer, i.e. without the bias node, if present
	unsigned int num_mut_nodes() const { return static_cast<unsigned int>(output_values.size() - (biasnode ? 1 : 0)); }
};

