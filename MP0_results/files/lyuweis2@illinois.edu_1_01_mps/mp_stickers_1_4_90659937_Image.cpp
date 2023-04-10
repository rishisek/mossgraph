#include "Image.h"


Image::Image() : PNG() {}


Image::Image(unsigned int width, unsigned int height) : PNG(width, height){}


void Image::lighten() {
    cs225::HSLAPixel * temp;
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++){
            temp = &getPixel(i,j);
            if (temp->l<=0.9){
                temp->l = temp->l + 0.1;
            } else {
                temp->l = 1;
            }
        }
    }
}

void Image::lighten(double x) {
    cs225::HSLAPixel * temp;
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++){
            temp = &getPixel(i,j);
            if (temp->l<=(1-x)){
                temp->l = temp->l + x;
            } else {
                temp->l = 1;
            }
        }
    }
}

void Image::darken	()	{
    cs225::HSLAPixel * temp;
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++){
            temp = &getPixel(i,j);
            if (temp->l >= 0.1){
                temp->l = temp->l - 0.1;
            } else {
                temp->l = 0;
            }
        }
    }
}

void Image::darken	(double x)	{
    cs225::HSLAPixel * temp;
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++){
            temp = &getPixel(i,j);
            if (temp->l >= x){
                temp->l = temp->l - x;
            } else {
                temp->l = 0;
            }
        }
    }
}

void Image::saturate()	{
    cs225::HSLAPixel * temp;
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++){
            temp = &getPixel(i,j);
            if (temp->s <= 0.9){
                temp->s = temp->s + 0.1;
            } else {
                temp->s = 1;
            }
        }
    }
}

void Image::saturate(double x)	{
    cs225::HSLAPixel * temp;
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++){
            temp = &getPixel(i,j);
            if (temp->s <= (1-x)){
                temp->s = temp->s + x;
            } else {
                temp->s = 1;
            }
        }
    }
}

void Image::desaturate	()	{
    cs225::HSLAPixel * temp;
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++){
            temp = &getPixel(i,j);
            if (temp->s >= 0.1){
                temp->s = temp->s - 0.1;
            } else {
                temp->s = 0;
            }
        }
    }
}

void Image::desaturate	(double x)	{
    cs225::HSLAPixel * temp;
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++){
            temp = &getPixel(i,j);
            if (temp->s >= x){
                temp->s = temp->s - x;
            } else {
                temp->s = 0;
            }
        }
    }
}

void Image::grayscale(){
    cs225::HSLAPixel * temp;
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++){
            temp = &getPixel(i,j);
            temp->s = 0;
        }
    }
}

void Image::rotateColor	(	double 	degrees	)	{
    cs225::HSLAPixel * temp;
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++){
            temp = &getPixel(i,j);
            temp->h = temp->h + degrees;
            while (temp->h > 360.0) {
                temp->h = temp->h - 360.0;
            }
            while (temp->h < 0) {
                temp->h = temp->h + 360.0;
            }
        }
    }
}

void Image::illinify	()	{
    cs225::HSLAPixel * temp;
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++){
            temp = &getPixel(i,j);
            if (temp->h >= 113.5 && temp->h <= 293.5) {
                temp->h = 216;
            } else {
                temp->h = 11;
            }
        }
    }
}

void Image::scale	(	double 	factor	)	{
    //cs225::HSLAPixel * temp;
    //cs225::HSLAPixel * temp_;
    if (factor <= 1) {
        for (unsigned int i = 0; i < width()*factor; i++) {
            for (unsigned int j = 0; j < height()*factor; j++){
 
                *&getPixel(i,j) = *&getPixel(int(i/factor), int(j/factor));
            }
        }
        resize(unsigned(width()*factor), unsigned(height()*factor));
    } else {
        resize(unsigned(width()*factor), unsigned(height()*factor));
        for ( int i = int(width())-1; i >= 0; i--) {
            for ( int j = int(height())-1; j >= 0; j--){
                *&getPixel(i,j) = *&getPixel(int(i/factor), int(j/factor));
            }
        }
        
    }
}


void Image::scale	(unsigned w, unsigned h ) {
    double factor = std::min(double(w)/width(), double(h)/height());
    scale(factor);
}	






