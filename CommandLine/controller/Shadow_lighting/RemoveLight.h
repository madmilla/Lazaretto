#include <ImageLoader.h>
#include <iostream> //debugging

using namespace ImageLib;
using namespace std;

class RemoveLight{
private:
	float meanC;
	float meanM;
	float meanY;
	float meanK;
public:
	RemoveLight();
	void CornerPointsValues(shared_ptr<ImageRGB> image, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY);
	void ApplyLightingFiltering(shared_ptr<ImageRGB> image, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY);
	void ApplyShadowFiltering(shared_ptr<ImageRGB> image, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY);
	//	ApplyLightingFiltering(image, TopLeftX, TopLeftY, TopRightX, TopRightY, BottomLeftX, BottomLeftY, BottomRightX, BottomRightY);
	//}
};