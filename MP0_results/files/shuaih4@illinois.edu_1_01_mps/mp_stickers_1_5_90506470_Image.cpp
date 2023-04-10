#include <string>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"

using namespace std;

Image::Image():PNG()
{

}

Image::Image(unsigned int width, unsigned int height):PNG(width, height) {

}

void Image::lighten(){
    for(unsigned int i = 0; i<width(); i++){
        for (unsigned int j = 0; j<height(); j++){
            HSLAPixel & cur = getPixel(i,j);
            cur.l += 0.1;
            if(cur.l > 1.0){
                cur.l = 1.0;
            }
        }
    }
}

void Image::lighten(double amount){
    for(unsigned int i = 0; i<width(); i++){
        for (unsigned int j = 0; j<height(); j++){
            HSLAPixel & cur = getPixel(i,j);
            cur.l += amount;
            if(cur.l > 1.0){
                cur.l = 1.0;
            }
        }
    }
}

void Image::darken(){
    for(unsigned int i = 0; i<width(); i++){
        for (unsigned int j = 0; j<height(); j++){
            HSLAPixel & cur = getPixel(i,j);
            cur.l -= 0.1;
            if(cur.l < 0.0){
                cur.l = 0.0;
            }
        }
    }
}

void Image::darken(double amount){
    for(unsigned int i = 0; i<width(); i++){
        for (unsigned int j = 0; j<height(); j++){
            HSLAPixel & cur = getPixel(i,j);
            cur.l -= amount;
            if(cur.l < 0.0){
                cur.l = 0.0;
            }
        }
    }
}

void Image::saturate(){
    for(unsigned int i = 0; i<width(); i++){
        for (unsigned int j = 0; j<height(); j++){
            HSLAPixel & cur = getPixel(i,j);
            cur.s += 0.1;
            if(cur.s > 1.0){
                cur.s = 1.0;
            }
        }
    }
}

void Image::saturate(double amount){
    for(unsigned int i = 0; i<width(); i++){
        for (unsigned int j = 0; j<height(); j++){
            HSLAPixel & cur = getPixel(i,j);
            cur.s += amount;
            if(cur.s > 1.0){
                cur.s = 1.0;
            }
        }
    }
}

void Image::desaturate(){
    for(unsigned int i = 0; i<width(); i++){
        for (unsigned int j = 0; j<height(); j++){
            HSLAPixel & cur = getPixel(i,j);
            cur.s -= 0.1;
            if(cur.s < 0.0){
                cur.s = 0.0;
            }
        }
    }
}

void Image::desaturate(double amount){
    for(unsigned int i = 0; i<width(); i++){
        for (unsigned int j = 0; j<height(); j++){
            HSLAPixel & cur = getPixel(i,j);
            cur.s -= amount;
            if(cur.s < 0.0){
                cur.s = 0.0;
            }
        }
    }
}

void Image::grayscale(){
    for(unsigned int i = 0; i<width(); i++){
        for (unsigned int j = 0; j<height(); j++){
            HSLAPixel & cur = getPixel(i,j);
            cur.s = 0.0;
        }
    } 
}

void Image::rotateColor(double degrees){
    for(unsigned int i = 0; i<width(); i++){
        for (unsigned int j = 0; j<height(); j++){
            HSLAPixel & cur = getPixel(i,j);
            cur.h += degrees;
            if(cur.h > 360.0){
                cur.h -= 360.0;
            } else if(cur.h < 0){
                cur.h += 360.0;
            }
        }
    }
}

void Image::illinify(){
    for(unsigned int i = 0; i<width(); i++){
        for (unsigned int j = 0; j<height(); j++){
            HSLAPixel & cur = getPixel(i,j);
            if(abs(11.0 - cur.h) < abs(216.0 - cur.h)){
                cur.h = 11.0;
            } else {
                cur.h = 216.0;
            }
        }
    }
}

void Image::scale(double factor){
    Image * temp = new Image();
    *temp = *this;
    resize(factor * width(), factor * height());
    for(unsigned int i = 0; i<width(); i++){
        for (unsigned int j = 0; j<height(); j++){
            HSLAPixel & newPixel = getPixel(i, j);
            HSLAPixel & oldPixel = temp->getPixel(i/factor, j/factor);
            newPixel = oldPixel;
        }
    }
    delete temp;
}

void Image::scale(unsigned w, unsigned h){
    double factor = min((double)w/(double)width(), (double)h/(double)height());
    scale(factor);
}





