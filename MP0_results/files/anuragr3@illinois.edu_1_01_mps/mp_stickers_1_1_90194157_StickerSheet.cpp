#include "StickerSheet.h"

StickerSheet::StickerSheet (const Image &picture, unsigned max)
{
    base = picture;
    max_ = max;
}

StickerSheet::StickerSheet (const StickerSheet & other)
{
    base = other.base;
    max_ = other.max_;

    for(size_t i=0; i<other.x_coord.size(); i++)
    {
        x_coord.push_back(other.x_coord.at(i));
    }
    
    for(size_t i=0; i<other.y_coord.size(); i++)
    {
        y_coord.push_back(other.y_coord.at(i));
    }

    for(size_t i=0; i<other.stickerVec.size(); i++)
    {
        Image* temp = other.stickerVec.at(i);
        stickerVec.push_back(temp);
    }
}

int StickerSheet::addSticker(Image& sticker, int x, int y)
{
    x_coord.push_back(x);
    y_coord.push_back(y);
    stickerVec.push_back(&sticker);

    if (stickerVec.size() > max_) 
    {
        max_ = stickerVec.size();
    }

    // if (x < 0 && abs(x) > x_negative)
    // {
    //     x_negative = abs(x);
    // }

    // if (y < 0 && abs(y) > y_negative)
    // {
    //     y_negative = abs(y);
    // }

    return stickerVec.size() - 1;
}


void StickerSheet::changeMaxStickers (unsigned max)	
{
    max_ = max;
    
    while(max_<stickerVec.size())
    {
        stickerVec.pop_back();
        x_coord.pop_back();
        y_coord.pop_back();
    }
}

int StickerSheet::setStickerAtLayer (Image& sticker, unsigned layer, int x, int y)	
{
    if (layer>=stickerVec.size())
    {
        return -1;
    }

    stickerVec.at(layer) = &sticker;
    x_coord.at(layer) = x;
    y_coord.at(layer) = y;

    return layer;
}

bool StickerSheet::translate (unsigned index, int x, int y)
{
    if (index>=stickerVec.size())
    {
        return false;
    }

    x_coord.at(index) = x;
    y_coord.at(index) = y;

    return true;

}

void StickerSheet::removeSticker (unsigned index)
{
    if (index<stickerVec.size())
    {
        stickerVec.erase(stickerVec.begin()+index, stickerVec.begin()+index+1);
        x_coord.erase(x_coord.begin()+index, x_coord.begin()+index+1);
        y_coord.erase(y_coord.begin()+index, y_coord.begin()+index+1);
    }
}

Image * StickerSheet::getSticker (unsigned index)
{
    if (index>=stickerVec.size())
    {
        return NULL;
    }

    return stickerVec.at(index);
}

int StickerSheet::layers () const
{
    return max_;
}

const StickerSheet& StickerSheet::operator= (const StickerSheet &other)
{
    x_coord.clear();
    y_coord.clear();
    stickerVec.clear();
    
    base = other.base;
    max_ = other.max_;

    for(size_t i=0; i<other.x_coord.size(); i++)
    {
        x_coord.push_back(other.x_coord.at(i));
    }
    
    for(size_t i=0; i<other.y_coord.size(); i++)
    {
        y_coord.push_back(other.y_coord.at(i));
    }

    for(size_t i=0; i<other.stickerVec.size(); i++)
    {
        Image* temp = other.stickerVec.at(i);
        stickerVec.push_back(temp);
    }

    return *this;
}

Image StickerSheet::render () const
{
    Image temp(base);

    int x_negative = 0;
    int y_negative = 0;

    for (size_t i = 0; i < x_coord.size(); i++) 
    {
        if (x_coord.at(i) < x_negative)
        {
            x_negative = x_coord.at(i);
        }
        if (y_coord.at(i) < y_negative)
        {
            y_negative = y_coord.at(i);
        }
    }
    
    x_negative = abs(x_negative);
    y_negative = abs(y_negative);
    
    if (x_negative > 0) 
    {
        Image temp2;
        temp2.resize(x_negative + temp.width(), temp.height());
        for (unsigned int i = 0; i < temp.width(); i++) 
        {
            for (unsigned int j = 0; j < temp.height(); j++)
            {
                cs225::HSLAPixel& prev = temp.getPixel(i,j);
                cs225::HSLAPixel& post = temp2.getPixel(i + x_negative, j);
                post = prev;
            }
        }
        temp = temp2;
    }

    if (y_negative > 0) 
    {
        Image temp2;
        temp2.resize(temp.width(), y_negative + temp.height());
        for (unsigned int i = 0; i < temp.width(); i++) 
        {
            for (unsigned int j = 0; j < temp.height(); j++)
            {
                cs225::HSLAPixel& prev = temp.getPixel(i,j);
                cs225::HSLAPixel& post = temp2.getPixel(i, y_negative + j);
                post = prev;
            }
        }
        temp = temp2;
    }
    

    for(size_t i = 0; i < stickerVec.size(); i++)
    {
        unsigned int xtemp = x_negative + x_coord.at(i);
        unsigned int ytemp = y_negative + y_coord.at(i);
        Image* stickerVecTemp = stickerVec.at(i);

        if (xtemp+stickerVecTemp->width() >= temp.width())
        {
            temp.resize(xtemp+stickerVecTemp->width(), temp.height());
        }

        if (ytemp+stickerVecTemp->height() >= temp.height())
        {
            temp.resize(temp.width(), ytemp+stickerVecTemp->height());
        }

        for (unsigned int k = 0; k<stickerVecTemp->width(); k++)
        {
            for (unsigned int j = 0; j<stickerVecTemp->height(); j++)
            {
                cs225::HSLAPixel& pixelTemp = stickerVecTemp->getPixel(k,j);
                
                if(pixelTemp.a != 0)
                {
                    unsigned int adjacentx = xtemp + k;
                    unsigned int adjacenty = ytemp + j;
                    cs225::HSLAPixel& pixelReal = temp.getPixel(adjacentx,adjacenty);
                    pixelReal.h = pixelTemp.h;
                    pixelReal.s = pixelTemp.s;
                    pixelReal.l = pixelTemp.l;
                    pixelReal.a = pixelTemp.a;
                }
            }
        } 
    }
    return temp;
}