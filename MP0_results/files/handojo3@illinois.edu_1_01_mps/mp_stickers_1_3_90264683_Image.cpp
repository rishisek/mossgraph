#include "Image.h"

Image::Image() {}
Image::Image(unsigned int width, unsigned int height) {
    PNG(width, height);
}
void Image::lighten() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & obj = getPixel(i,j);
            int max = 1;
            if (obj.l > 0.89) {
                obj.l = max;
            } else {
                obj.l += 0.1;
            }
        }
    }
}
void Image::lighten(double amount){
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & obj = getPixel(i,j);
            int max = 1;
            if (obj.l > 1 - amount) {
                obj.l = max;
            } else {
                obj.l += amount;
            }
        }
    }
}
void Image::darken(){
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & obj = getPixel(i,j);
            int min = 0;
            if (obj.l < 0.11) {
                obj.l = 0;
            } else {
                obj.l -= 0.1;
            }
        }
    } 
}
void Image::darken(double amount){
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & obj = getPixel(i,j);
            int min = 0;
            if (obj.l < amount) {
                obj.l = 0;
            } else {
                obj.l -= amount;
            }
        }
    } 
}
void Image::saturate(){
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & obj = getPixel(i,j);
            if (obj.s >= 0.90) {
                obj.s = 1.0;
            } else {
                obj.s += 0.1;
            }
        }
    }
}
void Image::saturate(double amount){
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & obj = getPixel(i,j);
            if (obj.s + amount> 1.0) {
                obj.s = 1.0;
            } else {
                obj.s += amount;
            }
        }
    } 
}
void Image::desaturate(){
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & obj = getPixel(i,j);
            if (obj.s <= 0.10) {
                obj.s = 0.0;
            } else {
                obj.s -= 0.1;
            }

        }
    } 
}
void Image::desaturate(double amount){
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & obj = getPixel(i,j);
            if (obj.s - amount < 0.0) {
                obj.s = 0.0;
            } else {
                obj.s -= amount;
            }
        }
    } 
}
void Image::grayscale(){
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & obj = getPixel(i,j);
            obj.s = 0;
        }
    }
}
void Image::rotateColor(double degrees){
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & obj = getPixel(i,j);
            double max = 360.0;
            double min = 0.0;
            if (obj.h + degrees > max) {
                double diff = degrees - (max - obj.h);
                obj.h = min + diff;
            } else if (obj.h + degrees < min) {
                double diff = obj.h + degrees;
                obj.h = max + diff;
            } else {
                obj.h += degrees;
            }
        }
    }
}
// To illinify an image is to transform the hue of every pixel to Illini Orange or Illini Blue.
// The hue of every pixel is set to the a hue value of either orange or blue, 
// based on if the pixel’s hue value is closer to orange than blue. Remember, hue values are a circle!
// Illini Orange: hue = 11
// Illini Blue: hue = 216

void Image::illinify() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & obj = getPixel(i,j);
            int diff1 = abs(obj.h - 11);
            int diff2 = abs(obj.h - 216);
            if (diff1 > 180) {
                diff1 = 360 - diff1;
            }
            if (diff2 > 180) {
                diff2 = 360 - diff2;
            }
            obj.h = (diff1 < diff2) ? 11 : 216;
        }
    }
}

void Image::scale(double factor) {
    double worig = width();
    double horig = height();
    double tmp= worig * factor;
    double tmp1 = horig * factor;
    //the original
    Image clone = *this;
    // The new Image after resizing with newer dimensions
    resize(tmp,tmp1);
    for (unsigned int i =  0; i < tmp; i++) {
        for (unsigned int j = 0; j < tmp1; j++) {
            int ind = j/factor;
            int ind1 = i/factor;
            getPixel(i,j) = clone.getPixel(ind1,ind);
        }
    }
}
void Image::scale(unsigned w, unsigned h){
    //original
    double worig = width();
    double horig = height();
    //factors
    double factor = w/worig;
    double factor1 = h/horig;
    double result = 0.0;
    result = (factor < factor1)? factor:factor1;
    scale(result);
}