#include "Image.h"

Image::Image() {
}

Image::Image(unsigned int w, unsigned int h) {
    resize(w,h);
}

void Image::lighten() {
    for(unsigned int i=0; i<width(); i++) {
       for(unsigned int j=0; j<height(); j++) {
            if(getPixel(i,j).l + 0.1 <= 1.0 )
            {
                getPixel(i,j).l += 0.1;
            }
            else
            {
                getPixel(i,j).l = 1.0;
            }
       }
    }
}

void Image::lighten(double value) {
    for(unsigned int i=0; i<width(); i++) {
       for(unsigned int j=0; j<height(); j++) {
            if(getPixel(i,j).l + value <= 1.0 )
            {
                getPixel(i,j).l += value;
            }
            else
            {
                getPixel(i,j).l = 1.0;
            }
       }
    }
}

void Image::darken() {
    for(unsigned int i=0; i<width(); i++) {
       for(unsigned int j=0; j<height(); j++) {
            if(getPixel(i,j).l - 0.1 >= 0.0 ) {
                getPixel(i,j).l -= 0.1;
            }
            else {
                getPixel(i,j).l = 0.0;
            }
       }
    }
}

void Image::darken(double value) {
    for(unsigned int i=0; i<width(); i++) {
       for(unsigned int j=0; j<height(); j++) {
            if(getPixel(i,j).l - value >= 0.0 ){
                getPixel(i,j).l -= value;
            }
            else {
                getPixel(i,j).l = 0.0;
            }
       }
    }
}

void Image::saturate() {
    for(unsigned int i=0; i<width(); i++) {
       for(unsigned int j=0; j<height(); j++) {
            if(getPixel(i,j).s + 0.1 < 1.0)
            {
                getPixel(i,j).s += 0.1;
            }
       }
    }
}

void Image::saturate(double value) {
    for(unsigned int i=0; i<width(); i++) {
       for(unsigned int j=0; j<height(); j++) {
            if(getPixel(i,j).s + value < 1.0)
            {
                getPixel(i,j).s += value;
            }
       }
    }
}

void Image::desaturate() {
    for(unsigned int i=0; i<width(); i++) {
       for(unsigned int j=0; j<height(); j++) {
            if(getPixel(i,j).s - 0.1 > 0.0)
            {
                getPixel(i,j).s -= 0.1;
            }
       }
    }
}

void Image::desaturate(double value) {
    for(unsigned int i=0; i<width(); i++) {
       for(unsigned int j=0; j<height(); j++) {
            if(getPixel(i,j).s - value > 0.0)
            {
                getPixel(i,j).s -= value;
            }
       }
    }
}

void Image::grayscale() {
    for(unsigned int i=0; i<width(); i++) {
       for(unsigned int j=0; j<height(); j++) {
            getPixel(i,j).s = 0;
       }
    }
}

void Image::illinify() {
    for(unsigned int i=0; i<width(); i++) {
       for(unsigned int j=0; j<height(); j++) {
            if((getPixel(i,j).h > 113.5 && getPixel(i,j).h < 293.5)) {
                getPixel(i,j).h = 216;
            }
            else{
                getPixel(i,j).h = 11;
            }
       }
    }
}

void Image::rotateColor(double n) {
    for(unsigned int i=0; i<width(); i++) {
       for(unsigned int j=0; j<height(); j++) {
            if((getPixel(i,j).h + n)>360)
            {
                getPixel(i,j).h = (getPixel(i,j).h + n)-360;
            }
            else if((getPixel(i,j).h + n)<0)
            {
                getPixel(i,j).h = (getPixel(i,j).h + n)+360;
            }
            else 
            {
                getPixel(i,j).h += n;
            }
       }
    }
}

void Image::scale(double value) {
    Image tmp;
    tmp.resize(width()*value, height()*value);
    for(unsigned int i=0; i<tmp.width(); i++)
    {
        for(unsigned int j=0; j<tmp.height(); j++)
        {
            tmp.getPixel(i,j) = getPixel(i*width()/tmp.width(),j*height()/tmp.height());
        }
    }
    resize(width()*value, height()*value);
    for(unsigned int i=0; i<width(); i++)
    {
        for(unsigned int j=0; j<height(); j++)
        {
            getPixel(i,j) = tmp.getPixel(i,j);
        }
    }
}

void Image::scale(unsigned w, unsigned h) {
    Image tmp;
    double wid = (double)(w)/width();
    double hei = (double)(h)/height();
    //cout << width() << " " << height() << endl;
    bool worh;
    if(wid <= hei) {
        tmp.resize(w, height()*wid);
        worh = true;
    }
    else {
        tmp.resize(width()*hei, h);
        worh = false;
    }
    //cout << tmp.width() << " " << tmp.height() << endl;
    for(unsigned int i=0; i<tmp.width(); i++)
    {
        for(unsigned int j=0; j<tmp.height(); j++)
        {
            tmp.getPixel(i,j) = getPixel(i*width()/tmp.width(),j*height()/tmp.height());
        }
    }
    if(worh==true) {
        resize(w, height()*wid);
    }
    else {
        resize(width()*hei, h);
    }
    for(unsigned int i=0; i<width(); i++)
    {
        for(unsigned int j=0; j<height(); j++)
        {
            getPixel(i,j) = tmp.getPixel(i,j);
        }
    }
}
