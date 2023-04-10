#include "Image.h"

Image::Image() {
    PNG();
}

Image::Image(unsigned int width, unsigned int height) {
    PNG(width, height);
}

void Image::lighten() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &p = getPixel(i, j);
            p.l += 0.1;
            if (p.l > 1) {
                p.l = 1;
            }
        } 
    }
}

void Image::lighten(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &p = getPixel(i, j);
            p.l += amount;
            if (p.l > 1) {
                p.l = 1;
            }
        } 
    }
}

void Image::darken() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &p = getPixel(i, j);
            p.l -= 0.1;
            if (p.l < 0) {
                p.l = 0;
            }
        } 
    }
}

void Image::darken(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &p = getPixel(i, j);
            p.l -= amount;
            if (p.l < 0) {
                p.l = 0;
            }
        } 
    }
}

void Image::saturate() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &p = getPixel(i, j);
            p.s += 0.1;
            if (p.s > 1) {
                p.s = 1;
            }
        } 
    }
}

void Image::saturate(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &p = getPixel(i, j);
            p.s += amount;
            if (p.s > 1) {
                p.s = 1;
            }
        } 
    }
}

void Image::desaturate() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &p = getPixel(i, j);
            p.s -= 0.1;
            if (p.s < 0) {
                p.s = 0;
            }
        } 
    }
}

void Image::desaturate(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &p = getPixel(i, j);
            p.s -= amount;
            if (p.s < 0) {
                p.s = 0;
            }
        } 
    }
}

void Image::grayscale() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &p = getPixel(i, j);
            p.s = 0;
        } 
    }
}

void Image::rotateColor(double degrees) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &p = getPixel(i, j);
            p.h += degrees;
            if (p.h < 0) {
                p.h += 360;
            }
            
            if (p.h > 360) {
                p.h -= 360;
            }
        } 
    }
}

void Image::illinify() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &p = getPixel(i, j);
            if (p.h > 113.5 && p.h < 293.5) {
                p.h = 216;
            } else {
                p.h = 11;
            }
        } 
    }
}

void Image::scale(double factor) {
    Image newImage(*this);
    unsigned scaled_w = width() * factor;
    unsigned scaled_h = height() * factor;
    resize(scaled_w, scaled_h);
    for (unsigned int i = 0; i < scaled_w; i++) {
        for (unsigned int j = 0; j < scaled_h; j++) {
            HSLAPixel &p = getPixel(i, j);
            HSLAPixel &newP = newImage.getPixel((int)(i / factor), (int)(j / factor));
            p = newP;
        } 
    }
}

void Image::scale(unsigned w, unsigned h) {
    double width = (double)w / (double) this->width();
    double height = (double)h / (double) this->height();
    if (width < height) {
        scale(width);
    } else {
        scale(height);
    }
}