// Include statements
#include "Image.h"
#include "../lib/cs225/PNG.h"
using namespace cs225;
#include <cmath>
#include <iostream>

// // ------------------------------------------------------------------------------------------------
// // DEFAULT CONSTRUCTOR
// // ------------------------------------------------------------------------------------------------
// Image::Image() {
//     PNG();
// }

// // ------------------------------------------------------------------------------------------------
// // PARAMERIZED CONSTRUCTOR
// // ------------------------------------------------------------------------------------------------
// Image::Image(unsigned int width, unsigned int height) {
//     PNG(width, height);
// }

// ------------------------------------------------------------------------------------------------
// DARKEN
// Decreases luminance by 0.1
// ------------------------------------------------------------------------------------------------
void Image::darken() {
    for (unsigned int r = 0; r < PNG::height(); r++) {
        for (unsigned int c = 0; c < PNG::width(); c++) {
            if (PNG::getPixel(c, r).l - 0.1 >= 0) { 
                PNG::getPixel(c, r).l -= 0.1;
            } else {
                PNG::getPixel(c, r).l = 0;
            }
        }
    }
}

// ------------------------------------------------------------------------------------------------
// DARKEN AMOUNT
// Decreases luminance by given amount
// ------------------------------------------------------------------------------------------------
void Image::darken(double amount) {
    for (unsigned int r = 0; r < PNG::height(); r++) {
        for (unsigned int c = 0; c < PNG::width(); c++) {
            if ((PNG::getPixel(c, r).l - amount >= 0) && (PNG::getPixel(c, r).l - amount <= 1)) {
                PNG::getPixel(c, r).l -= amount;
            } else { 
                PNG::getPixel(c, r).l = 0;
            }
        }
    }
}

// ------------------------------------------------------------------------------------------------
// DESATURATE
// Desaturates image by decreasing saturation by 0.1
// ------------------------------------------------------------------------------------------------
void Image::desaturate() {
    for (unsigned int r = 0; r < PNG::height(); r++) {
        for (unsigned int c = 0; c < PNG::width(); c++) {
            if (PNG::getPixel(c, r).s - 0.1 >= 0) {
                PNG::getPixel(c, r).s -= 0.1;
            } else {
                PNG::getPixel(c, r).s = 0;
            }
        }
    }
}

// ------------------------------------------------------------------------------------------------
// DESATURATE AMOUNT
// Desaturates image by decreasing saturation by given amount
// ------------------------------------------------------------------------------------------------
void Image::desaturate(double amount) {
    for (unsigned int r = 0; r < PNG::height(); r++) {
        for (unsigned int c = 0; c < PNG::width(); c++) {
            if ((PNG::getPixel(c, r).s - amount >= 0) && (PNG::getPixel(c, r).s - amount <= 1)) {
                PNG::getPixel(c, r).s -= amount;
            } else {
                PNG::getPixel(c, r).s = 0;
            }
        }
    }
}

// ------------------------------------------------------------------------------------------------
// GRAYSCALE
// ------------------------------------------------------------------------------------------------
void Image::grayscale() {
   for (unsigned int r = 0; r < PNG::height(); r++) {
        for (unsigned int c = 0; c < PNG::width(); c++) {
            PNG::getPixel(c, r).s = 0;
        }
    } 
}

// ------------------------------------------------------------------------------------------------
// ILLINIFY
// Sets Hue values of every pixel to either orange or blue based on whether the
// pixel's hue value is closer to orange than blue
// ------------------------------------------------------------------------------------------------
void Image::illinify() {
    for (unsigned int r = 0; r < PNG::height(); r++) {
        for (unsigned int c = 0; c < PNG::width(); c++) {
            double hue = PNG::getPixel(c, r).h;
            // If hue is closer to 11 (Orange), set h = 11
            if ((std::abs(371 - hue)) < (std::abs(216 - hue))) {
                PNG::getPixel(c, r).h = 11;
            // else, set h = 216
            } else {
                PNG::getPixel(c, r).h = 216;
            }
        }
    } 
}

