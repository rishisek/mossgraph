#include "Image.h"
void Image::lighten (){
    for (unsigned int i = 0; i < height(); i++) {
    for (unsigned int j = 0; j < width(); j++) {
        cs225::HSLAPixel & a = getPixel(j, i);
        if (a.l< 0.9) {
            a.l = a.l + 0.1;
        } else {
            a.l = 1;
        }    
    }
    }
}
void Image::lighten (double amount){
    for (unsigned int i = 0; i < height(); i++) {
    for (unsigned int j = 0; j < width(); j++) {
        cs225::HSLAPixel & a = getPixel(j, i);
        if (a.l < 1-amount) {
            a.l = a.l + amount;
        } else {
            a.l = 1;
        }
    }
    }
}
void Image::darken (){
    for (unsigned int i = 0; i < height(); i++) {
    for (unsigned int j = 0; j < width(); j++) {
        cs225::HSLAPixel & a = getPixel(j, i);
        if (a.l > 0.1) {
            a.l = a.l - 0.1;
        } else {
                a.l = 0;
        }      
    }
    }
}
void Image::darken (double amount){
    for (unsigned int i = 0; i < height(); i++) {
        for (unsigned int j = 0; j < width(); j++) {
            cs225::HSLAPixel & a = getPixel(j, i);
            if (a.l > amount)
                a.l = a.l - amount;
            else 
                a.l = 0;
        }
    }
}
void Image::saturate (){
    for (unsigned int i = 0; i < height(); i++) {
    for (unsigned int j = 0; j < width(); j++) {
        cs225::HSLAPixel & a = getPixel(j, i);
        if (a.s < 0.9) {
            a.s = a.s + 0.1;
        } else {
            a.s = 1;
        }    
    }
    }
}
void Image::saturate (double amount){
    for (unsigned int i = 0; i < height(); i++) {
    for (unsigned int j = 0; j < width(); j++) {
        cs225::HSLAPixel & a = getPixel(j, i);
        if (a.s < 1 - amount) {
            a.s = a.s + amount;
        } else {
            a.s = 1;
        }
    }
    }
}
void Image::desaturate (){
    for (unsigned int i = 0; i < height(); i++) {
    for (unsigned int j = 0; j < width(); j++) {
        cs225::HSLAPixel & a = getPixel(j, i);
        if (a.s > 0.1) {
            a.s = a.s - 0.1;
        } else {
            a.s = 0;
        }    
    }
    }
}
void Image::desaturate (double amount){
    for (unsigned int i = 0; i < height(); i++) {
    for (unsigned int j = 0; j < width(); j++) {
        cs225::HSLAPixel & a = getPixel(j, i);
        if (a.s > amount) {
        a.s = a.s - amount;
        } else {
        a.s = 0;
        }  
    }
    }
}
void Image::grayscale (){
    for (unsigned int i = 0; i < height(); i++) {
    for (unsigned int j = 0; j < width(); j++) {
        cs225::HSLAPixel & a = getPixel(j, i);
        a.s = 0;
    }
    }
}
void Image::rotateColor (double degrees){
    for (unsigned int i = 0; i < height(); i++) {
    for (unsigned int j = 0; j < width(); j++) {
        cs225::HSLAPixel & a = getPixel(j, i);
        a.h = a.h + degrees;
        while (a.h > 360) {
            a.h = a.h - 360;
        }
        while (a.h < 0) {
            a.h = a.h + 360;
        }
    }
    }
}
void Image::illinify (){
    for (unsigned int i = 0; i < height(); i++) {
    for (unsigned int j = 0; j < width(); j++) {
        cs225::HSLAPixel & a = getPixel(j, i);
        if (0 <= a.h <= 113.5 || (293.5 <= a.h && a.h <= 360)) {
            a.h = 11;
        } else {
            a.h = 216;
        }
    }
    }
}
void Image::scale (double factor){
    int nwidth = width()*factor;
    int nheight = height()*factor;
    Image ptr(*this);
    resize(nwidth, nheight);
    for (unsigned int i = 0; i < height(); i++) {
        for (unsigned int j = 0; j < width(); j++) {
            cs225::HSLAPixel & old = getPixel(j, i);
            old = ptr.getPixel(int(j / factor), int(i / factor));
        }
    }
}
void Image::scale (unsigned w, unsigned h){
    scale(std::min((double) w / width(), (double) h / height()));
}

void Image::enlarge(unsigned w, unsigned h, unsigned x, unsigned y) {
    Image cpy(*this);
    resize(w, h);
    for (unsigned i = 0; i < cpy.width(); i++) {
        for (unsigned j = 0; j < cpy.height(); j++) {
            getPixel(i, j) = cs225::HSLAPixel();
        }
    }

    for (unsigned i = 0; i < cpy.width(); i++) {
        for (unsigned j = 0; j < cpy.height(); j++) {
            getPixel(i + x, j + y) = cpy.getPixel(i, j);
        }
    }
}