#include <vector>
#include <memory>
#include <iostream>
#include "imageLib\ImageLoader.h"
#include "imageLib\ImageRGB.h"
#include "imageLib\ImageGray.h"
#include "CharChecker.h"
#include "SplitLicensePlate.h"
#include "OCRPatternMatching.h"
#include <Windows.h>
#include <WinBase.h>
#include <cstdlib>
#include "dirent.h"
#if DEBUG
	#include <vld.h>
#endif

using namespace ImageLib;

int main(short argc, char *argv[])
{
	unsigned short successCount = 0;
	unsigned short failCount = 0;
	//unsigned short licCount = 0;
	DIR *pDIR;
	struct dirent *entry;
	if (pDIR = opendir("C:\\Images\\recognize\\")){
		OCRPatternMatching matching;
		while (entry = readdir(pDIR)){
			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
				std::string filename = entry->d_name;
				if (filename.substr(filename.length() - 4, 4) != ".png")
					continue;
				std::string antwoord = filename.substr(0, 8);
				std::cout << "Start recognition of " << filename << std::endl;
				std::unique_ptr<ImageRGB> rgb(loadImg("C:\\Images\\recognize\\" + filename));
				std::unique_ptr<ImageGray> image = std::make_unique<ImageGray>(rgb->width(), rgb->height());
				for (unsigned int x = 0; x < rgb->width(); x++) {
					for (unsigned int y = 0; y < rgb->height(); y++) {
						image->at(x, y) = (unsigned char)((int)(rgb->at(x, y, Channel::Red) + rgb->at(x, y, Channel::Green) + rgb->at(x, y, Channel::Blue)) / 3);
					}
				}
				SplitLicensePlate* makeSplit = new SplitLicensePlate(*image);

				/*/TEST SAve
				corona::Image* destination = corona::CreateImage(image->width(), image->height(), corona::PF_R8G8B8);
				unsigned char * pixels = (unsigned char*)destination->getPixels();
				//unsigned char * pixels = new unsigned char[character.width() * character.height() * 3];
				int count = 0;%
				for (std::vector<unsigned char>::iterator it = image->begin(); it != image->end(); ++it) {
					pixels[count] = *it;
					pixels[count + 1] = *it;
					pixels[count + 2] = *it;
					count += 3;
				}
				std::string path = "C:\\Images\\";
				path += std::to_string(licCount);
				path += ".png";
				corona::SaveImage(path.c_str(), corona::FF_PNG, destination);
				*/

				std::vector<ImageGray> characters = makeSplit->SplitImage();
				/*int number = 0;
				for (ImageGray &character : characters) {
					corona::Image* destination = corona::CreateImage(character.width(), character.height(), corona::PF_R8G8B8);
					unsigned char * pixels = (unsigned char*)destination->getPixels();
					//unsigned char * pixels = new unsigned char[character.width() * character.height() * 3];
					int count = 0;
						for (std::vector<unsigned char>::iterator it = character.begin(); it != character.end(); ++it) {
						pixels[count] = *it;
						pixels[count + 1] = *it;
						pixels[count + 2] = *it;
						count += 3;
					}
					std::string path = "C:\\Images\\lic";
					path += std::to_string(licCount);
					path += "test";
					path += std::to_string(number);
					path += ".png";
					corona::SaveImage(path.c_str(), corona::FF_PNG, destination);
					++number;
				}
				*/

				//char recognition starts here
				std::string kenteken = matching.RecognizeLicenseplate(characters);
				std::cout << "LICENSE PLATE: " << kenteken << std::endl;
				delete makeSplit;
				if (antwoord != kenteken) {
					failCount++;
					std::cout << "MISMATCH" << std::endl;
					Beep(3000, 200);
				}
				else {
					successCount++;
				}
				//licCount++;
			}
		}
		closedir(pDIR);
	}
	std::cout << "RESULT: success: " << successCount << " failed: " << failCount << std::endl;
	//int bla;
	//std::cin >> bla;
	return 0;
}


