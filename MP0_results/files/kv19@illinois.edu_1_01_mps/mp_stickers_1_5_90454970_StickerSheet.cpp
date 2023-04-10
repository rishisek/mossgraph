#include "Image.h"
#include "StickerSheet.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

StickerSheet::StickerSheet(const Image &picture, unsigned max)
{
    base_image = picture; 
    max_stickers = max;
    for (unsigned i = 0;i<max_stickers;i++)
    {
        stickers.push_back(nullptr);
        xpos.push_back(0);
        ypos.push_back(0);
    }
}
StickerSheet::StickerSheet (const StickerSheet &other)
{
    base_image = other.base_image;
    max_stickers = other.max_stickers;
    for (unsigned i = 0;i<max_stickers;i++)
    {
        xpos.push_back(other.xpos[i]);
        ypos.push_back(other.ypos[i]);
        stickers.push_back(other.stickers[i]);
    }
}
StickerSheet::~StickerSheet()
{
   Clear_sheet();
}
void StickerSheet::Clear_sheet()
{
    stickers.clear();
    xpos.clear();
    ypos.clear();
}
const StickerSheet & StickerSheet::operator= (const StickerSheet &other)
{
    Clear_sheet();
    base_image = other.base_image;
    max_stickers = other.max_stickers;
    for (unsigned int i = 0;i<max_stickers;i++)
    {
        xpos.push_back(other.xpos[i]);
        ypos.push_back(other.ypos[i]);
        stickers.push_back(other.stickers[i]);
    }
   return *this;
}
void StickerSheet::changeMaxStickers (unsigned max)
{
    if(max>max_stickers)
    {
        for(unsigned int i = 0;i<(max-max_stickers);i++)
        {
            stickers.push_back(nullptr);
            xpos.push_back(0);
            ypos.push_back(0);
        }
        max_stickers = max;
    }
    else if(max<max_stickers)
    {
        for(unsigned int i = 0;i<(max_stickers-max);i++)
        {
            stickers.pop_back();
            xpos.pop_back();
            ypos.pop_back();
        }
        max_stickers = max;
    }
}
int StickerSheet::addSticker (Image &sticker, int x, int y)
{
    for (unsigned int i = 0;i<max_stickers;i++)
    {
        if(stickers[i] == nullptr)
        {
            stickers[i] = &sticker;
            xpos[i] = x;
            ypos[i] = y;
            return int(i-1);
        }
    }
    max_stickers+=1;
    stickers.push_back(&sticker);
    xpos.push_back(x);
    ypos.push_back(y);
    return int(max_stickers-1);
}
int StickerSheet::setStickerAtLayer (Image &sticker, unsigned layer, int x, int y)
{
    if(layer>=max_stickers)
    {
        return -1;
    }
    else
    {
        stickers[layer] = &sticker;
        xpos[layer] = x;
        ypos[layer] = y;
        return int(layer);
    }
}
bool StickerSheet::translate (unsigned index, int x, int y)
{
    if((index>=max_stickers)||(stickers[index]==nullptr))
    {
        return false;
    }
    else
    {
        xpos[index] = x;
        ypos[index] = y;
        return true;
    }
}
void StickerSheet::removeSticker (unsigned index)
{
    if (index<max_stickers)
    {
        stickers[index] = nullptr;
        xpos[index] = 0;
        ypos[index] = 0;
    }   
}
Image* StickerSheet::getSticker (unsigned index)
{
    if(index>=max_stickers)
    {
        return NULL;
    }
    else
    {
        return stickers[index];
    }
}
int StickerSheet::layers () const
{
    return int(stickers.size());
}

Image StickerSheet::render () const
{
  
    Image result = base_image;
    Image temp_base = base_image;
    unsigned reswidth = result.width();
    unsigned resheight = result.height();
    unsigned scaledx,scaledy;
    int minxval = 0;
    int minyval = 0;
    vector<int> sh_xpos = xpos;
    vector<int> sh_ypos = ypos;
    for (unsigned i = 0; i < max_stickers; i++) 
    {
        if(stickers[i]!=nullptr)
        {
            if(sh_xpos[i]<minxval)
            {
                minxval = sh_xpos[i];
            }
            if(sh_ypos[i]<minyval)
            {
                minyval = sh_ypos[i];
            }
        }
    }
    if(minxval<0)
    {
        for(unsigned i = 0;i<max_stickers;i++)
        {
            sh_xpos[i] -= minxval;
        }
    }
    if(minyval<0)
    {
        for (unsigned i = 0;i<max_stickers;i++)
        {
            sh_ypos[i] -= minyval;
        }
    }
    for (unsigned i =0 ;i<max_stickers;i++)
    {
        if(stickers[i]!=nullptr)
        {
            scaledx = sh_xpos[i] + stickers[i]->width();
            scaledy = sh_ypos[i] + stickers[i]->height();
            if (reswidth < scaledx)
            { 
                reswidth = scaledx;
            }
            if (resheight < scaledy) 
            {
                resheight = scaledy;
            }
        }
    }
    reswidth-=minxval;
    resheight-=minyval;
    result.resize(reswidth,resheight);
    for (unsigned x = 0; x < base_image.width(); x++) 
    {
        for (unsigned y = 0; y < base_image.height(); y++) 
        {
            cs225::HSLAPixel &base = temp_base.getPixel(x, y);
            cs225::HSLAPixel &final = result.getPixel(x - minxval, y - minyval);
            final = base;
        }
    }
    for (unsigned i = 0; i < max_stickers; i++) 
    {
        if (stickers[i]!=nullptr) 
        {
            for (unsigned x = sh_xpos[i]; x < (sh_xpos[i] + stickers[i]->width()); x++) 
            {
                for (unsigned y = sh_ypos[i]; y < (sh_ypos[i] + stickers[i]->height()); y++) 
                {
                    cs225::HSLAPixel &sticker = stickers[i]->getPixel(x - sh_xpos[i], y - sh_ypos[i]);
                    cs225::HSLAPixel &finalPixel = result.getPixel(x, y);
                    if (sticker.a != 0)
                    {
                        finalPixel = sticker;
                    }
                }
            }
        }
    }
    return result;
}





