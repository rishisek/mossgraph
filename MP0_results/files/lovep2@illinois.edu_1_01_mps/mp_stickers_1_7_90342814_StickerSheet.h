/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include <vector>

using namespace std;

class StickerSheet {
    public:
        StickerSheet(const Image &picture, unsigned max);
        StickerSheet & operator= (const StickerSheet &other) = default;
        StickerSheet (const StickerSheet &other) = default;
        void changeMaxStickers(unsigned int max);
        int addSticker(Image &sticker, int x, int y);
        int setStickerAtLayer(Image &sticker, unsigned int layer, int x, int y);
        bool translate(unsigned int index, int x, int y);
        void removeSticker(unsigned int index);
        Image *getSticker(unsigned int index);
        int layers() const;
        Image render() const;
    private:
        Image base_picture;
        vector<Image *> stickers;
        vector<int> x_cord;
        vector<int> y_cord;
};