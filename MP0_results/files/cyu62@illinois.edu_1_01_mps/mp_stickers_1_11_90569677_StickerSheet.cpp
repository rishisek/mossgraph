#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    base_ = Image(picture);
    max_ = max;
}
StickerSheet::StickerSheet(const StickerSheet &other) {
    base_ = other.base_;
    max_ = other.max_;
    stickers_.clear();
    for (unsigned int i = 0; i < other.stickers_.size(); i++) {
        stickers_.push_back(other.stickers_.at(i));
    }
}
StickerSheet::~StickerSheet() {}


const StickerSheet & StickerSheet::operator=(const StickerSheet &other) {
    base_ = other.base_;
    max_ = other.max_;
    stickers_.clear();
    for (unsigned int i = 0; i < other.stickers_.size(); i++) {
        stickers_.push_back(other.stickers_.at(i));
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    if (stickers_.size() == max) {
        return;
    }
    if (stickers_.size() > max) {
        for (unsigned int i = max - 1; i < stickers_.size(); i++) {
            stickers_.erase(stickers_.begin() + i);
        }
    }
    max_ = max;
}
int StickerSheet::addSticker(Image &sticker, int x, int y) {
    Sticker n{&sticker, x, y};
    if (stickers_.size() != max_) {
        stickers_.push_back(n);
        return stickers_.size() - 1;
    } else {
        stickers_.push_back(n);
        max_++;
        return stickers_.size() - 1;  
    }
    
}
int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
    Sticker n{&sticker, x, y};
    for (unsigned int i = 0; i < stickers_.size(); i++) {
        if (i == layer) {
            stickers_.at(i) = n;
            return i;
        }
    }
    return -1;
}
bool StickerSheet::translate(unsigned index, int x, int y) {
    if (stickers_.size() <= index || index < 0 || stickers_.at(index).img == NULL) {
        return false;
    }
    stickers_.at(index).x = x;
    stickers_.at(index).y = y;
    return true;
}

void StickerSheet::removeSticker(unsigned index) {
    stickers_.erase(stickers_.begin() + index);
}

Image* StickerSheet::getSticker(unsigned index) {
    if (index >= stickers_.size()) {
        return NULL;
    }
    Sticker n = stickers_.at(index);
    return n.img;
}
int StickerSheet::layers() const {
    return max_;
}
Image StickerSheet::render() const {
    Image to_return(base_);
    for (unsigned int n = 0; n < stickers_.size(); n++) {
        if (stickers_.at(n).img->width() + stickers_.at(n).x > to_return.width()) {
            to_return.resize(stickers_.at(n).img->width() + stickers_.at(n).x, to_return.height());
        }
        if (stickers_.at(n).img->height() + stickers_.at(n).y > to_return.height()) {
            to_return.resize(to_return.width(), stickers_.at(n).img->height() + stickers_.at(n).y);
        }
        for (unsigned int i = 0; i < stickers_.at(n).img->width(); i++) {
            for (unsigned int j = 0; j < stickers_.at(n).img->height(); j++) {
                HSLAPixel &pixel = to_return.getPixel(i + stickers_.at(n).x , j + stickers_.at(n).y);
                const HSLAPixel &base_pixel = stickers_.at(n).img->getPixel(i, j);
                if (base_pixel.a != 0) {
                    pixel = base_pixel;
                }
            }
        }
    }
    
    return to_return;
}