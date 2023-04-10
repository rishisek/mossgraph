#include "Image.h"
#include <iostream>
#include <cmath>

Image::Image() {

}
Image::Image(unsigned int width, unsigned int height) {

}


void Image::illinify() {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel &pixel = this->getPixel(i , j);
            int orange = abs(pixel.h - 11);
            int blue = abs(pixel.h - 216);
            if (orange < blue) {
                pixel.h = 11;
            } else {
                pixel.h = 216;
            }
        }
    }
}

void Image::lighten() {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j =0; j < this->height(); j++) {
            cs225::HSLAPixel &pixel = this->getPixel(i , j);
            pixel.l += 0.1;
            if (pixel.l > 1) {
                pixel.l = 1;
            }
        }
    }
}

void Image::lighten(double amount) {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j =0; j < this->height(); j++) {
            cs225::HSLAPixel &pixel = this->getPixel(i , j);
            pixel.l += amount;
            if (pixel.l > 1) {
                pixel.l = 1;
            }
        }
    }
}

void Image::darken() {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j =0; j < this->height(); j++) {
            cs225::HSLAPixel &pixel = this->getPixel(i , j);
            pixel.l -= 0.1;
            if (pixel.l < 0) {
                pixel.l = 0;
            }
        }
    }
}

void Image::darken(double amount) {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j =0; j < this->height(); j++) {
            cs225::HSLAPixel &pixel = this->getPixel(i , j);
            pixel.l -= amount;
            if (pixel.l < 0.0) {
                pixel.l = 0.0;
            }
        }
    }
}

void Image::saturate() {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j =0; j < this->height(); j++) {
            cs225::HSLAPixel &pixel = this->getPixel(i , j);
            pixel.s = pixel.s + 0.1;
            if (pixel.s > 1.0) {
                pixel.s = 1.0;
            }
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j =0; j < this->height(); j++) {
            cs225::HSLAPixel &pixel = this->getPixel(i , j);
            pixel.s = pixel.s + amount;
            if (pixel.s > 1.0) {
                pixel.s = 1.0;
            }
        }
    }
}

void Image::desaturate() {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j =0; j < this->height(); j++) {
            cs225::HSLAPixel &pixel = this->getPixel(i , j);
            pixel.s = pixel.s - 0.1;
            if (pixel.s > 1.0) {
                pixel.s = 1.0;
            }
        }
    }
}

void Image::desaturate(double amount) {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j =0; j < this->height(); j++) {
            cs225::HSLAPixel &pixel = this->getPixel(i , j);
            pixel.s = pixel.s + amount;
            if (pixel.s > 1.0) {
                pixel.s = 1.0;
            }
        }
    }
}

void Image::grayscale() {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j =0; j < this->height(); j++) {
            cs225::HSLAPixel &pixel = this->getPixel(i , j);
            pixel.s = 0.0;
        }
    }
}


void Image::rotateColor(double degrees) {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j =0; j < this->height(); j++) {
            cs225::HSLAPixel &pixel = this->getPixel(i , j);
            double hue = this->getPixel(i , j).h + degrees;
            while (hue >= 360.0) {
                hue -= 360.0;
            }
            while (hue < 0.0) {
                hue += 360.0;
            }
            this->getPixel(i , j).h = hue;
        }
    }
}

void Image::scale(double factor) {
    int newWidth = (int)(this->width() * factor);
    int newHeight = (int)(this->height() * factor);
    Image newImage = *this;
   newImage.resize(newWidth, newHeight);
    for (int i = 0; i < newWidth; i++){
        for (int j = 0; j < newHeight; j++) {
            unsigned int oldWidth = i / factor;
            unsigned int oldHeight = j / factor;
            if (oldWidth >= 0 && oldWidth < width() && oldHeight >= 0 && oldHeight < height()) {
               newImage.getPixel(i,j) = getPixel(oldWidth, oldHeight);
            }
        }
    }
    *this = newImage;
}


void Image::scale(unsigned w, unsigned h) {
    double wRatio = (double)w / this->width();
    double hRatio = (double)h / this->height();
    double factor = min(wRatio, hRatio);
    scale(factor);
}
