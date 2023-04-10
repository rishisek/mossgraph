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
        Image pic_;
        vector<Image*> stickers_;
        vector<int> x_;
        vector<int> y_;
    public:
        StickerSheet(const Image &picture, unsigned max);
        int addSticker(Image &sticker, int x, int y);
        void changeMaxStickers(unsigned int max);
        Image* getSticker(unsigned int index);
        int layers() const;
        void removeSticker(unsigned int index);
        Image render() const;
        int setStickerAtLayer(Image &sticker, unsigned int layer, int x, int y);
        bool translate(unsigned int index, int x, int y);
        StickerSheet & operator=(const StickerSheet &other) = default;
        StickerSheet (const StickerSheet &other) = default;
};