#include "NeuronLayer.h"

using namespace std;

// Author: Harmen Klink
// Co-author: Simon Voordouw
NeuronLayer::NeuronLayer(unsigned int size, unsigned int connections_per_neuron, bool biasnode)
: biasnode(biasnode), gradients(size)
{
	for (unsigned int i = 0; i < size; ++i) {
		weights.emplace_back(connections_per_neuron, rand() / double(RAND_MAX)); //Random weight of range - 1 to 1
		output_values.push_back(0);
	}

	if (biasnode) {
		output_values.push_back(1);
		weights.emplace_back(connections_per_neuron, rand() / double(RAND_MAX));
		gradients.emplace_back(0);
	}
}


NeuronLayer::~NeuronLayer()
{
}
