/*
Lars Veenendaal
version: 0.2:
+ Slight optimalization
+ Short ifs
- Removed unused code.

Jeroen Huisen
When it works this file will be cleaned and maded usefull
based on http://colormine.org/convert/rgb-to-lab
and http://www.brucelindbloom.com/index.html?Equations.html
*/

#include "colorSpace.h"

ColorSpace::ColorSpace(ImageRGB img) :Filter(img){
	A = new float[img.height() * img.width()];
	B = new float[img.height() * img.width()];
}

float * ColorSpace::XYZtoRGB(float X, float Y, float Z)
{

	float var_R = X * 3.2404542 + Y * -1.5371385 + Z * -0.4985314;
	float var_G = X * -0.9692660 + Y * 1.8760108 + Z* 0.0415560;
	float var_B = X * 0.0556434 + Y * -0.2040259 + Z * 1.0572252;

	var_R = var_R / 100.0;
	var_G = var_G / 100.0;
	var_B = var_B / 100.0;

	var_R = (var_R > 0.0031308) ? ((pow(var_R, (1.0 / 2.4)))*1.055 - 0.055) : (var_R * 12.92);
	var_G = (var_G > 0.0031308) ? ((pow(var_G, (1.0 / 2.4)))*1.055 - 0.055) : (var_G * 12.92);
	var_B = (var_B > 0.0031308) ? ((pow(var_B, (1.0 / 2.4)))*1.055 - 0.055) : (var_B * 12.92);

	float R = (float)((float)var_R * (float)255);        //R from 0 to 255
	float G = (float)((float)var_G * (float)255);        //G from 0 to 255
	float B = (float)((float)var_B * (float)255);        //B from 0 to 255

	if (R >= 255){
		R = 255;
	}else if (R <= 0){
		R = 0;
	}
	if (G >= 255){
		G = 255;
	}else if (G <= 0){
		G = 0;
	}
	if (B >= 255){
		B = 255;
	}else if (B <= 0){
		B = 0;
	}


	float * returnValue = new float[3];
	returnValue[0] = R;
	returnValue[1] = G;
	returnValue[2] = B;


	return returnValue;
}


float * ColorSpace::LABtoRGB(float  L, float  A, float B)
{
	float y = (L + 16.0) / 116.0;
	float x = A / 500.0 + y;
	float z = y - B / 200.0;

	float x3 = x * x * x;
	float z3 = z * z * z;

	float X = 95.047;
	float Y = 100.000;
	float Z = 108.883;
	X = X * (x3 > (216 / 24389) ? x3 : (x - 16.0 / 116.0) / 7.787);
	Y = Y * (L > ((24389 / 27) * (216 / 24389)) ? pow(((L + 16.0) / 116.0), 3) : L / (24389 / 27));
	Z = Z * (z3 > (216 / 24389) ? z3 : (z - 16.0 / 116.0) / 7.787);

	return XYZtoRGB(X, Y, Z);
}

float * ColorSpace::LABtoRGBTEST(float  L, float  A, float B)
{
	float y = (L + 16.0) / 116.0;
	float x = A / 500.0 + y;
	float z = y - B / 200.0;

	float x3 = x * x * x;
	float y3 = y * y * y;
	float z3 = z * z * z;

	float X = 95.047;
	float Y = 100.000;
	float Z = 108.883;

	X = (x3 > 0.008856) ? (X * x3) : (X * ((x - 16.0 / 116.0) / 7.787));
	Y = (y3 > 0.008856) ? (Y * y3) : (Y * ((y - 16.0 / 116.0) / 7.787));
	Z = (z3 > 0.008856) ? (Z * z3) : (Z * ((z - 16.0 / 116.0) / 7.787));
	return XYZtoRGB(X, Y, Z);
}

void ColorSpace::ToRGB(){
	for (int y = 0; y < image->height(); y++){
		for (int x = 0; x < image->width(); x++){
			float* test = LABtoRGBTEST(*image->data(x, y, Channel::Red), A[x + image->width()*y], B[x + image->width()*y]);
			*editedImage->data(x, y, Channel::Red) = test[0];
			*editedImage->data(x, y, Channel::Green) = test[1];
			*editedImage->data(x, y, Channel::Blue) = test[2];
		}
	}
}

void ColorSpace::ToRGB(int xmin = 0, int ymin = 0, int xmax = 0, int ymax = 0){
	if (xmax == 0){ xmax = image->width(); }
	if (ymax == 0){ ymax = image->height(); }
	for (int y = ymin; y < ymax; y++){
		for (int x = xmin; x < xmax; x++){
			float* test = LABtoRGBTEST(*image->data(x, y, Channel::Red), A[x + image->width()*y], B[x + image->width()*y]);
			*editedImage->data(x, y, Channel::Red) = test[0];
			*editedImage->data(x, y, Channel::Green) = test[1];
			*editedImage->data(x, y, Channel::Blue) = test[2];
		}
	}
}

float* ColorSpace::RGBtoXYZ(unsigned char R, unsigned char G, unsigned char B){

	float var_R = (float)((float)R / (float)255);        //R from 0 to 255
	float var_G = (float)((float)G / (float)255);        //G from 0 to 255
	float var_B = (float)((float)B / (float)255);        //B from 0 to 255

	var_R = (var_R > 0.04045) ? (pow(((var_R + 0.055) / 1.055), 2.4)) : (var_R / 12.92);
	var_G = (var_G > 0.04045) ? (pow(((var_G + 0.055) / 1.055), 2.4)) : (var_G / 12.92);
	var_B = (var_B > 0.04045) ? (pow(((var_B + 0.055) / 1.055), 2.4)) : (var_B / 12.92);

	var_R = var_R * 100;
	var_G = var_G * 100;
	var_B = var_B * 100;

	//Observer. = 2°, Illuminant = D65
	float * returnValue = new float[3];
	returnValue[0] = var_R * 0.4124564 + var_G * 0.3575761 + var_B * 0.1804375;
	returnValue[1] = var_R * 0.2126729 + var_G * 0.7151522 + var_B * 0.0721750;
	returnValue[2] = var_R * 0.0193339 + var_G * 0.1191920 + var_B * 0.9503041;

	return returnValue;
}

