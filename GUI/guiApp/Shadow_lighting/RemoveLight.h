#include <ImageLoader.h>

using namespace ImageLib;
using namespace std;

class RemoveLight{
public:
	RemoveLight();
	void ApplyLightingFiltering(shared_ptr<ImageRGB> image, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY);
	void ApplyShadowFiltering(shared_ptr<ImageRGB> image, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY){
		ApplyLightingFiltering(image, TopLeftX, TopLeftY, TopRightX, TopRightY, BottomLeftX, BottomLeftY, BottomRightX, BottomRightY);
	}
};