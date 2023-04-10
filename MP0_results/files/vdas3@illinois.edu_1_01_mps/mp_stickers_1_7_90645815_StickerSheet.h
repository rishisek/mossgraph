/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include <vector>

struct Sticker {
    Image* image;
    int x;
    int y;
};

class StickerSheet {
    public:
        StickerSheet (const Image &picture, unsigned max);
        StickerSheet (const StickerSheet &other);
       ~StickerSheet();
        const StickerSheet & operator=(const StickerSheet &other);
        void changeMaxStickers(unsigned max);
        int addSticker(Image &sticker, int x, int y);
        int setStickerAtLayer (Image &sticker, unsigned layer, int x, int y);
        bool translate (unsigned index, int x, int y);
        void removeSticker (unsigned index);
        Image *getSticker (unsigned index);
        int layers () const;
        Image render () const;
    private:
        void Copy(const StickerSheet &other);
        std::vector<Sticker> stickers_;
        unsigned max_;
        Image base_;
};
