#include <vector>
#include "StickerSheet.h"
#include "Image.h"
#include <iostream>

using namespace std;

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    stickers_.resize(max);
    x_.resize(max);
    y_.resize(max);
    pic_ = picture;
}
int StickerSheet::addSticker(Image &sticker, int x, int y) {
    for (unsigned int i = 0; i < stickers_.size(); i++) {
        if (stickers_[i] == NULL) {
            stickers_[i] = &sticker;
            x_[i] = x;
            y_[i] = y;
            return i;
        }
    }
    stickers_.push_back(&sticker);
    x_.push_back(x);
    y_.push_back(y);
    return stickers_.size() - 1;
}
void StickerSheet::changeMaxStickers(unsigned int max) {
    stickers_.resize(max);
    x_.resize(max);
    y_.resize(max);
}
Image* StickerSheet::getSticker(unsigned int index) {
    if (index >= stickers_.size()) {
        return NULL;
    }
    return stickers_[index];
}
int StickerSheet::layers() const {
    return stickers_.size();
}
void StickerSheet::removeSticker(unsigned int index) {
    if (index >= stickers_.size()) {
        return;
    }
    stickers_[index] = NULL;
}
Image StickerSheet::render() const {
    int right = pic_.width();
    int left = 0;
    int top = 0;
    int bottom = pic_.height();
    for (unsigned int i = 0; i < stickers_.size(); i++) {
        if (stickers_[i] != NULL) {
            if (x_[i] < left) {
                left = x_[i];
            }
            if (y_[i] < top) {
                top = y_[i];
            }
            if (x_[i] + (int)(stickers_[i]->width()) - 1 > right) {
                right = x_[i] + (int)(stickers_[i]->width());
            }
            if (y_[i] + (int)(stickers_[i]->height()) - 1 > bottom) {
                bottom = y_[i] + (int)(stickers_[i]->height());
            }
        }
    }
    Image ret(right - left, bottom - top);
    for (unsigned int i = 0; i < pic_.width(); i++) {
        for (unsigned int j = 0; j < pic_.height(); j++) {
            HSLAPixel old_p = pic_.getPixel(i,j);
            HSLAPixel & new_p = ret.getPixel(i-left, j-top);
            new_p = old_p;
        }
    }
    for (unsigned int layer = 0; layer < stickers_.size(); layer++) {
        if (stickers_[layer] == NULL) {
            continue;
        }
        for (unsigned int i = 0; i < stickers_[layer]->width(); i++) {
            for (unsigned int j = 0; j < stickers_[layer]->height(); j++) {
                HSLAPixel old_p = stickers_[layer]->getPixel(i,j);
                HSLAPixel & new_p = ret.getPixel(x_[layer] + i - left, y_[layer] + j - top);
                if (old_p.a != 0.0) {
                    new_p = old_p;
                }
            }
        }
    }
    return ret;
}
int StickerSheet::setStickerAtLayer(Image &sticker, unsigned int layer, int x, int y) {
    if (layer >= stickers_.size()) {
        return -1;
    }
    stickers_[layer] = &sticker;
    x_[layer] = x;
    y_[layer] = y;
    return layer;
}
bool StickerSheet::translate(unsigned int index, int x, int y) {
    if (index >= stickers_.size() || stickers_[index] == NULL) {
        return false;
    }
    x_[index] = x;
    y_[index] = y;
    return true;
}