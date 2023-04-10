#include "Image.h"
#include "cs225/PNG.h"
using namespace cs225;

Image::Image(unsigned int width, unsigned int height)
{this->resize(width,height);}

void Image::lighten(){

    for(unsigned int k = 0; k<this->width(); k++){
        for (unsigned int t = 0; t<this->height(); t++){
            cs225::HSLAPixel &x = this->getPixel(k,t);
            x.l += 0.1;
            if (x.l>1) {
                x.l = 1;}
            if (x.l<0) {
                x.l = 0;}
            }
    }
}

void Image::lighten(double amount){

    for(unsigned int k = 0; k < this->width(); k++){
        for (unsigned int t = 0; t<this->height(); t++){
            cs225::HSLAPixel &x = this->getPixel(k,t);
            x.l += amount;
            if (x.l>1) {
                x.l = 1;}
            if (x.l<0) {
                x.l = 0;}
            }
    }
}

void Image::darken(){
    for(unsigned int k = 0; k<this->width(); k++){
        for (unsigned int t = 0; t<this->height(); t++){
            cs225::HSLAPixel &x = this->getPixel(k,t);
            x.l = x.l-0.1;
            if (x.l<0) {
                x.l = 0;}
            if (x.l>1) {
                x.l = 1;}
            }
    }
}

void Image::darken(double amount){
    for(unsigned int k = 0; k<this->width(); k++){
        for (unsigned int t = 0; t<this->height(); t++){
            cs225::HSLAPixel &x = this->getPixel(k,t);
            x.l = x.l-amount;
            if (x.l<0) {x.l = 0;}
            if (x.l>1) {x.l = 1;}
            }
    }
}

void Image::saturate(){
    for(unsigned int k = 0; k<this->width(); k++){
        for (unsigned int t = 0; t<this->height(); t++){
            cs225::HSLAPixel &x = this->getPixel(k,t);
            x.s = x.s+0.1;
            if (x.s<0) {x.s = 0;}
            if (x.s>1) {x.s = 1;}
            }
    }
}
void Image::saturate(double amount){
    for(unsigned int k = 0; k<this->width(); k++){
        for (unsigned int t = 0; t<this->height(); t++){
            cs225::HSLAPixel &x = this->getPixel(k,t);
            x.s = x.s+amount;
            if (x.s<0) {x.s = 0;}
            if (x.s>1) {x.s = 1;}
            }
    }
}

void Image::desaturate(){
    for(unsigned int k = 0; k<this->width(); k++){
        for (unsigned int t = 0; t<this->height(); t++){
            cs225::HSLAPixel &x = this->getPixel(k,t);
            x.s = x.s-0.1;
            if (x.s<0) {x.s = 0;}
            if (x.s>1) {x.s = 1;}
            }
    }
}
void Image::desaturate(double amount){
    for(unsigned int k = 0; k<this->width(); k++){
        for (unsigned int t = 0; t<this->height(); t++){
            cs225::HSLAPixel &x = this->getPixel(k,t);
            x.s = x.s-amount;
            if (x.s<0) {x.s = 0;}
            if (x.s>1) {x.s = 1;}
            }
    }
}

void Image::grayscale(){
    for(unsigned int k = 0; k<this->width(); k++){
        for (unsigned int t = 0; t<this->height(); t++){
            cs225::HSLAPixel &x = this->getPixel(k,t);
            x.s = 0;
            }
    }
}

void Image::rotateColor(double degrees){
        for(unsigned int k = 0; k<this->width(); k++){
        for (unsigned int t = 0; t<this->height(); t++){
            cs225::HSLAPixel &x = this->getPixel(k,t);
            x.h = x.h+degrees;
            while(x.h>360){
                x.h -= 360;
            }
            while(x.h<0){
                x.h += 360;
            }
            }
    }
}

void Image::illinify(){
int illini_orange;
int illini_blue;
        for(unsigned int k = 0; k< this->width(); k++){
        for (unsigned int t = 0; t< this->height(); t++){
            cs225::HSLAPixel &x = this->getPixel(k,t);
            int l = std::abs(x.h-11);
            int g = std::abs(x.h-216);
            if (l<g){x.h = 11;}
            if (g<l){x.h = 216;}
            }
    }
}

void Image::scale(double factor){
unsigned int w = factor*this->width();
unsigned int h = factor*this->height();
Image* nayawala = new Image;
*nayawala = *this;
this->resize(w,h);
for(unsigned int k = 0; k<w; k++){
        for (unsigned int t = 0; t<h; t++){
            cs225::HSLAPixel &x = this->getPixel(k,t);
            cs225::HSLAPixel &y = nayawala->getPixel(k/factor,t/factor);
            x = y;
        }
    }
    delete nayawala;
}

void Image::scale(unsigned w,unsigned h){
    double factor;
    double width = this->width();
    double height = this->height();
    double wi = w/width;
    double hi = h/height;
    if (wi<hi) {factor  = wi;}
    else {factor = hi;}
    unsigned int ww = factor*this->width();
    unsigned int hh = factor*this->height();
    Image* nayawala = new Image;
    *nayawala = *this;
    this->resize(ww,hh);
    for (unsigned int i = 0; i<ww; i++){
        for (unsigned int j = 0; j<hh; j++){
            HSLAPixel &x = this->getPixel(i,j);
            HSLAPixel &y = nayawala->getPixel(i/factor,j/factor);
            x = y;
        }
    }
    delete nayawala;
}