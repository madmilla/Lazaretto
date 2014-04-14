#include "NeuralNetworkOCR.h"
#include "CheckPatterns.h"
#include "ImageList.h"


NeuralNetworkOCR::NeuralNetworkOCR() 
: neural_network(std::vector<unsigned int>{58, 80, 36})
{
}

NeuralNetworkOCR::NeuralNetworkOCR(const std::string & importFile)
: neural_network(importFile)
{

}

NeuralNetworkOCR::~NeuralNetworkOCR()
{
}

std::pair<char, double> NeuralNetworkOCR::convert(const ImageGray & img)
{
	auto input = img_to_input(img);

	neural_network.feedForward(input);

	// TODO: calculate percentage

	return { output_to_char(neural_network.getOutput()), 1.0f };
}

const std::vector<double> & NeuralNetworkOCR::output_nodes() const
{
	return neural_network.getOutput();
}

void NeuralNetworkOCR::train(const ImageList & images, int passes)
{
	for (int pass = 0; pass < passes; pass++) {
		auto img_data = images.getRandom();

		auto input = img_to_input(img_data.image);

		neural_network.feedForward(input);

		neural_network.backPropagate(char_to_output(img_data.getChar()));
	}
}

std::vector<double> NeuralNetworkOCR::img_to_input(const ImageGray & img)
{
	std::vector<double> input {
		patterns.countBlackPixelsPerRowHorizontal(img, 10),
		patterns.countBlackPixelsPerRowHorizontal(img, 25),
		patterns.countBlackPixelsPerRowHorizontal(img, 40),
		patterns.countBlackPixelsPerRowHorizontal(img, 50),
		patterns.countBlackPixelsPerRowHorizontal(img, 60),
		patterns.countBlackPixelsPerRowHorizontal(img, 75),
		patterns.countBlackPixelsPerRowHorizontal(img, 90),

		patterns.countBlackPixelsPerLineVertical(img, 10),
		patterns.countBlackPixelsPerLineVertical(img, 25),
		patterns.countBlackPixelsPerLineVertical(img, 40),
		patterns.countBlackPixelsPerLineVertical(img, 50),
		patterns.countBlackPixelsPerLineVertical(img, 60),
		patterns.countBlackPixelsPerLineVertical(img, 75),
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
		patterns.firstEdgeLocationBottom(img, 90),

		/*patterns.percentageBlack(img, 30, 30, 45, 45),
		patterns.percentageBlack(img, 40, 40, 60, 60),
		patterns.percentageBlack(img, 55, 55, 70, 70),*/
	};

	return input;
}

char NeuralNetworkOCR::output_to_char(const std::vector<double> & output)
{
	unsigned int highest = 0;
	for (unsigned int i = 1; i < output.size() - 1; ++i) {
		if (output[i] > output[highest]) {
			highest = i;
		}
	}
	if (highest < 10) {
		return highest + 48;
	}
	else {
		return highest + 55;
	}
}

std::vector<double> NeuralNetworkOCR::char_to_output(char c)
{
	std::vector<double> output(36, -1.0f);

	if (c > 47 && c < 58) {
		output[c - 48] = 1.0; // Numbers 0-9 in indices 0-9
	}
	else if (c > 64 && c < 91) {
		output[c - 55] = 1.0; // Characters A-Z in indices 10-35
	}
	else if (c > 96 && c < 123) {
		output[c - 87] = 1.0;
	}
	return output;
}

void NeuralNetworkOCR::export(std::string filename) const
{
	neural_network.exportNetwork(filename);
}