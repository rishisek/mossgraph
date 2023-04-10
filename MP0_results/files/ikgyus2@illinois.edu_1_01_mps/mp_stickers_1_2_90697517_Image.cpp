#include "Image.h"

#include <iostream>
#include <vector>
#include <cmath>

#include "cs225/HSLAPixel.h"

using namespace std;

Image::Image(unsigned width, unsigned height) : PNG(width,height) {}

void Image::lighten() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel& pix = getPixel(i,j);
            pix.l += 0.1;
            if (pix.l > 1) {
                pix.l = 1;
            } else if (pix.l < 0) {
                pix.l = 0;
            }
        }
    }
}
void Image::lighten(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel& pix = getPixel(i,j);
            pix.l += amount;
            if (pix.l > 1) {
                pix.l = 1;
            } else if ( pix.l < 0) {
                pix.l = 0;
            }
        }
    }
}

void Image::darken() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel& pix = getPixel(i,j);
            pix.l -= 0.1;
            if (pix.l < 0) {
                pix.l = 0;
            } else if (pix.l > 1) {
                pix.l = 1;
            }
        }
    }
}
void Image::darken(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel& pix = getPixel(i,j);
            pix.l -= amount;
            if (pix.l < 0) {
                pix.l = 0;
            } else if (pix.l > 1) {
                pix.l = 1;
            }
        }
    }
}
void Image::saturate() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel& pix = getPixel(i,j);
            pix.s += 0.1;
            if (pix.s > 1) {
                pix.s = 1;
            } else if (pix.s < 0) {
                pix.s = 0;
            }
        }
    }
}
void Image::saturate(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel& pix = getPixel(i,j);
            pix.s += amount;
            if (pix.s > 1) {
                pix.s = 1;
            } else if (pix.s < 0) {
                pix.s = 0;
            }
        }
    }
}
void Image::desaturate() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel& pix = getPixel(i,j);
            pix.s -= 0.1;
            if (pix.s < 0) {
                pix.s = 0;
            } else if (pix.s > 1) {
                pix.s = 1;
            }
        }
    }
}
void Image::desaturate(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel& pix = getPixel(i,j);
            pix.s -= amount;
            if (pix.s < 0) {
                pix.s = 0;
            } else if (pix.s > 1) {
                pix.s = 1;
            }
        }
    }
}
void Image::grayscale() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel& pix = getPixel(i,j);
            pix.s = 0;
        }
    }
}
void Image::rotateColor(double degrees) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel& pix = getPixel(i,j);
            pix.h += degrees;
            if (pix.h > 360) {
                pix.h -= 360;
            } if (pix.h < 0) {
                pix.h += 360;
            }
        }
    }
}

void Image::illinify() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel& pix = getPixel(i,j);
            if (pix.h > 113.5 && pix.h < 293.5) {
                pix.h = 216;
            } else {
                pix.h = 11;
            }
        }
    }
}

void Image::scale(double factor) {
    unsigned int width_tmp = width() * factor;
    unsigned int height_tmp = height() * factor;
    Image* pic = new Image();
    *pic = *this;
    resize(width_tmp, height_tmp);
    for (unsigned int i = 0; i < width_tmp; i++) {
        for (unsigned int j = 0; j < height_tmp; j++) {
            HSLAPixel& pix = getPixel(i, j);
            HSLAPixel& copix = pic->getPixel(i/factor, j/factor);
            pix = copix;
        }
    }
    delete pic;
}

// void Image::scale(double factor) {
//     Image* pic = new Image(*this);
//     this->resize(factor * width(), factor * height());
//     for (unsigned int i = 0; i < factor * width(); i++) {
//         for (unsigned int j = 0; j < factor * height(); j++) {
//             HSLAPixel& pix = getPixel(i/factor,j/factor);
//             HSLAPixel& copix = this->getPixel(i,j);
//             pix = copix;
//         }
//     }
//     delete pic;
// }

void Image::scale(unsigned w, unsigned h) {
    float factor;
    float width_ = (float)w / width();
    float height_ = (float)h / height();
    if (width_ * height() < h) {
        factor = width_;
    } else {
        factor = height_;
    }
    scale(factor);
}