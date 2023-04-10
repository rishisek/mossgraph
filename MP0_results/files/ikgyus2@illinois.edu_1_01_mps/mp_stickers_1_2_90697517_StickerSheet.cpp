#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"

#include <vector>
#include <iostream>

using namespace std;



StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    // cap = max;                    // set maximum size
    // base = new Image(picture);    // make copy
    // stickers_ = new Sticker[max]();     // create array
    max_ = max;
    origi_ = picture;
    // coord = vector<vector>;
    sticker_.resize(max);
    xval.resize(max);
    yval.resize(max);
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    max_ = other.max_;
    origi_ = other.origi_;
    sticker_ = other.sticker_;
    xval = other.xval;
    yval = other.yval;
}

StickerSheet::~StickerSheet() {
    // for (int i = 0; i < (int) sticker_.size(); i++) {
    //     delete sticker_[i];
    //     sticker_[i] = nullptr;
    // }
}



const StickerSheet & StickerSheet::operator=(const StickerSheet &other) {
    // clear();
    // max_ = other.max_;
    // for (int i = 0; i < (int) other.sticker_.size(); i++) {
    //     stickers_.push_back(new Image(*other.sticker_[i]));
    // }
    if (this == &other) {
        return *this;
    } else {
        max_ = other.max_;
        origi_ = other.origi_;
        sticker_ = other.sticker_;
        xval = other.xval;
        yval = other.yval;
        return *this;
    }
}

void StickerSheet::changeMaxStickers(unsigned max) {
    // coord.resize(max);
    max_ = max;
    xval.resize(max);
    yval.resize(max);
    for (unsigned int i = 0; i < sticker_.size(); i++) {
        if (sticker_[i] == nullptr) {
            sticker_[i] = nullptr;
        }
    }
    sticker_.resize(max);
}
// Adds a sticker to the StickerSheet, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet. 
int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
    for (unsigned int i = 0; i < sticker_.size(); i++) {
        if (sticker_[i] == nullptr) {
            // sticker_[i] = nullptr;
            xval[i] = x;
            yval[i] = y;
            sticker_[i] = &sticker;
            return -1;
        }
    }
    max_ += 1;
    sticker_.push_back(&sticker);
    xval.push_back(x);
    yval.push_back(y);
    return sticker_.size() - 1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    // Changes the x and y coordinates of the Image in the specified layer
    // if (index < 0 || index >= sticker_.size()) {
    //     return true;
    // }
    // coord =
    if (sticker_[index] == nullptr || index >= sticker_.size()) {
        return false;
    }
    xval[index] = x;
    yval[index] = y;
    return true;
}

void StickerSheet::removeSticker(unsigned index) {
    // delete stickers_[index];
    // stickers_[index] = nullptr;
    if (index < sticker_.size()) {
        if (sticker_[index] != nullptr) {
            sticker_[index] = nullptr;
        }
        xval[index] = 0;
        yval[index] = 0;
    }
}

Image * StickerSheet::getSticker(unsigned index) {
    if (sticker_[index] == nullptr || index >= sticker_.size()) {
        return NULL;
    }
    return sticker_[index];
}

Image StickerSheet::render() const {
    // setting width and height of base image
    int wid_max = (int) origi_.width();
    int hei_max = (int) origi_.height();
    int wid_min = 0;
    int hei_min = 0;
    for (unsigned int i = 0; i < sticker_.size(); i++) {
        if (int(sticker_[i]->width()) + xval[i] > wid_max) { wid_max = xval[i] + int(sticker_[i]->width()); }
        if (int(sticker_[i]->height()) + yval[i] > hei_max) { hei_max = yval[i] + int(sticker_[i]->height()); }
        // min?
        if (wid_min > xval[i]) { wid_min = xval[i]; }
        if (hei_min > yval[i]) { hei_min = yval[i]; }
    }
    unsigned int wid = wid_min + wid_max;
    unsigned int hei = hei_min + hei_max;
    Image ans(origi_);
    ans.resize(wid, hei);
    //current loc
    for (unsigned int x = 0; x < origi_.width(); x++) {
        for (unsigned int y = 0; y < origi_.width(); y++) {
            // int xloc = wid_min + x;
            // int yloc = hei_min + y;
            ans.getPixel(wid_min + x, hei_min + y) = origi_.getPixel(x, y);
        }
    }
    // putting sticker
    for (unsigned int m = 0; m < sticker_.size(); m++) {
        // if (sticker_[m])
        int temp_x = wid_min + xval[m];
        int temp_y = hei_min + yval[m];
        for (unsigned int x = 0; x < sticker_[m]->width(); x++) {
            for (unsigned int y = 0; y < sticker_[m]->height(); y++) {
                if (sticker_[m]->getPixel(x, y).a != 0) {
                    // ans.getPixel(int(xval + wid_min) + x, int(yval + hei_min) + y) = sticker_[m]->getPixel(x, y);
                    ans.getPixel(temp_x + x, temp_y + y) = sticker_[m]->getPixel(x, y);
                }
            }
        }
    }
    return ans;
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
    if (layer < sticker_.size()) {
        sticker_[layer] = &sticker;
        xval[layer] = x;
        yval[layer] = y;
        return layer;
    }
    return -1;
}

int StickerSheet::layers() const {
    return max_;
}