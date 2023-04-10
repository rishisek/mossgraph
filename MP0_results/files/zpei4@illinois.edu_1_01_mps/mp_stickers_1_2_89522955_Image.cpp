#include <iostream>
#include "Image.h"
#include "cs225/PNG.h"

void Image::illinify() {
	unsigned int imageWidth = width();
	unsigned int imageHeight = height();
	for (unsigned int i = 0; i < imageHeight; i++) {
		for (unsigned int j = 0; j < imageWidth; j++) {
			HSLAPixel &curPixel = getPixel(j, i);
			if (curPixel.h >= 113.5 && curPixel.h < 293.5) {
                curPixel.h = 216;
            }
			else {
                curPixel.h = 11;
		    }
        }
	}
}

void Image::rotateColor(double degrees) {
	unsigned int imageWidth = width();
	unsigned int imageHeight = height();
	//HSLAPixel &cur_pixel;
	for (unsigned int i = 0; i < imageHeight; i++) {
		for (unsigned int j = 0; j < imageWidth; j++) {
			HSLAPixel & cur_pixel = getPixel(j, i);
			cur_pixel.h += degrees;
			while (cur_pixel.h > 360.0) {
				cur_pixel.h -= 360.0;
			}
			while (cur_pixel.h < 0.0) {
				cur_pixel.h += 360.0;
			}
		}
	}
}

void Image::grayscale() {
	unsigned int imageWidth = width();
	unsigned int imageHeight = height();
	//HSLAPixel &cur_pixel;
	for (unsigned int i = 0; i < imageHeight; i++) {
		for (unsigned int j = 0; j < imageWidth; j++) {
			HSLAPixel & cur_pixel = getPixel(j, i);
			cur_pixel.s = 0.0;
		}
	}
}

void Image::lighten() {
	unsigned int imageWidth = width();
	unsigned int imageHeight = height();
	for (unsigned int i = 0; i < imageHeight; i++) {
		for (unsigned int j = 0; j < imageWidth; j++) {
			HSLAPixel & cur_pixel = getPixel(j, i);
			cur_pixel.l += 0.1;
			if (cur_pixel.l > 1.0) {
                cur_pixel.l = 1.0;
            }
			if (cur_pixel.l < 0.0){
                cur_pixel.l = 0.0;
            } 
		}
	}
}

void Image::lighten(double amount) {
	unsigned int imageWidth = width();
	unsigned int imageHeight = height();
	for (unsigned int i = 0; i < imageHeight; i++) {
		for (unsigned int j = 0; j < imageWidth; j++) {
			HSLAPixel & cur_pixel = getPixel(j, i);
			cur_pixel.l += amount;
			if (cur_pixel.l > 1.0){ 
                cur_pixel.l = 1.0;
            }
			if (cur_pixel.l < 0.0){ 
                cur_pixel.l = 0.0;
            }
        }
	}
}

void Image::darken() {
	unsigned int imageWidth = width();
	unsigned int imageHeight = height();
	for (unsigned int i = 0; i < imageHeight; i++) {
		for (unsigned int j = 0; j < imageWidth; j++) {
			HSLAPixel & cur_pixel = getPixel(j, i);
			cur_pixel.l -= 0.1;
			if (cur_pixel.l < 0.0) cur_pixel.l = 0.0;
			if (cur_pixel.l > 1.0) cur_pixel.l = 1.0;
		}
	}
}

void Image::darken(double amount) {
	unsigned int imageWidth = width();
	unsigned int imageHeight = height();
	for (unsigned int i = 0; i < imageHeight; i++) {
		for (unsigned int j = 0; j < imageWidth; j++) {
			HSLAPixel & cur_pixel = getPixel(j, i);
			cur_pixel.l -= amount;
			if (cur_pixel.l < 0.0) cur_pixel.l = 0.0;
			if (cur_pixel.l > 1.0) cur_pixel.l = 1.0;
		}
	}
}

void Image::saturate() {
	unsigned int imageWidth = width();
	unsigned int imageHeight = height();
	for (unsigned int i = 0; i < imageHeight; i++) {
		for (unsigned int j = 0; j < imageWidth; j++) {
			HSLAPixel & cur_pixel = getPixel(j, i);
			cur_pixel.s += 0.1;
			if (cur_pixel.s > 1.0) cur_pixel.s = 1.0;
			if (cur_pixel.s < 0.0) cur_pixel.s = 0.0;
		}
	}
}

void Image::saturate(double amount) {
	unsigned int imageWidth = width();
	unsigned int imageHeight = height();
	for (unsigned int i = 0; i < imageHeight; i++) {
		for (unsigned int j = 0; j < imageWidth; j++) {
			HSLAPixel & cur_pixel = getPixel(j, i);
			cur_pixel.s += amount;
			if (cur_pixel.s > 1.0) cur_pixel.s = 1.0;
			if (cur_pixel.s < 0.0) cur_pixel.s = 0.0;
		}
	}
}

void Image::desaturate() {
	unsigned int imageWidth = width();
	unsigned int imageHeight = height();
	for (unsigned int i = 0; i < imageHeight; i++) {
		for (unsigned int j = 0; j < imageWidth; j++) {
			HSLAPixel & cur_pixel = getPixel(j, i);
			cur_pixel.s -= 0.1;
			if (cur_pixel.s < 0.0) cur_pixel.s = 0.0;
			if (cur_pixel.s > 1.0) cur_pixel.s = 1.0;
		}
	}
}

void Image::desaturate(double amount) {
	unsigned int imageWidth = width();
	unsigned int imageHeight = height();
	for (unsigned int i = 0; i < imageHeight; i++) {
		for (unsigned int j = 0; j < imageWidth; j++) {
			HSLAPixel & cur_pixel = getPixel(j, i);
			cur_pixel.s -= amount;
			if (cur_pixel.s < 0.0) cur_pixel.s = 0.0;
			if (cur_pixel.s > 1.0) cur_pixel.s = 1.0;
		}
	}
}

void Image::scale(double factor) {

	unsigned int newWidth = width() * factor;
	unsigned int newHeight = height() * factor;
	Image * copy = new Image();
	*copy = *this;
	resize(newWidth, newHeight);
	for (unsigned int i = 0; i < newHeight; i++) {
		for (unsigned int j = 0; j < newWidth; j++) {
			HSLAPixel & cur_pixel = getPixel(j, i);
			HSLAPixel & cur_copy_pixel = copy->getPixel(j / factor, i / factor);
			cur_pixel = cur_copy_pixel;
		}
	}
	
	delete copy;
}

void Image::scale(unsigned x, unsigned y) {

	Image * copy = new Image();
	*copy = *this;
	resize(x, y);
	double copy_x = x / width();
	double copy_y = y / height();
	for (unsigned int i = 0; i < y; i++) {
		for (unsigned int j = 0; j < x; j++) {
			HSLAPixel & cur_pixel = getPixel(j, i);
			HSLAPixel & cur_copy_pixel = copy->getPixel(j / copy_x, i / copy_y);
			cur_pixel = cur_copy_pixel;
		}
	}
	
	delete copy;
}