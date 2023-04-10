#include "Image.h"

Image::Image(){
    PNG();
}

Image::Image(unsigned int width, unsigned int height){
    PNG(width, height);
}

void Image::darken(){

    for (unsigned i = 0; i < width(); i++){
        for (unsigned j = 0; j < height(); j++){
            if (getPixel(i,j).l - 0.1 >= 0)
                getPixel(i,j).l -= 0.1;
            else{
                getPixel(i,j).l = 0;
            }
        }
    }
}

void Image::darken(double amount){
    for (unsigned i = 0; i < width(); i++){
        for (unsigned j = 0; j < height(); j++){
            if (getPixel(i,j).l - amount >= 0)
                getPixel(i,j).l -= amount;
            else{
                getPixel(i,j).l = 0;
            }
        }
    }
}

void Image::desaturate(){
     for (unsigned i = 0; i < width(); i++){
        for (unsigned j = 0; j < height(); j++){
            if (getPixel(i,j).s - 0.1 >= 0)
                getPixel(i,j).s -= 0.1;
            else{
                getPixel(i,j).s = 0;
            }
        }
    }
}

void Image::desaturate(double amount){
    for (unsigned i = 0; i < width(); i++){
        for (unsigned j = 0; j < height(); j++){
            if (getPixel(i,j).s - amount >= 0)
                getPixel(i,j).s -= amount;
            else{
                getPixel(i,j).s = 0;
            }
        }
    }
}

void Image::grayscale(){
    for (unsigned i = 0; i < width(); i++){
        for (unsigned j = 0; j < height(); j++){
            getPixel(i,j).s = 0;
        }
    }
}

void Image::illinify(){
    for (unsigned i = 0; i < width(); i++){
        for (unsigned j = 0; j < height(); j++){
            getPixel(i,j).h = 11;
        }
    }
}
void Image::lighten(){
   for (unsigned i = 0; i < width(); i++){
        for (unsigned j = 0; j < height(); j++){
            if (getPixel(i,j).l + 0.1 <= 1){
                getPixel(i,j).l += 0.1;
            }

            else{
                getPixel(i,j).l = 1;
            }
        }
    }
}

void Image::lighten(double amount){
   for (unsigned i = 0; i < width(); i++){
        for (unsigned j = 0; j < height(); j++){
            if (getPixel(i,j).l + amount <= 1){
                getPixel(i,j).l += amount;
            }

            else{
                getPixel(i,j).l = 1;
            }
        }
    }
}

void Image::rotateColor(double degrees){
   for (unsigned i = 0; i < width(); i++){
        for (unsigned j = 0; j < height(); j++){
            if(degrees < 0) degrees += 360;
            if (getPixel(i,j).h + degrees <= 360){
                getPixel(i,j).h += degrees;
            }

            else{
                getPixel(i,j).h += degrees;
                
                while (0.0 > getPixel(i,j).h || getPixel(i,j).h >= 360.0){
                    if (getPixel(i,j).h < 0){
                        getPixel(i,j).h += 360;
                    }
                    else getPixel(i,j).h -= 360;
                }
            }
        }
    }
}

void Image::saturate(){
     for (unsigned i = 0; i < width(); i++){
        for (unsigned j = 0; j < height(); j++){
            if (getPixel(i,j).s + 0.1 <= 1)
                getPixel(i,j).s += 0.1;
            else{
                getPixel(i,j).s = 1;
            }
        }
    }
}

void Image::saturate(double amount){
     for (unsigned i = 0; i < width(); i++){
        for (unsigned j = 0; j < height(); j++){
            if (getPixel(i,j).s + amount <= 1)
                getPixel(i,j).s += amount;
            else{
                getPixel(i,j).s = 1;
            }
        }
    }
}

void Image::scale(double factor){
    Image* temp = new Image(*this);
    
    resize(width()*factor, height()*factor);
    
    for (unsigned i = 0; i < temp->width(); i++){
        unsigned a,b;
        for (unsigned j = 0; j < temp->height(); j++){
            if (j==0) b = 0;
            else b = (j-1) * factor;

            while (b <= j*factor){
                if (i==0) a = 0;
                else a = (i-1)*factor;
                
                while (a <= i*factor){
                    getPixel(a,b) = temp->getPixel(i,j);
                    a++;
                }
                b++;
            }
        }
    }

    delete temp;
}

void Image::scale(unsigned w, unsigned h){
    Image* temp = new Image(*this);
    double factor_w = w / width();
    double factor_h = h / height();

    resize(w, h);

    
    for (unsigned i = 0; i < temp->width(); i++){
        unsigned a,b;
        for (unsigned j = 0; j < temp->height(); j++){
            if (j==0) b = 0;
            else b = (j-1) * factor_h;

            while (b <= j*factor_h){
                if (i==0) a = 0;
                else a = (i-1)*factor_w;
                
                while (a <= i*factor_w){
                    getPixel(a,b) = temp->getPixel(i,j);
                    a++;
                }
                b++;
            }
        }
    }

    delete temp;
}