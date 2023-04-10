#include "Image.h"
#include "cs225/PNG.h"

using namespace cs225;

void Image::darken() {
    darken(0.1);
}

void Image::darken(double amount) {
    unsigned int height = PNG::height();
    unsigned int width = PNG::width();
    
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            HSLAPixel & current = getPixel(j, i);
            current.l -= amount;
            if (current.l < 0.0) {
                current.l = 0.0;
            }
            if (current.l > 1.0) {
                current.l = 1.0;
            }
        }
    }
}

void Image::desaturate() {
    desaturate(0.1);
}

void Image::desaturate(double amount) {
    unsigned int height = PNG::height();
    unsigned int width = PNG::width();

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            HSLAPixel & current = getPixel(j, i);
            current.s -= amount;
            if (current.s < 0.0) {
                current.s = 0.0;
            }
            if (current.s > 1.0) {
                current.s = 1.0;
            }
        }
    }
}

void Image::grayscale() {
    unsigned int height = PNG::height();
    unsigned int width = PNG::width();

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            HSLAPixel & current = getPixel(j, i);
            current.s = 0.0;
        }
    }
}

void Image::illinify() {
    unsigned int height = PNG::height();
    unsigned int width = PNG::width();

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            HSLAPixel & current = getPixel(j, i);
            if (current.h < 293.5 && current.h >= 113.5) {
                current.h = 216;
            } else {
                current.h = 11;
            }
        }
    }
}

void Image::lighten() {
    lighten(0.1);
}

void Image::lighten(double amount) {
    unsigned int height = PNG::height();
    unsigned int width = PNG::width();

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            HSLAPixel & current = getPixel(j, i);
            current.l += amount;
            if (current.l < 0.0) {
                current.l = 0.0;
            }
            if (current.l > 1.0) {
                current.l = 1.0;
            }
        }
    }
}

void Image::rotateColor(double degrees) {
    unsigned int height = PNG::height();
    unsigned int width = PNG::width();

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            HSLAPixel & current = getPixel(j, i);
            current.h += degrees;
            while(current.h > 360.0) {
                current.h -= 360.0;
            }
            while(current.h < 0.0)  {
                current.h += 360.0;
            }
        }
    }
}

void Image::saturate() {
    saturate(0.1);
}

void Image::saturate(double amount) {
    unsigned int height = PNG::height();
    unsigned int width = PNG::width();

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            HSLAPixel & current = getPixel(j, i);
            current.s += amount;
            if (current.s < 0.0) {
                current.s = 0.0;
            }
            if (current.s > 1.0) {
                current.s = 1.0;
            }
        }
    }
}

void Image::scale(double factor) {
    unsigned int height = PNG::height() * factor;
    unsigned int width = PNG::width() * factor;

    Image * scaled = new Image();
    *scaled = *this;
    resize(width, height);

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            HSLAPixel & current = getPixel(j, i);
            HSLAPixel & copy = scaled->getPixel(j / factor, i / factor);
            current = copy;
        }
    }

    delete scaled;
}

void Image::scale(unsigned w, unsigned h) {
    Image * scaled = new Image();
    *scaled = *this;
    PNG::resize(w, h);

    double wfactor = w / PNG::width();
    double hfactor = h / PNG::height();

    for (unsigned int i = 0; i < h; i++) {
        for (unsigned int j = 0; j < w; j++) {
            HSLAPixel & current = getPixel(j, i);
            HSLAPixel & copy = scaled->getPixel(j / wfactor, i / hfactor);
            current = copy;
        }
    }

    delete scaled;
}