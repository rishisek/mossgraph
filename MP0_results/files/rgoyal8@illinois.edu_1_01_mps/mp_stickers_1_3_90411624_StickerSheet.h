/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */

#pragma once
#include <vector>
#include <utility>
#include "Image.h"

class StickerSheet{
    public: 
        StickerSheet(const Image &picture, unsigned max);
        void changeMaxStickers(unsigned max);
        int addSticker(Image &sticker, int x, int y);
        int setStickerAtLayer(Image &sticker, unsigned layer, int x, int y);
        bool translate(unsigned index, int x, int y);
        void removeSticker(unsigned index);
        Image * getSticker(unsigned index);
        int layers() const;
        Image render() const;
    private:
        std::vector<Image*> image_vectors_;
        std::vector<std::pair<int, int>> image_location_;
        Image image_;
        unsigned int max_;
        unsigned int layer_;
};
