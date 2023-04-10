#pragma once

#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

class StickerSheet{
  public:
    StickerSheet (const Image &picture, unsigned max);
    ~StickerSheet ();
    StickerSheet (const StickerSheet &other);
    const StickerSheet& operator= (const StickerSheet &other);
    void changeMaxStickers (unsigned max);
    int addSticker (Image &sticker, int x, int y);
    int setStickerAtLayer(Image &sticker, unsigned layer, int x, int y);
    bool translate (unsigned index, int x, int y);
    void removeSticker (unsigned index);
    Image* getSticker (unsigned index);
    int layers () const;
    Image render () const;
    void emptyVectors();
  private:
    int max_stickers;
    Image sticker_image;
    vector<int> x_coords;
    vector<int> y_coords;
    vector<Image*> stickers;
};