/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
 #include <vector>
 #include "Image.h"

#pragma once
class StickerSheet {
    public:
StickerSheet (const Image &picture, unsigned max);
StickerSheet (const StickerSheet &other);
const StickerSheet & operator= (const StickerSheet &other);
void changeMaxStickers (unsigned max);
int addSticker (Image &sticker, int x, int y);
int setStickerAtLayer (Image &sticker, unsigned layer, int x, int y);
bool translate (unsigned index, int x, int y);
void removeSticker (unsigned index);
Image * getSticker (unsigned index);
int layers () const;
Image render () const;
    private:
    unsigned long max_st;
    std::vector<Image*> image_d;
    Image baseimage;
    std::vector<std::pair<int, int>> thevector;
};
