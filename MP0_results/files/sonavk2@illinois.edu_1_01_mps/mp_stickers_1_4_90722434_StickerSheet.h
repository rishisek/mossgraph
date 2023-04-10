/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include "cs225/PNG.h"
#include <vector>


class StickerSheet {
    public:
    StickerSheet(const Image &picture, unsigned max);
    ~StickerSheet();
    StickerSheet(const StickerSheet &other);
    const StickerSheet& operator=(const StickerSheet &other);
    void changeMaxStickers(unsigned max);
    int addSticker(Image &sticker, int x, int y);
    int setStickerAtLayer(Image &sticker, unsigned layer, int x, int y);
    bool translate(unsigned index, int x, int y);
    void removeSticker(unsigned index);
    Image* getSticker(unsigned index);
    int layers() const;
    Image render() const; 

    private:
    std::vector<Image*> stickers_;
    Image* base_;
    unsigned max_;
    std::vector<int> xCoord;
    std::vector<int> yCoord;
};