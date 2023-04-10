#include "Image.h"
#include <cmath>
#include <iostream>

Image::Image() {

}

Image::Image(unsigned int width, unsigned int height) {
    PNG(width, height);
}

void Image::lighten() {
    for(unsigned int i = 0; i < height(); i++) {
        for(unsigned int j = 0; j < width(); j++) {
            if(getPixel(j, i).l + 0.1 <= 1) {
                getPixel(j, i).l += 0.1;
            }
            else {
                getPixel(j, i).l = 1;
            }
        }
    }
}

void Image::lighten(double amount) {
    for(unsigned int i = 0; i < height(); i++) {
        for(unsigned int j = 0; j < width(); j++) {
            if(getPixel(j, i).l + amount <= 1) {
                getPixel(j, i).l += amount;
            }
            else {
                getPixel(j, i).l = 1;
            }
        }
    }
}

void Image::darken() {
    for(unsigned int i = 0; i < height(); i++) {
        for(unsigned int j = 0; j < width(); j++) {
            if(getPixel(j, i).l - 0.1 >= 0) {
                getPixel(j, i).l -= 0.1;
            }
            else {
                getPixel(j, i).l = 0;
            }
        }
    }
}

void Image::darken(double amount) {
    for(unsigned int i = 0; i < height(); i++) {
        for(unsigned int j = 0; j < width(); j++) {
            if(getPixel(j, i).l - amount >= 0) {
                getPixel(j, i).l -= amount;
            }
            else {
                getPixel(j, i).l = 0;
            }
        }
    }
}

void Image::saturate() {
    for(unsigned int i = 0; i < height(); i++) {
        for(unsigned int j = 0; j < width(); j++) {
            if(getPixel(j, i).s + 0.1 <= 1) {
                getPixel(j, i).s += 0.1;
            }
            else {
                getPixel(j, i).s = 1;
            }
        }
    }
}

void Image::saturate(double amount) {
    for(unsigned int i = 0; i < height(); i++) {
        for(unsigned int j = 0; j < width(); j++) {
            if(getPixel(j, i).s + amount <= 1) {
                getPixel(j, i).s += amount;
            }
            else {
                getPixel(j, i).s = 1;
            }
        }
    }
}

void Image::desaturate() {
    for(unsigned int i = 0; i < height(); i++) {
        for(unsigned int j = 0; j < width(); j++) {
            if(getPixel(j, i).s - 0.1 >= 0) {
                getPixel(j, i).s -= 0.1;
            }
            else {
                getPixel(j, i).s = 0;
            }
        }
    }
}

void Image::desaturate(double amount) {
    for(unsigned int i = 0; i < height(); i++) {
        for(unsigned int j = 0; j < width(); j++) {
            if(getPixel(j, i).s - amount >= 0) {
                getPixel(j, i).s -= amount;
            }
            else {
                getPixel(j, i).s = 0;
            }
        }
    }
}

void Image::grayscale() {
    for(unsigned int i = 0; i < height(); i++) {
        for(unsigned int j = 0; j < width(); j++) {
            getPixel(j, i).s = 0;
        }
    }
}

void Image::rotateColor(double degrees) {
    for(unsigned int i = 0; i < height(); i++) {
        for(unsigned int j = 0; j < width(); j++) {
            if(getPixel(j, i).h + degrees < 360 && getPixel(j, i).h + degrees >= 0) {
                getPixel(j, i).h += degrees;
            }
            else if(getPixel(j, i).h + degrees >= 360) {
                getPixel(j, i).h  += degrees - 360;
            }
            else if(getPixel(j, i).h + degrees < 0) {
                getPixel(j, i).h += degrees + 360;
            }
        }
    }
}

void Image::illinify() {
    for(unsigned int i = 0; i < height(); i++) {
        for(unsigned int j = 0; j < width(); j++) {
            if(fabs(getPixel(j, i).h - 11) < fabs(getPixel(j, i).h - 216)) {
                getPixel(j, i).h = 11;
            }
            else {
                getPixel(j, i).h = 216;
            }
        }
    }
}

void Image::scale(double factor) {
    if(factor != 1) {
        Image* newImage = new Image();
        *newImage = *this;
        newImage->resize(width() * factor, height() * factor);
        if(factor > 1) {
            for(unsigned int i = 0; i < height(); i++) {
                for(unsigned int j = 0; j < width(); j++) {
                    cs225::HSLAPixel& oldPixel = getPixel(j, i);
                    cs225::HSLAPixel& newPixel = newImage->getPixel(factor * j, factor * i);
                    newPixel = oldPixel;
                    for(unsigned int x = factor * i; x < (unsigned int)((factor * i) + factor); x++) {
                        for(unsigned int y = j * factor; y < (unsigned int)((j * factor) + factor); y++) {
                            newImage->getPixel(y, x) = newPixel;
                        }
                    }
                }
            }
        }
        else if(factor < 1) {
            for(unsigned int i= 0; i < newImage->height(); i++) {
                for(unsigned int j = 0; j < newImage->width(); j++) {
                    cs225::HSLAPixel& oldPixel = getPixel(j/factor, i/factor);
                    cs225::HSLAPixel& newPixel = newImage->getPixel(j, i);
                    newPixel = oldPixel;
                }
            }
        }
        *this = *newImage;
        delete newImage;
    }
}

void Image::scale(unsigned w, unsigned h) {
    Image* newImage = new Image();
    *newImage = *this;
    double factor = 1;
    double curAR = (double)height()/width();
    double newAR = (double)h/w;
    if(curAR != newAR) {
        if(curAR > newAR) {
            newImage->resize(h/curAR, h);
            factor = (double)h/height();
        }
        else if(curAR < newAR) {
            newImage->resize(w, w * curAR);
            factor = (double)w/width();
        }
    }
    else {
        newImage->resize(w, h);
        factor = (double)w/width();
    }
    if(factor > 1) {
        for(unsigned int i = 0; i < height(); i++) {
            for(unsigned int j = 0; j < width(); j++) {
                cs225::HSLAPixel& oldPixel = getPixel(j, i);
                cs225::HSLAPixel& newPixel = newImage->getPixel(factor * j, factor * i);
                newPixel = oldPixel;
                for(unsigned int x = factor * i; x < (unsigned int)((factor * i) + factor); x++) {
                    for(unsigned int y = j * factor; y < (unsigned int)((j * factor) + factor); y++) {
                        newImage->getPixel(y, x) = newPixel;
                    }
                }
            }
        }
    }
    else if(factor < 1) {
        for(unsigned int i= 0; i < newImage->height(); i++) {
            for(unsigned int j = 0; j < newImage->width(); j++) {
                cs225::HSLAPixel& oldPixel = getPixel(j/factor, i/factor);
                cs225::HSLAPixel& newPixel = newImage->getPixel(j, i);
                newPixel = oldPixel;
            }
        }
    }
    *this = *newImage;
    delete newImage;
}