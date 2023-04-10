#include "Image.h"
//constructors 
Image::Image(){

}
Image::Image(unsigned int width, unsigned int height){

}

//functions
void Image::lighten(){
    for(unsigned int r = 0; r < this->height(); r++){
        for(unsigned int c = 0; c < this->width(); c++){
            cs225::HSLAPixel & pix = this->getPixel(c,r);
            pix.l = pix.l + 0.1;
            if(pix.l > 1){
                pix.l = 1;
            }
        }
    }
}

void Image::lighten(double amount){
    for(unsigned int r = 0; r < this->height(); r++){
        for(unsigned int c = 0; c < this->width(); c++){
            cs225::HSLAPixel & pix = this->getPixel(c,r);
            pix.l = pix.l + amount;
            if(pix.l > 1){
                pix.l = 1;
            }
        }
    }
}

void Image::darken(){
    for(unsigned int r = 0; r < height(); r++){
        for(unsigned int c = 0; c < width(); c++){
            cs225::HSLAPixel & pix = this->getPixel(c,r);
            pix.l = pix.l - 0.1;
            if(pix.l < 0){
                pix.l = 0;
            }
        }
    }
}

void Image::darken(double amount){
    for(unsigned int r = 0; r < this->height(); r++){
        for(unsigned int c = 0; c < this->width(); c++){
           cs225::HSLAPixel & pix = this->getPixel(c,r);
            pix.l = pix.l - amount;
            if(pix.l < 0){
                pix.l = 0;
            } 
        }
    }
}

void Image::saturate(){
    for(unsigned int r = 0; r < this->height(); r++){
        for(unsigned int c = 0; c < this->width(); c++){
            cs225::HSLAPixel & pix = this->getPixel(c,r);
            pix.s = pix.s + 0.1;
            if(pix.s > 1){
                pix.s = 1;
            }
        }
    }
}

void Image::saturate(double amount){
    for(unsigned int r = 0; r < this->height(); r++){
        for(unsigned int c = 0; c < this->width(); c++){
            cs225::HSLAPixel & pix = this->getPixel(c,r);
            pix.s = pix.s + amount;
            if(pix.s > 1){
                pix.s = 1;
            }
        }
    }
}

void Image::desaturate(){
    for(unsigned int r = 0; r < this->height(); r++){
        for(unsigned int c = 0; c < this->width(); c++){
            cs225::HSLAPixel & pix = this->getPixel(c,r);
            pix.s = pix.s - 0.1;
            if(pix.s < 0){
                pix.s = 0;
            }
        }
    }
}

void Image::desaturate(double amount){
    for(unsigned int r = 0; r < this->height(); r++){
        for(unsigned int c = 0; c < this->width(); c++){
            cs225::HSLAPixel & pix = this->getPixel(c,r);
            pix.s = pix.s - amount;
            if(pix.s < 0){
                pix.s = 0;
            }
        }
    }
}

void Image::grayscale(){
    for(unsigned int r = 0; r < this->height(); r++){
        for(unsigned int c = 0; c < this->width(); c++){
            cs225::HSLAPixel & pix = this->getPixel(c,r);
            pix.s = 0;
        }
    }

}

void Image::rotateColor(double degrees){
    for(unsigned int r = 0; r < this->height(); r++){
        for(unsigned int c = 0; c < this->width(); c++){
            cs225::HSLAPixel & pix = this->getPixel(c,r);
            if (degrees < 0){
                pix.h = 360 + fmod((pix.h + degrees), 360);
            }
            else{
                pix.h = fmod((pix.h + degrees), 360);
            }
        }
    }
}

//“Illini Orange” has a hue of 11
//“Illini Blue” has a hue of 216
void Image::illinify(){
    for(unsigned int r = 0; r < this->height(); r++){
        for(unsigned int c = 0; c < this->width(); c++){
            cs225::HSLAPixel & pix = this->getPixel(c,r);
            if (pix.h > 102.5 && pix.h < 293.5){
                pix.h = 216;
            }
            else {
                pix.h = 11;
            }
        }
    }
}

void Image::scale(double factor){
    PNG * factimage = new PNG(this->width() * factor, this->height() * factor);
    for(unsigned int r = 0; r < this->height() * factor; r++){
        for(unsigned int c = 0; c < this->width() * factor; c++){
            factimage->getPixel(c,r) = this->getPixel(c/factor,r/factor);  
        }
    }
    
    this->resize(this->width() * factor, this->height() * factor);

    for(unsigned int r = 0; r < this->height(); r++){
        for(unsigned int c = 0; c < this->width(); c++){
            this->getPixel(c,r) = factimage->getPixel(c,r);
        }
    }
    delete factimage;
}

//we are going from 10,20 to 50,100 becasue 100,100
void Image::scale(unsigned w, unsigned h){
     double wratio = (double)w / this->width();
     double hratio = (double)h / this->height();
     double factor = 1;
     if(wratio < hratio){
        factor = wratio;
     }
     else{
        factor = hratio;
     }
     scale(factor);
    // for(unsigned int r = 0; r < h; r++){
    //     for(unsigned int c = 0; c < w; c++){
    //         factimage->getPixel(c,r) = this->getPixel(c/factor,r/factor); 
    //     }
    // }
    
    // this->resize(w, h);

    // for(unsigned int r = 0; r < this->height(); r++){
    //     for(unsigned int c = 0; c < this->width(); c++){
    //         this->getPixel(c,r) = factimage->getPixel(c,r);
    //     }
    // }
}