#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <iostream>
#include <algorithm>

using cs225::PNG;
using cs225::HSLAPixel;

void Image::lighten() {
    for (unsigned i = 0; width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            HSLAPixel& current = getPixel(i, j);
            current.l += 0.1;
            if (current.l > 1) {
                current.l = 1;
            } 
            if (current.l < 0) {
                current.l = 0;
            }
        }
    }
}
 void Image::lighten(double amount) {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            HSLAPixel& current = getPixel(i, j);
            current.l += amount;
            if (current.l > 1) {
                current.l = 1;
            }
            if (current.l < 0) {
                current.l = 0;
            }
        }
    }
 }

 void Image::darken() {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            HSLAPixel& current = getPixel(i, j);
            current.l -= 0.1;
            if (current.l < 0) {
                current.l = 0;
            }
            if (current.l > 1) {
                current.l = 1;
            }
        }
    }
 }

 void Image::darken(double amount) {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            HSLAPixel& current = getPixel(i, j);
            current.l -= 0.1;
            if (current.l < 0) {
                current.l = 0;
            }
            if (current.l > 1) {
                current.l = 1;
            }
        }
    }
 }

 void Image::saturate() {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            HSLAPixel& current = getPixel(i, j);
            current.s += 0.1;
            if (current.s > 1) {
                current.s = 1;
            }
            if (current.s < 0) {
                current.s = 0;
            }
        }
    }
 }

 void Image::saturate(double amount) {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            HSLAPixel& current = getPixel(i, j);
            current.s += amount;
            if (current.s > 1) {
                current.s = 1;
            }
            if (current.s < 0) {
                current.s = 0;
            }
        }
    }
 }

 void Image::desaturate() {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            HSLAPixel& current = getPixel(i, j);
            current.s -= 0.1;
            if (current.s < 0) {
                current.s = 0;
            }
            if (current.s > 1) {
                current.s = 1;
            }
        }
    }
 }

 void Image::desaturate(double amount) {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            HSLAPixel& current = getPixel(i, j);
            current.s -= amount;
            if (current.s < 0) {
                current.s = 0;
            }
            if (current.s > 1) {
                current.s = 1;
            }
        }
    }
 }

 void Image::grayscale() {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            HSLAPixel& current = getPixel(i, j);
            current.s = 0;
        }
    }
 }

 void Image::rotateColor(double degrees) {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            HSLAPixel& current = getPixel(i, j);
            current.h += degrees;
            while (current.h > 360) {
                current.h -= 360;
            }
            while (current.h < 0) {
                current.h += 360;
            }
        } 
    }
 }

 void Image::illinify() {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            HSLAPixel& current = getPixel(i, j);
            if ((current.h > 113.5) && (current.h < 293.5)) {
                current.h = 216;
            }
            else {
                current.h = 11;
            }
        }
    }
 }

 void Image::scale(double factor) {
    if (factor > 1) {
        resize(width()*factor, height()*factor);
        for (int i = width() - 1; i >= 0; i--) {
            for (int j = height() - 1; j >= 0; j--) {
                HSLAPixel& new_pixel = getPixel((unsigned)i, (unsigned)j);
                HSLAPixel& current = getPixel((unsigned)i/factor, (unsigned)j/factor);
                new_pixel = current;
            }
        }
    }
    if (factor < 1) {
        for (unsigned i = 0; i < (width()*factor); i++) {
            for (unsigned j = 0; j < (height()*factor); j++) {
                HSLAPixel& new_pixel = getPixel(i, j);
                HSLAPixel& current = getPixel(i/factor, j/factor);
                new_pixel = current;
            }
        }
        resize(width()*factor, height()*factor);
    }
}

void Image::scale(unsigned w, unsigned h) {
    double width_scale = (double)w/(double)width();
    double height_scale = (double)h/(double)height();
    double factor = std::min(width_scale, height_scale);
    scale(factor);
}