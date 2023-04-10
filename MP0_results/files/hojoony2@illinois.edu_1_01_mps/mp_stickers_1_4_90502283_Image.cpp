#include "Image.h"
#include "algorithm"
#include "cstdlib"
#include <iostream> 


Image::Image() {
    height_ = 0; 
    width_ = 0;   
}

Image::Image(unsigned int width, unsigned int height) {
    width_  = width;
    height_  = height; 
    image = PNG(width_, height_);
}

void Image::lighten() {
    for (unsigned int i = 0; i < height(); i++) {
        for (unsigned int j = 0; j < width(); j++) {
            cs225::HSLAPixel& a = getPixel(j, i);
            a.l = a.l + 0.1;
            if (a.l > 1) { 
                a.l = 1;
            }
        }
    }
}
void Image::lighten(double amount) { 
    for (unsigned int i = 0; i < height(); i++) {
        for (unsigned int j = 0; j < width(); j++) {
            cs225::HSLAPixel& a = getPixel(j, i);
            a.l = a.l + amount;
            if (a.l > 1) { 
                a.l = 1;
            }
        }
    }
}
void Image::darken() { 
    for (unsigned int i = 0; i < height(); i++) {
        for (unsigned int j = 0; j < width(); j++) {
            cs225::HSLAPixel& a = getPixel(j, i);
            a.l = a.l - 0.1;
            if (a.l < 0) { 
                a.l = 0;
            }
        }
    }
}
void Image::darken(double amount) {
    for (unsigned int i = 0; i < height(); i++) {
        for (unsigned int j = 0; j < width(); j++) {
            cs225::HSLAPixel& a = getPixel(j, i);
            a.l = a.l - amount;
            if (a.l < 0) { 
                a.l = 0;
            }
        }
    }
}
void Image::saturate() {
    for (unsigned int i = 0; i < height(); i++) {
        for (unsigned int j = 0; j < width(); j++) {
            cs225::HSLAPixel& a = getPixel(j, i);
            a.s = a.s + 0.1;
            if (a.s > 1) { 
                a.s = 1;
            }
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned int i = 0; i < height(); i++) {
        for (unsigned int j = 0; j < width(); j++) {
            cs225::HSLAPixel& a = getPixel(j, i);
            a.s = a.s + amount;
            if (a.s > 1) { 
                a.s = 1;
            }
        }
    }
}

void Image::desaturate() {
    for (unsigned int i = 0; i < height(); i++) {
        for (unsigned int j = 0; j < width(); j++) {
            cs225::HSLAPixel& a = getPixel(j, i);
            a.s = a.s - 0.1;
            if (a.s < 0) { 
                a.s = 0;
            }
        }
    }
}
void Image::desaturate(double amount) {
    for (unsigned int i = 0; i < height(); i++) {
        for (unsigned int j = 0; j < width(); j++) {
            cs225::HSLAPixel& a = getPixel(j, i);
            a.s = a.s - amount;
            if (a.s < 0) { 
                a.s = 0;
            }
        }
    }
}
void Image::grayscale() {
    for (unsigned int i = 0; i < height(); i++) {
        for (unsigned int j = 0; j < width(); j++) {
            cs225::HSLAPixel& a = getPixel(j, i);
            a.s = 0;
        }
    }
}
void Image::rotateColor(double degrees) {
    for (unsigned int i = 0; i < height(); i++) {
        for (unsigned int j = 0; j < width(); j++) {
            cs225::HSLAPixel& a = getPixel(j, i);
            a.h = a.h + degrees;
            if (a.h > 360) { 
                a.h = a.h - 360;
            } else if (a.h < 0) {
                a.h = a.h + 360;
            }
        }
    }
}
void Image::illinify() {
    for (unsigned int i = 0; i < height(); i++) {
        for (unsigned int j = 0; j < width(); j++) {
            cs225::HSLAPixel& a = getPixel(j, i);
            unsigned int blu = std::min(std::abs(a.h - 216), (360 - std::abs(a.h -216)));
            unsigned int og = std::min(std::abs(a.h - 11), (360 - std::abs(a.h -11)));
            if (blu > og) {
                a.h = 11; 
            } else if (blu < og) {
                a.h = 216;
            }
        }
    }
}
 
void Image::scale(double factor) {
    Image k = *this;
    resize(factor * width(), factor * height());
    for (unsigned int i = 0; i < height(); i++) {
        for (unsigned int j = 0; j < width(); j++) { 
            cs225::HSLAPixel& a = getPixel(j, i);
            a = k.getPixel(j * (1/factor), i * (1/factor)); 
        }
    }
}
void Image::scale(unsigned w, unsigned h) {
    // first find the width fac and height fac
    double wfac = (double) w/ (double)width(); // 10
    double hfac = (double) h/ (double)height(); // 5
    
    if (wfac >= hfac) { // 5
        scale(hfac); 
    } else { // 
        scale(wfac);
    }
}