#include "Image.h"
#include "cs225/PNG.h"

using namespace cs225;

void Image::lighten() {
	unsigned int image_width = width();
	unsigned int image_height = height();
	for (unsigned int i = 0; i < image_height; i++) {
		for (unsigned int j = 0; j < image_width; j++) {
			HSLAPixel & pixel = getPixel(j, i);
			pixel.l += 0.1;
			if (pixel.l > 1.0) pixel.l = 1.0;
			if (pixel.l < 0.0) pixel.l = 0.0;
		}
	}
}

void Image::lighten(double amount) {
	unsigned int image_width = width();
	unsigned int image_height = height();
	for (unsigned int i = 0; i < image_height; i++) {
		for (unsigned int j = 0; j < image_width; j++) {
			HSLAPixel & pixel = getPixel(j, i);
			pixel.l += amount;
			if (pixel.l > 1.0) pixel.l = 1.0;
			if (pixel.l < 0.0) pixel.l = 0.0;
		}
	}
}

void Image::darken() {
	unsigned int image_width = width();
	unsigned int image_height = height();
	for (unsigned int i = 0; i < image_height; i++) {
		for (unsigned int j = 0; j < image_width; j++) {
			HSLAPixel & pixel = getPixel(j, i);
			pixel.l -= 0.1;
			if (pixel.l < 0.0) pixel.l = 0.0;
			if (pixel.l > 1.0) pixel.l = 1.0;
		}
	}
}

void Image::darken(double amount) {
	unsigned int image_width = width();
	unsigned int image_height = height();
	for (unsigned int i = 0; i < image_height; i++) {
		for (unsigned int j = 0; j < image_width; j++) {
			HSLAPixel & pixel = getPixel(j, i);
			pixel.l -= amount;
			if (pixel.l < 0.0) pixel.l = 0.0;
			if (pixel.l > 1.0) pixel.l = 1.0;
		}
	}
}

void Image::saturate() {
	unsigned int image_width = width();
	unsigned int image_height = height();
	for (unsigned int i = 0; i < image_height; i++) {
		for (unsigned int j = 0; j < image_width; j++) {
			HSLAPixel & pixel = getPixel(j, i);
			pixel.s += 0.1;
			if (pixel.s > 1.0) pixel.s = 1.0;
			if (pixel.s < 0.0) pixel.s = 0.0;
		}
	}
}

void Image::saturate(double amount) {
	unsigned int image_width = width();
	unsigned int image_height = height();
	for (unsigned int i = 0; i < image_height; i++) {
		for (unsigned int j = 0; j < image_width; j++) {
			HSLAPixel & pixel = getPixel(j, i);
			pixel.s += amount;
			if (pixel.s > 1.0) pixel.s = 1.0;
			if (pixel.s < 0.0) pixel.s = 0.0;
		}
	}
}

void Image::desaturate() {
	unsigned int image_width = width();
	unsigned int image_height = height();
	for (unsigned int i = 0; i < image_height; i++) {
		for (unsigned int j = 0; j < image_width; j++) {
			HSLAPixel & pixel = getPixel(j, i);
			pixel.s -= 0.1;
			if (pixel.s < 0.0) pixel.s = 0.0;
			if (pixel.s > 1.0) pixel.s = 1.0;
		}
	}
}

void Image::desaturate(double amount) {
	unsigned int image_width = width();
	unsigned int image_height = height();
	for (unsigned int i = 0; i < image_height; i++) {
		for (unsigned int j = 0; j < image_width; j++) {
			HSLAPixel & pixel = getPixel(j, i);
			pixel.s -= amount;
			if (pixel.s < 0.0) pixel.s = 0.0;
			if (pixel.s > 1.0) pixel.s = 1.0;
		}
	}
}

void Image::grayscale() {
	unsigned int image_width = width();
	unsigned int image_height = height();
	for (unsigned int i = 0; i < image_height; i++) {
		for (unsigned int j = 0; j < image_width; j++) {
			HSLAPixel & pixel = getPixel(j, i);
			pixel.s = 0.0;
		}
	}
}

void Image::rotateColor(double degrees) {
	unsigned int image_width = width();
	unsigned int image_height = height();
	for (unsigned int i = 0; i < image_height; i++) {
		for (unsigned int j = 0; j < image_width; j++) {
			HSLAPixel & pixel = getPixel(j, i);
			pixel.h += degrees;
			while (pixel.h > 360.0) {
				pixel.h -= 360.0;
			}
			while (pixel.h < 0.0) {
				pixel.h += 360.0;
			}
		}
	}
}

void Image::illinify() {
	unsigned int image_width = width();
	unsigned int image_height = height();
	for (unsigned int h = 0; h < image_height; h++) {
		for (unsigned int w = 0; w < image_width; w++) {
			HSLAPixel & cur_pixel = getPixel(w, h);
			if (cur_pixel.h >= 113.5 && cur_pixel.h < 293.5) cur_pixel.h = 216;
			else cur_pixel.h = 11;
		}
	}
}

void Image::scale(double factor) {

	unsigned int newWidth = width() * factor;
	unsigned int newHeight = height() * factor;

	Image * copyImage = new Image();
	*copyImage = *this;
	resize(newWidth, newHeight);

	for (unsigned int h = 0; h < newHeight; h++) {
		for (unsigned int w = 0; w < newWidth; w++) {
			HSLAPixel & cur_pixel = getPixel(w, h);
			HSLAPixel & cur_copy_pixel = copyImage->getPixel(w / factor, h / factor);
			cur_pixel = cur_copy_pixel;
		}
	}
	
	delete copyImage;
}

void Image::scale(unsigned x, unsigned y) {

	double widthF = ((double)(x*1.0)) / ((double)width()*1.0);
    double heightF = ((double)(y*1.0)) / ((double)height()*1.0);
    if (widthF < heightF)
      scale(widthF);
    else scale(heightF);
  }
