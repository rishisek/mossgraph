#include "StickerSheet.h"
#include "Image.h"
#include <vector>
#include <iostream>

StickerSheet::StickerSheet(const Image & picture, unsigned max) {
    picture_ = picture;
    max_ = max;
    stickers.resize(max);
    x_coords.resize(max);
    y_coords.resize(max);
}

StickerSheet::StickerSheet(const StickerSheet & other) {
    this->picture_ = other.picture_;
    this->max_ = other.max_;
    this->stickers = other.stickers;
    this->x_coords = other.x_coords;
    this->y_coords = other.y_coords;
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other) {
    this->picture_ = other.picture_;
    this->max_ = other.max_;
    this->stickers = other.stickers;
    this->x_coords = other.x_coords;
    this->y_coords = other.y_coords;
    return *this;
}

int StickerSheet::addSticker(Image & sticker, int x, int y) {
    int index = 0;
    while (int q = 1) {
        if (index == (int) max_) {
            stickers.push_back(&sticker);
            x_coords.push_back(x);
            y_coords.push_back(y);
            max_++;
            break;
        } 
        else if (stickers[index] == NULL) {
            stickers[index] = &sticker;
            x_coords[index] = x;
            y_coords[index] = y;
            break;
        }
        index++;
    }
    return index;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    stickers.resize(max);
    x_coords.resize(max);
    y_coords.resize(max);
    max_ = max;
}

Image* StickerSheet::getSticker(unsigned index) {
    return stickers[index];
}

int StickerSheet::layers() const {
    return max_;
}

void StickerSheet::removeSticker(unsigned index) {
    stickers[index] = NULL;
}

Image StickerSheet::render() const {
    unsigned int image_width = picture_.width();
    unsigned int image_height = picture_.height();
    unsigned int image_left_adjustment = 0;
    unsigned int image_top_adjustment = 0;
    int image_left_border = 0;
    int image_top_border = 0;
    int image_right_border = (int)picture_.width();
    int image_bottom_border = (int)picture_.height();

    for (unsigned int i = 0; i < max_; i++) {
        if (stickers[i] != NULL) {
            int sticker_left_edge = x_coords[i];
            int sticker_top_edge = y_coords[i];
            int sticker_right_edge = x_coords[i] + (int)stickers[i]->width();
            int sticker_bottom_edge = y_coords[i] + (int)stickers[i]->height();
            if (sticker_left_edge < image_left_border) {
                image_left_border = sticker_left_edge;
                image_left_adjustment = std::abs(image_left_border);
            }
            if (sticker_top_edge < image_top_border) {
                image_top_border = sticker_top_edge;
                image_top_adjustment = std::abs(image_top_border);
            }
            if (sticker_right_edge > image_right_border) {
                image_right_border = sticker_right_edge;
            }
            if (sticker_bottom_edge > image_bottom_border) {
                image_bottom_border = sticker_bottom_edge;
            }
        }
    }

    Image final = Image(picture_);
    final.resize(image_left_adjustment + image_right_border, 
                image_top_adjustment + image_bottom_border);
    
    for (unsigned int a = 0; a < image_width; a++) {
        for (unsigned int b = 0; b < image_height; b++) {
            final.getPixel(a + image_left_adjustment, b + image_top_adjustment) = 
            picture_.getPixel(a,b);
        }
    }
    for (unsigned int c = 0; c < final.width(); c++) {
        for (unsigned int d = 0; d < image_top_adjustment; d++) {
            final.getPixel(c,d) = cs225::HSLAPixel();
        }
    }
    for (unsigned int e = 0; e < image_left_adjustment; e++) {
        for (unsigned int f = 0; f < final.height(); f++) {
            final.getPixel(e,f) = cs225::HSLAPixel();
        }
    }
    for (unsigned int h = 0; h < max_; h++) {
        if (stickers[h] != NULL) {
            for (unsigned int i = 0; i < stickers[h]->width(); i++) {
                for (unsigned int j = 0; j < stickers[h]->height(); j++) {
                    if (stickers[h]->getPixel(i,j).a != 0) {
                        int x = x_coords[h] + i + image_left_adjustment;
                        int y = y_coords[h] + j + image_top_adjustment;
                        final.getPixel(x,y) = stickers[h]->getPixel(i,j);
                    }
                }
            }
        }
    }
    return final;
}

int StickerSheet::setStickerAtLayer(Image & sticker, unsigned layer, int x, int y) {
    if (layer > (max_ - 1) || layer < 0) {
        return -1;
    }
    else {
        stickers[layer] = &sticker;
        x_coords[layer] = x;
        y_coords[layer] = y;
    }
    return layer;
}

bool StickerSheet::translate(unsigned index, int x, int y) {
    if (stickers[index] == NULL || index > (max_ - 1) || index < 0) {
        return false;
    }
    else {
        x_coords[index] = x;
        y_coords[index] = y;
        return true;
    }
}
