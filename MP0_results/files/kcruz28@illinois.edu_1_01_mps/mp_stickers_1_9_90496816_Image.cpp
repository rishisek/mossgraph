#include "Image.h"
#include <cmath>

void Image::lighten() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            cs225::HSLAPixel & the_pixel = getPixel(x, y);
            if (the_pixel.l + 0.1 > 1.0) {
                the_pixel.l = 1.0;
            } else {
                the_pixel.l += 0.1;
            }
        }
    }
}



void Image::lighten(double amount) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            cs225::HSLAPixel & the_pixel = getPixel(x, y);
            if (the_pixel.l + 0.1 > 1.0) {
                the_pixel.l = 1.0;
            } else {
                the_pixel.l += amount;
            }
        }
    }
}


void Image::darken() {
     for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            cs225::HSLAPixel & the_pixel = getPixel(x, y);
            if (the_pixel.l <= 1 && the_pixel.l > 0) {
                the_pixel.l -= 0.1;
            }
        }
    }
}

void Image::darken(double amount) {
     for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            cs225::HSLAPixel & the_pixel = getPixel(x, y);
            if (the_pixel.l - 0.1 < 0) {
                the_pixel.l = 0;
            } else {
                the_pixel.l -= amount;
            }
        }
    }
}

void Image::saturate() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            cs225::HSLAPixel & the_pixel = getPixel(x, y);
            if (the_pixel.s < 1 && the_pixel.s >= 0) {
                the_pixel.s += 0.1;
            }
        }
    }
}


void Image::saturate(double amount) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            cs225::HSLAPixel & the_pixel = getPixel(x, y);
            if (the_pixel.s < 1 && the_pixel.s >= 0) {
                the_pixel.s += amount;
            }
        }
    }
}

void Image::desaturate() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            cs225::HSLAPixel & the_pixel = getPixel(x, y);
            if (the_pixel.s <= 1 && the_pixel.s > 0) {
                the_pixel.s -= 0.1;
            }
        }
    }
}

void Image::desaturate(double amount) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            cs225::HSLAPixel & the_pixel = getPixel(x, y);
            if (the_pixel.s <= 1 && the_pixel.s > 0) {
                the_pixel.s -= amount;
            }
        }
    }
}

void Image::grayscale() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            cs225::HSLAPixel & the_pixel = getPixel(x, y);
            the_pixel.s = 0;
        }
    }
}

void Image::rotateColor(double degrees) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            cs225::HSLAPixel & the_pixel = getPixel(x, y);
            if (degrees > 0) {
                if (the_pixel.h + degrees > 360) {
                    the_pixel.h = degrees - (360 - the_pixel.h);
                } else {
                    the_pixel.h += degrees;
                }
            } else {
                if (the_pixel.h + degrees < 0) {
                    the_pixel.h = 360 + (the_pixel.h += degrees); 
                
                } else {
                    the_pixel.h += degrees;
                }
            }      
        }
    }
}

void Image::illinify() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            cs225::HSLAPixel & the_pixel = getPixel(x, y);
            // if (the_pixel.h < 360 && the_pixel.h >= 0) {
            //     the_pixel.h = 216;
            // }
            if (std::abs(the_pixel.h - 216) < std::abs(the_pixel.h -  11)) {
                the_pixel.h = 11;
            } else {
                the_pixel.h = 216;
            }
            
        }
    }
}

void Image::scale(double factor) {
    unsigned int x_scale = (unsigned int)(this ->width() * factor);
    unsigned int y_scale = (unsigned int)(this ->height() * factor);

    Image copy = *this;

    this -> resize(x_scale, y_scale);

    for (unsigned int x = 0; x < this->width(); x++) {
        for (unsigned int y = 0; y < this->height(); y++) {
            cs225::HSLAPixel & the_pixel = copy.getPixel((int)x/factor, (int)y/factor);
            this->getPixel(x, y) = the_pixel;
        }
    }
}

void Image::scale(unsigned int w, unsigned int h) {
   double x_scale = (double) w / width();
   double y_scale = (double) h / height();

    if (x_scale < y_scale) {
        scale(x_scale);
    } else {
        scale(y_scale);
    }
   
   
}