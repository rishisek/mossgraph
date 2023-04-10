#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>
#include <iostream> 
#include <cmath>


using namespace std;
using namespace cs225;

Image::Image() : PNG(){

}

Image::Image(unsigned int width, unsigned int height) :PNG(width,height) {

}



void Image::darken() { 
// Darken an Image by decreasing the luminance of every pixel by 0.1
    for(unsigned int i = 0; i<width();i++){
        for(unsigned int j = 0; j<height();j++) {
            //HSLAPixel & pix = getPixel(i,j); // getPix method is called to retrive the current pix, then the result is put into pix which is of the type HSLAPixel
            getPixel(i,j).l -= 0.1; 
            if (getPixel(i,j).l > 1.0) {
                getPixel(i,j).l = 1.0;
            }

            else if (getPixel(i,j).l < 0.0) {
                     getPixel(i,j).l = 0.0;
            }

            //making sure the luminance remains in the range [0,1]

        }
    }
}

void Image::darken(double amount) {
    for(unsigned int i = 0; i<width();i++) {
        for (unsigned int j = 0; j<height();j++ ){
            //HSLAPixel & pix = getPixel(i,j); // getPix method is called to retrive the current pix, then the result is put into pix which is of the type HSLAPixel
            getPixel(i,j).l -= amount; 
            if (getPixel(i,j).l > 1.0) {
                getPixel(i,j).l = 1.0;
            }

            else if (getPixel(i,j).l < 0.0) {
                (getPixel(i,j).l = 0.0);
            }
        }
    }
}

void Image::desaturate() {
    for(unsigned int i = 0; i<width();i++){
        for(unsigned int j = 0; j<height();j++) {
           // HSLAPixel & pix = getPixel(i,j); // getPix method is called to retrive the current pix, then the result is put into pix which is of the type HSLAPixel
            getPixel(i,j).s -= 0.1; 
            if (getPixel(i,j).s > 1.0) {
                getPixel(i,j).s = 1.0;
            }

            else if (getPixel(i,j).s < 0.0) {
                    (getPixel(i,j).s = 0.0);
            }

            //making sure the luminance remains in the range [0,1]

        }
    }
    
}

void Image::desaturate(double amount) {
    for(unsigned int i = 0; i<width();i++){
        for(unsigned int j = 0; j<height();j++) {
            //HSLAPixel & pix = getPixel(i,j); // getPix method is called to retrive the current pix, then the result is put into pix which is of the type HSLAPixel
            getPixel(i,j).s -= amount; 
            if (getPixel(i,j).s > 1.0) {
                getPixel(i,j).s = 1.0;
            }

            else if (getPixel(i,j).s < 0.0) {
                    (getPixel(i,j).s = 0.0);
            }

            //making sure the luminance remains in the range [0,1]

        }
    }
    
}

void Image::saturate() {
    for(unsigned int i = 0; i<width();i++){
        for(unsigned int j = 0; j<height();j++) {
            //HSLAPixel & pix = getPixel(i,j); // getPix method is called to retrive the current pix, then the result is put into pix which is of the type HSLAPixel
            getPixel(i,j).s += 0.1; 
            if (getPixel(i,j).s > 1.0) {
                getPixel(i,j).s = 1.0;
            }

            else if (getPixel(i,j).s < 0.0) {
                    (getPixel(i,j).s = 0.0);
            }

            //making sure the luminance remains in the range [0,1]

        }
    }
    
}

void Image::saturate(double amount) {
    for(unsigned int i = 0; i<width();i++){
        for(unsigned int j = 0; j<height();j++) {
            //HSLAPixel & pix = getPixel(i,j); // getPix method is called to retrive the current pix, then the result is put into pix which is of the type HSLAPixel
            getPixel(i,j).s += amount; 
            if (getPixel(i,j).s > 1.0) {
                getPixel(i,j).s = 1.0;
            }

            else if (getPixel(i,j).s < 0.0) {
                    (getPixel(i,j).s = 0.0);
            }

            //making sure the luminance remains in the range [0,1]

        }
    }
    
}

void Image::lighten(double amount) {
    for(unsigned int i = 0; i<width();i++) {
        for (unsigned int j = 0; j<height();j++ ){
            //HSLAPixel & pix = getPixel(i,j); // getPix method is called to retrive the current pix, then the result is put into pix which is of the type HSLAPixel
            getPixel(i,j).l += amount; 
            if (getPixel(i,j).l > 1.0) {
                getPixel(i,j).l = 1.0;
            }

            else if (getPixel(i,j).l < 0.0) {
                (getPixel(i,j).l = 0.0);
            }
        }
    }
}

void Image::lighten() {
    for(unsigned int i = 0; i<width();i++) {
        for (unsigned int j = 0; j<height();j++ ){
            
            getPixel(i,j).l += 0.1; 
            if (getPixel(i,j).l > 1.0) {
                getPixel(i,j).l = 1.0;
            }

            else if (getPixel(i,j).l < 0.0) {
                (getPixel(i,j).l = 0.0);
            }
        }
    }
}

void Image::grayscale() {
    for(unsigned int i = 0; i<width();i++) {
        for (unsigned int j = 0; j<height();j++ ){
            
            getPixel(i,j).s = 0.0;  
            

            }
        }
    }


void Image::illinify() {
    
    for(unsigned int i = 0; i<width();i++) {
        for (unsigned int j = 0; j<height();j++ ){
            
            if(getPixel(i,j).h >= 113.5 && getPixel(i,j).h < 293.5) { 
                getPixel(i,j).h = 216;

            }

            else getPixel(i,j).h = 11;
            
        }
    }
}


void Image::rotateColor(double degrees) {
    for(unsigned int i = 0; i<width();i++) {
        for (unsigned int j = 0; j<height();j++ ){
            
           getPixel(i,j).h += degrees;
           if (getPixel(i,j).h < 0.0) {
            getPixel(i,j).h += 360;
           }

           else if (getPixel(i,j).h >360) {
            getPixel(i,j).h -= 360;
           }
            
            
        }

    }
}
 
void Image::scale(double factor) {
    

    Image nayi = *this;
    unsigned  new_w = width() * factor;
    unsigned  new_h = height() * factor;

    resize(new_w,new_h);
    
    for(unsigned int i = 0; i<new_w;i++) {
        for (unsigned int j = 0; j<new_h;j++ ) { 
            getPixel(i,j) = nayi.getPixel(i/factor,j/factor);
        }
    }
    
}

void Image::scale(unsigned w, unsigned h) {
    double factor = min(double(w/width()), double(h/height()));
    scale(factor);  

}  


    










