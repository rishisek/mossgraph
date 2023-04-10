#include "/workspaces/cs225/cs225git/mp_stickers/src/Image.h"
#include <math.h>
#include "/workspaces/cs225/cs225git/mp_stickers/lib/cs225/HSLAPixel.h"

Image::Image(){
    PNG();
}

Image::Image(unsigned int width, unsigned int height){
    PNG(width, height);
}

void Image::lighten(){
    for (unsigned int i=0;i<width();i++){
        for (unsigned int j=0; j<height();j++){
            cs225::HSLAPixel *pix = &getPixel(i,j);
            pix->l += 0.1;
            if (pix->l >= 1){pix->l = 1;}i;
        }
    }
}

void Image::lighten(double amount){
    for (unsigned int i=0;i<width();i++){
        for (unsigned int j=0; j<height();j++){
            cs225::HSLAPixel *pix = &getPixel(i,j);
            pix->l += amount;
            if (pix->l >= 1){pix->l = 1;};
        }
    }
}

void Image::darken(){
    for (unsigned int i=0;i<width();i++){
        for (unsigned int j=0; j<height();j++){
            cs225::HSLAPixel *pix = &getPixel(i,j);
            pix->l -= 0.1;
            if (pix->l <= 1){pix->l = 0;};
        }
    }
}

void Image::darken(double amount){
    for (unsigned int i=0;i<width();i++){
        for (unsigned int j=0; j<height();j++){
            cs225::HSLAPixel *pix = &getPixel(i,j);
            pix->l -= amount;
            if (pix->l <= 1){pix->l = 0;};
        }
    }
}

void Image::saturate(){
    for (unsigned int i=0;i<width();i++){
        for (unsigned int j=0; j<height();j++){
            cs225::HSLAPixel *pix = &getPixel(i,j);
            pix->s += 0.1;
            if (pix->s >= 1){pix->s = 1;};
        }
    }
}

void Image::saturate(double amount){
    for (unsigned int i=0;i<width();i++){
        for (unsigned int j=0; j<height();j++){
            cs225::HSLAPixel *pix = &getPixel(i,j);
            pix->s += amount;
            if (pix->s >= 1){pix->s = 1;};
        }
    }
}

void Image::desaturate(){
    for (unsigned int i=0;i<width();i++){
        for (unsigned int j=0; j<height();j++){
            cs225::HSLAPixel *pix = &getPixel(i,j);
            pix->s -= 0.1;
            if (pix->s <= 1){pix->s = 0;};
        }
    }
}

void Image::desaturate(double amount){
    for (unsigned int i=0;i<width();i++){
        for (unsigned int j=0; j<height();j++){
            cs225::HSLAPixel *pix = &getPixel(i,j);
            pix->s -= amount;
            if (pix->s <= 1){pix->s = 0;};
        }
    }
}

void Image::greyscale(){
    for (unsigned int i=0;i<width();i++){
        for (unsigned int j=0; j<height();j++){
            cs225::HSLAPixel *pix = &getPixel(i,j);
            pix->s = 0;
        }
    }
}

void Image::rotateColor(double degrees){
    for (unsigned int i=0;i<width();i++){
        for (unsigned int j=0; j<height();j++){
            cs225::HSLAPixel *pix = &getPixel(i,j);
            int x = pix->h;
            x = x + degrees;
            x = x % 360;
            if (x<0){x+=360;}
            pix->h = x;
        }
    }
}

void Image::illinify(){
    double left1 = 293;
    double right1 = 113;
    for (unsigned int y = 0; y < height() ;y++){
        for (unsigned int x = 0; x < width(); x++){
            cs225::HSLAPixel *pix = &getPixel(x,y);
            if (pix -> h<=left1 && pix->h >= right1){ pix->h = 216;}
            else {pix -> h = 11;};
        }
    }

}

void Image::scale(double factor){
    PNG * unchanged = new PNG(*this);
    this->resize(ceil(factor*width()),ceil(factor*height()));
    
    if (factor < 1 & factor > 0)
    {
        for (unsigned int y = 0; y < height() ;y++){
            for (unsigned int x = 0; x < width(); x++){
                cs225::HSLAPixel *newpixel = &(this->getPixel(x,y));
                cs225::HSLAPixel *oldpixel = &(unchanged->getPixel(ceil(x/factor),ceil(y/factor)));
                newpixel -> h = oldpixel -> h;
                newpixel -> l = oldpixel -> l;
                newpixel -> s = oldpixel -> s;
                newpixel -> a = oldpixel -> a;
            }
        }
    }
    else if (factor >= 1)
    {
        for (unsigned y = 0; y < height()/factor ;y++)
        {
            for (unsigned  x = 0; x < width()/factor; x++)
            {
                cs225::HSLAPixel *oldpixel = &(unchanged->getPixel(x,y));
                for (unsigned i = 0; i < ceil(factor); i++)
                    {
                    for (unsigned j = 0; j < ceil(factor); j++)
                        {
                            cs225::HSLAPixel *newpixel = &(this->getPixel((x*factor) +i,(y*factor)+j));                
                            newpixel -> h = oldpixel -> h;
                            newpixel -> l = oldpixel -> l;
                            newpixel -> s = oldpixel -> s;
                            newpixel -> a = oldpixel -> a;
                        }
                    }
            }
        }
    }
    delete unchanged;
    unchanged = NULL;
}

void Image::scale(unsigned w, unsigned h){
    PNG::resize(w,h);
}