// ------------------------------------------------------------------------------------------------
// LIGHTEN
// Increases l by 0.1
// ------------------------------------------------------------------------------------------------
void Image::lighten() {
    for (unsigned int r = 0; r < PNG::height(); r++) {
        for (unsigned int c = 0; c < PNG::width(); c++) {
            if (PNG::getPixel(c, r).l + 0.1 <= 1) {
                PNG::getPixel(c, r).l += 0.1;
            } else {
                PNG::getPixel(c, r).l = 1;
            }
        }
    }
}

// ------------------------------------------------------------------------------------------------
// LIGHTEN AMOUNT
// Increases l by amount
// ------------------------------------------------------------------------------------------------
void Image::lighten(double amount) {
    for (unsigned int r = 0; r < PNG::height(); r++) {
        for (unsigned int c = 0; c < PNG::width(); c++) {
            if ((PNG::getPixel(c, r).l + amount <= 1) && (PNG::getPixel(c, r).l + amount >= 0)) {
                PNG::getPixel(c, r).l += amount;
            } else {
                PNG::getPixel(c, r).l = 1;
            }
        }
    }
}

// ------------------------------------------------------------------------------------------------
// ROTATE COLOR
// Rotating in a positive direction increases the degree of the hue. 
// ------------------------------------------------------------------------------------------------
void Image::rotateColor(double degrees) {
    for (unsigned int r = 0; r < PNG::height(); r++) {
        for (unsigned int c = 0; c < PNG::width(); c++) {
            if (PNG::getPixel(c, r).h + degrees >= 360) {
                PNG::getPixel(c, r).h = PNG::getPixel(c, r).h + degrees - 360;
            } else if (PNG::getPixel(c, r).h + degrees <= 0) {
                PNG::getPixel(c, r).h = PNG::getPixel(c, r).h + degrees + 360;
            } else {
                PNG::getPixel(c, r).h += degrees;
            }
        }
    }
}

// ------------------------------------------------------------------------------------------------
// SATURATE
// Saturates an Image by increasing the saturation of every pixel by 0.1.
// ------------------------------------------------------------------------------------------------
void Image::saturate() {
    for (unsigned int r = 0; r < PNG::height(); r++) {
        for (unsigned int c = 0; c < PNG::width(); c++) {
            if (PNG::getPixel(c, r).s + 0.1 <= 1) {
                PNG::getPixel(c, r).s += 0.1;
            } else {
                PNG::getPixel(c, r).s = 1;
            }
        }
    }
}

// ------------------------------------------------------------------------------------------------
// SATURATE AMOUNT
// Saturates an Image by increasing the saturation of every pixel by amount.
// ------------------------------------------------------------------------------------------------
void Image::saturate(double amount) {
    for (unsigned int r = 0; r < PNG::height(); r++) {
        for (unsigned int c = 0; c < PNG::width(); c++) {
            if ((PNG::getPixel(c, r).s + amount <= 1) && (PNG::getPixel(c, r).s + amount >= 0)) {
                PNG::getPixel(c, r).s += amount;
            } else {
                PNG::getPixel(c, r).s = 1;
            }
        }
    }
}

// ------------------------------------------------------------------------------------------------
// SCALE
// ------------------------------------------------------------------------------------------------
void Image::scale(double factor) {
    // Storing a copy of current image to change into new image
    if (factor == 1) {
        return;
    }
    unsigned int new_width = width() * factor;
    unsigned int new_height = height() * factor;

    Image copy_image = Image(*this);

    resize(new_width, new_height);

    for (unsigned int w = 0; w < new_width; w++) {
        for (unsigned int h = 0; h < new_height; h++) {
            HSLAPixel &originalPixel = PNG::getPixel(w, h);
            HSLAPixel &copyPixel = copy_image.getPixel(w / factor, h / factor);
            originalPixel = copyPixel;
        }
    }
}

// ------------------------------------------------------------------------------------------------
// SCALE with Amount
// ------------------------------------------------------------------------------------------------
void Image::scale(unsigned w, unsigned h) {
    // Finding ratio of w and h:
    double heightRatio = (h * 1.0) / height();
    double widthRatio = (w * 1.0) / width();
    // Seeing which ratio is smaller:
    if (heightRatio < widthRatio) {
        scale(heightRatio);
    } else {
        scale(widthRatio);
    }
}
