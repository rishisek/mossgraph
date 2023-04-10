#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

void Image::lighten()
{
    int hei = this->height();
    int wid = this->width();
    
    for (int i = 0; i < wid; i++){
        for (int j = 0; j <hei; j++){
            if(this->getPixel(i,j).l+.1>=1.0){
                this->getPixel(i,j).l = 1.0;
                continue;
            }
            else
                this->getPixel(i,j).l = this->getPixel(i,j).l+.1;
        }
    }
}
void Image::lighten(double amount){
    int hei = this->height();
    int wid = this->width();
     for (int i = 0; i < wid; i++){
        for (int j = 0; j <hei; j++){
            if(this->getPixel(i,j).l+amount>=1.0){
                this->getPixel(i,j).l = 1.0;
                continue;
            }
            else
                this->getPixel(i,j).l = this->getPixel(i,j).l+amount;
        }
    }
}
void Image::darken()
{
    int hei = this->height();
    int wid = this->width();
    
    for (int i = 0; i < wid; i++){
        for (int j = 0; j <hei; j++){
            if(this->getPixel(i,j).l-.1<=0.0){
                this->getPixel(i,j).l = 0.0;
                continue;
            }
            else
                this->getPixel(i,j).l = this->getPixel(i,j).l-.1;
        }
    }
}
void Image::darken(double amount){
    int hei = this->height();
    int wid = this->width();
     for (int i = 0; i < wid; i++){
        for (int j = 0; j <hei; j++){
            if(this->getPixel(i,j).l+-amount<=0.0){
                this->getPixel(i,j).l = 0.0;
                continue;
            }
            else
                this->getPixel(i,j).l = this->getPixel(i,j).l-amount;
        }
    }
}
void Image::grayScale(){
    int hei = this->height();
    int wid = this->width();
    for (int i = 0; i < wid; i++){
        for (int j = 0; j <hei; j++){
            this->getPixel(i,j).s=0;
        }
    }
}
void Image::illinify(){
    int hei = this->height();
    int wid = this->width();
    for (int i = 0; i < wid; i++){
        for (int j = 0; j <hei; j++){
            cs225::HSLAPixel & pixel = this->getPixel(i,j);
            double od, bd;
            if (pixel.h >= 191){
                od = 371-pixel.h;
            }
            else{
                od = sqrt((pixel.h-11)*(pixel.h-11));
            }
            if(pixel.h>=36&&pixel.h<=216){
                bd = 216-pixel.h;
                bd = sqrt(bd*bd);
            }
            else
            {
                bd = pixel.h -216;
                bd = sqrt(bd*bd);
            }
            if(od>=bd){
                pixel.h = 216;
                pixel.h = 11;
            }
        }
    }
}
void Image::desaturate(){
    int hei = this->height();
    int wid = this->width();
    for (int i = 0; i < wid; i++){
        for (int j = 0; j <hei; j++){
            this->getPixel(i,j).s=this->getPixel(i,j).s-.1;
        }
    }
}
void Image::desaturate(double amount){
    int hei = this->height();
    int wid = this->width();
    for (int i = 0; i < wid; i++){
        for (int j = 0; j <hei; j++){
            this->getPixel(i,j).s=this->getPixel(i,j).s-amount;
        }
    }
}
void Image::saturate(){
    int hei = this->height();
    int wid = this->width();
    for (int i = 0; i < wid; i++){
        for (int j = 0; j <hei; j++){
            this->getPixel(i,j).s=this->getPixel(i,j).s+.1;
        }
    }
}
void Image::saturate(double amount){
    int hei = this->height();
    int wid = this->width();
    for (int i = 0; i < wid; i++){
        for (int j = 0; j <hei; j++){
            this->getPixel(i,j).s=this->getPixel(i,j).s+amount;
        }
    }
}
void Image::rotateColor(double degrees){
    int hei = this->height();
    int wid = this->width();
    for (int i = 0; i < wid; i++){
        for (int j = 0; j <hei; j++){
            if(this->getPixel(i,j).h+degrees>360){
                this->getPixel(i,j).h = this->getPixel(i,j).h +degrees-360;
            }
            else if(this->getPixel(i,j).h+degrees<0){
                this->getPixel(i,j).h = this->getPixel(i,j).h +degrees+360;
            }
            else{
                this->getPixel(i,j).h = this->getPixel(i,j).h +degrees;
            }
        }
    }
}
void Image::scale(double factor){
    unsigned int newwid = this->width()*factor;
    unsigned int newhei = this->height()*factor;
    double xr = this->width()/(double)newwid;
    double yr = this->height()/(double)newhei;
    if(xr > yr){
        xr = yr;
    }
    else{
        yr = xr;
    }
    cs225::PNG si(*this);
    this->resize(ceil(newwid),ceil(newhei));
    for (unsigned int i = 0; i < newwid; i++){
        for (unsigned int j = 0; j < newhei; j++){
            int ox = i*xr;
            int oy = j * yr;
            this->getPixel(i,j) = si.getPixel(ox,oy);
        }
    }
}
void Image::scale(unsigned w, unsigned h){
    unsigned int newwid = w;
    unsigned int newhei = h;
    double xr = (double)newwid/(this->width());
    double yr = (double)newhei/(this->height());
    if(yr > xr){
        scale(xr);
    }
    else{
        scale(yr);
    }
}