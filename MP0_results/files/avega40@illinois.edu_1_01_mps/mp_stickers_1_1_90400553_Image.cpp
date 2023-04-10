#include "Image.h"

using namespace std;
using namespace cs225;

Image::Image() {}

Image::Image(unsigned int w, unsigned int h) : PNG (w, h) {}

void Image::darken() {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            if (getPixel(w,h).l == 0) {
            } else {
                getPixel(w,h).l = getPixel(w,h).l - 0.1;
            }
        }
    }
}

void Image::darken(double amount) {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            if (getPixel(w,h).l - amount <= 0) {
                getPixel(w,h).l = 0;
            } else {
                getPixel(w,h).l = getPixel(w,h).l - amount;
            }
        }
    }
}

void Image::desaturate() {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            if (getPixel(w,h).s == 0) {
            } else {
                getPixel(w,h).s = getPixel(w,h).s - 0.1;
            }
        }
    }
}

void Image::desaturate(double amount) {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            if (getPixel(w,h).s - amount <= 0) {
                getPixel(w,h).s = 0;
            } else {
                getPixel(w,h).s = getPixel(w,h).s - amount;
            }
        }
    }
}

void Image::grayscale() {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            getPixel(w,h).s = 0;
        }
    }
}

void Image::illinify() {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            if(getPixel(w,h).h > 113.5 || getPixel(w,h).h < 293.5) {
                getPixel(w,h).h = 216;
            } else {
                getPixel(w,h).h = 11;
            }
        }
    }
}

void Image::lighten() {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            if (getPixel(w,h).l + 0.1 >= 1) {
                getPixel(w,h).l = 1;
            } else {
                getPixel(w,h).l = getPixel(w,h).l + 0.1;
            }
        }
    }
}

void Image::lighten(double amount) {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            if (getPixel(w,h).l + amount >= 1) {
                getPixel(w,h).l = 1;
            } else {
                getPixel(w,h).l = getPixel(w,h).l + amount;
            }
        }
    }
}

void Image::rotateColor(double degrees) {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            if (getPixel(w,h).h + degrees > 360) {
                getPixel(w,h).h = getPixel(w,h).h + degrees - 360;
            } else if (getPixel(w,h).h + degrees < 0) {
                getPixel(w,h).h = getPixel(w,h).h + degrees + 360;
            } else {
                getPixel(w,h).h = getPixel(w,h).h + degrees;
            }
        }
    }
}

void Image::saturate() {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            if (getPixel(w,h).s == 1) {
            } else {
                getPixel(w,h).s = getPixel(w,h).s + 0.1;
            }
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            if (getPixel(w,h).l + amount >= 1) {
                getPixel(w,h).s = 1;
            } else {
                getPixel(w,h).s = getPixel(w,h).s + amount;
            }
        }
    }
}

void Image::scale(double factor) {
    unsigned int w = width() * factor;
    unsigned int h = height() * factor;
    Image *i = new Image();
    (*i).resize(w,h);
    for (unsigned int w_ = 0; w_ < w; w_++) {
        for (unsigned int h_ = 0; h_ < h; h_++) {
            HSLAPixel & old = (*this).getPixel(w_/factor, h_/factor);
            HSLAPixel & knew = (*i).getPixel(w_,h_);
            knew = old;
        }
    }
    *this = *i;
    delete i;
}

void Image::scale(unsigned w, unsigned h) {
    double f = min(double(w) / double(width()), double(h) / double (height()));
    scale(f);
}