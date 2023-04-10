#include "Image.h"
using namespace cs225;

void Image::lighten(){
    for (unsigned int i=0; i<this->width();i++){
        for (unsigned int j=0;j<this->height();j++){
            HSLAPixel &p = this->getPixel(i,j);
            if(p.l>=0.9)
            p.l=1;
            else
            p.l=p.l+0.1;
        }

    }
}

void Image::lighten(double amount){
    for (unsigned int i=0; i<this->width();i++){
        for (unsigned int j=0;j<this->height();j++){
            HSLAPixel &p = this->getPixel(i,j);
            if(p.l + amount >=1)
            p.l=1;
            else
            p.l=p.l+amount;
        }

    }
}

void Image::darken(){
    for (unsigned int i=0; i<this->width();i++){
        for (unsigned int j=0;j<this->height();j++){
            HSLAPixel &p = this->getPixel(i,j);
            if(p.l <=0.1)
            p.l=0;
            else
            p.l=p.l-0.1;
        }

    }
}
void Image::darken(double amount){
    for (unsigned int i=0; i<this->width();i++){
        for (unsigned int j=0;j<this->height();j++){
            HSLAPixel &p = this->getPixel(i,j);
            if(p.l <=amount)
            p.l=0;
            else
            p.l=p.l-amount;
        }

    }
}

void Image::saturate(){
    for (unsigned int i=0; i<this->width();i++){
        for (unsigned int j=0;j<this->height();j++){
            HSLAPixel &p = this->getPixel(i,j);
            if(p.s >=0.9)
            p.s=0;
            else
            p.s=p.s+0.1;
        }

    }
}
void Image::saturate(double amount){
    for (unsigned int i=0; i<this->width();i++){
        for (unsigned int j=0;j<this->height();j++){
            HSLAPixel &p = this->getPixel(i,j);
            if(p.s+amount >=1)
            p.s=1;
            else
            p.s=p.s+amount;
        }

    }
}

void Image::desaturate(){
    for (unsigned int i=0; i<this->width();i++){
        for (unsigned int j=0;j<this->height();j++){
            HSLAPixel &p = this->getPixel(i,j);
            if(p.s <=0.1)
            p.s=0;
            else
            p.s=p.s-0.1;
        }

    }
}

void Image::desaturate(double amount){
    for (unsigned int i=0; i<this->width();i++){
        for (unsigned int j=0;j<this->height();j++){
            HSLAPixel &p = this->getPixel(i,j);
            if(p.s <=amount)
            p.s=0;
            else
            p.s=p.s-amount;
        }

    }
}

void Image::grayscale(){
    for (unsigned int i=0; i<this->width();i++){
        for (unsigned int j=0;j<this->height();j++){
            HSLAPixel &p = this->getPixel(i,j);
            p.s=0;
        }
    }
}

void Image::rotateColor(double degrees){
    for (unsigned int i=0; i<this->width();i++){
        for (unsigned int j=0;j<this->height();j++){
            HSLAPixel &p = this->getPixel(i,j);
           double temp=p.h;
           temp=temp+degrees;
            if (temp <0)
                temp=temp+360;
           if (temp>360)
                temp=temp-360;
            p.h=temp;
        }

    }
}

void Image::illinify(){
    for (unsigned int i=0; i<this->width();i++){
        for (unsigned int j=0;j<this->height();j++){
            HSLAPixel &p = this->getPixel(i,j);
            if(p.h>(113.5)&&(p.h<293.5))
            p.h=216;
            else
            p.h=11;
        }
    }
}

void Image::scale(double factor){
unsigned x=(this->width()*factor);
unsigned y=(this->height()*factor);
PNG* temp= new PNG(*this);
temp->resize(x,y);
for (unsigned int i=0;i<x;i++){
    for (unsigned int j=0; j<y;j++){
        HSLAPixel &temp_pix= this->getPixel((i/factor),(j/factor));
        HSLAPixel &temp_pix_=temp->getPixel(i,j);
        temp_pix_=temp_pix;
        /*HSLAPixel &p=temp->getPixel(i,j);
        unsigned int i_=(unsigned int)(this->width()*i/x +0.5);
        unsigned int j_=(unsigned int)(this->width()*j/y +0.5);
        p=this->getPixel(i_,j_);*/
    }
}
this->resize(x,y);
for (unsigned int i=0;i<x;i++){
    for (unsigned int j=0; j<y;j++){
    this->getPixel(i,j)=temp->getPixel(i,j);
    }
}
delete temp;
}

void Image::scale(unsigned w,unsigned h){
double w_=double(this->width());
double h_=double(this->height());
double factor_w=(w/w_);
double factor_h=(h/h_);
if (factor_h>factor_w)
scale(factor_w);
scale(factor_h);
}

Image::Image()
{
    PNG();
};
Image::Image(unsigned int width, unsigned int height) : PNG(width, height){};