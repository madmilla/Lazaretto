#include <vector>
#include "basetimer.h"
#include "NeuralNetworkOCR.h"
#include "ImageList.h"


/*
int main(int argc, const char* argv[])
{
	std::string img_dir = argv[1];

	ImageList img_list(img_dir);

	//NeuralNetworkOCR ocr("OCR.txt");
	NeuralNetworkOCR ocr;

	BaseTimer tmr;
	tmr.start();
	ocr.train(img_list, 1 * 1000 * 1000);
	tmr.stop();

	ocr.export("OCR.txt");

	std::cout << "training took: " << tmr.elapsedSeconds() << " seconds." << std::endl;

	int success = 0;

	for (int pass = 0; pass < 1000; pass++) {
		auto img_data = img_list.getRandom();
		

		auto result = ocr.convert(img_data.image);
		

		if (result.first == img_data.getChar()) {
			success++;
		}
		else {
			std::cout << "filename: " << img_data.filename << std::endl;
			std::cout << "target char: " << img_data.getChar() << std::endl;
			std::cout << "target output nodes: " << ocr.char_to_output(img_data.getChar()) << std::endl;
			std::cout << "output char: " << result.first << std::endl;
			std::cout << "output nodes: " << ocr.output_nodes() << std::endl;

			std::cout << "------------------------" << std::endl;
		}
	}
	std::cout << "Times success out of 1000 passes: " << success;
	std::cin.ignore();
	return 0;
	}*/