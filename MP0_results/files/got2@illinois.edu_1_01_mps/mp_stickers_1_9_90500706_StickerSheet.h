/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"
#include <vector>
using std::vector;

class StickerSheet {
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
    //void resizeNeg(Image &output, int width, int height) const;
    Image base_;
    unsigned max_;
    vector<Image *> layers_;
    vector<int> x_coords_;
    vector<int> y_coords_;
};