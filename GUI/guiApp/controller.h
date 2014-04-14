#include <memory>
#include <exception>
#include <string>
#include <utility>

#include "ImageLib.h"

//UTIL
#include "Util/general.h"
#include "Util/stopwatch.h"
#include "Exceptions/allExceptions.h"

//Classes
#include "Localization/localization.h"
#include "Shadow_Lighting/shadow_lighting.h"
#include "Rotation/imageCorrection.h"

#include "OCR1/OCRPatternMatching.h"
#include "OCR1/SplitLicensePlate.h"

#include "OCR2/FileData.h"
#include "OCR2/OpticalCharacterRecognition2.h"

#include "OCRNN/NeuralNetworkOCR.h"

// File: controller.h
// @Author Lars Veenendaal 1633223
// 0.1 - Skeleton setup

using namespace ImageLib;
using namespace std;

class Controller{
private:
public:
	string Find_licenseplate(string filename);
	int RetryWithImprovedImage(shared_ptr<ImageRGB> img, vector<Blob> &possibleBlobs);
};