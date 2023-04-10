/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */
#include "Image.h"


using namespace cs225;
Image::Image(){

}
/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

Image::Image(unsigned int width, unsigned int height){
    PNG(width,height);
}
    
void Image::darken(){
    for(unsigned int i = 0; i < Image::width(); i++){
        for(unsigned int j = 0; j < Image::height(); j++){
            if(Image::getPixel(i,j).l - 0.1 <= 0){
                Image::getPixel(i,j).l = 0;
            }
            else{
                Image::getPixel(i,j).l -= 0.1;
            }
        }
    }
}
void Image::darken(double amount){
    for(unsigned int i = 0; i < Image::width(); i++){
        for(unsigned int j = 0; j < Image::height(); j++){
            if(Image::getPixel(i,j).l - amount <= 0){
                Image::getPixel(i,j).l = 0;
            }
            else{
                Image::getPixel(i,j).l -= amount;
            }
        }
    }
}
void Image::desaturate(){
    for(unsigned int i = 0; i < Image::width(); i++){
        for(unsigned int j = 0; j < Image::height(); j++){
            if(Image::getPixel(i,j).s - 0.1 <= 0){
                Image::getPixel(i,j).s = 0;
            }
            else{
                Image::getPixel(i,j).s -= 0.1;
            }
        }
    }
}

void Image::desaturate(double amount){
    for(unsigned int i = 0; i < Image::width(); i++){
        for(unsigned int j = 0; j < Image::height(); j++){
            if(Image::getPixel(i,j).s - amount <= 0){
                Image::getPixel(i,j).s = 0;
            }
            else{
                Image::getPixel(i,j).s -= amount;
            }
        }
    }
}


void Image::lighten(){
    for(unsigned int i = 0; i < Image::width(); i++){
        for(unsigned int j = 0; j < Image::height(); j++){
            if(Image::getPixel(i,j).l + 0.1 >= 1){
                Image::getPixel(i,j).l = 1;
            }
            else{
                Image::getPixel(i,j).l += 0.1;
            }
        }
    }
}
void Image::lighten(double amount){
    for(unsigned int i = 0; i < Image::width(); i++){
        for(unsigned int j = 0; j < Image::height(); j++){
            if(Image::getPixel(i,j).l + amount >= 1){
                Image::getPixel(i,j).l = 1;
            }
            else{
                Image::getPixel(i,j).l += amount;
            }
        }
    }
}

void Image::saturate(){
    for(unsigned int i = 0; i < Image::width(); i++){
        for(unsigned int j = 0; j < Image::height(); j++){
            if(Image::getPixel(i,j).s + 0.1 >= 1){
                Image::getPixel(i,j).s = 1;
            }
            else{
                Image::getPixel(i,j).s += 0.1;
            }
        }
    }
}
void Image::saturate(double amount){
    for(unsigned int i = 0; i < Image::width(); i++){
        for(unsigned int j = 0; j < Image::height(); j++){
            if(Image::getPixel(i,j).s + amount >= 1){
                Image::getPixel(i,j).s = 1;
            }
            else{
                Image::getPixel(i,j).s += amount;
            }
        }
    }
}

void Image::rotateColor(double degrees){
    for(unsigned int i = 0; i < Image::width(); i++){
        for(unsigned int j = 0; j < Image::height(); j++){
            if(Image::getPixel(i,j).h + degrees > 360){
                Image::getPixel(i,j).h = Image::getPixel(i,j).h + degrees - 360;
            }
            else if(Image::getPixel(i,j).h + degrees < 0){
                Image::getPixel(i,j).s += Image::getPixel(i,j).h + degrees + 360;
            }
            else{
                Image::getPixel(i,j).s += Image::getPixel(i,j).h + degrees;
            }
        }
    }
}

void Image::illinify(){
    for(unsigned int i = 0; i < Image::width(); i++){
        for(unsigned int j = 0; j < Image::height(); j++){
            double orr;
            double blu;

            if(std::abs(Image::getPixel(i,j).h - 38.8) < std::abs(Image::getPixel(i,j).h - 38.8 - 360)){
                orr = std::abs(Image::getPixel(i,j).h - 38.8);
            }
            else{
                orr = std::abs(Image::getPixel(i,j).h - 38.8 - 360);
            }
            if(std::abs(Image::getPixel(i,j).h - 240) < std::abs(Image::getPixel(i,j).h - 240 - 360)){
                blu = std::abs(Image::getPixel(i,j).h - 240);
            }
            else{
                blu = std::abs(Image::getPixel(i,j).h - 240 - 360);
            }
            if(orr < blu){
                Image::getPixel(i,j).h = 38.8;
            }
            else{
                Image::getPixel(i,j).h = 240;
            }
        }
    }
}

void Image::scale(double factor){
    unsigned int w  = (int) (Image::width() * factor);
    unsigned int h  = (int) (Image::height() * factor);
   

    HSLAPixel* newImage = new HSLAPixel[w*h];
        int ii = 0;
        int jj = 0;
        for(unsigned int i = 0; i < w; i++){
            for(unsigned int j = 0; j < h; j++){
                newImage[j*w + i] = Image::getPixel((unsigned int)(i/factor),(unsigned int)(j/factor));
        }
    }

    Image::resize(w,h);
        for(unsigned int i = 0; i < w; i++){
            for(unsigned int j = 0; j < h; j++){
                Image::getPixel(i,j) = newImage[j*w + i];
        }


}
}

void Image::scale(unsigned w, unsigned h){
    
   

    HSLAPixel* newImage = new HSLAPixel[w*h];
    
        int ii = 0;
        int jj = 0;
        for(unsigned int i = 0; i < w; i++){
            for(unsigned int j = 0; j < h; j++){
                newImage[j*w + i] = Image::getPixel((unsigned int)(i/(w/Image::width())),(unsigned int)(j/(h/Image::height())));
        }
    }
    Image::resize(w,h);
        for(unsigned int i = 0; i < w; i++){
            for(unsigned int j = 0; j < h; j++){
                Image::getPixel(i,j) = newImage[j*w + i];
        }
}

}