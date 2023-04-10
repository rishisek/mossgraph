#include "Image.h"

Image::Image() {
    PNG();
}
Image::Image(unsigned int width, unsigned int height) {
    PNG(width, height);
}

void Image::darken() {
    unsigned int width = PNG::width();
    unsigned int height = PNG::height();
    for (unsigned int x=0; x < width; x++) {
        for (unsigned int y=0; y < height; y++) {
            cs225::HSLAPixel &current = getPixel(x, y);
            if (current.l >= 0.1) {
                current.l = current.l - 0.1;
            } else {
                current.l = 0;
            }
        }
    }
}
void Image::darken(double amount) {
    for (unsigned int x=0; x < width(); x++) {
        for (unsigned int y=0; y < height(); y++) {
            cs225::HSLAPixel &current = getPixel(x, y);
            if (current.l >= amount) {
                current.l = current.l - amount;
            } else {
                current.l = 0;
            }
        }
    }
}

void Image::desaturate() {
    for (unsigned int x=0; x < width(); x++) {
        for (unsigned int y=0; y < height(); y++) {
            cs225::HSLAPixel &current = getPixel(x, y);
            if (current.s >= 0.1) {
                current.s = current.s - 0.1;
            } else {
                current.s = 0;
            }
        }
    }
}
void Image::desaturate(double amount) {
    for (unsigned int x=0; x < width(); x++) {
        for (unsigned int y=0; y < height(); y++) {
            cs225::HSLAPixel &current = getPixel(x, y);
            if (current.s >= amount) {
                current.s = current.s - amount;
            } else {
                current.s = 0;
            }
        }
    }
}

void Image::grayscale() {
    for (unsigned int x=0; x < width(); x++) {
        for (unsigned int y=0; y < height(); y++) {
            cs225::HSLAPixel &current = getPixel(x, y);
            current.s = 0;
        }
    }
}

void Image::illinify() {
    for (unsigned int x=0; x < width(); x++) {
        for (unsigned int y=0; y < height(); y++) {
            cs225::HSLAPixel &current = getPixel(x, y);
            if (current.h >= 113.5 || current.h <= 293.5) {
                current.h = 216;
            } else {
                current.h = 11;
            }
        }
    }
}

void Image::lighten() {
    for (unsigned int x=0; x < width(); x++) {
        for (unsigned int y=0; y < height(); y++) {
            cs225::HSLAPixel &current = getPixel(x, y);
            if ((1-current.l) >= 0.1) {
                current.l = current.l + 0.1;
            } else {
                current.l = 1;
            }
        }
    }
}
void Image::lighten(double amount) {
    for (unsigned int x=0; x < width(); x++) {
        for (unsigned int y=0; y < height(); y++) {
            cs225::HSLAPixel &current = getPixel(x, y);
            if ((1-current.l) >= amount) {
                current.l = current.l + amount;
            } else {
                current.l = 1;
            }
        }
    }
}

void Image::rotateColor(double degrees) {
    for (unsigned int x=0; x < width(); x++) {
        for (unsigned int y=0; y < height(); y++) {
            cs225::HSLAPixel &current = getPixel(x, y);
            if (degrees >= 0) {
                if ((degrees + current.h) > 360) {
                    current.h = degrees + current.h - 360;
                } else {
                    current.h = degrees + current.h;
                }
            } else {
                if ((degrees + current.h) < 0) {
                    current.h = degrees + current.h + 360;
                } else {
                    current.h = degrees + current.h;
                }
            }
        }
    }
}

void Image::saturate() {
    for (unsigned int x=0; x < width(); x++) {
        for (unsigned int y=0; y < height(); y++) {
            cs225::HSLAPixel &current = getPixel(x, y);
            if ((1-current.s) >= 0.1) {
                current.s = current.s + 0.1;
            } else {
                current.s = 1;
            }
        }
    }
}
void Image::saturate(double amount) {
    for (unsigned int x=0; x < width(); x++) {
        for (unsigned int y=0; y < height(); y++) {
            cs225::HSLAPixel &current = getPixel(x, y);
            if ((1-current.s) >= amount) {
                current.s = current.s + amount;
            } else {
                current.s = 1;
            }
        }
    }
}

void Image::scale(double factor) {
    unsigned int width = PNG::width() * factor;
    unsigned int height = PNG::height() * factor;
    Image temp;
    temp.resize(width, height);
    for (unsigned int x=0; x < width; x++) {
        for (unsigned int y=0; y < height; y++) {
            temp.getPixel(x, y) = getPixel(x / factor, y / factor);
        }
    }
    resize(width, height);
    for (unsigned int x=0; x < width; x++) {
        for (unsigned int y=0; y < height; y++) {
            getPixel(x, y) = temp.getPixel(x, y);
        }
    }
}
void Image::scale(unsigned w, unsigned h) {//doesn't work for down sizing
    double w_factor = static_cast<double>(w) / PNG::width();
    double h_factor = static_cast<double>(h) / PNG::height();
    if (w_factor <= h_factor) {
        scale(w_factor);
    } else {
        scale(h_factor);
    }
}