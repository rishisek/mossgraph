#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <cmath>
using namespace cs225;

Image::Image() {

}

Image::Image(unsigned int width, unsigned int height) {
    
}

void Image::lighten() {
    for (unsigned i = 0; i < Image::height(); i++) {
        for (unsigned j = 0; j < Image::width(); j++) {
            HSLAPixel& currentPixel = Image::getPixel(j, i);
            if (currentPixel.l + 0.1 > 1) {
                HSLAPixel& temp_pixel = Image::getPixel(j, i);
                temp_pixel.l = 1;
            } else {
                HSLAPixel& temp_pixel = Image::getPixel(j, i);
                temp_pixel.l = currentPixel.l + 0.1;
            }
        }
    }
}

void Image::lighten(double amount) {
    for (unsigned i = 0; i < Image::height(); i++) {
        for (unsigned j = 0; j < Image::width(); j++) {
            HSLAPixel& currentPixel = Image::getPixel(j, i);
            if (currentPixel.l + amount > 1) {
                HSLAPixel& temp_pixel = Image::getPixel(j, i);
                temp_pixel.l = 1;
            } else {
                HSLAPixel& temp_pixel = Image::getPixel(j, i);
                temp_pixel.l = currentPixel.l + amount;
            }
        }
    }
}

void Image::darken() {
    for (unsigned i = 0; i < Image::height(); i++) {
        for (unsigned j = 0; j < Image::width(); j++) {
            HSLAPixel& currentPixel = Image::getPixel(j, i);
            if (currentPixel.l - 1 < 0) {
                HSLAPixel& temp_pixel = Image::getPixel(j, i);
                temp_pixel.l = 0;
            } else {
                HSLAPixel& temp_pixel = Image::getPixel(j, i);
                temp_pixel.l = currentPixel.l - 0.1;
            }
        }
    }
}

void Image::darken(double amount) {
    for (unsigned i = 0; i < Image::height(); i++) {
        for (unsigned j = 0; j < Image::width(); j++) {
            HSLAPixel& currentPixel = Image::getPixel(j, i);
            if (currentPixel.l - amount < 0) {
                HSLAPixel& temp_pixel = Image::getPixel(j, i);
                temp_pixel.l = 0;
            } else {
                HSLAPixel& temp_pixel = Image::getPixel(j, i);
                temp_pixel.l = currentPixel.l - amount;
            }
        }
    }
}

void Image::saturate() {
    for (unsigned i = 0; i < Image::height(); i++) {
        for (unsigned j = 0; j < Image::width(); j++) {
            HSLAPixel& currentPixel = Image::getPixel(j, i);
            if (currentPixel.s + 0.1 > 1) {
                HSLAPixel& temp_pixel = Image::getPixel(j, i);
                temp_pixel.s = 1;
            } else {
                HSLAPixel& temp_pixel = Image::getPixel(j, i);
                temp_pixel.s = currentPixel.s + 0.1;
            }
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned i = 0; i < Image::height(); i++) {
        for (unsigned j = 0; j < Image::width(); j++) {
            HSLAPixel& currentPixel = Image::getPixel(j, i);
            if (currentPixel.s + amount > 1) {
                HSLAPixel& temp_pixel = Image::getPixel(j, i);
                temp_pixel.s = 1;
            } else {
                HSLAPixel& temp_pixel = Image::getPixel(j, i);
                temp_pixel.s = currentPixel.s + amount;
            }
        }
    }
}

void Image::desaturate() {
    for (unsigned i = 0; i < Image::height(); i++) {
        for (unsigned j = 0; j < Image::width(); j++) {
            HSLAPixel& currentPixel = Image::getPixel(j, i);
            if (currentPixel.s - 0.1 < 0) {
                HSLAPixel& temp_pixel = Image::getPixel(j, i);
                temp_pixel.s = 0;
            } else {
                HSLAPixel& temp_pixel = Image::getPixel(j, i);
                temp_pixel.s = currentPixel.s - 0.1;
            }
        }
    }
}

void Image::desaturate(double amount) {
    for (unsigned i = 0; i < Image::height(); i++) {
        for (unsigned j = 0; j < Image::width(); j++) {
            HSLAPixel& currentPixel = Image::getPixel(j, i);
            if (currentPixel.s - amount < 0) {
                HSLAPixel& temp_pixel = Image::getPixel(j, i);
                temp_pixel.s = 0;
            } else {
                HSLAPixel& temp_pixel = Image::getPixel(j, i);
                temp_pixel.s = currentPixel.s - amount;
            }
        }
    }
}

void Image::grayscale() {
    for (unsigned i = 0; i < Image::height(); i++) {
        for (unsigned j = 0; j < Image::width(); j++) {
            HSLAPixel& currentPixel = Image::getPixel(j, i);
            currentPixel.s = 0;
        }
    }
}

void Image::rotateColor(double degrees) {
    for (unsigned i = 0; i < Image::height(); i++) {
        for (unsigned j = 0; j < Image::width(); j++) {
            HSLAPixel& currentPixel = Image::getPixel(j, i);
            if (degrees < 0) {
                degrees = std::abs(degrees);
            }
            if (currentPixel.h + degrees > 360) {
                currentPixel.h = (currentPixel.h + degrees - 360);
            } else {
                currentPixel.h += degrees;
            }
        }
    }
}

void Image::illinify() {
    for (unsigned i = 0; i < Image::height(); i++) {
        for (unsigned j = 0; j < Image::width(); j++) {
            HSLAPixel& currentPixel = Image::getPixel(j, i);
            if (currentPixel.h >= 113.5 && currentPixel.h <= 293.5) {
                // 113.5 is between 11 and 216, 293.5 between 216 and 11
                currentPixel.h = 216;
            } else {
                currentPixel.h = 11;
            }
        }
    }
}

void Image::scale(double factor) {
    Image copyI = *this;
    resize(factor * width(), factor * height());
    double width_ratio = copyI.width() / width();
    double height_ratio = copyI.height() / height();
    for (unsigned i = 0; i < height(); i++) {
        for (unsigned j = 0; j < width(); j++) {
            HSLAPixel& currentPixel = Image::getPixel(j, i);
            //currentPixel = copy->getPixel(j * height_ratio, i * width_ratio);
            HSLAPixel copy = copyI.getPixel(j * width_ratio, i * height_ratio);
        }
    }
}

void Image::scale(unsigned w, unsigned h) {
    Image copyI = *this;
    resize(w * width(), h * height());
    double width_ratio = copyI.width() / width();
    double height_ratio = copyI.height() / height();
    for (unsigned i = 0; i < height(); i++) {
        for (unsigned j = 0; j < width(); j++) {
            HSLAPixel& currentPixel = Image::getPixel(j, i);
            currentPixel = copyI.getPixel(j * width_ratio, i * height_ratio);
        }
    }
}