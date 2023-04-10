//#pragma once

#include "Image.h"
#include "cs225/PNG.h"
#include <iostream>
#include <string>

using namespace cs225;

Image::Image(){
    image_ = new PNG();
}

Image::Image(unsigned int width, unsigned int height){
    image_ = new PNG(width, height);
}

void Image::darken(){
    for (unsigned int w = 0; w < width(); w++ ){
        for (unsigned int h = 0; h < height(); h++){
            HSLAPixel & curPixel = getPixel(w, h);
            curPixel.l = curPixel.l - 0.1;
            if (curPixel.l < 0.0) {
                curPixel.l = 0.0;
            }
            if (curPixel.l > 1.0){
                curPixel.l = 1.0;
            }
        }
    }
}

void Image::darken(double amount){
    for (unsigned int w = 0; w < width(); w++ ){
        for (unsigned int h = 0; h < height(); h++){
            HSLAPixel & curPixel = getPixel(w, h);
            curPixel.l = curPixel.l - amount;
            if (curPixel.l < 0.0) {
                curPixel.l = 0.0;
            }
            if (curPixel.l > 1.0){
                curPixel.l = 1.0;
            }
        }
    }
}

void Image::desaturate(){
    for (unsigned int w = 0; w < width(); w++ ){
        for (unsigned int h = 0; h < height(); h++){
            HSLAPixel & curPixel = getPixel(w, h);
            curPixel.s = curPixel.s - 0.1;
            if (curPixel.s < 0.0) {
                curPixel.s = 0.0;
            }
            if (curPixel.s > 1.0){
                curPixel.s = 1.0;
            }
        }
    }
}

void Image::desaturate(double amount){
    for (unsigned int w = 0; w < width(); w++ ){
        for (unsigned int h = 0; h < height(); h++){
            HSLAPixel & curPixel = getPixel(w, h);
            curPixel.s = curPixel.s - amount;
            if (curPixel.s < 0.0) {
                curPixel.s = 0.0;
            }
            if (curPixel.s > 1.0){
                curPixel.s = 1.0;
            }
        }
    }
}

void Image::grayscale(){
    for (unsigned int w = 0; w < width(); w++ ){
        for (unsigned int h = 0; h < height(); h++){
            HSLAPixel & curPixel = getPixel(w, h);
            curPixel.s = 0.0;
        }
    }
}

void Image::illinify(){
    for (unsigned int w = 0; w < width(); w++ ){
        for (unsigned int h = 0; h < height(); h++){
            HSLAPixel & curPixel = getPixel(w, h);
            if (curPixel.h >= 113.5 && curPixel.h < 293.5){
                curPixel.h = 216;
            }
            else{
                curPixel.h = 11;
            }
        }
    }
}

void Image::lighten(){
    for (unsigned int w = 0; w < width(); w++ ){
        for (unsigned int h = 0; h < height(); h++){
            HSLAPixel & curPixel = getPixel(w, h);
            curPixel.l = curPixel.l + 0.1;
            if (curPixel.l < 0.0) {
                curPixel.l = 0.0;
            }
            if (curPixel.l > 1.0){
                curPixel.l = 1.0;
            }
        }
    }
}

void Image::lighten(double amount){
    for (unsigned int w = 0; w < width(); w++ ){
        for (unsigned int h = 0; h < height(); h++){
            HSLAPixel & curPixel = getPixel(w, h);
            curPixel.l = curPixel.l + amount;
            if (curPixel.l < 0.0) {
                curPixel.l = 0.0;
            }
            if (curPixel.l > 1.0){
                curPixel.l = 1.0;
            }
        }
    }
}

void Image::rotateColor(double degrees){
    for (unsigned int w = 0; w < width(); w++ ){
        for (unsigned int h = 0; h < height(); h++){
            HSLAPixel & curPixel = getPixel(w, h);
            curPixel.h = curPixel.h + degrees;
            while (curPixel.h < 0) {
                curPixel.h = 360 + curPixel.h;
            }
            while (curPixel.h > 360){
                curPixel.h = curPixel.h - 360;
            }
        }
    }
}

void Image::saturate(){
    for (unsigned int w = 0; w < width(); w++ ){
        for (unsigned int h = 0; h < height(); h++){
            HSLAPixel & curPixel = getPixel(w, h);
            curPixel.s = curPixel.s + 0.1;
            if (curPixel.s < 0.0) {
                curPixel.s = 0.0;
            }
            if (curPixel.s > 1.0){
                curPixel.s = 1.0;
            }
        }
    }
}

void Image::saturate(double amount){
    for (unsigned int w = 0; w < width(); w++ ){
        for (unsigned int h = 0; h < height(); h++){
            HSLAPixel & curPixel = getPixel(w, h);
            curPixel.s = curPixel.s + amount;
            if (curPixel.s < 0.0) {
                curPixel.s = 0.0;
            }
            if (curPixel.s > 1.0){
                curPixel.s = 1.0;
            }
        }
    }
}

void Image::scale(double factor){
    unsigned int imageWidth = width();
    unsigned int imageHeight = height();
    unsigned int newWidth = imageWidth * factor;
    unsigned int newHeight = imageHeight * factor;

    Image * scaleImage = new Image();
    *scaleImage = *this;
    resize(newWidth, newHeight);

    for (unsigned int w = 0; w < newWidth; w++ ){
        for (unsigned int h = 0; h < newHeight; h++){
            HSLAPixel & curPixel = getPixel(w, h);
            HSLAPixel & scalePixel = scaleImage->getPixel((w / factor), (h / factor));
            curPixel = scalePixel;
        }
    }

    delete scaleImage;
}

void Image::scale(unsigned w, unsigned h){
    unsigned int imageWidth = width();
    unsigned int imageHeight = height();
    //unsigned int newWidth = width * factor;
    //unsigned int newHeight = height * factor;

    Image * scaleImage = new Image();
    *scaleImage = *this;
    resize(w, h);

    // make factor
    double factor_w = w / imageWidth;
    double factor_h = h / imageHeight;

    for (unsigned int i = 0; i < w; i++ ){
        for (unsigned int j = 0; j < h; j++){
            HSLAPixel & curPixel = getPixel(i, j);
            HSLAPixel & scalePixel = scaleImage->getPixel((i / factor_w), (j / factor_h));
            curPixel = scalePixel;
        }
    }

    delete scaleImage;
}