#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    base_ = picture;
    max_ = max;
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    Copy(other);
}

StickerSheet::~StickerSheet() {
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other) {
    if (this != &other) {
        for (unsigned int i = 0; i < other.stickers_.size(); i++) {
        stickers_.push_back(other.stickers_.at(i));
        }
        base_ = other.base_;
        max_ = other.max_;
    }
    return *this;
}

void StickerSheet::Copy(const StickerSheet &other) {
    for (unsigned int i = 0; i < other.stickers_.size(); i++) {
        stickers_.push_back(other.stickers_.at(i));
    }
    base_ = other.base_;
    max_ = other.max_;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    while (max_ > max) {
        max_--;
        removeSticker(max_);
    }
    max_ = max;
}

int StickerSheet::addSticker(Image &sticker, int x, int y) {
    if (stickers_.size() >= max_) {
        max_++;
    }
    stickers_.push_back({&sticker, x, y});
    return stickers_.size() - 1;
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
    if (layer >= max_) {
        return -1;
    }

    stickers_.at(layer) = {&sticker, x, y};
    return layer;
}

bool StickerSheet::translate(unsigned index, int x, int y) {
    if (index >= stickers_.size()) {
        return false;
    }
    stickers_.at(index).x = x;
    stickers_.at(index).y = y;
    return true;
}

void StickerSheet::removeSticker(unsigned index) {
    if (index >= stickers_.size()) return;
    stickers_.erase(stickers_.begin() + index);
}

Image* StickerSheet::getSticker(unsigned index) {
    if (index >= stickers_.size()) {
        return NULL;
    } 
    return stickers_.at(index).image;
}

int StickerSheet::layers() const {
    return max_;
}

Image StickerSheet::render() const {
    Image rendered = Image(base_.width(), base_.height());
    int negX = 0;
    int negY = 0;
    for (Sticker sticker : stickers_) {
        if (sticker.x < negX) {
            negX = sticker.x;
        }
        if (sticker.y < negY) {
            negY = sticker.y;
        }
    }

    int newW = base_.width() - negX;
    int newH = base_.height() - negY;
    rendered.resize(newW, newH);

    for (unsigned int i = 0; i < base_.width(); i++) {
        for (unsigned int j = 0; j < base_.height(); j++) {
            HSLAPixel &p = rendered.getPixel(i - negX, j - negY);
            p = base_.getPixel(i, j);
        }
    }

    for (unsigned int i = 0; i < stickers_.size(); i++) {
        for (unsigned int x = 0; x < stickers_.at(i).image ->width(); x++) {
            for (unsigned int y = 0; y < stickers_.at(i).image ->height(); y++) {
                HSLAPixel &bp = rendered.getPixel(x + stickers_.at(i).x - negX, y + stickers_.at(i).y - negY);
                HSLAPixel &sp = stickers_.at(i).image->getPixel(x, y);
                if (sp.a != 0) {
                    bp = sp;
                }
            }
        }
    }
    return rendered;
}