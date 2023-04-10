#include "Image.h"
using namespace cs225;
using namespace std;
//7:24pm@14th


// By default, calling any method from another class in here alters "THIS" object, eliminating the need to dereference with this->method()

Image::Image(){}

Image::Image(unsigned int width, unsigned int height):PNG(width, height){}  // since image doesn't actually deal with making a new picture when you call it in the render function

void Image::lighten(){
for (unsigned int i = 0; i < width(); i++){
    for (unsigned int j = 0; j < height(); j++){
        getPixel(i,j).l += 0.1;
        if (getPixel(i,j).l > 1) {getPixel(i,j).l = 1;}
    }
}
}

void Image::lighten(double amount){
for (unsigned int i = 0; i < width(); i++){
    for (unsigned int j = 0; j < height(); j++){
        getPixel(i,j).l += amount;
        if (getPixel(i,j).l > 1) {getPixel(i,j).l = 1;}
    }
}   
}

// remember that width() and height() have type unsigned int
void Image::darken(){
for (unsigned int i = 0; i < width(); i++){
    for (unsigned int j = 0; j < height(); j++){
        getPixel(i,j).l -= 0.1;
        if (getPixel(i,j).l < 0) {getPixel(i,j).l = 0;} // this is known as clamping
    }
}
}

void Image::darken(double amount){
for (unsigned int i = 0; i < width(); i++){
    for (unsigned int j = 0; j < height(); j++){
        getPixel(i,j).l -= amount;
        if (getPixel(i,j).l < 0) {getPixel(i,j).l = 0;}
    }
}
}

void Image::saturate(){
for (unsigned int i = 0; i < width(); i++){
    for (unsigned int j = 0; j < height(); j++){
        getPixel(i,j).s += 0.1;
        if (getPixel(i,j).s > 1) {getPixel(i,j).s = 1;}
    }
}
}

void Image::saturate(double amount){
for (unsigned int i = 0; i < width(); i++){
    for (unsigned int j = 0; j < height(); j++){
        getPixel(i,j).s += amount;
        if (getPixel(i,j).s > 1) {getPixel(i,j).s = 1;}
    }
}
}

void Image::desaturate(){
for (unsigned int i = 0; i < width(); i++){
    for (unsigned int j = 0; j < height(); j++){
        getPixel(i,j).s -= 0.1; // do we typecast these?
        if (getPixel(i,j).s < 0) {getPixel(i,j).s = 0;}
    }
}
}

void Image::desaturate(double amount){
for (unsigned int i = 0; i < width(); i++){
    for (unsigned int j = 0; j < height(); j++){
        getPixel(i,j).s -= amount;
        if (getPixel(i,j).s < 0) {getPixel(i,j).s = 0;}
    }
}
}

void Image::grayscale(){
for (unsigned int i = 0; i < width(); i++){
    for (unsigned int j = 0; j < height(); j++){
        getPixel(i,j).s = 0; // setting every pixel to 0
    }
}
}

void Image::rotateColor(double degrees){
for (unsigned int i = 0; i < width(); i++){
    for (unsigned int j = 0; j < height(); j++){
        getPixel(i,j).h += degrees;
        if (getPixel(i,j).h > 360){
            getPixel(i,j).h -= 360;
        }

        if (getPixel(i,j).h < 0){
            getPixel(i,j).h += 360;
        }
    }
}

}
void Image::illinify(){
for (unsigned int i = 0; i < width(); i++){
    for (unsigned int j = 0; j < height(); j++){
        if (getPixel(i,j).h >= 113.5 && getPixel(i,j).h <= 293.5){
            getPixel(i,j).h = 216; // set to blue as you are in the range of blue including 113.5 or 293.5
        }

        else {
            getPixel(i,j).h = 11; // set to orange for everything outside the range of blue... all double values are accounted for (0 to 113.49999 and 293.500001 to 360)
        }
    }
}
}


void Image::scale(double factor){

Image* original = new Image(*this); // creating new pointer space in the heap

resize(int(width()*factor), int(height()*factor)); // works on "this"

if (factor == 0){
    return;
}

for (unsigned int i = 0; i < width(); i++){
    for (unsigned int j = 0; j < height(); j++){
        getPixel(i,j) = original->getPixel(i/factor, j/factor);
    }
}
delete original; // freeing memory
}

void Image::scale(unsigned w, unsigned h){

    double newwidthFactor = (double)w / (double)(width());    
    double newheightFactor = (double)h / (double)(height());

    if (newwidthFactor < newheightFactor){ // smaller factor passed in
        scale(newwidthFactor);
    }

    else{
        scale(newheightFactor);
    }
}
