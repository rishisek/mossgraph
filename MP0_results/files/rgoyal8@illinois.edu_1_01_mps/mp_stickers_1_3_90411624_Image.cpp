

#include "Image.h"
#include <iostream>


Image::Image(){
    width_ = 0;
    height_  = 0;
}

Image::Image(unsigned int width, unsigned int height): width_(width), height_(height){
}

void Image::lighten (){
    for(unsigned int i = 0; i < width(); ++i){
        for (unsigned int j = 0; j < height(); ++j){
            if(getPixel(i,j).l <= (1- 0.1)){
                getPixel(i,j).l += 0.1;
            } else {
                getPixel(i,j).l = 1;
            }
        }

    }
}
void Image::lighten (double amount){
    for(unsigned int i = 0; i < width(); ++i){
        for (unsigned int j = 0; j < height(); ++j){
            if(getPixel(i,j).l <= (1-amount)){
                getPixel(i,j).l += amount;
            } else {
                getPixel(i,j).l = 1;
            }
        }
    }
}
void Image::darken (){
    for(unsigned int i = 0; i < width(); ++i){
        for (unsigned int j = 0; j < height(); ++j){
            if((getPixel(i,j).l - .1) >= 0){
                getPixel(i,j).l -= 0.1;
            } else {
                getPixel(i,j).l = 0;
            }
        }

    }
}
void Image::darken (double amount){
    for(unsigned int i = 0; i < width(); ++i){
        for (unsigned int j = 0; j < height(); ++j){
            if((getPixel(i,j).l - amount) >= 0){
                getPixel(i,j).l -= amount;
            } else {
                getPixel(i,j).l = 0;
            }
        }
    }
}
void Image::saturate (){
      for(unsigned int i = 0; i < width(); ++i){
        for (unsigned int j = 0; j < height(); ++j){
            if(getPixel(i,j).s <= (1- 0.1)){
                getPixel(i,j).s += 0.1;
            } else {
                getPixel(i,j).s = 1;
            }
        }
    }
}
void Image::saturate (double amount){
    for(unsigned int i = 0; i < width(); ++i){
        for (unsigned int j = 0; j < height(); ++j){
            if(getPixel(i,j).s <= (1-amount)){
                getPixel(i,j).s += amount;
            } else {
                getPixel(i,j).s = 1;
            }
        }
    }
}
void Image::desaturate (){
    for(unsigned int i = 0; i < width(); ++i){
        for (unsigned int j = 0; j < height(); ++j){
            if((getPixel(i,j).s - .1) >= 0){
                getPixel(i,j).s -= 0.1;
            } else {
                getPixel(i,j).s = 0;
            }
        }

    }
}
void Image::desaturate (double amount){
    for(unsigned int i = 0; i < width(); ++i){
        for (unsigned int j = 0; j < height(); ++j){
            if((getPixel(i,j).s - amount) >= 0){
                getPixel(i,j).s -= amount;
            } else {
                getPixel(i,j).s = 0;
            }
        }
    }
}
void Image::grayscale (){
    for(unsigned int i = 0; i < width(); ++i){
        for (unsigned int j = 0; j < height(); ++j){
            getPixel(i,j).s = 0;
        }
    }
}
void Image::rotateColor (double degrees){
    if(degrees < 0){
        degrees = degrees + 360;
    }
    for(unsigned int i = 0; i < width(); ++i){
        for (unsigned int j = 0; j < height(); ++j){
            getPixel(i,j).h = int(getPixel(i,j).h + degrees) % 360;
        }
    }
}
void Image::illinify (){
    for(unsigned int i = 0; i < width(); ++i){
        for (unsigned int j = 0; j < height(); ++j){
            if(113 < getPixel(i,j).h && getPixel(i,j).h < 294){
                getPixel(i,j).h = 216;
            } else {getPixel(i,j).h = 11;}
        }
    }
}

void Image::scale (double factor){
    double newWidth_ = double(width())*factor;
    double newHeight_ = double(height()) * factor;
    PNG newData(*this);
    resize(newWidth_, newHeight_);

    for (unsigned i = 0; i < newWidth_; i++) {
        for (unsigned j = 0; j < newHeight_; j++) {
            int width_col = i/factor;
            int height_row = j/factor;
            getPixel(i, j) = newData.getPixel(width_col, height_row);
        }
    }

}

void Image::scale (unsigned w, unsigned h){
    double width_ratio = double(w)/double(width());
    double height_ratio = double(h)/double(height());
    double ratio = double(width())/double(height());
    double factor;
    if(w/h > ratio){
        w = width() * height_ratio;
        factor = height_ratio;
    } else{
        h = height() * width_ratio;
        factor = width_ratio;
    }
    PNG newData(*this);
    resize(w, h);

    for (unsigned i = 0; i < w; i++) {
        for (unsigned j = 0; j < h; j++) {
            int width_col = i/factor;
            int height_row = j/factor;
            getPixel(i, j) = newData.getPixel(width_col, height_row);
        }
    }
}
