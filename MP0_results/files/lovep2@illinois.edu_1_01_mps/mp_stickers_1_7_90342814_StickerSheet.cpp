#include <vector>
#include "Image.h"
#include "StickerSheet.h"
#include <iostream>

using namespace std;

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    base_picture = picture;
    stickers.resize(max);
    x_cord.resize(max);
    y_cord.resize(max);
}
void StickerSheet::changeMaxStickers(unsigned int max) {
    stickers.resize(max);
    x_cord.resize(max);
    y_cord.resize(max);
}
int StickerSheet::addSticker(Image &sticker, int x, int y) {
    for (unsigned int layer = 0; layer < stickers.size(); layer++) {
        if(stickers[layer] == NULL) {
            stickers[layer] = &sticker;
            x_cord[layer] = x;
            y_cord[layer] = y;
            return layer;
        }
    }
    stickers.push_back(&sticker);
    x_cord.push_back(x);
    y_cord.push_back(y);
    return stickers.size() - 1;
}
int StickerSheet::setStickerAtLayer(Image &sticker, unsigned int layer, int x, int y) {
   if(layer < stickers.size()) {
        stickers[layer] = &sticker;
        x_cord[layer] = x;
        y_cord[layer] = y;
        return layer;
   }
   return -1;
}
bool StickerSheet::translate(unsigned int index, int x, int y) {
    if(index >= stickers.size() || stickers[index] == NULL) {
        return false;
    }
    x_cord[index] = x;
    y_cord[index] = y;
    return true;
}
void StickerSheet::removeSticker(unsigned int index) {
    if (index < stickers.size()) {
        stickers[index] = NULL;
    }
}
Image* StickerSheet::getSticker(unsigned int index) {
    if(index < stickers.size()) {
        return stickers[index];
    }
    return NULL;
}
int StickerSheet::layers() const {
    return stickers.size();
}
Image StickerSheet::render() const {
    int xMin = 0;
    int yMin = 0;
    int xMax = base_picture.width();
    int yMax = base_picture.height(); 
    for (unsigned int i = 0; i < stickers.size(); i++) {
        if (stickers[i] != NULL) {
            int sticker_xMin = x_cord[i];
            int sticker_yMin = y_cord[i];
            int sticker_xMax = stickers[i]->width();
            int sticker_yMax = stickers[i]->height();
            xMin = min(xMin, sticker_xMin);
            yMin = min(yMin, sticker_yMin);
            if (sticker_xMin + sticker_xMax - 1 > xMax) {
                xMax = max(xMax, sticker_xMin + sticker_xMax);
            }
            if (sticker_yMin + sticker_yMax - 1 > yMax) {
                yMax = max(yMax, sticker_yMin + sticker_yMax);
            }
        }
    }
    Image img(xMax-xMin, yMax-yMin);
    for (unsigned int i = 0; i < base_picture.width(); i++) {
        for(unsigned int j = 0; j < base_picture.height(); j++) {
            HSLAPixel & pixel = img.getPixel(i-xMin, j-yMin);
            HSLAPixel old_pixel = base_picture.getPixel(i,j);
            pixel = old_pixel;
        }
    }
    for (unsigned int i = 0; i < stickers.size(); i++) {
        if (stickers[i] == NULL) {
            continue;
        }
        for (unsigned int j = 0; j < stickers[i]->width(); j++) {
            for(unsigned int k = 0; k < stickers[i]->height(); k++) {
                HSLAPixel & pixel = img.getPixel(j+x_cord[i]-xMin, k+y_cord[i]-yMin);
                HSLAPixel old_pixel = stickers[i]->getPixel(j,k);
                if (old_pixel.a != 0) {
                    pixel = old_pixel;
                }
            }
        }
    }
    return img;
}