#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Image.h"

using namespace std;
using namespace cs225;

        
void Image::darken() {
    for (unsigned int i = 0; i < width(); i++){
        for (unsigned int j = 0; j < height(); j++){
            HSLAPixel &pixel = getPixel(i,j);
            pixel.l -= 0.1;
            if (pixel.l < 0)
                pixel.l = 0;
            else if (pixel.l > 1)
                pixel.l = 1;
        }
    }
}

void Image::darken(double amount){
    for (unsigned int i = 0; i < width(); i++){
        for (unsigned int j = 0; j < height(); j++){
            HSLAPixel &pixel = getPixel(i,j);
            pixel.l -= amount;
            if (pixel.l < 0)
                pixel.l = 0;
            else if (pixel.l > 1)
                pixel.l = 1;
        }
    }
}

void Image::lighten(){
    for (unsigned int i = 0; i < width(); i++){
        for (unsigned int j = 0; j < height(); j++){
            HSLAPixel &pixel = getPixel(i,j);
            pixel.l += 0.1;
            if (pixel.l < 0)
                pixel.l = 0;
            else if (pixel.l > 1)
                pixel.l = 1;
        }
    }
}

void Image::lighten(double amount){
    for (unsigned int i = 0; i < width(); i++){
        for (unsigned int j = 0; j < height(); j++){
            HSLAPixel &pixel = getPixel(i,j);
            pixel.l += amount;
            if (pixel.l < 0)
                pixel.l = 0;
            else if (pixel.l > 1)
                pixel.l = 1;
        }
    }
}

void Image::desaturate(){
    for (unsigned int i = 0; i < width(); i++){
        for (unsigned int j = 0; j < height(); j++){
            HSLAPixel &pixel = getPixel(i,j);
            pixel.s -= 0.1;
            if (pixel.s < 0)
                pixel.s = 0;
            else if (pixel.s > 1)
                pixel.s = 1;
        }
    }
}

void Image::desaturate(double amount){
    for (unsigned int i = 0; i < width(); i++){
        for (unsigned int j = 0; j < height(); j++){
            HSLAPixel &pixel = getPixel(i,j);
            pixel.s -= amount;
            if (pixel.s < 0)
                pixel.s = 0;
            else if (pixel.s > 1)
                pixel.s = 1;
        }
    }
}

void Image::saturate(){
    for (unsigned int i = 0; i < width(); i++){
        for (unsigned int j = 0; j < height(); j++){
            HSLAPixel &pixel = getPixel(i,j);
            pixel.s += 0.1;
            if (pixel.s < 0)
                pixel.s = 0;
            else if (pixel.s > 1)
                pixel.s = 1;
        }
    }
}

void Image::saturate(double amount){
    for (unsigned int i = 0; i < width(); i++){
        for (unsigned int j = 0; j < height(); j++){
            HSLAPixel &pixel = getPixel(i,j);
            pixel.s += amount;
            if (pixel.s < 0)
                pixel.s = 0;
            else if (pixel.s > 1)
                pixel.s = 1;
        }
    }
}

void Image::grayscale(){
    for (unsigned int i = 0; i < width(); i++){
        for (unsigned int j = 0; j < height(); j++){
            HSLAPixel &pixel = getPixel(i,j);
            pixel.s = 0;
        }
    }
}

void Image::illinify(){
    for (unsigned int i = 0; i < width(); i++){
        for (unsigned int j = 0; j < height(); j++){
            HSLAPixel &pixel = getPixel(i,j);
            if (pixel.h >= 113 && pixel.h <= 294)
                pixel.h = 216;
            else
                pixel.h = 11;
        }
    }
}

void Image::rotateColor(double degrees){
    for (unsigned int i = 0; i < width(); i++){
        for (unsigned int j = 0; j < height(); j++){
            HSLAPixel &pixel = getPixel(i,j);
            pixel.h += degrees;
            if (pixel.h < 0)
                pixel.h += 360;
            else if (pixel.h > 360)
                pixel.h -= 360;
        }
    }
}

void Image::scale(double factor){
    unsigned int w = width() * factor;
    unsigned int h = height() * factor;
    Image orig = *this;
    resize(w,h);

    for (unsigned int i = 0; i < width(); i++){
        for (unsigned int j = 0; j < height(); j++){
            HSLAPixel &pixel = getPixel(i,j);
            HSLAPixel &temp_pixel = orig.getPixel(i/factor,j/factor);
            pixel = temp_pixel;
        }
    }
    
}

void Image::scale(unsigned w, unsigned h){
    double factor = min((double)w/(double)width(), (double)h/(double)height());
    scale(factor);
}

