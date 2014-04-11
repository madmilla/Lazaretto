#include <vector>
#include <memory>
#include <iostream>
#include "ImageLoader.h"
#include "ImageRGB.h"
#include "ImageGray.h"
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
		
		while (entry = readdir(pDIR)){
			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
				std::string filename = entry->d_name;
				if (filename.substr(filename.length() - 4, 4) != ".png")
					continue;

				std::string antwoord = filename.substr(0, 8);




	}
	std::cout << "RESULT: success: " << successCount << " failed: " << failCount << std::endl;
	int bla;
	std::cin >> bla;
	return 0;
}


