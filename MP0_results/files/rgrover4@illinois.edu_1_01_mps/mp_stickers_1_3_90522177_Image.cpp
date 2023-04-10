#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;

void Image::lighten(){
    for(unsigned int i = 0; i < width(); i++){
        for(unsigned int j = 0; j < PNG::height(); j++){
            HSLAPixel & curPix = PNG::getPixel(i, j);
            if(curPix.l <= 0.9){
                curPix.l = curPix.l + 0.1;
            //Issue may arise here, dbl check
            } else {
                curPix.l = 1;
            }
        }
    }
}

void Image::lighten(double amount){
    for(unsigned int i = 0; i < PNG::width(); i++){
        for(unsigned int j = 0; j < PNG::height(); j++){
            HSLAPixel & curPix = PNG::getPixel(i, j);
            if(curPix.l + amount <= 1){
                curPix.l = curPix.l + amount;
            } else {
                curPix.l = 1;
            }
        }
    }
}

void Image::darken(){
    for(unsigned int i = 0; i < PNG::width(); i++){
        for(unsigned int j = 0; j < PNG::height(); j++){
            HSLAPixel & curPix = PNG::getPixel(i, j);
            if(curPix.l >= 0.1){
                curPix.l = curPix.l - 0.1;
            } else {
                curPix.l = 0;
            }
        }
    }
}

void Image::darken(double amount){
    for(unsigned int i = 0; i < PNG::width(); i++){
        for(unsigned int j = 0; j < PNG::height(); j++){
            HSLAPixel & curPix = PNG::getPixel(i, j);
            if(curPix.l - amount >= 0 ){
                curPix.l = curPix.l - amount;
            } else {
                curPix.l = 0;
            }
        }
    }
}

void Image::saturate(){
    for(unsigned int i = 0; i < PNG::width(); i++){
        for(unsigned int j = 0; j < PNG::height(); j++){
            HSLAPixel & curPix = PNG::getPixel(i, j);
            if(curPix.s <= 0.9){
                curPix.s = curPix.s + 0.1;
            //Issue may arise here, dbl check
            } else {
                curPix.s = 1;
            }
        }
    }
}

void Image::saturate(double amount){
    for(unsigned int i = 0; i < PNG::width(); i++){
        for(unsigned int j = 0; j < PNG::height(); j++){
            HSLAPixel & curPix = PNG::getPixel(i, j);
            if(curPix.s + amount <= 1){
                curPix.s = curPix.s + amount;
            } else {
                curPix.s = 1;
            }
        }
    }
}

void Image::desaturate(){
    for(unsigned int i = 0; i < PNG::width(); i++){
        for(unsigned int j = 0; j < PNG::height(); j++){
            HSLAPixel & curPix = PNG::getPixel(i, j);
            if(curPix.s >= 0.1){
                curPix.s = curPix.s - 0.1;
            } else {
                curPix.s = 0;
            }
        }
    }
}

void Image::desaturate(double amount){
    for(unsigned int i = 0; i < PNG::width(); i++){
        for(unsigned int j = 0; j < PNG::height(); j++){
            HSLAPixel & curPix = PNG::getPixel(i, j);
            if(curPix.s - amount >= 0){
                curPix.s = curPix.s - amount;
            } else {
                curPix.s = 0;
            }
        }
    }
}

void Image::grayscale(){
    for(unsigned int i = 0; i < PNG::width(); i++){
        for(unsigned int j = 0; j < PNG::height(); j++){
            HSLAPixel & curPix = PNG::getPixel(i, j);
            curPix.s = 0;
        }
    }
}

void Image::rotateColor(double degrees){
    for(unsigned int i = 0; i < PNG::width(); i++){
        for(unsigned int j = 0; j < PNG::height(); j++){
            HSLAPixel & curPix = PNG::getPixel(i, j);
            if(curPix.h + degrees > 360){
                curPix.h = curPix.h + degrees - 360;
            } else if(curPix.h + degrees < 0){
                curPix.h = curPix.h + degrees + 360;
            } else {
                curPix.h = curPix.h + degrees;
            }
        }
    }
}

void Image::illinify(){
    for (unsigned int i = 0; i < PNG::width(); i++) {
        for (unsigned int j = 0; j < PNG::height(); j++) {
            HSLAPixel & curPix = PNG::getPixel(i, j);
            if(curPix.h >= 113 && curPix.h <= 293){
                curPix.h = 216;
            } else {
                curPix.h = 11;
            }
        }
    }
}

void Image::scale(double factor){
    double width = PNG::width() * factor;
    double height = PNG::height() * factor;
    //DO THIS BEFORE RESIZING OR FOR LOOP WILL FAIL IN RESIZING
    PNG oldImage = *this;
    resize(width, height);

    for(unsigned int i = 0; i < this -> width(); i++){
        for(unsigned int j = 0; j < this -> height(); j++){
            HSLAPixel & tempPix =  oldImage.getPixel(i/factor, j/factor);
            this -> getPixel(i, j) = tempPix;
        }    
    }
}

void Image::scale(unsigned w, unsigned h){
    double width = (double)w/PNG::width();
    double height = (double)h/PNG::height();
    if(width < height){
        scale(width);
    } else {
        scale(height);
    }
}
