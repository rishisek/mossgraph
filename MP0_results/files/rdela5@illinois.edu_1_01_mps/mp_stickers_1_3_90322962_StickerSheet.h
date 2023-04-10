/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include <vector>

class StickerSheet {
    private:
    std::vector<Image*> stickers;
    std::vector<int> x_coords;
    std::vector<int> y_coords;
    unsigned max_;
    Image picture_;

    public:

    StickerSheet(const Image & picture, unsigned max);
    StickerSheet(const StickerSheet & other);

    int addSticker(Image & sticker, int x, int y);
    void changeMaxStickers(unsigned max);
    Image * getSticker(unsigned index);
    int layers() const;
    const StickerSheet & operator=(const StickerSheet & other);
    void removeSticker(unsigned index);
    Image render() const;
    int setStickerAtLayer(Image & sticker, unsigned layer, int x, int y);
    bool translate(unsigned index, int x, int y);
};