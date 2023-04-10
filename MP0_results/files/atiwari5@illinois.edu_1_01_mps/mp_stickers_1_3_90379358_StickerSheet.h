/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */

#pragma once
#include <vector>
#include "Image.h"
using namespace std;


class StickerSheet {
    private:
        unsigned int max_;
        vector <const Image*> stickers_;
        Image base_;
        vector <int> x_cord;
        vector <int> y_cord;
    public:
        StickerSheet(const Image &picture, unsigned max);
        // StickerSheet (const StickerSheet &other) = default;
        // const StickerSheet & operator= (const StickerSheet &other) = default;
        void changeMaxStickers(unsigned max);
        int addSticker(Image &sticker, int x, int y);
        int setStickerAtLayer(Image &sticker, unsigned layer, int x, int y);
        int layers() const;
        void removeSticker(unsigned index);
        bool translate(unsigned index, int x, int y);
        Image render() const;
        Image * getSticker(unsigned index);
};

