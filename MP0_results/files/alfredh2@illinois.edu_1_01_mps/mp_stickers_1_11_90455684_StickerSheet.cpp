#include "StickerSheet.h"

StickerSheet::StickerSheet (const Image &picture, unsigned max) {
    base_ = picture;
    max_ = max;
    stickers.resize(0);
}

void StickerSheet::copy(const StickerSheet &other) {
    base_ = other.base_;
    max_ = other.max_;
    stickers = other.stickers;
}

StickerSheet::StickerSheet (const StickerSheet &other) {
    copy(other);
}

const StickerSheet & StickerSheet::operator= (const StickerSheet &other) {
    if (this != &other) {
        copy(other);
    }
    return *this;
}

void StickerSheet::changeMaxStickers (unsigned max) {
    max_ = max;
    while (stickers.size() > max) {
        stickers.pop_back();
    }
}

int StickerSheet::addSticker (Image &sticker, int x, int y) {
    stickStruct s;
    s.image = &sticker;
    s.x = x;
    s.y = y;
    s.layer = stickers.size();

    if (stickers.size() == max_) {
        max_++;
    }
    stickers.push_back(s);

    return stickers.size() - 1;
}

int StickerSheet::setStickerAtLayer (Image &sticker, unsigned layer, int x, int y) {
    if (layer < max_) {
        for (unsigned int i = 0; i < stickers.size(); i++) {
            if (stickers[i].layer == layer) {
                stickers[i].image = &sticker;
                stickers[i].x = x;
                stickers[i].y = y;
                return (int) layer;
            }
        }
    }
    return -1;
    
}

bool StickerSheet::translate (unsigned index, int x, int y) {
    if (index + 1 <= max_ && index >= 0) {
        for (unsigned int i = 0; i < stickers.size(); i++) {
            if (stickers[i].layer == index) {
                stickers[index].x = x;
                stickers[index].y = y;
                return true;
            }
       } 
    }
    return false;
}


void StickerSheet::removeSticker (unsigned index) {
    stickers.erase(stickers.begin() + index);
}

Image * StickerSheet::getSticker (unsigned index) {
    if (index < stickers.size()) {
        return stickers[index].image;
    }
    return NULL;
}

int StickerSheet::layers () const {
    return max_;
}

Image StickerSheet::render () const {

    // Initialize width and height to that of base image
    int width = (int) base_.width();
    int height = (int) base_.height();
    // Find lowest and highest values of coordinates of stickers to recalculate a max width and height for final image
    int x_min = 0;
    int y_min = 0;
    int x_max = width;
    int y_max = height;
    // Check x, y min, max for each sticker
    for (unsigned int i = 0; i < stickers.size(); i++) {
        if (stickers[i].x < x_min) {
            x_min = stickers[i].x;
        }
        if (stickers[i].x + (int) stickers[i].image->width() > x_max) {
            x_max = stickers[i].x + (int) stickers[i].image->width();
        }
        if (stickers[i].y < y_min) {
            y_min = stickers[i].y;
        }
        if (stickers[i].y + (int) stickers[i].image->height() > y_max) {
            y_max = stickers[i].y + (int) stickers[i].image->height();
        }
    }
    // Recalculate the width and height of the final image and then generate it
    width = x_max - x_min;
    height = y_max - y_min;
    
    Image final(width, height);
    for (unsigned int w = 0; w < base_.width(); w++) {
        for (unsigned int h = 0; h < base_.height(); h++) {
            if (base_.getPixel(w, h).a != 0) {
                final.getPixel(w + abs(x_min), h + abs(y_min)) = base_.getPixel(w, h);
            }
        }
    }
    
    // Stickers
    // For each sticker in the vector
    for (unsigned int i = 0; i < stickers.size(); i++) {
        for (unsigned int x = 0; x < stickers[i].image->width(); x++) {
            for (unsigned int y = 0; y < stickers[i].image->height(); y++) {
                // If alpha of pixel is not 0
                if (stickers[i].image->getPixel(x, y).a != 0) {
                    // Copy the pixel over 
                    int x_final = (int) x + abs(x_min) + stickers[i].x;
                    int y_final = (int) y + abs(y_min) + stickers[i].y;
                    final.getPixel(x_final, y_final) = stickers[i].image->getPixel(x, y);
                }
            }
        }
    }
    return final; 
}