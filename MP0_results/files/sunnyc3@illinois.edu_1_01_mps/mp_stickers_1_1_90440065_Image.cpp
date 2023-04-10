#include "Image.h"

Image::Image() {
    PNG();
}

Image::Image(unsigned int width, unsigned int height) {
    PNG(width, height);
}

void Image::darken() {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel* curPixel = &getPixel(i,j);
            curPixel->l -= 0.1;
            if (curPixel->l < 0.0) {
                curPixel->l = 0.0;
            } 
            else if (curPixel->l > 1.0) {
                curPixel->l = 1.0;
            }
        }
    }
}

void Image::darken(double amount) {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel* curPixel = &getPixel(i,j);
            curPixel->l -= amount;
            if (curPixel->l < 0.0) {
                curPixel->l = 0.0;
            } 
            else if (curPixel->l > 1.0) {
                curPixel->l = 1.0;
            }
        }
    }
}

void Image::desaturate() {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel* curPixel = &getPixel(i,j);
            curPixel->s -= 0.1;
            if (curPixel->s < 0.0) {
                curPixel->s = 0.0;
            } 
            else if (curPixel->s > 1.0) {
                curPixel->s = 1.0;
            }
        }
    }
}

void Image::desaturate(double amount) {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel* curPixel = &getPixel(i,j);
            curPixel->s -= amount;
            if (curPixel->s < 0.0) {
                curPixel->s = 0.0;
            } 
            else if (curPixel->s > 1.0) {
                curPixel->s = 1.0;
            }
        }
    }
}

void Image::grayscale() {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel* curPixel = &getPixel(i,j);
            curPixel->s = 0.0;
        }
    }
}

void Image::illinify() {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel* curPixel = &getPixel(i,j);
            if ((curPixel->h < 113.5) ||
                (curPixel->h > 293.5)) {
                curPixel->h = 11;
            } 
            else {
                curPixel->h = 216;
            }
        }
    }
}

void Image::lighten() {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel* curPixel = &getPixel(i,j);
            curPixel->l += 0.1;
            if (curPixel->l < 0.0) {
                curPixel->l = 0.0;
            }
            else if (curPixel->l > 1.0) {
                curPixel->l = 1.0;
            }
        }
    }
}

void Image::lighten(double amount) {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel* curPixel = &getPixel(i,j);
            curPixel->l += amount;
            if (curPixel->l < 0.0) {
                curPixel->l = 0.0;
            }
            else if (curPixel->l > 1.0) {
                curPixel->l = 1.0;
            }
        }
    }
}

void Image::rotateColor(double degrees) {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel* curPixel = &getPixel(i,j);
            curPixel->h += degrees;
            while (curPixel->h > 360.0) {
                curPixel->h -= 360.0;
            }
            while (curPixel->h < 0.0) {
                curPixel->h += 360.0;
            }
        }
    }
}

void Image::saturate() {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel* curPixel = &getPixel(i,j);
            curPixel->s += 0.1;
            if (curPixel->s < 0.0) {
                curPixel->s = 0.0;
            }
            else if (curPixel->s > 1.0) {
                curPixel->s = 1.0;
            }
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned int i = 0; i < this->width(); i++) {
        for (unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel* curPixel = &getPixel(i,j);
            curPixel->s += amount;
            if (curPixel->s < 0.0) {
                curPixel->s = 0.0;
            }
            else if (curPixel->s > 1.0) {
                curPixel->s = 1.0;
            }
        }
    }
}

void Image::scale(double factor) {
    Image copy = Image(*this);
    unsigned int old_w = width();
    unsigned int old_h = height();
    this->resize(this->width()*factor, this->height()*factor);
    for (double i = 0; i < old_w; i += (1/factor)) {
        for (double j = 0; j < old_h; j+= (1/factor)) {
            this->getPixel(i*factor, j*factor) = copy.getPixel((int) i, (int) j);
        }
    }
}

void Image::scale(unsigned w, unsigned h) {
    double width_factor = (double) w / (double) this->width();
    double height_factor = (double) h / (double) this->height();
    if (width_factor <= height_factor) {
        scale(width_factor);
    }
    else {
        scale(height_factor);
    }
}