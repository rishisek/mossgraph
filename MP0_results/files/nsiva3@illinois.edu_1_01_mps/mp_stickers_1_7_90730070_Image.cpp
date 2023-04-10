#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <algorithm>
#include <iostream>

using cs225::PNG;
using cs225::HSLAPixel;

// finish scale at the bottom
using namespace std;
using namespace cs225;

void Image::lighten() {
    lighten(0.1);
}
void Image::lighten(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & pixel = getPixel(i, j);
            pixel.l += amount;
            if (pixel.l > 1) {
                pixel.l = 1;
            }
        }
    }
}
void Image::darken() {
    darken(0.1);
}
void Image::darken(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & pixel = getPixel(i, j);
            pixel.l -= amount;
            if (pixel.l < 0) {
                pixel.l = 0;
            }
        }
    }
}
void Image::saturate() {
    saturate(0.1);
}
void Image::saturate(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & pixel = getPixel(i, j);
            pixel.s += amount;
            if (pixel.s > 1) {
                pixel.s = 1;
            }
        }
    }
}
void Image::desaturate() {
    desaturate(0.1);
}
void Image::desaturate(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
             HSLAPixel & pixel = getPixel(i, j);
             pixel.s -= amount;
             if (pixel.s < 0) {
                pixel.s = 0;
            }
        }
    }
}
void Image::grayscale() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & pixel = getPixel(i, j);
            pixel.s = 0;
        }
    }
}
void Image::rotateColor(double degrees) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & pixel = getPixel(i, j);
            pixel.h += degrees;
            while (pixel.h > 360) {
                pixel.h -= 360;
            }
            while (pixel.h < 0) {
                pixel.h += 360;
            }
        }
    }
}
void Image::illinify() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            // 102.5, 102 -> 11, 103 -> 216
            // 293.5, 293 -> 216, 294 -> 11
            HSLAPixel & pixel = getPixel(i, j);
            if ((pixel.h > 113) && (pixel.h < 294)) {
                pixel.h = 216;
            } else {
                pixel.h = 11;
            }
        }
    }
}
void Image::scale(double factor) {
    unsigned int w = width() * factor;
	unsigned int h = height() * factor;
	Image * copied = new Image();
	*copied = *this;
	resize(w, h);
	for (unsigned int i = 0; i < h; i++) {
		for (unsigned int j = 0; j < w; j++) {
			HSLAPixel & curr = getPixel(j, i);
			HSLAPixel & curr_copy = copied->getPixel(j / factor, i / factor);
			curr = curr_copy;
		}
	}
	delete copied;
}
void Image::scale(unsigned w, unsigned h) {
    Image * copied = new Image();
	*copied = *this;
	resize(w, h);
	double xFactor = w / width();
	double yFactor = h / height();
	for (unsigned int i = 0; i < h; h++) {
		for (unsigned int j = 0; j < w; w++) {
			HSLAPixel & curr = getPixel(j, i);
			HSLAPixel & curr_copy = copied->getPixel(j / xFactor, i / yFactor);
			curr = curr_copy;
		}
	}
	delete copied;
}