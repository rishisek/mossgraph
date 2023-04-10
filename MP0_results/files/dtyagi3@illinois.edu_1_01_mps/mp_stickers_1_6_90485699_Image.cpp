#include "Image.h"
#include "cs225/PNG.h"

using namespace cs225;

void Image::darken() {
    unsigned int img_ht = height();
	unsigned int img_wdth = width();
	for (unsigned int height = 0; height < img_ht; height++) {
		for (unsigned int width = 0; width < img_wdth; width++) {
			HSLAPixel & current_pixel = getPixel(width, height);
			current_pixel.l -= 0.1;
			if (current_pixel.l < 0.0) current_pixel.l = 0.0;
			if (current_pixel.l > 1.0) current_pixel.l = 1.0;
		}
	}
}

void Image::darken(double amount) {
    unsigned int img_ht = height();
	unsigned int img_wdth = width();
	for (unsigned int height = 0; height < img_ht; height++) {
		for (unsigned int width = 0; width < img_wdth; width++) {
			HSLAPixel & current_pixel = getPixel(width, height);
			current_pixel.l -= amount;
			if (current_pixel.l < 0.0) current_pixel.l = 0.0;
			if (current_pixel.l > 1.0) current_pixel.l = 1.0;
		}
	}
}

void Image::lighten() {
    unsigned int img_ht = height();
	unsigned int img_wdth = width();
	for (unsigned int height = 0; height < img_ht; height++) {
		for (unsigned int width = 0; width < img_wdth; width++) {
			HSLAPixel & current_pixel = getPixel(width, height);
			current_pixel.l += 0.1;
			if (current_pixel.l > 1.0) current_pixel.l = 1.0;
			if (current_pixel.l < 0.0) current_pixel.l = 0.0;
		}
	}
}

void Image::lighten(double amount) {
    unsigned int img_ht = height();
	unsigned int img_wdth = width();
	for (unsigned int height = 0; height < img_ht; height++) {
		for (unsigned int width = 0; width < img_wdth; width++) {
			HSLAPixel & current_pixel = getPixel(width, height);
			current_pixel.l += amount;
			if (current_pixel.l > 1.0) current_pixel.l = 1.0;
			if (current_pixel.l < 0.0) current_pixel.l = 0.0;
		}
	}
}

void Image::saturate() {
    unsigned int img_ht = height();
	unsigned int img_wdth = width();
	for (unsigned int height = 0; height < img_ht; height++) {
		for (unsigned int width = 0; width < img_wdth; width++) {
			HSLAPixel & current_pixel = getPixel(width, height);
			current_pixel.s += 0.1;
			if (current_pixel.s > 1.0) current_pixel.s = 1.0;
			if (current_pixel.s < 0.0) current_pixel.s = 0.0;
		}
	}
}

void Image::saturate(double amount) {
    unsigned int img_ht = height();
	unsigned int img_wdth = width();
	for (unsigned int height = 0; height < img_ht; height++) {
		for (unsigned int width = 0; width < img_wdth; width++) {
			HSLAPixel & current_pixel = getPixel(width, height);
			current_pixel.s += amount;
			if (current_pixel.s > 1.0) current_pixel.s = 1.0;
			if (current_pixel.s < 0.0) current_pixel.s = 0.0;
		}
	}
}

void Image::desaturate() {
    unsigned int img_ht = height();
	unsigned int img_wdth = width();
	for (unsigned int height = 0; height < img_ht; height++) {
		for (unsigned int width = 0; width < img_wdth; width++) {
			HSLAPixel & current_pixel = getPixel(width, height);
			current_pixel.s -= 0.1;
			if (current_pixel.s < 0.0) current_pixel.s = 0.0;
			if (current_pixel.s > 1.0) current_pixel.s = 1.0;
		}
	}
}

void Image::desaturate(double amount) {
    unsigned int img_ht = height();
	unsigned int img_wdth = width();
	for (unsigned int height = 0; height < img_ht; height++) {
		for (unsigned int width = 0; width < img_wdth; width++) {
			HSLAPixel & current_pixel = getPixel(width, height);
			current_pixel.s -= amount;
			if (current_pixel.s < 0.0) current_pixel.s = 0.0;
			if (current_pixel.s > 1.0) current_pixel.s = 1.0;
		}
	}
}

void Image::grayscale() {
    unsigned int img_ht = height();
	unsigned int img_wdth = width();
	for (unsigned int height = 0; height < img_ht; height++) {
		for (unsigned int width = 0; width < img_wdth; width++) {
			HSLAPixel & current_pixel = getPixel(width, height);
			current_pixel.s = 0.0;
		}
	}
}

void Image::rotateColor(double degrees) {
    unsigned int img_ht = height();
	unsigned int img_wdth = width();
	for (unsigned int height = 0; height < img_ht; height++) {
		for (unsigned int width = 0; width < img_wdth; width++) {
			HSLAPixel & current_pixel = getPixel(width, height);
			current_pixel.h += degrees;
			while (current_pixel.h > 360.0) {
				current_pixel.h -= 360.0;
			}
			while (current_pixel.h < 0.0) {
				current_pixel.h += 360.0;
			}
		}
	}
}

void Image::scale(double factor) {

	unsigned int newWdth = width() * factor;
	unsigned int newHt = height() * factor;

	Image * copyOfImage = new Image();
	*copyOfImage = *this;
	resize(newWdth, newHt);

	for (unsigned int height = 0; height < newHt; height++) {
		for (unsigned int width = 0; width < newWdth; width++) {
			HSLAPixel & current_pixel = getPixel(width, height);
			HSLAPixel & current_copy_pixel = copyOfImage->getPixel(width / factor, height / factor);
			current_pixel = current_copy_pixel;
		}
	}
	
	delete copyOfImage;
}

void Image::scale(unsigned x, unsigned y) {

	Image * copyOfImage = new Image();
	*copyOfImage = *this;
	resize(x, y);

	double factorOfX = x / width();
	double factorOfY = y / height();

	for (unsigned int height = 0; height < y; height++) {
		for (unsigned int width = 0; width < x; width++) {
			HSLAPixel & current_pixel = getPixel(width, height);
			HSLAPixel & current_copy_pixel = copyOfImage->getPixel(width / factorOfX, height / factorOfY);
			current_pixel = current_copy_pixel;
		}
	}
	
	delete copyOfImage;
}

void Image::illinify() {
    unsigned int img_ht = height();
	unsigned int img_wdth = width();
	for (unsigned int height = 0; height < img_ht; height++) {
		for (unsigned int width = 0; width < img_wdth; width++) {
			HSLAPixel & current_pixel = getPixel(width, height);
			if (current_pixel.h >= 113.5 && current_pixel.h < 293.5) current_pixel.h = 216;
			else current_pixel.h = 11;
		}
	}
}