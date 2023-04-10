#include "Image.h"
using namespace cs225;
#include <cmath>

Image::Image() {
}

Image::Image(unsigned int width, unsigned int height) {
    total_ = width + height;
}

void Image::lighten() {
    for (unsigned int row = 0; row < width(); row++) {
        for (unsigned int col = 0; col < height(); col++) {
            if (getPixel(row, col).l <= 0.9) {
                getPixel(row, col).l = getPixel(row, col).l + 0.1;
            } else {
                getPixel(row, col).l = 1;
            }
        }
    }
}

void Image::lighten(double amount) {
    for (unsigned int row = 0; row < width(); row++) {
        for (unsigned int col = 0; col < height(); col++) {
            if (getPixel(row, col).l <= (1 - amount)) {
                getPixel(row, col).l = getPixel(row, col).l + amount;
            } else {
                getPixel(row, col).l = 1;
            }
        }
    }
}

void Image::darken() {
    for (unsigned int row = 0; row < width(); row++) {
        for (unsigned int col = 0; col < height(); col++) {
            if (getPixel(row, col).l >= 0.1) {
                getPixel(row, col).l = getPixel(row, col).l - 0.1;
            } else {
                getPixel(row, col).l = 0;
            }
        }
    }
}

void Image::darken(double amount) {
    for (unsigned int row = 0; row < width(); row++) {
        for (unsigned int col = 0; col < height(); col++) {
            if (getPixel(row, col).l >= amount) {
                getPixel(row, col).l = getPixel(row, col).l - amount;
            } else {
                getPixel(row, col).l = 0;
            }
        }
    }
}

void Image::saturate() {
    for (unsigned int row = 0; row < width(); row++) {
        for (unsigned int col = 0; col < height(); col++) {
            if (getPixel(row, col).s <= 0.9) {
                getPixel(row, col).s = getPixel(row, col).s + 0.1;
            } else {
                getPixel(row, col).s = 1;
            }
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned int row = 0; row < width(); row++) {
        for (unsigned int col = 0; col < height(); col++) {
            if (getPixel(row, col).s <= (1 - amount)) {
                getPixel(row, col).s = getPixel(row, col).s + amount;
            } else {
                getPixel(row, col).s = 1;
            }
        }
    }
}

void Image::desaturate() {
    for (unsigned int row = 0; row < width(); row++) {
        for (unsigned int col = 0; col < height(); col++) {
            if (getPixel(row, col).s >= 0.1) {
                getPixel(row, col).s = getPixel(row, col).s - 0.1;
            } else {
                getPixel(row, col).s = 0;
            }
        }
    }
}

void Image::desaturate(double amount) {
    for (unsigned int row = 0; row < width(); row++) {
        for (unsigned int col = 0; col < height(); col++) {
            if (getPixel(row, col).s >= amount) {
                getPixel(row, col).s = getPixel(row, col).s - amount;
            } else {
                getPixel(row, col).s = 0;
            }
        }
    }
}

void Image::grayscale() {
    for (unsigned int row = 0; row < width(); row++) {
        for (unsigned int col = 0; col < height(); col++) {
            getPixel(row, col).s = 0;
        }
    }
}

void Image::rotateColor(double degrees) {
    for (unsigned int row = 0; row < width(); row++) {
        for (unsigned int col = 0; col < height(); col++) {
            getPixel(row, col).h = getPixel(row, col).h + degrees;
            if (getPixel(row, col).h > 360) {
                getPixel(row, col).h = getPixel(row, col).h - 360;
            } else if (getPixel(row, col).h < 0) {
                getPixel(row, col).h = getPixel(row, col).h + 360;
            }
        }
    }
}

void Image::illinify() {
    for (unsigned int row = 0; row < width(); row++) {
        for (unsigned int col = 0; col < height(); col++) {
            if (getPixel(row, col).h <= 113.5 || getPixel(row, col).h <= 293.5) {
                getPixel(row, col).h = 11;
            } else {
                getPixel(row, col).h = 216;
            }
        }
    }
}

void Image::scale(double factor) {
    // Firstly, store the original image
    Image stored = *this;

    // Assign new heights and widths that scaled image will have
    unsigned int w2 = width() * factor;
    unsigned int h2 = height() * factor;

    // ratio will act as steppers so we know which pixels to grab
    double ratio = 1 / factor;

    // And resize
    resize(factor*width(), factor*height());

    for (unsigned int x = 0; x < w2; x++) {
        for (unsigned int y = 0; y < h2; y++) {

            getPixel(x, y) = stored.getPixel(floor(ratio*x), floor(ratio*y));
        }
    }
}

void Image::scale(unsigned w, unsigned h) {
    // Firstly, store the original image
    Image stored = *this;

    //Find new w2 and h2 and factor
    
    double x_factor = double(w) / double(width());
    double y_factor = double(h) /  double(height());

    double factor;
    if (x_factor < y_factor) {
        factor = x_factor;
    } else {
        factor = y_factor;
    }

    // Assign new heights and widths that scaled image will have
    unsigned int w2 = width() * factor;
    unsigned int h2 = height() * factor;

    // And resize
    resize(w2, h2);
    double ratio = 1 / factor;

    for (unsigned int x = 0; x < w2; x++) {
        for (unsigned int y = 0; y < h2; y++) {

            getPixel(x, y) = stored.getPixel(floor(ratio*x), floor(ratio*y));
        }
    }
}




