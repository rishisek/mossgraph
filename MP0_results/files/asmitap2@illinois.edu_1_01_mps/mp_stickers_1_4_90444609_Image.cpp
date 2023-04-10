#include "Image.h"
using namespace cs225;
using namespace std;
#include <string>

Image::Image(){}
Image::Image(unsigned int width, unsigned int height):PNG(width,height){}

void Image::darken(){
for (unsigned int i = 0; i < width(); i++){
    for (unsigned int j = 0; j < height(); j++){
        getPixel(i,j).l -= 0.1;
        if (getPixel(i,j).l < 0) {getPixel(i,j).l = 0;} 
        else if (getPixel(i,j).l > 1){ getPixel(i,j).l=1.0;}
    }
}
}

void Image::darken(double amount){
    for (unsigned int i = 0; i < width(); i++){
    for (unsigned int j = 0; j < height(); j++){
        getPixel(i,j).l -= amount;
        if (getPixel(i,j).l < 0) {getPixel(i,j).l = 0;}
        else if (getPixel(i,j).l > 1){ getPixel(i,j).l=1.0;}
    }
}

}

void Image::desaturate(){
    for(unsigned int i=0;i<width();i++){
        for(unsigned int j=0; j<height();j++){
            getPixel(i,j).s -= 0.1;
            if (getPixel(i,j).s < 0) {getPixel(i,j).s = 0;}
            else if (getPixel(i,j).s > 1){ getPixel(i,j).s=1.0;}
    }

}
}

void Image::desaturate(double amount){
    for(unsigned int i=0;i<width();i++){
        for(unsigned int j=0; j<height();j++){
            getPixel(i,j).s -= amount;
            if (getPixel(i,j).s < 0) {getPixel(i,j).s = 0;}
            else if (getPixel(i,j).s > 1){ getPixel(i,j).s=1.0;}
    }
}
}

void Image::saturate(){
    for(unsigned int i=0;i<width();i++){
        for(unsigned int j=0; j<height();j++){
            getPixel(i,j).s +=0.1;
            if (getPixel(i,j).s < 0) {getPixel(i,j).s = 0;}
            else if (getPixel(i,j).s > 1){ getPixel(i,j).s=1.0;}
    }


}

}
void Image::saturate(double amount){
    for(unsigned int i=0;i<width();i++){
        for(unsigned int j=0; j<height();j++){
            getPixel(i,j).s += amount;
            if (getPixel(i,j).s < 0) {getPixel(i,j).s = 0;}
            else if (getPixel(i,j).s > 1){ getPixel(i,j).s=1.0;}
         }
    }
}

void Image::grayscale(){
    for(unsigned int i=0;i<width();i++){
        for(unsigned int j=0; j<height();j++){
            getPixel(i,j).s=0;
    }
  }
}

void Image::illinify(){
    for(unsigned int i=0;i<width();i++){
        for(unsigned int j=0; j<height();j++){
            if (getPixel(i,j).h>=113.5 && getPixel(i,j).h<=293.5){
                getPixel(i,j).h=216;}
            else {getPixel(i,j).h=11;}
    }
  }
}

void Image::lighten(){
    for(unsigned int i=0;i<width();i++){
        for(unsigned int j=0; j<height();j++){
            getPixel(i,j).l +=0.1;
            if (getPixel(i,j).l < 0) {getPixel(i,j).l = 0;}
            else if (getPixel(i,j).l > 1){ getPixel(i,j).l=1.0;}
}
}
}
void Image::lighten(double amount){
    for(unsigned int i=0;i<width();i++){
        for(unsigned int j=0; j<height();j++){
            getPixel(i,j).l += amount;
            if (getPixel(i,j).l < 0) {getPixel(i,j).l = 0;}
            else if (getPixel(i,j).l > 1){ getPixel(i,j).l=1.0;}
    }
}    
}

void Image::rotateColor(double degrees){
    for(unsigned int i=0; i<width();i++){
        for(unsigned int j=0; j<height(); j++){
            getPixel(i,j).h=getPixel(i,j).h+degrees;
            while(getPixel(i,j).h>360){getPixel(i,j).h-=360;}
            while(getPixel(i,j).h<0){getPixel(i,j).h+=360;}
        }
    }
}

void Image::scale(double factor){
    if(factor==0){return;}
    Image previous = *this;
    unsigned int nwidth= width()*factor;
    unsigned int nheight= height()*factor;
    resize(nwidth,nheight);
    for(unsigned int i=0; i<width();i++){
        for(unsigned int j=0; j<height();j++){
            getPixel(i,j)=previous.getPixel(i/factor,j/factor);
            //currentpix=newpix;
            }
        }

    }
    

void Image::scale(unsigned w, unsigned h){
   double dWidth= w;
   double dHeight= h;
   double originalw=width();
   double originalh=height();
   double newFactorWidth= dWidth/originalw;
   double newFactorHeight= dHeight/originalh;
   if (newFactorWidth<newFactorHeight){scale(newFactorWidth); }
   else{scale(newFactorHeight);}  
}