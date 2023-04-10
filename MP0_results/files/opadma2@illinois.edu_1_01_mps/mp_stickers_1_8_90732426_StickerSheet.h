/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include <vector>
#include "Image.h"
#include "cs225/PNG.h"
#include <iostream>
class StickerSheet{
    public:
        StickerSheet(const Image &picture, unsigned max);
        StickerSheet(const StickerSheet &other);
        const StickerSheet & operator= (const StickerSheet &other);
        void changeMaxStickers (unsigned max);
        int addSticker (Image &sticker, int x, int y);
        int setStickerAtLayer (Image &sticker, unsigned layer, int x, int y);
        bool translate (unsigned index, int x, int y);
        void removeSticker (unsigned index);
        Image * getSticker (unsigned index);
        int layers () const;
        Image render () const;
        ~StickerSheet();
        
    private:
        unsigned int max_;
        unsigned int numStickers;
        std::vector<int> x_;
        std::vector<int> y_;
        std::vector<Image *> sheet_;
        Image* base;
        void destroy();
};