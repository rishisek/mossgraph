#include "Image.h"
#include <cmath>

Image::Image() {
    PNG();
}
Image::Image(unsigned int width, unsigned int height) {
    PNG(width, height);
}

void Image::darken() {
    for(unsigned int i = 0; i < this->width(); i++) {
        for(unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel* pixel = &getPixel(i, j);
            pixel->l -= 0.1;
            if(pixel->l < 0) {
                pixel->l = 0;
            }
            else if(pixel->l > 1) {
                pixel->l = 1;
            }
        }
    }
}
void Image::darken(double amount) {
    for(unsigned int i = 0; i < this->width(); i++) {
        for(unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel* pixel = &getPixel(i, j);
            pixel->l -= amount;
            if(pixel->l < 0) {
                pixel->l = 0;
            }
            else if(pixel->l > 1) {
                pixel->l = 1;
            }
        }
    }
}

void Image::desaturate() {
    for(unsigned int i = 0; i < this->width(); i++) {
        for(unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel* pixel = &getPixel(i, j);
            pixel->s -= 0.1;
            if(pixel->s < 0) {
                pixel->s = 0;
            }
            else if(pixel->s > 1) {
                pixel->s = 1;
            }
        }
    }
}
void Image::desaturate(double amount) {
    for(unsigned int i = 0; i < this->width(); i++) {
        for(unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel* pixel = &getPixel(i, j);
            pixel->s -= amount;
            if(pixel->s < 0) {
                pixel->s = 0;
            }
            else if(pixel->s > 1) {
                pixel->s = 1;
            }
        }
    }
}

void Image::grayscale() {
    for(unsigned int i = 0; i < this->width(); i++) {
        for(unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel* pixel = &getPixel(i, j);
            pixel->s = 0;
        }
    }
}

void Image::illinify() {
    for(unsigned int i = 0; i < this->width(); i++) {
        for(unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel* pixel = &getPixel(i, j);
            if(std::abs(pixel->h - 11) < std::abs(pixel->h - 216)) {
                pixel->h = 11;
            }
            else {
                pixel->h = 216;
            }
        }
    }
}

void Image::lighten() {
    for(unsigned int i = 0; i < this->width(); i++) {
        for(unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel* pixel = &getPixel(i, j);
            pixel->l += 0.1;
            if(pixel->l < 0) {
                pixel->l = 0;
            }
            else if(pixel->l > 1) {
                pixel->l = 1;
            }
        }
    }
}
void Image::lighten(double amount) {
    for(unsigned int i = 0; i < this->width(); i++) {
        for(unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel* pixel = &getPixel(i, j);
            pixel->l += amount;
            if(pixel->l < 0) {
                pixel->l = 0;
            }
            else if(pixel->l > 1) {
                pixel->l = 1;
            }
        }
    }
}

void Image::rotateColor(double degrees) {
    for(unsigned int i = 0; i < this->width(); i++) {
        for(unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel* pixel = &getPixel(i, j);
            pixel->h += degrees;
            if(pixel->h > 360) {
                double truncated = pixel->h - (int) pixel->h;
                pixel->h = (int) pixel->h % 360;
                pixel->h += truncated;
            }
            else if(pixel->h < 0) {
                while(pixel->h < 0) {
                    pixel->h += 360;
                }
            }
        }
    }
}

void Image::saturate() {
    for(unsigned int i = 0; i < this->width(); i++) {
        for(unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel* pixel = &getPixel(i, j);
            pixel->s += 0.1;
            if(pixel->s < 0) {
                pixel->s = 0;
            }
            else if(pixel->s > 1) {
                pixel->s = 1;
            }
        }
    }
}
void Image::saturate(double amount) {
    for(unsigned int i = 0; i < this->width(); i++) {
        for(unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel* pixel = &getPixel(i, j);
            pixel->s += amount;
            if(pixel->s < 0) {
                pixel->s = 0;
            }
            else if(pixel->s > 1) {
                pixel->s = 1;
            }
        }
    }
}

void Image::scale(double factor) {
    Image copy = Image(*this);
    unsigned int old_w = width();
    unsigned int old_h = height();
    double new_width = width() * factor;
    double new_height = height() * factor;
    resize(new_width, new_height); 
    for(double i = 0; i < old_w; i += (1/factor)) {
        for(double j = 0; j < old_h; j += (1/factor)) {
            int map_x = i*factor;
            int map_y = j*factor;
            this->getPixel(map_x, map_y) = copy.getPixel((int)i, (int)j);
        }
    }
}

void Image::scale(unsigned w, unsigned h) {
    double factor1 = (double)w / (double)width();
    double factor2 = (double)h / (double)height();
    double factor_use;
    if((factor1 * height()) > h) {
        factor_use = factor2;
    }
    else {
        factor_use = factor1;
    }
    scale(factor_use);
}