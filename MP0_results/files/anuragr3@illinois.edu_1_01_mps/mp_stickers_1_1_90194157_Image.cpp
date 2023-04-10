#include <iostream>
#include "Image.h"
#include <cmath>
using namespace std;


Image::Image()
{

};

Image::Image (unsigned int width, unsigned int height)
{
    
};

void Image::darken()
{
    for (unsigned int i = 0; i < width(); i++)
    {
        for (unsigned int j = 0; j < height(); j++)
        {
            cs225::HSLAPixel &img = getPixel(i,j);
            img.l -= 0.1;

            if (img.l < 0)
            {
                img.l = 0;
            }

        }
    }
}

void Image:: darken(double amount)
{
    for (unsigned int i = 0; i < width(); i++)
    {
        for (unsigned int j = 0; j < height(); j++)
        {
            cs225::HSLAPixel &img = getPixel(i,j);
            img.l -= amount;

            if (img.l < 0)
            {
                img.l = 0;
            }

        }
    }
}

void Image::desaturate()
{
for (unsigned int i = 0; i < width(); i++)
    {
        for (unsigned int j = 0; j < height(); j++)
        {
            cs225::HSLAPixel &img = getPixel(i,j);
            img.s -= 0.1;

            if (img.s < 0)
            {
                img.s = 0;
            }

        }
    }
}

void Image::desaturate(double amount)
{
    for (unsigned int i = 0; i < width(); i++)
    {
        for (unsigned int j = 0; j < height(); j++)
        {
            cs225::HSLAPixel &img = getPixel(i,j);
            img.s -= amount;

            if (img.s < 0)
            {
                img.s = 0;
            }

        }
    } 
}

void Image::grayscale()
{
    for (unsigned int i = 0; i < width(); i++)
    {
        for (unsigned int j = 0; j < height(); j++)
        {
            cs225::HSLAPixel &img = getPixel(i,j);
            img.s = 0;
        }
    }
}

void Image::illinify()
{
    for (unsigned int i = 0; i < width(); i++)
    {
        for (unsigned int j = 0; j < height(); j++)
        {
            cs225::HSLAPixel &img = getPixel(i,j);
            if (img.h  >= 114 && img.h <= 243)
            {
                img.h = 216;
            }
            else
            {
                img.h = 11;
            }
        }
    }
}

void Image::lighten()
{
    for (unsigned int i = 0; i < width(); i++)
    {
        for (unsigned int j = 0; j < height(); j++)
        {
            cs225::HSLAPixel &img = getPixel(i,j);
            img.l += 0.1;

            if (img.l > 1)
            {
                img.l = 1;
            }

        }
    }

}

void Image::lighten(double amount)
{
    for (unsigned int i = 0; i < width(); i++)
    {
        for (unsigned int j = 0; j < height(); j++)
        {
            cs225::HSLAPixel &img = getPixel(i,j);
            img.l += amount;

            if (img.l > 1)
            {
                img.l = 1;
            }

        }
    }

}

void Image::rotateColor(double degrees)
{
    for (unsigned int i = 0; i < width(); i++)
    {
        for (unsigned int j = 0; j < height(); j++)
        {
            cs225::HSLAPixel &img = getPixel(i,j);
            img.h += degrees;
            img.h = fmod(img.h,360);
            if (img.h < 0)
            {
                img.h+=360;
            }
        }
    }
    

}

void Image::saturate()
{
    for (unsigned int i = 0; i < width(); i++)
        {
            for (unsigned int j = 0; j < height(); j++)
            {
                cs225::HSLAPixel &img = getPixel(i,j);
                img.s += 0.1;

                if (img.s > 1)
                {
                    img.s = 1;
                }   

            }
        }
}

void Image::saturate(double amount)
{
for (unsigned int i = 0; i < width(); i++)
    {
        for (unsigned int j = 0; j < height(); j++)
        {
            cs225::HSLAPixel &img = getPixel(i,j);
            img.s += amount;

            if (img.s > 1)
            {
                img.s = 1;
            }

        }
    }
}

void Image::scale(double factor)
{
    double heightPost = height()*factor;
    double widthPost = width()*factor;

    PNG old(*this);
    resize(widthPost, heightPost);

    for(unsigned int i = 0; i < width(); i++)
    {
        for(unsigned int j = 0; j < height(); j++)
        {
            cs225::HSLAPixel& prev = getPixel(i,j);
            cs225::HSLAPixel& post = old.getPixel((unsigned) (((double) i)/factor), (unsigned) ((double) j)/factor);

            prev = post;
        }
    }

}

void Image::scale(unsigned w, unsigned h)
{
    double deez = w/width();
    double nuts = h/height();

    double factor_ = min(deez, nuts);
    scale(factor_);
}
