#include "NeuralNetworkOCR.h"
#include "CheckPatterns.h"



std::string NeuralNetworkOCR::recognise(const std::vector<ImageGray> &images) {
	std::string text = "";
	for (unsigned int i = 0; i < images.size(); ++i) {
		neural_network.feedForward(getInputsFromImage(images[i]));
		text += outputToChar(neural_network.getOutput());
	}
	return text;
}

std::vector<double> NeuralNetworkOCR::getInputsFromImage(const ImageLib::ImageGray & img)
{
	std::vector<double> input{
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
	patterns.firstEdgeLocationBottom(img, 90) };

	return input;
}


char NeuralNetworkOCR::outputToChar(const std::vector<double> output) {
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