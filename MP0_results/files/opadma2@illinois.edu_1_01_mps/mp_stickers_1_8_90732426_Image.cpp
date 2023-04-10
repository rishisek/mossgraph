#include "Image.h"
using namespace cs225;
Image::Image()
    : PNG()
{

}
Image::Image(unsigned int width, unsigned int height)
    : PNG(width, height)
{

}
void Image::lighten(){
    for(unsigned int w =0; w<width();w++){
        for(unsigned int h =0; h<height();h++){
            HSLAPixel & p = getPixel(w,h);
            if(p.l+0.1<=1){
                p.l = p.l + 0.1;
            }
            else{
                p.l = 1;
            }
        }
    }
}
void Image::lighten(double amount){
    for(unsigned int w =0; w<width();w++){
        for(unsigned int h =0; h<height();h++){
            HSLAPixel & p = getPixel(w,h);
            if(p.l+amount<=1){
                p.l = p.l + amount;
            }
            else{
                p.l = 1;
            }
        }
    }
}
void Image::darken(){
    for(unsigned int w =0; w<width();w++){
        for(unsigned int h =0; h<height();h++){
            HSLAPixel & p = getPixel(w,h);
            if(p.l-0.1>=0){
                p.l = p.l - 0.1;
            }
            else{
                p.l = 0;
            }
        }
    }
}
void Image::darken(double amount){
    for(unsigned int w =0; w<width();w++){
        for(unsigned int h =0; h<height();h++){
            HSLAPixel & p = getPixel(w,h);
            if(p.l-amount>=0){
                p.l = p.l - amount;
            }
            else{
                p.l = 0;
            }
        }
    }
}
void Image::saturate(){
    for(unsigned int w =0; w<width();w++){
        for(unsigned int h =0; h<height();h++){
            HSLAPixel & p = getPixel(w,h);
            if(p.s+0.1<=1){
                p.s = p.s + 0.1;
            }
            else{
                p.s = 1;
            }
        }
    }
}
void Image::saturate(double amount){
    for(unsigned int w =0; w<width();w++){
        for(unsigned int h =0; h<height();h++){
            HSLAPixel & p = getPixel(w,h);
            if(p.s+amount<=1){
                p.s = p.s + amount;
            }
            else{
                p.s = 1;
            }
        }
    }
}
void Image::desaturate(){
    for(unsigned int w =0; w<width();w++){
        for(unsigned int h =0; h<height();h++){
            HSLAPixel & p = getPixel(w,h);
            if(p.s-0.1>=0){
                p.s = p.s - 0.1;
            }
            else{
                p.s = 0;
            }
        }
    }
}
void Image::desaturate(double amount){
    for(unsigned int w =0; w<width();w++){
        for(unsigned int h =0; h<height();h++){
            HSLAPixel & p = getPixel(w,h);
            if(p.s-amount>=0){
                p.s = p.s - amount;
            }
            else{
                p.s = 0;
            }
        }
    }
}
void Image::grayscale(){
    for(unsigned int w =0; w<width();w++){
        for(unsigned int h =0; h<height();h++){
            HSLAPixel & p = getPixel(w,h);
            p.s=0;
        }
    }
}
void Image::rotateColor(double degrees){
    for(unsigned int w =0; w<width();w++){
        for(unsigned int h =0; h<height();h++){
            HSLAPixel & p = getPixel(w,h);
            p.h=p.h + degrees;
            while(p.h > 360){
                p.h = p.h-360;
            }
            while(p.h < 0){
                p.h = p.h +360.0;
            }
        }
    }
}
void Image::illinify(){
    for(unsigned int w =0; w<width();w++){
        for(unsigned int h =0; h<height();h++){
            HSLAPixel & p = getPixel(w,h);
            int orangeD;
            int blueD;
            if((p.h > 11)){
                orangeD = (360-p.h)+11;
            }
            else {
                orangeD = (p.h)+(360-11);
            }
            if(std::abs(p.h-11) < orangeD){
                orangeD  = std::abs(p.h-11);
            }
            if((p.h > 216)){
                blueD = (360-p.h)+216;
            }
            else{
                blueD = (p.h)+(360-216);
            }
            if(std::abs(p.h-216) < blueD){
                blueD  = std::abs(p.h-216);
            }
            if(blueD < orangeD){
                p.h = 216;
            }
            else{
                p.h = 11;
            }
        }
    }
}
void Image::scale(double factor){
    Image *ocopy = new Image();
    *ocopy = *this;
    resize(width()*factor, height()*factor);
    for(unsigned int w =0; w<width();w++){
        for(unsigned int h =0; h<height();h++){
            HSLAPixel & p = getPixel(w,h);
            HSLAPixel & pOld = ocopy->getPixel(w/factor,h/factor);
            p = pOld;
        }
    }
    delete ocopy;
}
void Image::scale(unsigned w, unsigned h){
    double factor;
    if ((double(w)/width())<(double(h)/height())){
        factor = double(w)/width();
    }
    else{
        factor =(double(h)/height());
    }
    Image *ocopy = new Image();
    *ocopy = *this;
    resize(width()*factor, height()*factor);
    for(unsigned int w =0; w<width();w++){
        for(unsigned int h =0; h<height();h++){
            HSLAPixel & p = getPixel(w,h);
            HSLAPixel & pOld = ocopy->getPixel(w/factor,h/factor);
            p = pOld;
        }
    }
    delete ocopy;
}