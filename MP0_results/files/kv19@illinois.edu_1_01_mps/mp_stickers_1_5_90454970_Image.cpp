#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

//Constructors
Image::Image()
{
    PNG();
}
Image::Image(unsigned int width, unsigned int height)
{
    PNG(width, height);
}
//Methods
void Image::lighten()
{
    for(unsigned int i = 0; i<(width()); i++)
    {
        for(unsigned int j = 0; j<(height()); j++)
        {
            cs225::HSLAPixel &pixel = getPixel(i, j);
            if((pixel.l+.1)>1)
            {
                pixel.l = 1;
            }
            else
            {
                pixel.l+=.1;
            }
        }
    }
}

void Image::lighten(double amount)
{
    for(unsigned int i = 0; i<(width()); i++)
    {
        for(unsigned int j = 0; j<(height()); j++)
        {
            cs225::HSLAPixel &pixel = getPixel(i, j);
            if((pixel.l+amount)>1)
            {
                pixel.l = 1;
            }
            else
            {
                pixel.l+=amount;
            }
        }
    }
}

void Image::darken()
{
    for(unsigned int i = 0; i<(width()); i++)
    {
        for(unsigned int j = 0; j<(height()); j++)
        {
            cs225::HSLAPixel &pixel = getPixel(i, j);
            if((pixel.l-.1)<0)
            {
                pixel.l = 0;
            }
            else
            {
                pixel.l-=.1;
            }
        }
    }
}

void Image::darken(double amount)
{
    for(unsigned int i = 0; i<(width()); i++)
    {
        for(unsigned int j = 0; j<(height()); j++)
        {
            cs225::HSLAPixel &pixel = getPixel(i, j);
            if((pixel.l-amount)<0)
            {
                pixel.l = 0;
            }
            else
            {
                pixel.l-=amount;
            }
        }
    }
}

void Image::saturate()
{
    for(unsigned int i = 0; i<(width()); i++)
    {
        for(unsigned int j = 0; j<(height()); j++)
        {
            cs225::HSLAPixel &pixel = getPixel(i, j);
            if((pixel.s+.1)>1)
            {
                pixel.s = 1;
            }
            else
            {
                pixel.s+=.1;
            }
        }
    }
}

void Image::saturate(double amount)
{
    for(unsigned int i = 0; i<(width()); i++)
    {
        for(unsigned int j = 0; j<(height()); j++)
        {
            cs225::HSLAPixel &pixel = getPixel(i, j);
            if((pixel.s+amount)>1)
            {
                pixel.s = 1;
            }
            else
            {
                pixel.s+=amount;
            }
        }
    }
}

void Image::desaturate()
{
    for(unsigned int i = 0; i<(width()); i++)
    {
        for(unsigned int j = 0; j<(height()); j++)
        {
            cs225::HSLAPixel &pixel = getPixel(i, j);
            if((pixel.s-.1)<0)
            {
                pixel.s = 0;
            }
            else
            {
                pixel.s-=.1;
            }
        }
    }
}

void Image::desaturate(double amount)
{
    for(unsigned int i = 0; i<(width()); i++)
    {
        for(unsigned int j = 0; j<(height()); j++)
        {
            cs225::HSLAPixel &pixel = getPixel(i, j);
            if((pixel.s-amount)<0)
            {
                pixel.s = 0;
            }
            else
            {
                pixel.s-=amount;
            }
        }
    }
}

void Image::grayscale()
{
    for(unsigned int i = 0; i<(width()); i++)
    {
        for(unsigned int j = 0; j<(height()); j++)
        {
            cs225::HSLAPixel &pixel = getPixel(i, j);
            pixel.s = 0;
        }
    }
}

void Image::rotateColor (double degrees)
{
    for(unsigned int i = 0; i<(width()); i++)
    {
        for(unsigned int j = 0; j<(height()); j++)
        {
            cs225::HSLAPixel &pixel = getPixel(i, j);
            pixel.h += degrees;
            if(pixel.h>360)
            {
                while(pixel.h>360)
                {
                    pixel.h -= 360;
                }
            }
            else if(pixel.h<0)
            {
                while(pixel.h<0)
                {
                    pixel.h+=360;
                }
            }
        }
    }
}

void Image::illinify()
{
    for(unsigned int i = 0; i<(width()); i++)
    {
        for(unsigned int j = 0; j<(height()); j++)
        {
            cs225::HSLAPixel &pixel = getPixel(i, j);
            if(abs(pixel.h-11)<abs(pixel.h-216))
            {
                pixel.h = 11;
            }
            else
            {
                pixel.h = 216;
            }
        }
    }
}

void Image::scale(double factor)
{
    unsigned int newWidth = factor*width();
    unsigned int newHeight = factor*height();
    Image *copy = new Image();
    *copy = *this;
    resize(newWidth, newHeight);

    for(unsigned int i = 0; i<newWidth; i++)
    {
        for(unsigned int j = 0; j<newHeight; j++)
        {
            cs225::HSLAPixel &pixel = getPixel(i, j);
            cs225::HSLAPixel &oldPixel = copy->getPixel(i/factor, j/factor);
            pixel = oldPixel;
        }
    }
    delete copy;
}

void Image::scale(unsigned int x, unsigned int y)
{
    double widscale = double(x)/double(width());
    double heiscale = double(y)/double(height());
    if(widscale<heiscale)
    {
        scale(widscale);
    }
    else
    {
        scale(heiscale);
    }
}
