
#include "Image.h"

#include <math.h>

Image::Image()
{
    PNG();
}
Image::Image(unsigned int width, unsigned int height)
{
    PNG(width, height);
}

void Image::lighten()
{
    for (unsigned int y = 0; y < height() ;y++){
        for (unsigned int x = 0; x < width(); x++){
            HSLAPixel *pix = &getPixel(x,y);
            pix -> l = pix -> l + 0.1;
            if (pix -> l >= 1){pix -> l = 1;};
        }
    }
}
void Image::lighten(double amount)
{
    for (unsigned int y = 0; y < height() ;y++){
        for (unsigned int x = 0; x < width(); x++){
            HSLAPixel *pix = &getPixel(x,y);
            pix -> l = pix -> l + amount;
            if (pix -> l >= 1){pix -> l = 1;};
        }
    }
}
void Image::darken()
{
    for (unsigned int y = 0; y < height() ;y++){
        for (unsigned int x = 0; x < width(); x++){
            HSLAPixel *pix = &getPixel(x,y);
            pix -> l = pix -> l - 0.1;
            if (pix -> l <= 0){pix -> l = 0;};        
            }
    }
}
void Image::darken(double amount)
{
    for (unsigned int y = 0; y < height() ;y++){
        for (unsigned int x = 0; x < width(); x++){
            HSLAPixel *pix = &getPixel(x,y);
            pix -> l = pix -> l - amount;
            if (pix -> l <= 0){pix -> l = 0;};
        }
    }
}
void Image::saturate()
{
    for (unsigned int y = 0; y < height() ;y++){
        for (unsigned int x = 0; x < width(); x++){
            HSLAPixel *pix = &getPixel(x,y);
            pix -> s = pix -> s + 0.1;
            if (pix -> s >= 1){pix -> s = 1;};        
            }
    }
}
void Image::saturate(double amount)
{
    for (unsigned int y = 0; y < height() ;y++){
        for (unsigned int x = 0; x < width(); x++){
            HSLAPixel *pix = &getPixel(x,y);
            pix -> s = pix -> s + amount;
            if (pix -> s >= 1){pix -> s = 1;};
        }
    }
}

void Image::desaturate()
{
    for (unsigned int y = 0; y < height() ;y++){
        for (unsigned int x = 0; x < width(); x++){
            HSLAPixel *pix = &getPixel(x,y);
            pix -> s = pix -> s - 0.1;
            if (pix -> s <= 0){pix -> l = 0;};
        }
    }
}
void Image::desaturate(double amount)
{
    for (unsigned int y = 0; y < height() ;y++){
        for (unsigned int x = 0; x < width(); x++){
            HSLAPixel *pix = &getPixel(x,y);
            pix -> s = pix -> s - amount;
            if (pix -> s <= 0){pix -> s = 0;};
        }
    }
}

void Image::grayscale()
{
    for (unsigned int y = 0; y < height() ;y++){
        for (unsigned int x = 0; x < width(); x++){
            HSLAPixel *pix = &getPixel(x,y);
            pix -> s =  0;
        }
    }
}

void Image::rotateColor( double degrees)
{
    for (unsigned int y = 0; y < height() ;y++){
        for (unsigned int x = 0; x < width(); x++){
            HSLAPixel *pix = &getPixel(x,y);
            int he = pix -> h ;
            he+= degrees;
            he %= 360;
            if (he<0){he+=360;}
            pix -> h = he;

        }
    }
}
void Image::illinify()
{
    double leftpoint = 293;
    double rightpoint = leftpoint-180;
    for (unsigned int y = 0; y < height() ;y++){
        for (unsigned int x = 0; x < width(); x++){
            HSLAPixel *pix = &getPixel(x,y);
            if (pix -> h<=leftpoint && pix->h >= rightpoint){ pix->h = 216;}
            else {pix -> h = 11;};
        }
    }
}
void Image::scale(double factor)
{
    //PNG::resize(factor*width(),factor*height());

    PNG * unchanged = new PNG(*this);
    this->resize(ceil(factor*width()),ceil(factor*height()));
    
    if (factor < 1 & factor > 0)
    {
        for (unsigned int y = 0; y < height() ;y++){
            for (unsigned int x = 0; x < width(); x++){
                HSLAPixel *newpixel = &(this->getPixel(x,y));
                HSLAPixel *oldpixel = &(unchanged->getPixel(ceil(x/factor),ceil(y/factor)));
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
                HSLAPixel *oldpixel = &(unchanged->getPixel(x,y));
                for (unsigned i = 0; i < ceil(factor); i++)
                    {
                    for (unsigned j = 0; j < ceil(factor); j++)
                        {
                            HSLAPixel *newpixel = &(this->getPixel((x*factor) +i,(y*factor)+j));                
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
    double wF = ((double)(w*1.0)) / ((double)width()*1.0);
    double hF = ((double)(h*1.0)) / ((double)height()*1.0);
    //cout<<wF<<hF<<endl;
    if (wF < hF)
      scale(wF);
    else scale(hF);


}