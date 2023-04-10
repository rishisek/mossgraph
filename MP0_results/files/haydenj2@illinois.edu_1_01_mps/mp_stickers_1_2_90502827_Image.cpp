/**
    @file Image.cpp
    Implementation of the Image class as a subclass of PNG
    @author haydenj2
*/

#include <iostream>
using std::cerr;
using std::endl;

#include <cmath>

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "image.h"
using cs225::HSLAPixel;

Image::Image(){}

Image::Image(unsigned int width, unsigned int height){}

void Image::lighten(){
    for(unsigned j = 0; j < height(); j++){
        for(unsigned i = 0; i < width(); i++){
            HSLAPixel & pixel = getPixel(i,j);
            if(pixel.l > 0.9){ pixel.l = 1; }
            else{pixel.l += 0.1;}
        }
    }
}

void Image::lighten(double amount){
    for(unsigned j = 0; j < height(); j++){
        for(unsigned i = 0; i < width(); i++){
            HSLAPixel & pixel = getPixel(i,j);
            if(pixel.l > (1.0 - amount)){ pixel.l = 1; }
            else{pixel.l += amount;}
        }
    }
}

void Image::darken(){
    for(unsigned j = 0; j < height(); j++){
        for(unsigned i = 0; i < width(); i++){
            HSLAPixel & pixel = getPixel(i,j);
            if(pixel.l < 0.1){ pixel.l = 0; }
            else{pixel.l -= 0.1;}
        }
    }
}

void Image::darken(double amount){
    for(unsigned j = 0; j < height(); j++){
        for(unsigned i = 0; i < width(); i++){
            HSLAPixel & pixel = getPixel(i,j);
            if(pixel.l < amount){ pixel.l = 0; }
            else{pixel.l -= amount;}
        }
    }
}

void Image::saturate(){
    for(unsigned j = 0; j < height(); j++){
        for(unsigned i = 0; i < width(); i++){
            HSLAPixel & pixel = getPixel(i,j);
            if(pixel.s > 0.9){ pixel.s = 1; }
            else{pixel.l += 0.1;}
        }
    }
}

void Image::saturate(double amount){
    for(unsigned j = 0; j < height(); j++){
        for(unsigned i = 0; i < width(); i++){
            HSLAPixel & pixel = getPixel(i,j);
            if(pixel.s > (1.0 - amount)){ pixel.s = 1; }
            else{pixel.s += amount;}
        }
    }
}

void Image::desaturate(){
    for(unsigned j = 0; j < height(); j++){
        for(unsigned i = 0; i < width(); i++){
            HSLAPixel & pixel = getPixel(i,j);
            if(pixel.s < 0.1){ pixel.s = 0; }
            else{pixel.s -= 0.1;}
        }
    }
}

void Image::desaturate(double amount){
    for(unsigned j = 0; j < height(); j++){
        for(unsigned i = 0; i < width(); i++){
            HSLAPixel & pixel = getPixel(i,j);
            if(pixel.s < amount){ pixel.s = 0; }
            else{pixel.s -= amount;}
        }
    }
}

void Image::grayscale(){
    for(unsigned j = 0; j < height(); j++){
        for(unsigned i = 0; i < width(); i++){
            HSLAPixel & pixel = getPixel(i,j);
            pixel.s = 0;
        }
    }
}

void Image::rotateColor(double amount){
    for(unsigned j = 0; j < height(); j++){
        for(unsigned i = 0; i < width(); i++){
            HSLAPixel & pixel = getPixel(i,j);
            pixel.h = pixel.h + amount;
            if(pixel.h > 360){ pixel.h = pixel.h - 360; }
        }
    }
}

void Image::illinify(){
    for(unsigned j = 0; j < height(); j++){
        for(unsigned i = 0; i < width(); i++){
            HSLAPixel & pixel = getPixel(i,j);
            if((pixel.h > 113) && (pixel.h < 294)){ pixel.h = 216; }
            else{ pixel.h = 11;}
        }
    }
}

void Image::scale(double factor){
    //create a vector to store the scaled image
    HSLAPixel * scaledData = new HSLAPixel[height() * width() * factor * factor];

    //for values of factor over 1, this will create factor x factor groups of pixels
    //for each pixel in the original image.
    if(factor >= 1){
        for(unsigned j = 0; j < height(); j++){
            for(unsigned i = 0; i < width(); i++){
                //this pixel is the seed for the following group of pixels
                HSLAPixel & seedPixel = getPixel(i, j);

                //loops through the factor x factor group and sets pixels equal to seed
                for(unsigned n = 0; n < factor; n++){
                    for(unsigned m = 0; m < factor; m++){
                        HSLAPixel & scaledPixel = scaledData[((i * lrint(factor)) + m) + ((j * lrint(factor)) + n)];
                        scaledPixel = seedPixel;
                    }
                }
            }
        }
    } 
}