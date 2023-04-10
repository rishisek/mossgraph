#include "Image.h"
#include <cmath>
#include <iostream>

Image::Image() {}

Image::Image(unsigned int width, unsigned int height) {
    PNG(width, height);

}

//Darken an Image by decreasing the luminance of every pixel by 0.1.
//This function ensures that the luminance remains in the range [0, 1].

void Image::darken() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &pixel = getPixel(i, j);
            if (pixel.l - .1 < 0) {
                pixel.l = 0;
            } else {
                pixel.l -= .1;
            }
        }
    }
}

void Image::darken(double amount) {
    // PNG png(width(), height());
    for (unsigned int i = 0; i < width(); i++) {
        
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &pixel = getPixel(i,j);
            if (pixel.l - amount < 0) {
                pixel.l = 0;
            } else {
                pixel.l -= amount;
            }
        }
        
    }
}

void Image::lighten() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &pixel = getPixel(i, j);
            if (pixel.l + .1 > 1) {
                pixel.l = 1;
            } else {
                pixel.l += .1;
            }
        }
    }
}

void Image::lighten(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &pixel = getPixel(i, j);
            if (pixel.l + amount > 1) {
                pixel.l = 1;
            } else {
                pixel.l += amount;
            }
        }
    }
}

void Image::saturate() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &pixel = getPixel(i, j);
            if (pixel.s + .1 > 1) {
                pixel.s = 1;
            } else {
                pixel.s += .1;
            }
        }
    }
}
void Image::saturate(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &pixel = getPixel(i, j);
            if (pixel.s + amount > 1) {
                pixel.s = 1;
            } else {
                pixel.s += amount;
            }
        }
    }
}

void Image::desaturate() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &pixel = getPixel(i, j);
            if (pixel.s - .1 < 0) {
                pixel.s = 0;
            } else {
                pixel.s -= .1;
            }
        }
    }
}

void Image::desaturate(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &pixel = getPixel(i, j);
            if (pixel.s - amount < 0) {
                pixel.s = 0;
            } else {
                pixel.s -= amount;
            }
        }
    }
}


void Image::grayscale() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &pixel = getPixel(i, j);
            pixel.s = 0;
        }
    }
}

void Image::illinify() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &pixel = getPixel(i, j);
            if (std::abs(pixel.h - 11) < std::abs(pixel.h - 216)) {
                pixel.h = 11;
            } else {
                pixel.h = 216;
            }
        }
    }
}


void Image::rotateColor(double degrees) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &pixel = getPixel(i, j);
            if (pixel.h + degrees > 360) {
                double x = std::abs(pixel.h - 360);
                pixel.h = std::abs(degrees - x);
            } else if (pixel.h + degrees < 0) {
                double x = std::abs(pixel.h + degrees);
                pixel.h = std::abs(360 - x);
            } else {
                pixel.h += degrees;
            }
        }
    }
}

void Image::scale(double factor) {
    Image og = Image(*this);
    unsigned int new_width = factor * this->width();
    unsigned int new_height = factor * this->height();
    resize(new_width, new_height);
    for (unsigned int i = 0; i < new_width; i++) {
        for (unsigned int j = 0; j < new_height; j++) {
            int row = i / factor;
            int col = j / factor;
            // std::cout << "Made to Line 170" << std::endl;
            HSLAPixel &pixel = getPixel(i, j);
            // std::cout << "Made to Line 172" << std::endl;
            HSLAPixel &og_pix = og.getPixel(row, col);
            // std::cout << "Made to Line 174" << std::endl;
            pixel = og_pix;

        }
    }

}
void Image::scale(unsigned w, unsigned h) {
    double factor_w = (1.0 * w) / (1.0 * this->width());
    double factor_h = (1.0 * h) / (1.0 * this->height());
    std::cout << "W factor: " << factor_w << " H factor" << factor_h << std::endl;

    if (factor_w < factor_h) {
        scale(factor_w);
    } else if (factor_h < factor_w){
        scale(factor_h);
    } else{
        scale(factor_w);
    }
}