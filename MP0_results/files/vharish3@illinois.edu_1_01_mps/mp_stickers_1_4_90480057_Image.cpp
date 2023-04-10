#include "Image.h"

using namespace cs225;

Image::Image(){
    
    PNG();
}
Image::Image(unsigned int width, unsigned int height){

    PNG(width, height);

}

void Image::lighten(){

    unsigned int rows = this->width();
    unsigned int cols = this->height();

    for (unsigned int i = 0; i < rows; i++){
        for (unsigned int j = 0; j < cols; j++){
            this->getPixel(i,j).l = (this->getPixel(i,j).l + 0.1);

            if (this->getPixel(i,j).l > 1.0){
                this->getPixel(i,j).l = 1.0;
            }
        }
    }
}

void Image::lighten(double amount){

    unsigned int rows = this->width();
    unsigned int cols = this->height();

    for (unsigned int i = 0; i < rows; i++){
        for (unsigned int j = 0; j < cols; j++){
            this->getPixel(i,j).l = (this->getPixel(i,j).l + amount);

            if (this->getPixel(i,j).l > 1.0){
                this->getPixel(i,j).l = 1.0;
            }
        }
    }

}

void Image::darken(){

    unsigned int rows = this->width();
    unsigned int cols = this->height();

    for (unsigned int i = 0; i < rows; i++){
        for (unsigned int j = 0; j < cols; j++){
            this->getPixel(i,j).l = (this->getPixel(i,j).l - 0.1);

            if (this->getPixel(i,j).l < 0){
                this->getPixel(i,j).l = 0.0;
            }
        }
    }

}

void Image::darken(double amount){

    unsigned int rows = this->width();
    unsigned int cols = this->height();

    for (unsigned int i = 0; i < rows; i++){
        for (unsigned int j = 0; j < cols; j++){
            this->getPixel(i,j).l = (this->getPixel(i,j).l - amount);

            if (this->getPixel(i,j).l < 0){
                this->getPixel(i,j).l = 0.0;
            }
        }
    }

}

void Image::saturate(){

    unsigned int rows = this->width();
    unsigned int cols = this->height();

    for (unsigned int i = 0; i < rows; i++){
        for (unsigned int j = 0; j < cols; j++){
            this->getPixel(i,j).s = (this->getPixel(i,j).s + 0.1);

            if (this->getPixel(i,j).s > 1.0){
                this->getPixel(i,j).s = 1.0;
            }
        }
    }

}

void Image::saturate(double amount){

    unsigned int rows = this->width();
    unsigned int cols = this->height();

    for (unsigned int i = 0; i < rows; i++){
        for (unsigned int j = 0; j < cols; j++){
            this->getPixel(i,j).s = (this->getPixel(i,j).s + amount);

            if (this->getPixel(i,j).s > 1.0){
                this->getPixel(i,j).s = 1.0;
            }
        }
    }

}

void Image::desaturate(){

    unsigned int rows = this->width();
    unsigned int cols = this->height();

    for (unsigned int i = 0; i < rows; i++){
        for (unsigned int j = 0; j < cols; j++){
            this->getPixel(i,j).s = (this->getPixel(i,j).s - 0.1);

            if (this->getPixel(i,j).s < 0){
                this->getPixel(i,j).s = 0.0;
            }
        }
    }

}

void Image::desaturate(double amount){

    unsigned int rows = this->width();
    unsigned int cols = this->height();

    for (unsigned int i = 0; i < rows; i++){
        for (unsigned int j = 0; j < cols; j++){
            this->getPixel(i,j).s = (this->getPixel(i,j).s - amount);

            if (this->getPixel(i,j).s < 0){
                this->getPixel(i,j).s = 0.0;
            }
        }
    }

}

void Image::grayscale(){

    unsigned int rows = this->width();
    unsigned int cols = this->height();

    for (unsigned int i = 0; i < rows; i++){
        for (unsigned int j = 0; j < cols; j++){
            this->getPixel(i,j).s = 0.0;
        }
    }    
}

void Image::rotateColor(double degrees){

    unsigned int rows = this->width();
    unsigned int cols = this->height();

    for (unsigned int i = 0; i < rows; i++){
        for (unsigned int j = 0; j < cols; j++){
            this->getPixel(i,j).h  = this->getPixel(i,j).h + degrees;
            if (this->getPixel(i,j).h > 360){
                this->getPixel(i,j).h = this->getPixel(i,j).h - 360.0; 
            }
            if (this->getPixel(i,j).h < 0){
                this->getPixel(i,j).h = this->getPixel(i,j).h + 360.0; 
            }
        }    

    }
}

void Image::illinify(){

    unsigned int rows = this->width();
    unsigned int cols = this->height();

    for (unsigned int i = 0; i < rows; i++){
        for (unsigned int j = 0; j < cols; j++){
            if (this->getPixel(i,j).h > 113.5 && this->getPixel(i,j).h <= 293.5 ){
                this->getPixel(i,j).h = 216;
            }
            else    
                this->getPixel(i,j).h = 11; 
        }
    }
}

void Image::scale(double factor){

    Image newImage = *this;
    unsigned new_h = this->height() * factor;
    unsigned new_w = this->width() * factor;
    this->resize(new_w, new_h);

    for(unsigned int i = 0; i < new_w; i++) {
        for(unsigned int j = 0; j < new_h; j++) {
            HSLAPixel & nuPix = getPixel(i,j);
            HSLAPixel & oldPix = newImage.getPixel(i / factor, j / factor);
            nuPix = oldPix;
            //this->getPixel(i,j) = newImage.getPixel(i / factor, j / factor);
        }
    }
}

void Image::scale(unsigned w, unsigned h){

    unsigned picW = this->width();
    unsigned picH = this->height();

    double factor1 = static_cast<double>(w) / static_cast<double>(picW);
    double factor2 = static_cast<double>(h) / static_cast<double>(picH);
    double factor;

    if(factor1 < factor2){
        factor = factor1;
    }
    else{
        factor = factor2;
    }

    this->scale(factor);
}