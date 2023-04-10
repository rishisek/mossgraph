#include "Image.h"
using namespace std;
using namespace cs225;

Image::Image() {}
Image::Image(unsigned int x, unsigned int y) : PNG(x, y) {}
void Image::darken() {
    darken(0.1);
}
void Image::darken(double amount) {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            HSLAPixel & p = getPixel(w, h);
            p.l = p.l - amount;
            if (p.l > 1.0) {
                p.l = 1.0;
            } else if (p.l < 0.0) {
                p.l = 0.0;
            }
        }
    }
}
void Image::desaturate() {
    desaturate(0.1);
}
void Image::desaturate(double amount) {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            HSLAPixel & p = getPixel(w, h);
            p.s = p.s - amount;
            if (p.s < 0.0) {
                p.s = 0.0;
            } else if ( p.s > 1.0) {
                p.s = 1.0;
            }
        }
    }
}
void Image::grayscale() {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            HSLAPixel & p = getPixel(w, h);
            p.s = 0;
        }
    }
}
void Image::illinify() {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            HSLAPixel & p = getPixel(w, h);
            if (p.h <= 293.5 && p.h >= 113.5) {
                p.h = 216.0;
            } else {
                p.h = 11.0;
            }
        }
    }
}
void Image::lighten() {
    lighten(0.1);
}
void Image::lighten(double amount) {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            HSLAPixel & p = getPixel(w, h);
            p.l = p.l + amount;
            if (p.l > 1.0) {
                p.l = 1.0;
            } else if (p.l < 0.0) {
                p.l = 0.0;
            }
        }
    }
}
void Image::rotateColor(double degrees) {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            HSLAPixel & p = getPixel(w, h);
            p.h = p.h + degrees;
            while (p.h > 360.0) {
                p.h = p.h - 360.0;
            }
            while (p.h < 0.0) {
                p.h = p.h + 360.0;
            }
        }
    }
}
void Image::saturate() {
    saturate(0.1);
}
void Image::saturate(double amount) {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            HSLAPixel & p = getPixel(w, h);
            p.s = p.s + amount;
            if (p.s < 0.0) {
                p.s = 0.0;
            } else if ( p.s > 1.0) {
                p.s = 1.0;
            }
        }
    }
}
void Image::scale(double factor) {
    unsigned int w = width();
    unsigned int h = height();
    Image* new_image = new Image();
    new_image->resize(w, h);
    for (unsigned int i = 0; i < w; i++) {
        for (unsigned int j = 0; j < h; j++) {
            HSLAPixel & new_p = new_image->getPixel(i,j);
            HSLAPixel & old_p = getPixel(i,j);
            new_p = old_p;
        }
    }
    resize(width()*factor, height()*factor);
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & new_p = getPixel(i,j);
            HSLAPixel & old_p = new_image->getPixel(i / factor,j / factor);
            new_p = old_p;
        }
    }
    delete new_image;
}
void Image::scale(unsigned int w, unsigned int h) {
    double factor = (double)w/(double)width();
    if ((double)h/(double)height() <  factor) {
        factor = (double)h/(double)height();
    }
    scale(factor);
}