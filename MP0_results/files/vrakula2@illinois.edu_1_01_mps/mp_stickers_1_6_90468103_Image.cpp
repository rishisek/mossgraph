#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;
using cs225::HSLAPixel;
using cs225::PNG;
void Image::lighten()
{
  for(unsigned x =0;x<width();x++)
  {
    for(unsigned y=0; y<height(); y++)
    {
      if(this->getPixel(x,y).l+.1>=1.0)
      {
        this->getPixel(x,y).l=1.0;
        continue;
      }
      else
        this->getPixel(x,y).l=this->getPixel(x,y).l+.1;
    }
  }
}
void Image::lighten(double amount)
{
  for(unsigned y=0; y<height(); y++)
  {
    for(unsigned x =0;x<width();x++)
    {
      if(this->getPixel(x,y).l+amount>=1.0)
      {
        this->getPixel(x,y).l=1;
        continue;
      }
      else
        this->getPixel(x,y).l=this->getPixel(x,y).l+amount;
    }
  }
}
void Image::darken()
{
  int width = this->width();
  int height = this->height();
  for(int y=0; y<height; y++)
  {
    for(int x =0;x<width;x++)
    {
      if(this->getPixel(x,y).l-.1<=0.0)
      {
        this->getPixel(x,y).l=0;
      }
      else
        this->getPixel(x,y).l=this->getPixel(x,y).l-.1;
    }
  }
}
void Image::darken(double amount)
{
  int height = this->height();
  for(unsigned x =0;x<width();x++)
  {
    for(int y=0; y<height; y++)
    {
      if(this->getPixel(x,y).l-amount<=0.0)
      {
        this->getPixel(x,y).l=0;
      }
      else this->getPixel(x,y).l=this->getPixel(x,y).l-amount;
    }
  }
}
void Image::grayScale()
{
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.s = 0;
    }
  }
}
void Image::illinify()
{
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      if ((pixel.h > 113) && (pixel.h < 294)) {
          pixel.h = 216;
      } else {
          pixel.h = 11;
      }
    }
  }
}
void Image::desaturate()
{
  for(unsigned x =0;x<width();x++)
  {
    for(unsigned y=0; y<height(); y++)
    {
      this->getPixel(x,y).s=this->getPixel(x,y).s-.1;
    }
  }
}
void Image::desaturate(double amount)
{
  for(unsigned x =0;x<width();x++)
  {
    for(unsigned y=0; y<height(); y++)
    {
      this->getPixel(x,y).s=this->getPixel(x,y).s-amount;
    }
  }
}
void Image::rotateColor(double degrees)
{
    for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.h += degrees;
      while (pixel.h > 360) {
        pixel.h -= 360;
      }
      while (pixel.h < 0) {
        pixel.h += 360;
      }
    }
  }
}
void Image::saturate()
{
  for(unsigned x =0;x<width();x++)
  {
    for(unsigned y=0; y<height(); y++)
    {
      this->getPixel(x,y).s=this->getPixel(x,y).s+.1;
    }
  }
}
void Image::saturate(double amount)
{
  for(unsigned x =0;x<width();x++)
  {
    for(unsigned y=0; y<height(); y++)
    {
      this->getPixel(x,y).s=this->getPixel(x,y).s+amount;
    }
  }
}
void Image::scale(double factor)
{
  unsigned int newWidth = width() * factor;
  unsigned int newHeight = height() * factor;

	Image * copyImage = new Image();
	*copyImage = *this;
	resize(newWidth, newHeight);

	for (unsigned int h = 0; h < newHeight; h++) {
		for (unsigned int w = 0; w < newWidth; w++) {
			HSLAPixel & cur_pixel = getPixel(w, h);
			HSLAPixel & cur_copy_pixel = copyImage->getPixel(w / factor, h / factor);
			cur_pixel = cur_copy_pixel;
		}
	}
	
	delete copyImage;
}
void Image::scale(unsigned w, unsigned h)
{
  unsigned newwidth=w;
  unsigned newheight=h;
  double xr=(double)newwidth/(this->width());

  double yr=(double)newheight/(this->height());
  if(yr>xr)
  {
    scale(xr);
  }
  else{
    scale(yr);
  }
}