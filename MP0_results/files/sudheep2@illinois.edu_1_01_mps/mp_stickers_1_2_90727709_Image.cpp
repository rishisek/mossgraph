#include "Image.h"
#include <iostream>
#include "cs225/HSLAPixel.h"
using namespace std;
using namespace cs225;


void Image::lighten() {
    for (unsigned int i = 0; i < height(); i++) {
         for (unsigned int j = 0; j < width(); j++){
            HSLAPixel & curr_px = getPixel(j, i);
            if (curr_px.l <= 0.0) {
                curr_px.l = 0.0;
            }
            if (curr_px.l < 1.0) {
                curr_px.l += 0.1;
            }
            
            if (curr_px.l >= 1.0) {
                curr_px.l = 1.0;
            }
        }
    }
}
void Image::lighten(double amount) {
    for (unsigned int i = 0; i < height(); i++){
         for (unsigned int j = 0; j < width(); j++){
            HSLAPixel & curr_px = getPixel(j, i);
            curr_px.l += amount;
            if (curr_px.l < 0.0) {
                curr_px.l = 0.0;
            }
            if (curr_px.l > 1.0) {
                curr_px.l = 1.0;
            }
            
        }
    }
}
void Image::darken() {
     for (unsigned int i = 0; i < height(); i++){
         for (unsigned int j = 0; j < width(); j++){
            HSLAPixel & curr_px = getPixel(j, i);
            if (curr_px.l > 0.0 && curr_px.l < 1.0) {
                curr_px.l -= 0.1;
            } else {
                if (curr_px.l > 1.0) {
                    curr_px.l = 1.0;
                }
                if (curr_px.l < 0.0) {
                    curr_px.l = 0.0;
                }
                
            }
        }
    }
}
void Image::darken(double amount) {
     for (unsigned int i = 0; i < height(); i++){
         for (unsigned int j = 0; j < width(); j++){
            HSLAPixel & curr_px = getPixel(j, i);
            curr_px.l -= amount;
            if (curr_px.l < 0.0) {
                curr_px.l = 0.0;
            }
            if (curr_px.l > 1.0) {
                curr_px.l = 1.0;
            }
        }
    }
}
void Image::saturate() {
     for (unsigned int i = 0; i < height(); i++){
         for (unsigned int j = 0; j < width(); j++){
            HSLAPixel & curr_px = getPixel(j, i);
            
            if (curr_px.s <= 1.0) {
                curr_px.s += 0.1;
            }
            if (curr_px.s < 0.0) {
                curr_px.s = 0.0;
            }
            if (curr_px.s > 1.0) {
                curr_px.s = 1.0;
            }
        }
    }
}
void Image::saturate(double amount) {
     for (unsigned int i = 0; i < height(); i++){
         for (unsigned int j = 0; j < width(); j++){
            HSLAPixel & curr_px = getPixel(j, i);
            curr_px.s += amount;
            if (curr_px.s > 1.0) {
                curr_px.s = 1.0;
            }
            if (curr_px.s < 0.0) {
                curr_px.s = 0.0;
            }
        }
    }
}
void Image::desaturate() {
     for (unsigned int i = 0; i < height(); i++){
         for (unsigned int j = 0; j < width(); j++){
            HSLAPixel & curr_px = getPixel(j, i);
            if (curr_px.s >= 0.1 || curr_px.s <= 1.1) {
                if(curr_px.s >= 0.1){
                    if(curr_px.s <= 1.1){
                        curr_px.s -= 0.1;
                    }
                }
                
            } else {
                if (curr_px.s < 0.1) {
                    curr_px.s = 0.0;
                }
                if (curr_px.s > 1.1) {
                    curr_px.s = 1.0;
                }
            }
        }
    }
}
void Image::desaturate(double amount) {
     for (unsigned int i = 0; i < height(); i++){
         for (unsigned int j = 0; j < width(); j++){
            HSLAPixel & curr_px = getPixel(j, i);
            curr_px.s -= amount;
            if (curr_px.s < 0.0) {
                curr_px.s = 0.0;
            }
            if (curr_px.s > 1.0) {
                curr_px.s = 1.0;
            }
        }
    }
}
void Image::grayscale() {
     for (unsigned int i = 0; i < height(); i++){
        for (unsigned int j = 0; j < width(); j++) {
            HSLAPixel & curr_px = getPixel(j, i);
            curr_px.s -= 0;
        }
    }
}
void Image::rotateColor(double degrees) {
     for (unsigned int i = 0; i < height(); i++){
         for (unsigned int j = 0; j < width(); j++){
            HSLAPixel & curr_px = getPixel(j, i);
            curr_px.h += degrees;
            if (curr_px.h > 360) {
                while (curr_px.h > 360) {
                    curr_px.h -= 360;
                }
            }
            if (curr_px.h < 0) {
                while (curr_px.h < 0) {
                    curr_px.h += 360;
                }
            }
        }
    }
}
void Image::illinify() {
     for (unsigned int i = 0; i < height(); i++){
         for (unsigned j = 0; j < width(); j++){
            HSLAPixel & curr_px = getPixel(j, i);
            if (curr_px.h <= 245 && curr_px.h >= 115) {
                    curr_px.h = 218;
                }
             else {
                curr_px.h = 12;
            }
        }
    }
}
void Image::scale(double factor) {

	if (factor != 1.0){
        unsigned scaled_h = factor * height();
        unsigned scaled_w = factor * width();
        Image copy_img = Image(*this);
        resize(scaled_w, scaled_h);
        
        for(unsigned w = 0; w < scaled_w; w++){
            for(unsigned h = 0; h < scaled_h; h++){
                HSLAPixel &curr_px = getPixel(w,h);
                HSLAPixel &copy_px = copy_img.getPixel(w/factor, h/factor);
                curr_px = copy_px;
            }
        }
    }
    else{
        return;
    }
}
void Image::scale(unsigned w, unsigned h) {

	double scaled_w =(1.0 * w) / width();
	double scaled_h = (1.0 * h) / height();

	double scale_factor = min(scaled_w, scaled_h);
    scale(scale_factor);
}
