#include <iostream>
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "StickerSheet.h"
using namespace cs225;





StickerSheet::StickerSheet (const Image &picture, unsigned max) {
    max_ = max; // max size
    count_ = 0;
    base_sticker = Image(picture); // deep copy of picture
    stickers_.resize(max_);
    x_cord.resize(max_);
    y_cord.resize(max_);
    for (unsigned int i = 0; i < max_; ++i) {
        stickers_[i] = nullptr;
    }
}

StickerSheet::StickerSheet (const StickerSheet &other) {
    max_ = other.max_;
    count_ = other.count_;
    base_sticker = Image(other.base_sticker);
    stickers_.resize(max_);
    x_cord.resize(max_);
    y_cord.resize(max_);
    for (unsigned i = 0; i < max_; i++) {
        stickers_[i] = other.stickers_[i];
        x_cord[i] = other.x_cord[i];
        y_cord[i] = other.y_cord[i];
    }
}

const StickerSheet & StickerSheet::operator=(const StickerSheet &other) {
    if (this == &other) {
        return *this;
    } else {
        max_ = other.max_;
        count_ = other.count_;
        base_sticker = Image(other.base_sticker);
        stickers_.resize(max_);
        x_cord.resize(max_);
        y_cord.resize(max_);
        for (unsigned i = 0; i < max_; i++) {
            stickers_[i] = other.stickers_[i];
            x_cord[i] = other.x_cord[i];
            y_cord[i] = other.y_cord[i];
        }
        return *this;
    }
}

// ex:
// max = 6
// max_ = 4

void StickerSheet::changeMaxStickers (unsigned max) {
    stickers_.resize(max);
    x_cord.resize(max);
    y_cord.resize(max);
    for (unsigned i = max_; i < max; ++i) {
        stickers_[i] = nullptr;
    }
    max_ = max;
}

int StickerSheet::addSticker(Image &sticker, int x, int y) {
    // count > max
    if (count_ >= max_) {
        changeMaxStickers(max_ + 1);
    }
    for (unsigned i = 0; i < max_; ++i) {
        if (stickers_[i] == nullptr) {
            stickers_[i] = &sticker;
            x_cord[i] = x;
            y_cord[i] = y;
            count_++;
            return i;
        }
    }
    return -1;
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
    if (layer >= max_) {
        return -1;
    }
    if (stickers_[layer] == nullptr) {
        count_++;
    } 
    stickers_[layer] = &sticker;
    x_cord[layer] = x;
    y_cord[layer] = y;
    return layer;
}

bool StickerSheet::translate (unsigned index, int x, int y) {
    if (stickers_[index] == nullptr) {
        return false;
    } else {
        x_cord[index] = x;
        y_cord[index] = y;
        return true;
    }
}

void StickerSheet::removeSticker(unsigned index) {
    if ((stickers_[index] == nullptr) || (index > max_)) {
        return;
    } else {
        Image * temp = stickers_[index];
        stickers_[index] = nullptr;
        x_cord[index] = 0;
        y_cord[index] = 0;
        count_--;
    }
}

Image * StickerSheet::getSticker(unsigned index) {
    if ((stickers_[index] == nullptr) || (index >= max_)) {
        return NULL;
    } else {
        return stickers_[index];
    }
}

int StickerSheet::layers() const {
    return max_;
}


// If a pixel's alpha channel in a sticker is zero (0), no pixel is drawn for that sticker at that pixel. 
// If the alpha channel is non-zero, a pixel is drawn.
// .a

Image StickerSheet::render() const {
    // need width and height of BASE image
    unsigned int width = base_sticker.width();
    unsigned int height = base_sticker.height();
    int origin_x = 0;
    int max_x = width;
    int origin_y = 0;
    int max_y = height;

    // base image 
    for (unsigned i = 0; i < max_; ++i) {
        //iterate through EACH sticker, need to get x and y coord / width and height to later put over
        if (stickers_[i] != nullptr) {
            if (x_cord[i] < origin_x) {
                origin_x = x_cord[i];
            }
            if (y_cord[i] < origin_y) {
                origin_y = y_cord[i];
            }
            if (x_cord[i] + ((int)stickers_[i]->width()) > max_x) {
                max_x = x_cord[i] + stickers_[i]->width();
            }
            if (y_cord[i] + ((int)stickers_[i]->height()) > max_y) {
                max_y = y_cord[i] + stickers_[i]->height();
            }
        }
        // unsigned int ind_x = x_cord[i];
        // unsigned int ind_y = y_cord[i];
        // unsigned int ind_width = stickers_[i]->width();
        // unsigned int ind_height = stickers_[i]->height();
        // for (unsigned x = 0; x < ind_width; ++x) {

        // for (unsigned y = 0; y < ind_height; ++y) {

        // if (individual_sticker.getPixel(x,y).a != 0) {

    } 
    origin_x = abs(origin_x);
    origin_y = abs(origin_y);
    int new_width = origin_x + max_x;
    int new_height = origin_y + max_y;
    Image to_return = Image(new_width, new_height);
    // base image onto canvas
    for (unsigned x = 0; x < base_sticker.width(); ++x) {
        for (unsigned y = 0; y < base_sticker.height(); ++y) {
            if (base_sticker.getPixel(x,y).a != 0) {
                HSLAPixel to_print = base_sticker.getPixel(x,y);
                to_return.getPixel(x+origin_x,y+origin_y) = to_print;
            }
        }
    }
    // sticker onto base image onto canvas
    for (unsigned i = 0; i < max_; ++i) {
        if (stickers_[i] != nullptr) {
            for (unsigned x = 0; x < stickers_[i]->width(); ++x) {
                for (unsigned y = 0; y < stickers_[i]->height(); ++y) {
                    if (stickers_[i]->getPixel(x,y).a != 0) {
                        HSLAPixel to_print = stickers_[i]->getPixel(x,y);
                        to_return.getPixel(x + origin_x + x_cord[i], y + origin_y + y_cord[i]) = to_print; 
                    }
                }
            }
        }
    }
    return to_return;
}



