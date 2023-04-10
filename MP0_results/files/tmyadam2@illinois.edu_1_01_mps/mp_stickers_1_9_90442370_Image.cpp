#include "Image.h"

using namespace cs225;

Image::Image(){
    PNG();
}

Image::Image(unsigned int width, unsigned height) : PNG(width, height) {
}
void Image::lighten(){
    for(unsigned int i = 0; i < width(); i++){
        for(unsigned int j = 0; j < height(); j++){
            HSLAPixel & pixel = getPixel(i,j);
            if((getPixel(i,j).l + 0.1) > 1){
                pixel.l = 1;
            }
            else{
                 pixel.l = getPixel(i,j).l + 0.1;
            }
        }
    }
}
void Image::lighten(double amount){
for(unsigned int i = 0; i < width(); i++){
        for(unsigned int j = 0; j < height(); j++){
            HSLAPixel & pixel = getPixel(i,j);
            if((getPixel(i,j).l+amount) > 1){
                pixel.l = 1;
            }
            else{
                pixel.l = getPixel(i,j).l + amount;
            }
        }
    }
}
void Image::darken(){
for(unsigned int i = 0; i < width(); i++){
        for(unsigned int j = 0; j < height(); j++){
            HSLAPixel & pixel = getPixel(i,j);
            if((getPixel(i,j).l-0.1) < 0){
                pixel.l = 0;
            }
            else{
                pixel.l = getPixel(i,j).l - 0.1;
            }
        }
    }
}
void Image::darken(double amount){
for(unsigned int i = 0; i < width(); i++){
        for(unsigned int j = 0; j < height(); j++){
            HSLAPixel & pixel = getPixel(i,j);
            if((getPixel(i,j).l-amount) < 0){
                pixel.l = 0;
            }
            else{
                pixel.l = getPixel(i,j).l - amount;
            }
        }
    }
}
void Image::saturate(){
    for(unsigned int i = 0; i < width(); i++){
        for(unsigned int j = 0; j < height(); j++){
            HSLAPixel & pixel = getPixel(i,j);
            if((getPixel(i,j).s + 0.1) > 1){
                pixel.s = 1;
            }
            else{
                pixel.s = getPixel(i,j).s + 0.1;
            }
        }
    }
}
void Image::saturate(double amount){
for(unsigned int i = 0; i < width(); i++){
        for(unsigned int j = 0; j < height(); j++){
            HSLAPixel & pixel = getPixel(i,j);
            if((getPixel(i,j).s + amount) > 1){
                pixel.l = 1;
            }
            else{
                pixel.l = getPixel(i,j).s + amount;
            }
        }
    }
}
void Image::desaturate(){
for(unsigned int i = 0; i < width(); i++){
        for(unsigned int j = 0; j < height(); j++){
            HSLAPixel & pixel = getPixel(i,j);
            if((getPixel(i,j).s - 0.1) < 0){
                pixel.s = 0;
            }
            else{
                pixel.s = getPixel(i,j).s - 0.1;
            }
        }
    }
}
void Image::desaturate(double amount){
for(unsigned int i = 0; i < width(); i++){
        for(unsigned int j = 0; j < height(); j++){
            HSLAPixel & pixel = getPixel(i,j);
            if((getPixel(i,j).s - amount) < 0){
                pixel.s = 0;
            }
            else{
                pixel.s = getPixel(i,j).s - amount;
            }
        }
    }
}

void Image::grayscale(){
for(unsigned int i = 0; i < width();i++){
    for(unsigned int j = 0; j < height(); j++){
        HSLAPixel & pixel = getPixel(i,j);
        pixel.s = 0;
    }
}
}

void Image::rotateColor(double degrees){
for(unsigned int i = 0; i < width(); i++){
        for(unsigned int j = 0; j < height(); j++){
            HSLAPixel & pixel = getPixel(i,j);
            if(pixel.h+degrees>360){
            //while((pixel.h + degrees) > 360){
                pixel.h = ((pixel.h + degrees) - 360);
            //}
            }
            else if((pixel.h+degrees)<0){
            //while((pixel.h+degrees)<0){
                pixel.h = ((pixel.h + degrees) + 360);
            //}
            }
            else{
                 pixel.h = (pixel.h + degrees);
            }
        }
    }
}


//11 orange 216 blue
void Image::illinify(){
for(unsigned int i = 0; i < width(); i++){
    for(unsigned int j = 0; j < height(); j++){
        HSLAPixel & pixel = getPixel(i,j);
        if((getPixel(i,j).h>113) && (getPixel(i,j).h<294)){
            pixel.h = 216;
        }
        else{
            pixel.h = 11;
        }
    }
}
}

void Image::scale(double factor){
    Image orignalImage =  *this;
    resize(width()*factor,height()*factor);
    for(unsigned int i = 0; i < width(); i++){
        for(unsigned int j = 0; j < height(); j++){
            this->getPixel(i,j) = orignalImage.getPixel(i/factor,j/factor);
        }
    }
}
void Image::scale(unsigned w, unsigned h){
    Image orignalImage =  *this;
    double wR = (double)w/width();
    double hR = (double)h/height();
//     for(unsigned int i = 0; i < width(); i++){
//         for(unsigned int j = 0; j < height(); j++){
//             if(wR>=hR){
                
//                this->getPixel(i,j) = orignalImage.getPixel(i*hR,j*hR); 
//             }
//             else{
//                 this->getPixel(i,j) = orignalImage.getPixel(i*wR,j*wR);
//             }
            
//         }
// }
if(hR<=wR){
    //resize(width()*hR,height()*hR);
    scale(hR);
}
else{
    //resize(width()*wR,height()*wR);
    scale(wR);
}
}
