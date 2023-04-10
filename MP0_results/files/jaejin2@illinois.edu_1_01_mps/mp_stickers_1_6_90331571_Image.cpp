# include "Image.h"

Image::Image(){
    PNG();
}

Image::Image(unsigned int width, unsigned int height){
    PNG(width, height); 
}


void Image::darken(){
    for(unsigned int h = 0; h >= 0 && h < Image::height(); h++){
        for(unsigned int w = 0; w >=0 && w < Image::width(); w++){
            HSLAPixel& pixel = getPixel(w, h);
            if(pixel.l>=0.1){
                pixel.l -= 0.1;
            }
            else if(pixel.l-0.1 < 0){
                pixel.l = 0;
            }
        }
    }
}
void Image::darken(double amount){
    for(unsigned int h = 0; h >= 0 && h < Image::height(); h++){
        for(unsigned int w = 0; w >=0 && w < Image::width(); w++){
            HSLAPixel& pixel = getPixel(w, h);
            if(pixel.l>=amount){
                pixel.l -= amount;
            }
            else if(pixel.l-amount < 0){
                pixel.l = 0;
            }
        }
    }
}
void Image::desaturate(){
    for(unsigned int h = 0; h >= 0 && h < Image::height(); h++){
        for(unsigned int w = 0; w >=0 && w < Image::width(); w++){
            HSLAPixel& pixel = getPixel(w, h);
            if(pixel.s>=0.1){
                pixel.s -= 0.1;
            }
            else if(pixel.s-0.1 < 0){
                pixel.s = 0;
            }
        }
    }
}
void Image::desaturate(double amount){
    for(unsigned int h = 0; h >= 0 && h < Image::height(); h++){
        for(unsigned int w = 0; w >=0 && w < Image::width(); w++){
            HSLAPixel& pixel = getPixel(w, h);
            if(pixel.s>=amount){
                pixel.s -= amount;
            }
            else if(pixel.s-amount < 0){
                pixel.s = 0;
            }
        }
    }
}
void Image::grayscale(){
    for(unsigned int h = 0; h >= 0 && h < Image::height(); h++){
        for(unsigned int w = 0; w >=0 && w < Image::width(); w++){
            HSLAPixel& pixel = getPixel(w, h);
            pixel.s = 0.0;
        }
    }
}
void Image::illinify(){
    for(unsigned int h = 0; h >= 0 && h < Image::height(); h++){
        for(unsigned int w = 0; w >=0 && w < Image::width(); w++){
            HSLAPixel& pixel = getPixel(w, h);
            if(113.5<pixel.h<293.5){
                pixel.h = 216.0;
            }
            else{
                pixel.h = 11.0;
            }
        }
    }
}
void Image::lighten(){
    for(unsigned int h = 0; h >= 0 && h < Image::height(); h++){
        for(unsigned int w = 0; w >=0 && w < Image::width(); w++){
            HSLAPixel& pixel = getPixel(w, h);
            if(pixel.l <= 0.9){
                pixel.l += 0.1;
            }
            else if(pixel.l + 0.1 > 1){
                pixel.l = 1;
            }
        }
    }
}

void Image::lighten(double amount){
    for(unsigned int h = 0; h >= 0 && h < Image::height(); h++){
        for(unsigned int w = 0; w >=0 && w < Image::width(); w++){
            HSLAPixel& pixel = getPixel(w, h);
            if(pixel.l <= 1-amount){
                pixel.l += amount;
            }
            else if(pixel.l+amount > 1){
                pixel.l = 1;
            }
        }
    }
}
void Image::rotateColor(double degrees){
    for(unsigned int h = 0; h>=0 && h< Image::height(); h++){
        for(unsigned int w=0; w>=0 && w< Image::width(); w++){
            HSLAPixel& pixel = getPixel(w,h);
            pixel.h += degrees;
            while(pixel.h>360){
                pixel.h -= 360;
            }
            while(pixel.h<0){
                pixel.h += 360;
            }
        }
    }
}
void Image::saturate(){
    for(unsigned int h=0; h>=0 && h< Image::height(); h++){
        for(unsigned int w=0; w>=0 && w< Image::width(); w++){
            HSLAPixel& pixel = getPixel(w,h);
            if(pixel.s<=0.9){
                pixel.s += 0.1;
            }
            else if(pixel.s+0.1>1){
                pixel.s = 1;
            }
        }
    }
}
void Image::saturate(double amount){
    for(unsigned int h=0; h>=0 && h< Image::height(); h++){
        for(unsigned int w=0; w>=0 && w< Image::width(); w++){
            HSLAPixel& pixel = getPixel(w,h);
            if(pixel.s <= 1-amount){
                pixel.s += amount;
            }
            else if(pixel.s-amount>1){
                pixel.s = 1;
            }
        }
    }
}
void Image::scale(double factor){
    unsigned int h = this->height()*factor;
    unsigned int w = this->width()*factor;
    Image *original = new Image(*this);
    resize(w,h);
    for(unsigned int i=0; i<w; i++){
        for(unsigned int j=0; j<h; j++){
            getPixel(i,j) = original->getPixel(i/factor, j/factor);
        }
    }
    delete original;
}
void Image::scale(unsigned w, unsigned h){
    double wid = (double)w;
    double hei = (double)h;
    double factorw = wid/width();
    double factorh = hei/height();
    double f = 0;
    if(factorw > factorh){
        f = factorh;
    }
    else{
        f = factorw;
    }
    unsigned int h_ = this->height()*f;
    unsigned int w_ = this->width()*f;
    Image *og = new Image(*this);
    resize(w_,h_);
    for(unsigned int i=0; i<w_; i++){
        for(unsigned int j=0; j<h_; j++){
            getPixel(i,j) = og->getPixel(i/f, j/f);
        }
    }
    delete og;
}