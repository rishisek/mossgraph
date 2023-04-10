#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"

#include <iostream>

using namespace cs225;

StickerSheet::StickerSheet(const Image & picture, unsigned max) {
    max_ = max;
    sticker_count = 0;
    stickers = new Image * [max];
    xcoords = new unsigned[max];
    ycoords = new unsigned[max];
    base = new Image(picture);
    xcoords[0] = 0;
    ycoords[0] = 0;
}

StickerSheet::StickerSheet(const StickerSheet & other) {
    copy(other);
}

void StickerSheet::copy(const StickerSheet & other) {
    max_ = other.max_;
    base = new Image(*(other.base));
    sticker_count = other.sticker_count;
    stickers = new Image * [max_];
    xcoords = new unsigned[max_];
    ycoords = new unsigned[max_];
    for (unsigned i = 0; i < sticker_count; i++) {
        stickers[i] = new Image();
        *(stickers[i]) = *(other.stickers[i]);
        xcoords[i] = other.xcoords[i];
        ycoords[i] = other.ycoords[i];
    }
}

void StickerSheet::clear() {
    for (unsigned i = 0; i < sticker_count; i++) {
        delete stickers[i];
        stickers[i] = NULL;
    }
    delete[] stickers;
    delete base;
    delete[] xcoords;
    delete[] ycoords;

}

int StickerSheet::addSticker(Image & sticker, int x, int y) {
    for (unsigned i = 0; i < max_; i++) {
        if (i == sticker_count) {
            stickers[i] = new Image(sticker);
            xcoords[i] = x;
            ycoords[i] = y;
            sticker_count++;
            return int(i);
        }
    }
    changeMaxStickers(max_ + 1);
    return addSticker(sticker, x, y);
}

void StickerSheet::changeMaxStickers(unsigned max) {
    Image ** temp_s = new Image * [sticker_count];
    unsigned * temp_xc = new unsigned[sticker_count];
    unsigned * temp_yc = new unsigned[sticker_count];
    for (unsigned i = 0; i < sticker_count; i++) {
        temp_s[i] = stickers[i];
        temp_xc[i] = xcoords[i];
        temp_yc[i] = ycoords[i];
    }

    delete[] stickers;
    delete xcoords;
    delete ycoords;
    stickers = new Image * [max];
    xcoords = new unsigned[max];
    ycoords = new unsigned[max];

    if (max < sticker_count) {
        for (unsigned i = max; i < sticker_count; i++) {
            delete temp_s[i];
            temp_s[i] = NULL;
        }
        sticker_count = max;
    } 

    for (unsigned i = 0; i < sticker_count; i++) {
        stickers[i] = temp_s[i];
        xcoords[i] = temp_xc[i];
        ycoords[i] = temp_yc[i];
    }

    max_ = max;
    delete[] temp_s;
    delete[] temp_xc;
    delete[] temp_yc;
}

Image * StickerSheet::getSticker(unsigned index) {
    if (index >= sticker_count) {
        return NULL;
    }
    return stickers[index];
}

int StickerSheet::layers() const {
    return max_ - sticker_count;
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other) {
    if (this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

void StickerSheet::removeSticker(unsigned index) {
    delete stickers[index];
    for (unsigned i = index; i < max_ - 1; i++) {
        stickers[i] = stickers[i + 1];
        xcoords[i] = xcoords[i + 1];
        ycoords[i] = ycoords[i + 1];
    }
    stickers[max_ - 1] = NULL;
    xcoords[max_ - 1] = 0;
    ycoords[max_ - 1] = 0;
    sticker_count--;
}

Image StickerSheet::render() const {
    Image result(*base);
    for (unsigned i = 0; i < sticker_count; i++) {
        unsigned currw = stickers[i]->width();
        unsigned currh = stickers[i]->height();
        if ((currw + xcoords[i]) > result.width()) {
            result.resize(currw + xcoords[i], result.height());
        }
        if ((currh + ycoords[i]) > result.height()) {
            result.resize(result.width(), currh + ycoords[i]);
        }

        for (unsigned w = 0; w < currw; w++) {
            for (unsigned h = 0; h < currh; h++) {
                HSLAPixel & curr_result = result.getPixel(w + xcoords[i], h + ycoords[i]);
                HSLAPixel & curr_ = stickers[i]->getPixel(w, h);
                if (curr_.a != 0) {
                    curr_result = curr_;
                }
            }
        }
    }
    return result;
}

int StickerSheet::setStickerAtLayer(Image & sticker, unsigned layer, int x, int y) {
    if (layer >= sticker_count) {
        return -1;
    }
    stickers[layer] = new Image(sticker);
    xcoords[layer] = x;
    ycoords[layer] = y;
    return layer;
}

bool StickerSheet::translate(unsigned index, int x, int y) {
    if (index < sticker_count && stickers[index] != NULL) {
        xcoords[index] = x;
        ycoords[index] = y;
        return true;
    }
    return false;
}