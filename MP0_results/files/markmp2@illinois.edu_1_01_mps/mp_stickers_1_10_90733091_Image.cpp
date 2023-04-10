#include "Image.h"
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"

void Image::lighten() { lighten(0.1); }
void Image::lighten(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            cs225::HSLAPixel& pixel = getPixel(i, j);
            pixel.l += amount;
            if (pixel.l > 1) {
                pixel.l = 1;
            }
        }
    }
}
void Image::darken() { darken(0.1); }
void Image::darken(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            cs225::HSLAPixel& pixel = getPixel(i, j);
            pixel.l -= amount;
            if (pixel.l < 0) {
                pixel.l = 0;
            }
        }
    }
}
void Image::saturate() { saturate(0.1); }
void Image::saturate(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            cs225::HSLAPixel& pixel = getPixel(i, j);
            if (pixel.s < 1) {
                pixel.s += amount;
            } else {
                pixel.s = 1;
            }
        }
    }
}
void Image::desaturate() { desaturate(0.1); }
void Image::desaturate(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            cs225::HSLAPixel& pixel = getPixel(i, j);
            if (pixel.s > 0) {
                pixel.s -= amount;
            } else {
                pixel.s = 0;
            }
        }
    }
}
void Image::grayscale() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            cs225::HSLAPixel& pixel = getPixel(i, j);
            pixel.s = 0;
        }
    }
}
void Image::rotateColor(double degrees) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            cs225::HSLAPixel& pixel = getPixel(i, j);
            pixel.h += degrees;
            while (pixel.h < 0) {
                pixel.h += 360;
            }
            while (pixel.h > 360) {
                pixel.h -= 360;
            }
        }
    }
}
void Image::illinify() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            cs225::HSLAPixel& pixel = getPixel(i, j);
            if (pixel.h > 113 && pixel.h < 294) {
                pixel.h = 216;
            } else {
                pixel.h = 11;
            }
        }
    }
}
void Image::scale(double factor) {
    unsigned int width_ = width() * factor;
	unsigned int height_ = height() * factor;
	Image * copy = new Image();
	*copy = *this;
	PNG::resize(width_, height_);
	for (unsigned int i = 0; i < width_; i++) {
		for (unsigned int j = 0; j < height_; j++) {
			cs225::HSLAPixel& cur = getPixel(i, j);
			cs225::HSLAPixel& tmp = copy->getPixel(i / factor, j / factor);
			cur = tmp;
		}
	}
	delete copy;
}
void Image::scale(unsigned w, unsigned h) {
	double width_ = ((double)(w*1.0)) / ((double)width()*1.0);
    double height_ = ((double)(h*1.0)) / ((double)height()*1.0);
    if (width_ < height_) {
      scale(width_);
    } else { 
      scale(height_);
    }
}