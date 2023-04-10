/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"
#include <vector>
using cs225::PNG;
using cs225::HSLAPixel;
using std::vector;
class StickerSheet
{
    private:    
    Image *picture_ ;
    unsigned max_;
    Image ** stickers_;
    int *x_;
    int *y_;
    unsigned count_;
    

    public:
    StickerSheet(const Image &picture, unsigned max);
    StickerSheet(const StickerSheet &other);
    const StickerSheet & operator=(const StickerSheet &other);	
    void changeMaxStickers(unsigned max);
    int addSticker(Image &sticker, int x, int y);
    int setStickerAtLayer (Image &sticker, unsigned layer, int x, int y);
    bool translate (unsigned index, int x, int y);
    void removeSticker (unsigned index);
    Image * getSticker(unsigned index);
    int layers() const;
    Image render() const;

};