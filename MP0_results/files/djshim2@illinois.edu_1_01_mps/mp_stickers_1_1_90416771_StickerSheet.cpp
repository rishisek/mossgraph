#include "StickerSheet.h"
#include "Image.h"
#include "cs225/HSLAPixel.h"
#include <iostream>

StickerSheet::StickerSheet(const Image & p, unsigned max)
{
  sticker_max=max;
  stickers=new Image*[max];
  x = new unsigned[max];
  y = new unsigned[max];
  this->base = new Image(p);
  layer = new unsigned[max];
  sticker_count=0;
  for (unsigned i = 0; i < max; i++) {
         stickers[i] = NULL;
         x[i]=0;
         y[i]=0;
         layer[i]=0;
     }
}
StickerSheet::~StickerSheet()
{
  destroy();
}
void StickerSheet::copy(const StickerSheet & other)
{
  sticker_count=other.sticker_count;
  sticker_max=other.sticker_max;
  stickers=new Image*[sticker_max];
  base = new Image(*(other.base));
  x=new unsigned[sticker_max];
  y=new unsigned[sticker_max];
  layer=new unsigned[sticker_max];
  for(unsigned i =0; i<sticker_max;i++)
  {
    if(other.layer[i]!=0)
    {
      layer[i]=other.layer[i];
      stickers[i]=new Image(*(other.stickers[i]));
      x[i]=other.x[i];
      y[i]=other.y[i];
    }
    else
    {
      stickers[i]=NULL;
      x[i]=0;
      y[i]=0;
      layer[i]=0;

    }
  }

}
void StickerSheet::destroy()
{
  delete []x;
  delete[]y;
  for(int i = 0; i<(int)sticker_max;i++)
  {
      delete stickers[i];
      stickers[i]=NULL;
  }
  delete[] stickers;
  delete[] layer;
  delete base;
}
StickerSheet::StickerSheet(const StickerSheet & other)
{
  copy(other);
}
const StickerSheet &    StickerSheet::operator= (const StickerSheet &other)
{
  destroy();
  copy(other);
  return *this;
}
void    StickerSheet::changeMaxStickers (unsigned max)
{
  if(sticker_max==max)
  {
    return;
  }
  Image* img = new Image(*base);
  Image ** stickerstemp = new Image *[max];
  unsigned *ytemp = new unsigned[max];
  unsigned *xtemp = new unsigned[max];
  unsigned *l2 = new unsigned[max];
  unsigned sc=0;
  if(max>sticker_max)
  {
    for(unsigned i=0;i<max;i++)
    {
      l2[i]=0;
      /*if(layer[i]!=0)
      {
        delete stickers[i];
        layer[i]=0;
      }*/
      stickerstemp[i]=NULL;
    }
    //sticker_max=max;
  }
  if(max<sticker_max)
  {
    for(unsigned i=max;i<sticker_max;i++)
    {
      if(layer[i]!=0)
      {
        delete stickers[i];
        layer[i]=0;
      }
    }
    sticker_max=max;
  }
  for(unsigned i = 0;i<sticker_max;i++)
  {
    if(i>=max)
    {
      break;
    }
    if(layer[i]!=0)
    {
      sc++;
      stickerstemp[i]=new Image(*stickers[i]);
      xtemp[i]=x[i];
      ytemp[i]=y[i];
      l2[i]=layer[i];
    }
    else
    {
      stickerstemp[i]=NULL;
      xtemp[i]=-1;
      ytemp[i]=-1;
      l2[i]=0;
    }
  }
  destroy();
  stickers=stickerstemp;
  x=xtemp;
  layer=l2;
  sticker_count=sc;
  y=ytemp;
  sticker_max=max;
  base=img;
}

int StickerSheet::addSticker (Image &sticker, unsigned x1, unsigned y1){
  unsigned i=0;
  if(sticker_count<sticker_max)
  {
    while(i<sticker_max)
    {
      if(layer[i]==0)
      {
        stickers[i]=new Image(sticker);
        x[i]=x1;
        y[i]=y1;
        sticker_count++;
        layer[i]=1;
        return i;
      }
      i++;
    }
   }
  return -1;
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer1, int x1, int y1){
  if (layer1 >= sticker_max) {
    return -1;
  }

  unsigned i = 0;
  while(i<sticker_max){
    if(layer[i]==0){
      stickers[i]=new Image(sticker);
      x[i]=x1;
      y[i]=y1;
      sticker_count++;
      layer[i]=1;
    }
    i++;
  }
  stickers[layer1] = &sticker;
  x[layer1] = x1;
  y[layer1] = y1;
  return layer1;
}

bool    StickerSheet::translate (unsigned index, unsigned x1, unsigned y1){
  if(index>=sticker_max || layer[index]==0)
  {
    return false;
  }
  else
  {
    x[index]=x1;
    y[index]=y1;
    return true;
  }
}
void    StickerSheet::removeSticker (unsigned index)
{
  if(index<sticker_max && layer[index] !=0)
  {
    delete stickers[index];
    stickers[index]=NULL;
    x[index]=-1;
    y[index]=-1;
    sticker_count-=1;
    layer[index]=0;
  }
}
Image *     StickerSheet::getSticker (unsigned index)
{
  if(index>=sticker_max ||layer[index]==0) return NULL;
  return stickers[index];
}

int StickerSheet::layers() const{
  return sticker_max;
}

Image   StickerSheet::render () const
{
  unsigned finalx=base->width();
  unsigned finaly=base->height();

  for(unsigned int a = 0; a<sticker_max;a++)
  {
    if(layer[a]!=0)
    {
      if(finalx<stickers[a]->width()+x[a])
      {
        finalx=stickers[a]->width()+x[a];
      }
      if(finaly<stickers[a]->height()+y[a])
      {
        finalx=stickers[a]->height()+x[a];
      }
    }
  }
  Image * out = new Image(*base);
  out->resize(finalx,finaly);
  for(unsigned i = 0; i<sticker_max;i++)
  {
    if(layer[i]!=0)
    {
      Image s = *stickers[i];
      unsigned stickerxmax = s.width();
      unsigned stickerymax = s.height();
      for(unsigned xco =x[i]; xco<x[i]+stickerxmax;xco++)
      {
        for(unsigned yco =y[i]; yco<y[i]+stickerymax;yco++)
        {
          cs225::HSLAPixel & pixel1 = s.getPixel(xco-x[i], yco-y[i]);
          cs225::HSLAPixel & pixel2 = out->getPixel(xco, yco);
          if(pixel1.a!=0)
          {
            pixel2.h=pixel1.h;
            pixel2.l=pixel1.l;
            pixel2.s=pixel1.s;
            pixel2.a=pixel1.a;
          }
        }
      }
    }
  }
  Image base2 = *out;
  delete out;
  return base2;
}