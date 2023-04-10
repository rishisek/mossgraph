#include "Image.h"

#include <cmath>


Image::Image()
{}

Image::Image(unsigned int width, unsigned int height) : PNG(width, height){
}

void Image::lighten(){
    for (unsigned int i = 0; i<this->width(); i++){
        for (unsigned int j = 0; j<this->height(); j++){
            HSLAPixel & p = getPixel(i,j); 
             
            if (p.l<0.9)
                p.l +=0.1;
            else{
                p.l = 1; 
            }
            
        }
    }
    
}

void Image::lighten(double amount){
    for (unsigned int i = 0; i<this->width(); i++){
        for (unsigned int j = 0; j<this->height(); j++){
            HSLAPixel & p = getPixel(i,j); 
            if (p.l+amount<1)
                p.l +=amount;
            else{
                p.l = 1; 
            }
            
        }
    }
    
}

void Image::darken(){
    for (unsigned int i = 0; i<this->width(); i++){
        for (unsigned int j = 0; j<this->height(); j++){
            HSLAPixel & p = getPixel(i,j); 
            if (p.l-0.1>0)
                p.l -=0.1;
            else{
                p.l = 0; 
            }
            
        }
    }
    return; 
} 
void Image::darken(double amount){
    for (unsigned int i = 0; i<this->width(); i++){
        for (unsigned int j = 0; j<this->height(); j++){
            HSLAPixel & p = getPixel(i,j); 
            if (p.l-amount>0)
                p.l -=amount;
            else{
                p.l = 0; 
            }
            
        }
    }
    return; 
}

void Image::saturate(){
    for (unsigned int i = 0; i<this->width(); i++){
        for (unsigned int j = 0; j<this->height(); j++){
            HSLAPixel & p = getPixel(i,j); 
            if (p.s+0.1<1)
                p.s +=0.1;
            else{
                p.s = 1; 
            }
            
        }
    }
    return; 
}
void Image::saturate(double amount){
    for (unsigned int i = 0; i<this->width(); i++){
        for (unsigned int j = 0; j<this->height(); j++){
            HSLAPixel & p = getPixel(i,j); 
            if (p.s+amount<1)
                p.s +=amount;
            else{
                p.s = 1; 
            }
            
        }
    }
    return; 
} 
void Image::desaturate(){
    for (unsigned int i = 0; i<this->width(); i++){
        for (unsigned int j = 0; j<this->height(); j++){
            HSLAPixel & p = getPixel(i,j); 
            if (p.s-0.1>0)
                p.s -=0.1;
            else{
                p.l = 0; 
            }
            
        }
    }
    return; 
}
void Image::desaturate(double amount){
    for (unsigned int i = 0; i<this->width(); i++){
        for (unsigned int j = 0; j<this->height(); j++){
            HSLAPixel & p = getPixel(i,j); 
            if (p.s-amount>0)
                p.l -=amount;
            else{
                p.l = 0; 
            }
            
        }
    }
    return; 
}
void Image::grayscale(){
    for (unsigned int i = 0; i< this->width(); i++){
        for (unsigned int j = 0; j< this->height(); j++ ){
            HSLAPixel & p = getPixel(i,j); 
            p.s = 0; 
        }
    } 
}
void Image::rotateColor(double degrees){
    for (unsigned int i = 0; i<this->width(); i++){
        for (unsigned int j = 0; j< this->height(); j++){
            HSLAPixel & p = getPixel(i,j); 
            p.h+=degrees; 
            if (p.h>360)
                p.h-=360; 
            if (p.h<0)
                p.h += 360; 
        }
    }
}
void Image::illinify(){
    for (unsigned int i = 0; i<this->width(); i++){
        for (unsigned int j = 0; j<this->height(); j++){
            HSLAPixel & p = getPixel(i,j); 
            double diff_blue = fabs(p.h-216);
            double diff_orange; 
            if (fabs(p.h-11)<fabs(p.h-371))
               diff_orange = fabs(p.h -11); 
            else{
                diff_orange = fabs(p.h -371);
            }
            if(diff_orange<diff_blue){
                p.h = 11; 
            }
            else{
                p.h = 216;
            }
        }
    }
} 
void Image::scale(double factor){
    if(factor  == 0)
        return; 
    PNG copy = *this; //we do not touch copy, edit "this"
   int oldheight = this->height(); 
   int oldwidth = this->width(); 
    this->resize(oldwidth * factor, oldheight* factor); 
    for (unsigned int i = 0; i<this->width(); i++){
        for (unsigned int j = 0; j<this->height(); j++){
            this->getPixel(i,j) = copy.getPixel(i/factor, j/factor); 
        }
    }
     
}
void Image::scale(unsigned w, unsigned h){
   double width_factor = w/this->width(); 
   double height_factor = h/this->height(); 
   if (width_factor<height_factor)
        scale(width_factor); 
    else{
        scale(height_factor); 
    }
   
}



