#include "Image.h"

using namespace cs225;

void Image::lighten() {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            HSLAPixel& pixel = getPixel(i, j);
            pixel.l += 0.1;
            if (pixel.l > 1) {
                pixel.l = 1;
            }
        }
    }
}
void Image::lighten (double amount) {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            HSLAPixel& pixel = getPixel(i, j);
            pixel.l += amount;
            if (pixel.l > 1) {
                pixel.l = 1;
            }
        }
    }
}
void Image::darken() {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            HSLAPixel& pixel = getPixel(i, j);
            pixel.l -= 0.1;
            if (pixel.l < 0) {
                pixel.l = 0;
            }
        }
    }
}
void Image::darken(double amount) {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            HSLAPixel& pixel = getPixel(i, j);
            pixel.l -= amount;
            if (pixel.l < 0) {
                pixel.l = 0;
            }
        }
    }
}
void Image::saturate() {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            HSLAPixel& pixel = getPixel(i, j);
            pixel.s += 0.1;
            if (pixel.s > 1) {
                pixel.s = 1;
            }
        }
    }
}
void Image::saturate(double amount) {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            HSLAPixel& pixel = getPixel(i, j);
            pixel.s += amount;
            if (pixel.s > 1) {
                pixel.s = 1;
            }
        }
    }
}
void Image::desaturate() {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            HSLAPixel& pixel = getPixel(i, j);
            pixel.s -= 0.1;
            if (pixel.s < 0) {
                pixel.s = 0;
            }
        }
    }
}
void Image::desaturate(double amount) {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            HSLAPixel& pixel = getPixel(i, j);
            pixel.s -= amount;
            if (pixel.s < 0) {
                pixel.s = 0;
            }
        }
    }
}
void Image::grayscale() {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            HSLAPixel& pixel = getPixel(i, j);
            pixel.s = 0;
        }
    }
}
void Image::rotateColor(double degrees) {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            HSLAPixel& pixel = getPixel(i, j);
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
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            HSLAPixel& pixel = getPixel(i, j);
            if (pixel.h >= 113.5 && pixel.h < 278.5) {
                pixel.h = 216;
            } else {
                pixel.h = 11;
            }
        }
    }
}
void Image::scale(double factor) {
    // base case
    if (factor == 1) {
        return;
    }
    Image copy = Image(*this);
    unsigned newWidth = width()* factor;
    unsigned newHeight = height()* factor;
    resize(newWidth, newHeight);

    for (unsigned i = 0; i < newWidth; i++) {
        for (unsigned j = 0; j < newHeight; j++) {
            HSLAPixel& currentPixel = getPixel(i, j);
            HSLAPixel& copyPixel = copy.getPixel(i/factor, j/factor);
            currentPixel = copyPixel;
        }
    }
}
void Image::scale(unsigned w, unsigned h){
    double wFactor = w / width();
    double hFactor = h / height();

    if (wFactor < hFactor) {
        scale(wFactor);
    } else {
        scale(hFactor);
    }
}