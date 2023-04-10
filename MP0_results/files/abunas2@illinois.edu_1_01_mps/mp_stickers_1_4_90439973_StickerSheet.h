/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include <vector>
#include "cs225/PNG.h"
#include "Image.h"


using namespace cs225;
class StickerSheet : public PNG {
    public:
    StickerSheet (const Image &picture, unsigned max);
    StickerSheet (const StickerSheet &other);
    const StickerSheet & operator=(const StickerSheet &other);
    void changeMaxStickers (unsigned max);
    int addSticker(Image &sticker, int x, int y);
    int setStickerAtLayer(Image &sticker, unsigned layer, int x, int y);
    bool translate (unsigned index, int x, int y);
    void removeSticker(unsigned index);
    Image * getSticker(unsigned index);
    int layers() const;
    Image render() const;



    private:
    unsigned int max_;
    unsigned int count_;
    Image base_sticker;
    std::vector<Image*> stickers_;
    std::vector<int> x_cord;
    std::vector<int> y_cord;

};
