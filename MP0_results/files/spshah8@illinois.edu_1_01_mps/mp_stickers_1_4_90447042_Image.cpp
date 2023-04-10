#include "Image.h"
using namespace cs225;

Image::Image(){
    PNG();
}

Image::Image(unsigned int width, unsigned int height){
    PNG(width, height);
}

void Image::lighten(){
    unsigned int x = this->width();
    unsigned int y = this->height();
    for (unsigned int i = 0; i < x; i++){
        for (unsigned int j = 0; j < y; j++){
            this->getPixel(i,j).l = this->getPixel(i,j).l + .1;
            if (this->getPixel(i,j).l > 1){
                this->getPixel(i,j).l = 1;
            }
        }
    }
}

void Image::lighten(double amount){
    unsigned int x = this->width();
    unsigned int y = this->height();
    for (unsigned int i = 0; i < x; i++){
        for (unsigned int j = 0; j < y; j++){
            this->getPixel(i,j).l = this->getPixel(i,j).l + amount;
            if (this->getPixel(i,j).l > 1){
                this->getPixel(i,j).l = 1;
            }
        }
    }
}

void Image::darken(){
    unsigned int x = this->width();
    unsigned int y = this->height();
    for (unsigned int i = 0; i < x; i++){
        for (unsigned int j = 0; j < y; j++){
            this->getPixel(i,j).l = this->getPixel(i,j).l - 0.1;
            if (this->getPixel(i,j).l < 0){
                this->getPixel(i,j).l = 0;
            }
        }
    }
}

void Image::darken(double amount){
    unsigned int x = this->width();
    unsigned int y = this->height();
    for (unsigned int i = 0; i < x; i++){
        for (unsigned int j = 0; j < y; j++){
            this->getPixel(i,j).l = this->getPixel(i,j).l - amount;
            if (this->getPixel(i,j).l < 0){
                this->getPixel(i,j).l = 0;
            }
        }
    }
}

void Image::rotateColor(double degrees){
    unsigned int x = this->width();
    unsigned int y = this->height();
    for (unsigned int i = 0; i < x; i++){
        for (unsigned int j = 0; j < y; j++){
            this->getPixel(i,j).h = this->getPixel(i,j).h + degrees;
            if (this->getPixel(i,j).h > 360){
                this->getPixel(i,j).h = this->getPixel(i,j).h - 360;
            }
            if (this->getPixel(i,j).h < 0){
                this->getPixel(i,j).h = this->getPixel(i,j).h + 360;
            }
        }
    }
}

void Image::saturate(){
    unsigned int x = this->width();
    unsigned int y = this->height();
    for (unsigned int i = 0; i < x; i++){
        for (unsigned int j = 0; j < y; j++){
            this->getPixel(i,j).s = this->getPixel(i,j).s + 0.1;
            if (this->getPixel(i,j).s > 1){
                this->getPixel(i,j).s = 1;
            }
        }
    }
}

void Image::saturate(double amount){
    unsigned int x = this->width();
    unsigned int y = this->height();
    for (unsigned int i = 0; i < x; i++){
        for (unsigned int j = 0; j < y; j++){
            this->getPixel(i,j).s = this->getPixel(i,j).s + amount;
            if (this->getPixel(i,j).s > 1){
                this->getPixel(i,j).s = 1;
            }
        }
    }
}

void Image::desaturate(){
    unsigned int x = this->width();
    unsigned int y = this->height();
    for (unsigned int i = 0; i < x; i++){
        for (unsigned int j = 0; j < y; j++){
            this->getPixel(i,j).s = this->getPixel(i,j).s - 0.1;
            if (this->getPixel(i,j).s < 0){
                this->getPixel(i,j).s = 0;
            }
        }
    }
}

void Image::desaturate(double amount){
    unsigned int x = this->width();
    unsigned int y = this->height();
    for (unsigned int i = 0; i < x; i++){
        for (unsigned int j = 0; j < y; j++){
            this->getPixel(i,j).s = this->getPixel(i,j).s - amount;
            if (this->getPixel(i,j).s < 0){
                this->getPixel(i,j).s = 0;
            }
        }
    }
}

void Image::grayscale(){
    unsigned int x = this->width();
    unsigned int y = this->height();
    for (unsigned int i = 0; i < x; i++){
        for (unsigned int j = 0; j < y; j++){
            this->getPixel(i,j).s = 0.0;
        }
    }
}

void Image::illinify(){
    unsigned int x = this->width();
    unsigned int y = this->height();
    for (unsigned int i = 0; i < x; i++){
        for (unsigned int j = 0; j < y; j++){
            if (this->getPixel(i,j).h <= 293.5 && this->getPixel(i,j).h > 113.5){
                this->getPixel(i,j).h = 216;
            }
            else{
                this->getPixel(i,j).h = 11;
            }
        }
    }

}

void Image::scale(double factor){
    Image new_Image = *this;
    unsigned new_height = this->height() * factor;
    unsigned new_width = this->width() * factor;
    this->resize(new_width, new_height);

    for (unsigned int i = 0; i < new_width; i++){
        for (unsigned int j = 0; j < new_height; j++){
            this->getPixel(i,j) = new_Image.getPixel(i/factor,j/factor);
        }
    }
}

void Image::scale(unsigned w, unsigned h){
    double fact_1 = (double)h / (double)this->height();
    double fact_2 = (double)w / (double)this->width();
    if (fact_1 <= fact_2){
        this->scale(fact_1);
    }
    else{
        this->scale(fact_2);
    }
}