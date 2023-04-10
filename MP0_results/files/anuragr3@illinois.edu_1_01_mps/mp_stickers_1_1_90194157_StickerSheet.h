/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include <vector>
#include "cs225/PNG.h"


class StickerSheet
{
    public:
    
        StickerSheet (const Image &picture, unsigned max);
        StickerSheet (const StickerSheet &other);
        const StickerSheet &operator= (const StickerSheet &other);
        void changeMaxStickers (unsigned max);
        int addSticker (Image& sticker, int x, int y);
        int setStickerAtLayer (Image& sticker, unsigned layer, int x, int y);
        bool translate (unsigned index, int x, int y);
        void removeSticker (unsigned index);
        Image * getSticker (unsigned index); 
        int layers () const;
        Image render () const;

    private:
        Image base;
        unsigned int max_;
        std::vector<int> x_coord;
        std::vector<int> y_coord;
        std::vector<Image*> stickerVec;
        // int x_negative = 0;
        // int y_negative = 0;
};

