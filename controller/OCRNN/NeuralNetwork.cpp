#include "NeuralNetwork.h"
#include <fstream>
#include <sstream>
#define TRAINING_RATE 0.2f


using namespace std;

// Author: Harmen Klink
// Co-author: Simon Voordouw
NeuralNetwork::NeuralNetwork(const std::vector<unsigned int> topology)
{
	// Every element in the topology vector represents a layer, the value of each element is the amount of neurons in that layer
	for (unsigned int layer = 0; layer < topology.size() - 1; layer++) {
		layers.emplace_back(topology[layer], topology[layer + 1], true);
	}
	layers.emplace_back(topology.back(), 0);
}
// Author: Kevin Bosman
// Co-author: Harmen Klink
NeuralNetwork::NeuralNetwork(const std::string &importFile) {
	std::ifstream importDataFile;
	importDataFile.open(importFile.c_str());
	std::string line;
	std::string label;

	// Read topology
	std::vector<unsigned> topology;

	getline(importDataFile, line);
	std::stringstream ss(line);
	ss >> label;
	if (importDataFile.eof() || label.compare("topology:") != 0) {
		abort();
	}

	while (!ss.eof()) {
		unsigned n;
		ss >> n;
		topology.push_back(n);
	}

	// Create Net
	// Every element in the topology vector represents a layer, the value of each element is the amount of neurons in that layer
	for (unsigned int layer = 0; layer < static_cast<unsigned int>(topology.size() - 1); layer++) {
		layers.emplace_back(topology[layer], topology[layer + 1], true);
	}
	layers.emplace_back(topology.back(), 0);

	// Set weights
	while (getline(importDataFile, line)) {
		// Read line
		//std::cout << line << std::endl;
		std::stringstream ss(line);

		// Read layer and neuron number
		unsigned layerNumber, neuronNumber;
		ss >> label;
		ss >> layerNumber;
		ss >> label;
		ss >> neuronNumber;
		// Assign weights
		double weight;
		for (unsigned int weight_i = 0; ss >> weight; ++weight_i){
			layers[layerNumber].weights[neuronNumber][weight_i] = weight;
		}
	}
}




NeuralNetwork::~NeuralNetwork()
{
}

// Author: Harmen Klink
// Co-author: Simon Voordouw
void NeuralNetwork::feedForward(const vector<double> &input) {
	// Set input values of input neurons
	if (input.size() != layers[0].num_nodes() - 1) {
		throw new std::runtime_error("Wrong size input vector");
	}

	for (unsigned int i = 0; i < layers[0].num_nodes() - 1; i++) {
		layers[0].output_values[i] = input[i];
	}

	// loop through layers after input layer
	for (unsigned int layer_i = 1; layer_i < num_layers(); ++layer_i) {
		// loop through every neuron of current layer except bias neuron
		NeuronLayer & current_layer = layers[layer_i];

		for (unsigned int current_neuron = 0; current_neuron < current_layer.num_mut_nodes(); ++current_neuron) {
			// Sum all the connections to this neuron from the previous layer
			double sum = 0.0;
			const NeuronLayer & previous_layer = layers[layer_i - 1];
			// Loop through all connections from the previous layer to this neuron	
			for (unsigned int input_neuron = 0; input_neuron < previous_layer.num_nodes(); ++input_neuron) {
				sum += previous_layer.output_values[input_neuron] * previous_layer.weights[input_neuron][current_neuron];
			}
			current_layer.output_values[current_neuron] = tanh(sum);
		};
	}
}

// Author: Harmen Klink
void NeuralNetwork::backPropagate(const std::vector<double> &target) {
	NeuronLayer &output_layer = layers.back();
	for (unsigned int neuron = 0; neuron < output_layer.num_mut_nodes(); ++neuron) { // NO BIAS NEURON IN OUTPUT LAYER ANYMORE????
		double neuron_error = target[neuron] - output_layer.output_values[neuron]; // Calculate neuron error
		//Calculate gradient for this output neuron by multiplying the neuron error with the derivative of the outputvalue of tanh
		output_layer.gradients[neuron] = neuron_error * (1 - (tanh(output_layer.output_values[neuron]) * tanh(output_layer.output_values[neuron])));
	}

	// Calculate hidden layer(s) neuron gradients
	for (unsigned int layer = static_cast<unsigned int>(layers.size() - 2); layer != 0; --layer) {
		NeuronLayer & current_layer = layers[layer];
		for (unsigned int current_neuron = 0; current_neuron < current_layer.num_nodes(); ++current_neuron) {
			
			double sum = 0.0; // Sum of this neuron's contribution to the errors of the next layer
			for (unsigned int next_neuron = 0; next_neuron < layers[layer + 1].num_mut_nodes(); ++next_neuron) {
				sum += layers[layer].weights[current_neuron][next_neuron] * layers[layer + 1].gradients[next_neuron];
			}
			layers[layer].gradients[current_neuron] = sum * (1 - (tanh(current_layer.output_values[current_neuron]) * tanh(current_layer.output_values[current_neuron])));
		}
	}

	// Update weights in all layers
	for (unsigned int layer = static_cast<unsigned int>(layers.size() - 1); layer != 0; --layer) {
		const NeuronLayer & current_layer = layers[layer];
		NeuronLayer & previous_layer = layers[layer - 1];
		for (unsigned int input_neuron = 0; input_neuron < previous_layer.num_nodes(); ++input_neuron) {
			for (unsigned int current_neuron = 0; current_neuron < current_layer.num_nodes() - 1; ++current_neuron) {
				previous_layer.weights[input_neuron][current_neuron] += TRAINING_RATE * previous_layer.output_values[input_neuron] * current_layer.gradients[current_neuron];
			}
		}
	}
}

// Author: Harmen Klink
const vector<double>& NeuralNetwork::getOutput() const {
	return layers.back().output_values;
}

// Author: Kevin Bosman
// Co-author: Harmen Klink
void NeuralNetwork::exportNetwork(const std::string filename) const {
	std::ofstream exportDataFile;
	exportDataFile.open(filename.c_str());

	// Topology
	exportDataFile << "topology:";
	for (unsigned int l = 0; l < static_cast<unsigned int>(layers.size()); l++) {
		exportDataFile << " " << layers[l].num_mut_nodes();
	}
	exportDataFile << std::endl;

	// Layer loop
	for (unsigned l = 0; l < layers.size() - 1; l++) {
		//exportDataFile << "layer:" << l << std::endl;
		const NeuronLayer &currentLayer = layers[l];
		// Neuron in layer loop
		for (unsigned n = 0; n < layers[l].num_nodes(); n++) {
			exportDataFile << "layer: " << l << " " << "neuron: " << n;
			const std::vector<double> &currentNeuronConnections = currentLayer.weights[n];
			// Weights loop
			for (unsigned w = 0; w < static_cast<unsigned int>(currentNeuronConnections.size()); w++) {
				exportDataFile << " " << currentNeuronConnections[w];
			}
			exportDataFile << std::endl;
		}
	}
}