void ColorSpace::ToXYZ(){
	for (int y = 0; y < image->height(); y++){
		for (int x = 0; x < image->width(); x++){
			float* test = RGBtoXYZ(*image->data(x, y, Channel::Red), *image->data(x, y, Channel::Green), *image->data(x, y, Channel::Blue));
			*editedImage->data(x, y, Channel::Red) = test[0];
			*editedImage->data(x, y, Channel::Green) = test[1];
			*editedImage->data(x, y, Channel::Blue) = test[2];
		}
	}
}

void ColorSpace::ToXYZ(int xmin, int ymin, int xmax, int ymax){
	for (int y = ymin; y < ymax; y++){
		for (int x = xmin; x < xmax; x++){
			float* test = RGBtoXYZ(*image->data(x, y, Channel::Red), *image->data(x, y, Channel::Green), *image->data(x, y, Channel::Blue));
			*editedImage->data(x, y, Channel::Red) = test[0];
			*editedImage->data(x, y, Channel::Green) = test[1];
			*editedImage->data(x, y, Channel::Blue) = test[2];
		}
	}
}

float * ColorSpace::XYZtoLAB(float x, float y, float z){
	float ref_X = 95.047;
	float ref_Y = 100.000;
	float ref_Z = 108.883;

	float var_X = (float)x / (float)ref_X;
	float var_Y = (float)y / (float)ref_Y;
	float var_Z = (float)z / (float)ref_Z;

	var_X = (var_X > 0.008856) ? (pow(var_X, (1.0 / 3.0))) : ((903.3 * var_X + 16.0) / 116.0);
	var_Y = (var_Y > 0.008856) ? (pow(var_Y, (1.0 / 3.0))) : ((903.3 * var_Y + 16.0) / 116.0);
	var_Z = (var_Z > 0.008856) ? (pow(var_Z, (1.0 / 3.0))) : ((903.3 * var_Z + 16.0) / 116.0);

	float* returnValue = new float[3];
	returnValue[0] = (116 * var_Y) - 16;
	returnValue[1] = 500 * (var_X - var_Y);
	returnValue[2] = 200 * (var_Y - var_Z);

	return	returnValue;
}

void ColorSpace::ToLAB(){
	cout << image->height();
	for (int y = 0; y < image->height(); y++){
		for (int x = 0; x < image->width(); x++){
			//std::cout << "rgb: " << (int)*image->Data(x, y, 0) << "\n" << (int)*image->Data(x, y, 1) << "\n" << (int)*image->Data(x, y, 2) << "\n\n";
			float* test = RGBtoXYZ(*image->data(x, y, Channel::Red), *image->data(x, y, Channel::Green), *image->data(x, y, Channel::Blue));
			//std::cout << "rgb to xyz: "<< test[0] << "\n" << test[1] << "\n" << test[2] << "\n\n";
			float* test2 = XYZtoLAB(test[0], test[1], test[2]);
			//std::cout << "xyz to lab: "<< test2[0] << "\n" << test2[1] << "\n" << test2[2] << "\n\n";
			A[x + image->width()*y] = test2[1];
			B[x + image->width()*y] = test2[2];
			*editedImage->data(x, y, Channel::Red) = test2[0];
			*editedImage->data(x, y, Channel::Green) = test2[1];
			*editedImage->data(x, y, Channel::Blue) = test2[2];
		}
	}
}

void ColorSpace::ToLAB(int xmin, int ymin, int xmax, int ymax){
	for (int y = ymin; y < ymax; y++){
		for (int x = xmin; x < xmax; x++){
			//std::cout << "rgb: " << (int)*image->Data(x, y, 0) << "\n" << (int)*image->Data(x, y, 1) << "\n" << (int)*image->Data(x, y, 2) << "\n\n";
			float* test = RGBtoXYZ(*image->data(x, y, Channel::Red), *image->data(x, y, Channel::Green), *image->data(x, y, Channel::Blue));
			//std::cout << "rgb to xyz: "<< test[0] << "\n" << test[1] << "\n" << test[2] << "\n\n";
			float* test2 = XYZtoLAB(test[0], test[1], test[2]);
			//std::cout << "xyz to lab: "<< test2[0] << "\n" << test2[1] << "\n" << test2[2] << "\n\n";
			A[x + image->width()*y] = test2[1];
			B[x + image->width()*y] = test2[2];
			*editedImage->data(x, y, Channel::Red) = test2[0];
		}
	}
}


void ColorSpace::Test(){

	std::cout << "\nRGB to XYZ:\n";
	float * test = RGBtoXYZ(240, 0, 0);

	std::cout << test[0] << "\n";
	std::cout << test[1] << "\n";
	std::cout << test[2] << "\n";

	std::cout << "\nXYZ to LAB:\n";
	float* test2 = XYZtoLAB(test[0], test[1], test[2]);

	std::cout << test2[0] << "\n";
	std::cout << test2[1] << "\n";
	std::cout << test2[2] << "\n";

	std::cout << "\nLAB to RGB:\n";
	float* test3 = LABtoRGBTEST(test2[0], test2[1], test2[2]);

	std::cout << test3[0] << "\n";
	std::cout << test3[1] << "\n";
	std::cout << test3[2] << "\n";
}