#include "filter.h"

// File: shadow_lighting.h
// @Author Jeroen Huisen
// @Author Lars Veenendaal 1633223
//
// 0.2 - Migration of tests 
// 0.1 - Skeleton setup

/*
	Still holds nothing.
*/

Filter::Filter(ImageRGB rgb_img){
	editedImage = std::make_shared<ImageRGB>(rgb_img.width(), rgb_img.height());
	image = std::make_shared<ImageRGB>(rgb_img);
}
shared_ptr<ImageRGB> Filter::getImage(){//Return image
	cout << "\nimg" << editedImage->height() << "\n";
	cout << "bagger" << image->height();
	return image;
}
shared_ptr<ImageRGB> Filter::getEditedImage(){//Return editedImage
	return editedImage;
}
void Filter::Copy(){//Copy data from image to editedImage
	for (int y = 0; y < image->height(); y++){
		for (int x = 0; x < image->width(); x++){
			*editedImage->data(x, y, Channel::Red) = *image->data(x, y, Channel::Red);
			*editedImage->data(x, y, Channel::Green) = *image->data(x, y, Channel::Green);
			*editedImage->data(x, y, Channel::Blue) = *image->data(x, y, Channel::Blue);
		}
	}
}