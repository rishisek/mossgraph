#include "Image.h"
using namespace cs225;
//using namespace std;
// Image(){
//     PNG();
// }
// Image(unsigned int width, unsigned int height){

// }

void Image::lighten(){
    // cout << width() << endl;
    for (unsigned int i=0; i< width();i++){
        for (unsigned int j=0; j<height();j++){
            if(getPixel(i,j).l<=0.9){
                getPixel(i,j).l+=0.1;
            }
            else{
                getPixel(i,j).l=1;
            }
        }
    }
}
void Image::lighten(double amount){
    for (unsigned int i=0; i<width();i++){
        for (unsigned int j=0; j<height();j++){
            if(getPixel(i,j).l<=(1-amount)){
                getPixel(i,j).l+=amount;
            }
            else{
                getPixel(i,j).l=1;
            }
        }
    }
}
void Image::darken(){
    for (unsigned int i=0; i<width();i++){
        for (unsigned int j=0; j<height();j++){
            if(getPixel(i,j).l>=0.1){
                getPixel(i,j).l-=0.1;
            }
            else{
                getPixel(i,j).l=0;
            }
        }
    }
}
void Image::darken(double amount){
    for (unsigned int i=0; i<width();i++){
        for (unsigned int j=0; j<height();j++){
            if(getPixel(i,j).l>=amount){
                getPixel(i,j).l-=amount;
            }
            else{
                getPixel(i,j).l=0;
            }
        }
    }
}
void Image::saturate(){
    for (unsigned int i=0; i<width();i++){
        for (unsigned int j=0; j<height();j++){
            if(getPixel(i,j).s<=0.9){
                getPixel(i,j).s+=0.1;
            }
            else{
                getPixel(i,j).s=1;
            }
        }
    }
}
void Image::saturate(double amount){
    for (unsigned int i=0; i<width();i++){
        for (unsigned int j=0; j<height();j++){
            if(getPixel(i,j).s<=(1-amount)){
                getPixel(i,j).s+=0.1;
            }
            else{
                getPixel(i,j).s=1;
            }
        }
    }
}
void Image::desaturate(){
    for (unsigned int i=0; i<width();i++){
        for (unsigned int j=0; j<height();j++){
            if(getPixel(i,j).s>=0.1){
                getPixel(i,j).s-=0.1;
            }
            else{
                getPixel(i,j).s=0;
            }
        }
    }
}
void Image::desaturate(double amount){
    for (unsigned int i=0; i<width();i++){
        for (unsigned int j=0; j<height();j++){
            if(getPixel(i,j).s>=amount){
                getPixel(i,j).s-=amount;
            }
            else{
                getPixel(i,j).s=0;
            }
        }
    }
}
void Image::grayscale(){
    for (unsigned int i=0; i<width();i++){
        for (unsigned int j=0; j<height();j++){
            getPixel(i,j).s=0;
        }
    }
}
void Image::rotateColor(double degrees){
    for (unsigned int i=0; i<width();i++){
        for (unsigned int j=0; j<height();j++){
            if((getPixel(i,j).h+degrees)>360){
                getPixel(i,j).h=getPixel(i,j).h+degrees-360;
            }
            else if((getPixel(i,j).h+degrees)<0){
                getPixel(i,j).h=getPixel(i,j).h+degrees+360;
            }
            else{
                getPixel(i,j).h=getPixel(i,j).h+degrees;
            }
        }
    }
}
void Image::illinify(){
    for (unsigned int i=0; i<width();i++){
        for (unsigned int j=0; j<height();j++){
            if(getPixel(i,j).h<=113){
                getPixel(i,j).h=11;
            }
            else{
                getPixel(i,j).h=216;
            }
        }
    }
}
void Image::scale(double factor){
    Image orig(*this);
    resize(width()*factor,height()*factor);
    for (unsigned int i=0; i<width();i++){
        for (unsigned int j=0; j<height();j++){
            getPixel(i,j)=orig.getPixel(i/factor, j/factor);
        }
    }
}
void Image::scale(unsigned w, unsigned h){
    Image orig(*this);
    double widthratio= (double)w/width();
    double heightratio=(double)h/height();
    if(widthratio<=heightratio){
        scale(widthratio);
    }
    else{
        scale(heightratio);
    }
}