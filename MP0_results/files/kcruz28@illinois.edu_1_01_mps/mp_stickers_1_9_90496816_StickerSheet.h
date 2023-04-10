/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#include "Image.h"
#include "cs225/HSLAPixel.h"
#include <vector>
#pragma once

class StickerSheet {
    public:
        StickerSheet (const Image &picture, unsigned int max);
        StickerSheet (const StickerSheet &other);
        const StickerSheet & operator= (const StickerSheet &other);
        void changeMaxStickers (unsigned int max);
        int addSticker (Image &sticker, int x, int y);
        int setStickerAtLayer (Image &sticker, unsigned layer, int x, int y);
        bool translate (unsigned index, int x, int y);
        void removeSticker (unsigned index);
        Image * getSticker (unsigned index);
        int layers () const;
        Image render () const;
    private:
        std::vector<Image*> stickers_;
        Image base_image_;
        std::vector<int> x_;
        std::vector<int> y_;
        unsigned int max_;
};



