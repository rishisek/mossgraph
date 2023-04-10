#include "Image.h"
#include <cstdlib>
using namespace cs225;

Image::Image() {
}

Image::Image(unsigned int width, unsigned int height) : PNG(width, height) {
}

void Image::lighten() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            if (getPixel(x,y).l <= 0.9) {
                getPixel(x,y).l += 0.1;
            }
            else {
                getPixel(x,y).l = 1;
            }
        }
    }
}

void Image::lighten(double amount) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            if (getPixel(x,y).l + amount <= 1) {
                getPixel(x,y).l += amount;
            }
            else {
                getPixel(x,y).l = 1;
            }
        }
    }
}

void Image::darken() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            if (getPixel(x,y).l >= 0.1) {
                getPixel(x,y).l -= 0.1;
            }
            else {
                getPixel(x,y).l = 0;
            }
        }
    }
}

void Image::darken(double amount) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            if (getPixel(x,y).l - amount >= 0) {
                getPixel(x,y).l -= amount;
            }
            else {
                getPixel(x,y).l = 0;
            }
        }
    }
}

void Image::saturate() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            if (getPixel(x,y).s <= 0.9) {
                getPixel(x,y).s += 0.1;
            }
            else {
                getPixel(x,y).s = 1;
            }
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            if (getPixel(x,y).s + amount <= 1) {
                getPixel(x,y).s += amount;
            }
            else {
                getPixel(x,y).s = 1;
            }
        }
    }
}

void Image::desaturate() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            if (getPixel(x,y).s >= 0.1) {
                getPixel(x,y).s -= 0.1;
            }
            else {
                getPixel(x,y).s = 0;
            }
        }
    }
}

void Image::desaturate(double amount) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            if (getPixel(x,y).s - amount >= 0) {
                getPixel(x,y).s -= amount;
            }
            else {
                getPixel(x,y).s = 0;
            }
        }
    }
}

void Image::grayscale() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            getPixel(x,y).s = 0;
        }
    }
}

void Image::rotateColor (double degrees) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            if (getPixel(x,y).h + degrees > 360) {
                getPixel(x,y).h = getPixel(x,y).h + degrees - 360;
            }
            else if (getPixel(x,y).h + degrees < 0) {
                getPixel(x,y).h = getPixel(x,y).h + degrees + 360;
            }
            else {
                getPixel(x,y).h = getPixel(x,y).h + degrees;
            }
        }
    }
}

void Image::illinify() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            if (std::abs(getPixel(x,y).h - 11) < std::abs(getPixel(x,y).h - 216)) {
                getPixel(x,y).h = 11;
            }
            else {
                getPixel(x,y).h = 216;
            }
        }
    }
}

void Image::scale(double factor) {
    unsigned int width = (unsigned int)(this->width() * factor);
    unsigned int height = (unsigned int)(this->height() * factor);
    Image *scaled = new Image;
    *scaled = *this;
    scaled->resize(width, height);
    for (unsigned int x = 0; x < width; x++) {
        for (unsigned int y = 0; y < height; y++) {
            scaled->getPixel(x, y) = this->getPixel((x / factor), (y / factor));
        }
    }
    resize(width, height);
    *this = *scaled;
    delete scaled;
}

void Image::scale(unsigned w, unsigned h) {
    double factor;

   if ((double) w / width() <= (double) h / height()) {
        factor = (double) w / width();
    }
    else {
        factor = (double) h / height();
    }
    scale(factor);
}