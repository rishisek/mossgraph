#include <cmath>
#include "Image.h"
#include "cs225/PNG.h"

using namespace cs225;

void Image::lighten() {
    for (unsigned x = 0; x < width(); x ++) {
        for (unsigned y = 0; y < height(); y ++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.l = fmin(1.0, pixel.l + 0.1);
        }
    }
}

void Image::lighten(double amount) {
    for (unsigned x = 0; x < width(); x ++) {
        for (unsigned y = 0; y < height(); y ++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.l = fmin(1.0, pixel.l + amount);
        }
    }
}

void Image::darken() {
    for (unsigned x = 0; x < width(); x ++) {
        for (unsigned y = 0; y < height(); y ++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.l = fmax(0.0, pixel.l - 0.1);
        }
    }
}

void Image::darken(double amount) {
    for (unsigned x = 0; x < width(); x ++) {
        for (unsigned y = 0; y < height(); y ++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.l = fmax(0.0, pixel.l - amount);
        }
    }
}

void Image::saturate() {
    for (unsigned x = 0; x < width(); x ++) {
        for (unsigned y = 0; y < height(); y ++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.s = fmin(1.0, pixel.s + 0.1);
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned x = 0; x < width(); x ++) {
        for (unsigned y = 0; y < height(); y ++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.s = fmin(1.0, pixel.s + amount);
        }
    }
}

void Image::desaturate() {
    for (unsigned x = 0; x < width(); x ++) {
        for (unsigned y = 0; y < height(); y ++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.s = fmax(0.0, pixel.s - 0.1);
        }
    }
}

void Image::desaturate(double amount) {
    for (unsigned x = 0; x < width(); x ++) {
        for (unsigned y = 0; y < height(); y ++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.s = fmax(0.0, pixel.s - amount);
        }
    }
}

void Image::grayscale() {
    for (unsigned x = 0; x < width(); x ++) {
        for (unsigned y = 0; y < height(); y ++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.s = 0.0;
        }
    }
}

void Image::rotateColor(double degrees) {
    for (unsigned x = 0; x < width(); x ++) {
        for (unsigned y = 0; y < height(); y ++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.h += degrees;
            while (pixel.h < 0.0) pixel.h += 360.0;
            while (pixel.h > 360.0) pixel.h -= 360.0;
        }
    }
}

void Image::illinify() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);

            if (pixel.h >= 113.5 && pixel.h < 278.5) {
                pixel.h = 216;
            }
            else {
                pixel.h = 11;
            }
        }
    }
}

void Image::scale(double factor) {
    if (factor == 1.0) return;

    // store a copy of this image for reference
    Image copy = Image(*this);

    // calculate the new dimensions of the image
    unsigned newWidth = width() * factor;
    unsigned newHeight = height() * factor;
    // resize this image to the desired dimensions
    resize(newWidth, newHeight);

    for (unsigned x = 0; x < newWidth; x ++) {
        for (unsigned y = 0; y < newHeight; y ++) {
            HSLAPixel & thisPixel = getPixel(x,y);
            HSLAPixel & copyPixel = copy.getPixel(x/factor, y/factor);
            thisPixel = copyPixel;
        }
    }
}

void Image::scale(unsigned w, unsigned h) {
    double widthFactor = (1.0 * w) / width();
    double heightFactor = (1.0 * h) / height();

    double factor = fmin(widthFactor, heightFactor);
    scale(factor);
}

