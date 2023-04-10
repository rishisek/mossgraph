#include "Image.h"
#include <iostream>

using cs225::PNG;
using cs225::HSLAPixel;
using namespace std;

void Image::lighten()
{
    for (unsigned i = 0; i < width(); i++) 
    {
      for (unsigned j = 0; j < height(); j++) 
      {
          HSLAPixel &pixel = this->getPixel(i, j);
          pixel.l += 0.1;
          if (pixel.l >= 1)
          {
            pixel.l=1;
          }
      }
    }
}
void Image::lighten (double amount)
{
    for (unsigned i = 0; i < width(); i++) 
    {
      for (unsigned j = 0; j < height(); j++) 
      {
          HSLAPixel &pixel = this->getPixel(i, j);
          pixel.l += amount;
          if (pixel.l >= 1)
          {
            pixel.l=1;
          }
      }
    }
}
void Image::darken()
{
    for (unsigned i = 0; i < width(); i++) 
    {
      for (unsigned j = 0; j < height(); j++) 
      {
          HSLAPixel &pixel = this->getPixel(i, j);
          pixel.l -= 0.1;
          if (pixel.l <= 0)
          {
            pixel.l=0;
          }
      }
    }
}
void Image::darken(double amount)
{
    for (unsigned i = 0; i < width(); i++) 
    {
      for (unsigned j = 0; j < height(); j++) 
      {
          HSLAPixel &pixel = this->getPixel(i, j);
          pixel.l -= amount;
          if (pixel.l <= 0)
          {
            pixel.l=0;
          }
      }
    }
}
void Image::saturate()
{
    for (unsigned i = 0; i < width(); i++) 
    {
      for (unsigned j = 0; j < height(); j++) 
      {
          HSLAPixel &pixel = this->getPixel(i, j);
          pixel.s += 0.1;
          if (pixel.s >= 1)
          {
            pixel.s=1;
          }
      }
    }
}
void Image::saturate(double amount)
{
    for (unsigned i = 0; i < width(); i++) 
    {
      for (unsigned j = 0; j < height(); j++) 
      {
          HSLAPixel &pixel = this->getPixel(i, j);
          pixel.s += amount;
          if (pixel.s >= 1)
          {
            pixel.s=1;
          }
      }
    }
}
void Image::desaturate()
{
    for (unsigned i = 0; i < width(); i++) 
    {
      for (unsigned j = 0; j < height(); j++) 
      {
          HSLAPixel &pixel = this->getPixel(i, j);
          pixel.s -= 0.1;
          if (pixel.s <= 0)
          {
            pixel.s=0;
          }
      }
    }
}
void Image::desaturate(double amount)
{
    for (unsigned i = 0; i < width(); i++) 
    {
      for (unsigned j = 0; j < height(); j++) 
      {
          HSLAPixel &pixel = this->getPixel(i, j);
          pixel.s -= amount;
          if (pixel.s <= 0)
          {
            pixel.s=0;
          }
      }
    }
}
void Image::grayscale()
{
    for (unsigned i = 0; i < width(); i++) 
    {
      for (unsigned j = 0; j < height(); j++) 
      {
          HSLAPixel &pixel = this->getPixel(i, j);
          pixel.s = 0;
      }
    }
}
void Image::rotateColor(double degree)
{
    for (unsigned i = 0; i < width(); i ++) 
    {
        for (unsigned j = 0; j < height(); j ++) 
        {
            HSLAPixel &pixel = this->getPixel(i,j);
            pixel.h += degree;
            while (pixel.h < 0.0)
            {
              pixel.h += 360.0;
            }
            while (pixel.h > 360.0) 
            {
              pixel.h -= 360.0;
            }
        }
    }
}
void Image::illinify()
{
    for (unsigned i = 0; i < width(); i++) 
    {
      for (unsigned j = 0; j < height(); j++) 
      {
          HSLAPixel &pixel = this->getPixel(i, j);
          pixel.h += 0.1;
          if (pixel.h >= 114 && pixel.h <= 243)
          {
            pixel.h = 216;
          }
          else
          {
            pixel.h = 11;
          }
      }
    }
}
void Image::scale(double factor)
{
  if(factor < 1) 
  {
    for(unsigned i = 0; i < width() * factor; i++) 
    {
      for(unsigned j = 0; j < height() * factor; j++) 
      {
        HSLAPixel& np = getPixel(i, j);
        HSLAPixel& op = getPixel(i / factor, j / factor);
        np = op;
      }
    }
    resize(width() * factor, height() * factor);
  }
  if(factor > 1) 
  {
    resize(width() * factor, height() * factor);
    for(int i = width() - 1; i >= 0; i--) 
    {
      for(int j = height() - 1; j >= 0; j--) 
      {
        HSLAPixel& np = getPixel((unsigned)i, (unsigned)j);
        HSLAPixel& op = getPixel((unsigned)i / factor, (unsigned)j / factor);
        np = op;
      }
    }
  }
}
void Image::scale(unsigned w, unsigned h)
{
  double wf = (double) w / (double) this->width();
  double hf = (double) h / (double) this->height();
  double factor = min(wf, hf);
  scale(factor);
}