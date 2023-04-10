#include "Image.h"
#include "cs225/PNG.h"
#include <iostream>

#include <cmath>

using namespace std;
using namespace cs225;


Image::Image() {}
Image::Image(unsigned int width, unsigned int height) : PNG(width, height) {}
void Image::darken() {
    darken(0.1);
}
void Image::darken(double amount) {
    for(unsigned int i = 0; i < width(); i++) {
        for(unsigned int j = 0; j < height(); j++) {
            HSLAPixel & pixel = getPixel(i, j);
            pixel.l = max(0.0,(pixel.l-amount));
            if (pixel.l > 1) {
                pixel.l = 1;
            }
        }
    }
}
void Image::desaturate() {
    desaturate(0.1);
}
void Image::desaturate(double amount){
    for(unsigned int i = 0; i < width(); i++) {
        for(unsigned int j = 0; j < height(); j++) {
            HSLAPixel & pixel = getPixel(i, j);
            pixel.s = max(0.0,(pixel.s-amount));
            if (pixel.s > 1) {
                pixel.s = 1;
            }
        }
    }
}
void Image::grayscale() {
    for(unsigned int i = 0; i < width(); i++) {
        for(unsigned int j = 0; j < height(); j++) {
            HSLAPixel & pixel = getPixel(i, j);
            pixel.s = 0;
        }
    }
}
void Image::illinify() {
    for(unsigned int i = 0; i < width(); i++) {
        for(unsigned int j = 0; j < height(); j++) {
            HSLAPixel & pixel = getPixel(i, j);
            if(pixel.h < 113.5 || pixel.l > 293.5) {
                pixel.h = 11.0;
            } else {
                pixel.h = 216.0;
            }
        }
    }
}
void Image::lighten() {
    lighten(0.1);
}
void Image::lighten(double amount) {
    for(unsigned int i = 0; i < width(); i++) {
        for(unsigned int j = 0; j < height(); j++) {
            HSLAPixel & pixel = getPixel(i, j);
            pixel.l = min(1.0, pixel.l + amount);
            if (pixel.l < 0) {
                pixel.l = 0;
            }
        }
    }
}
void Image::rotateColor(double degrees) {
    for(unsigned int i = 0; i < width(); i++) {
        for(unsigned int j = 0; j < height(); j++) {
            HSLAPixel & pixel = getPixel(i, j);
            pixel.h = pixel.h + degrees; 
            if (pixel.h > 360) {
                pixel.h = pixel.h - 360;
            } else if (pixel.h < 0) {
                pixel.h = pixel.h + 360;;
            }
        }
    }
}
void Image::saturate() {
    saturate(0.1);
}
void Image::saturate(double amount) {
    for(unsigned int i = 0; i < width(); i++) {
        for(unsigned int j = 0; j < height(); j++) {
            HSLAPixel & pixel = getPixel(i, j);
            pixel.s = min(1.0,(pixel.s+amount));
            if (pixel.s < 0) {
                pixel.s = 0;
            }
        }
    }
}
void Image::scale(double factor) {
    unsigned int width_ = width() * factor;
    unsigned int height_ = height() * factor;
    Image *img = new Image();
    (*img).resize(width_, height_);
    for (unsigned int i = 0; i < width_; i++) {
        for (unsigned int j = 0; j < height_; j++) {
            HSLAPixel & oldPixel = (*this).getPixel(i/factor, j/factor);
            HSLAPixel & pixel = (*img).getPixel(i,j);
            pixel = oldPixel;
        }
    }
    *this = *img;
    delete img;
}
void Image::scale(unsigned int w, unsigned int h) {
    double factor = min((double(w) / double(width())), (double(h) / double(height())));
    scale(factor);
}
