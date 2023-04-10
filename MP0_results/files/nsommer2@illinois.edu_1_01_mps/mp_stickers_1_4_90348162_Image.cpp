#include "Image.h"
#include "cs225/PNG.h"

using namespace cs225;

void Image::lighten() {
	for (unsigned int h = 0; h < height(); h++) {
		for (unsigned int w = 0; w < width(); w++) {
			HSLAPixel & current = getPixel(w, h);
			current.l += 0.1;
			if (current.l > 1.0) current.l = 1.0;
			if (current.l < 0.0) current.l = 0.0;
		}
	}
}

void Image::lighten(double amount) {
	for (unsigned int h = 0; h < height(); h++) {
		for (unsigned int w = 0; w < width(); w++) {
			HSLAPixel & current = getPixel(w, h);
			current.l += amount;
			if (current.l > 1.0) current.l = 1.0;
			if (current.l < 0.0) current.l = 0.0;
		}
	}
}

void Image::darken() {
	for (unsigned int h = 0; h < height(); h++) {
		for (unsigned int w = 0; w < width(); w++) {
			HSLAPixel & current = getPixel(w, h);
			current.l -= 0.1;
			if (current.l < 0.0) current.l = 0.0;
			if (current.l > 1.0) current.l = 1.0;
		}
	}
}

void Image::darken(double amount) {
	for (unsigned int h = 0; h < height(); h++) {
		for (unsigned int w = 0; w < width(); w++) {
			HSLAPixel & current = getPixel(w, h);
			current.l -= amount;
			if (current.l < 0.0) current.l = 0.0;
			if (current.l > 1.0) current.l = 1.0;
		}
	}
}

void Image::saturate() {
	for (unsigned int h = 0; h < height(); h++) {
		for (unsigned int w = 0; w < width(); w++) {
			HSLAPixel & current = getPixel(w, h);
			current.s += 0.1;
			if (current.s > 1.0) current.s = 1.0;
			if (current.s < 0.0) current.s = 0.0;
		}
	}
}

void Image::saturate(double amount) {
	for (unsigned int h = 0; h < height(); h++) {
		for (unsigned int w = 0; w < width(); w++) {
			HSLAPixel & current = getPixel(w, h);
			current.s += amount;
			if (current.s > 1.0) current.s = 1.0;
			if (current.s < 0.0) current.s = 0.0;
		}
	}
}

void Image::desaturate() {
	for (unsigned int h = 0; h < height(); h++) {
		for (unsigned int w = 0; w < width(); w++) {
			HSLAPixel & current = getPixel(w, h);
			current.s -= 0.1;
			if (current.s < 0.0) current.s = 0.0;
			if (current.s > 1.0) current.s = 1.0;
		}
	}
}

void Image::desaturate(double amount) {
	for (unsigned int h = 0; h < height(); h++) {
		for (unsigned int w = 0; w < width(); w++) {
			HSLAPixel & current = getPixel(w, h);
			current.s -= amount;
			if (current.s < 0.0) current.s = 0.0;
			if (current.s > 1.0) current.s = 1.0;
		}
	}
}

void Image::grayscale() {
	for (unsigned int h = 0; h < height(); h++) {
		for (unsigned int w = 0; w < width(); w++) {
			HSLAPixel & current = getPixel(w, h);
			current.s = 0.0;
		}
	}
}

void Image::rotateColor(double degrees) {
	for (unsigned int h = 0; h < height(); h++) {
		for (unsigned int w = 0; w < width(); w++) {
			HSLAPixel & current = getPixel(w, h);
			current.h += degrees;
			while (current.h > 360.0) {
				current.h -= 360.0;
			}
			while (current.h < 0.0) {
				current.h += 360.0;
			}
		}
	}
}

void Image::illinify() {
	for (unsigned int h = 0; h < height(); h++) {
		for (unsigned int w = 0; w < width(); w++) {
			HSLAPixel & current = getPixel(w, h);
			if (current.h >= 113.5 && current.h < 293.5) current.h = 216;
			else current.h = 11;
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
			HSLAPixel &current = getPixel(w, h);
			HSLAPixel &copy_pixel = copyImage->getPixel(w / factor, h / factor);
			current = copy_pixel;
		}
	}
	
	delete copyImage;
}

void Image::scale(unsigned x, unsigned y) {

	Image * copyImage = new Image();
	*copyImage = *this;
	resize(x, y);

	double xFactor = x / width();
	double yFactor = y / height();

	for (unsigned int h = 0; h < y; h++) {
		for (unsigned int w = 0; w < x; w++) {
			HSLAPixel &current = getPixel(w, h);
			HSLAPixel &copy_pixel = copyImage->getPixel(w / xFactor, h / yFactor);
			current = copy_pixel;
		}
	}
	
	delete copyImage;
}