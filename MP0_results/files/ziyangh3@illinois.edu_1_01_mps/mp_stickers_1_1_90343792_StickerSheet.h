/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#include<Image.h>
#include<vector>
#include <iostream>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#pragma once
using namespace std;

class StickerSheet{
    public:

        StickerSheet(const Image &picture, unsigned max);
        StickerSheet(const StickerSheet &other);
        //~StickerSheet();
        const StickerSheet & operator= (const StickerSheet &other);
        void changeMaxStickers (unsigned max);
        int addSticker (Image &sticker, int x, int y);
        int setStickerAtLayer (Image &sticker, unsigned layer, int x, int y);
        bool translate (unsigned index, int x, int y);
        void removeSticker (unsigned index);
        Image * getSticker (unsigned index);
        int layers () const;
        Image render () const;

    private:
        Image picture_;
        unsigned max_; //maximum number of stickers that can be stored
        unsigned num_; //number of stickers
        vector<int> xcoord_;
        vector<int> ycoord_; 
        vector<Image*> sheet_;
        
        //void copy(const StickerSheet &other);
        //void clear(const StickerSheet &other);


};
