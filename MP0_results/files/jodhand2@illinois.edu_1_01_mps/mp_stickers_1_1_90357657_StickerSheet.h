/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"
using namespace std; 
#include <vector>
struct layer{
    int x; 
    int y; 
    Image* StructSticker; 
    //layer(int x_, int y_, Image* sticker_); 
};


class StickerSheet{
    public: 
    StickerSheet(const Image & picture, unsigned max); 
    StickerSheet(const StickerSheet & other); 
    void copy(const StickerSheet & obj); 
    //void destroy(); 
    //~StickerSheet(); 
    const StickerSheet & operator=(const StickerSheet & other); 
    void changeMaxStickers(unsigned max); 
    int addSticker(Image & sticker, int x, int y); 
    int setStickerAtLayer(Image & sticker, unsigned layer, int x, int y); 
    bool translate (unsigned index, int x, int y); 
    void removeSticker(unsigned index); 
    Image* getSticker(unsigned index) const; 
    int layers() const; 
    Image render() const; 
    

    private:
    Image picture_; 
    unsigned max_;
    vector<layer> layers_; 
};

