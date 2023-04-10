#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    maxLayers_ = max;
    stickers_.resize(max);
    locations_.resize(max);

    baseImage_ = Image(picture);

    // leftMostPixel_ = 0;
    // rightMostPixel_ = picture.width();
    // topMostPixel_ = 0;
    // bottomMostPixel_ = picture.height();
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    copy(other);
}

const StickerSheet & StickerSheet::operator=(const StickerSheet &other) {
    if (this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

void StickerSheet::copy(const StickerSheet &other) {
    maxLayers_ = other.maxLayers_;
    baseImage_ = Image(other.baseImage_);

    changeMaxStickers(other.maxLayers_);
    for (unsigned int i = 0; i < other.stickers_.size(); ++i) {
        stickers_[i] = other.stickers_[i];
        locations_[i].first = other.locations_[i].first;
        locations_[i].second = other.locations_[i].second;
    }

    // leftMostPixel_ = other.leftMostPixel();
    // rightMostPixel_ = other.rightMostPixel();
    // topMostPixel_ = other.topMostPixel();
    // bottomMostPixel_ = other.bottomMostPixel();
}

void StickerSheet::clear() {
    for (unsigned int i = 0; i < maxLayers_; ++i) {
        delete stickers_[i];
    }
}

void StickerSheet::changeMaxStickers(unsigned max) {
    stickers_.resize(max);
    locations_.resize(max);
    maxLayers_ = max;
}

int StickerSheet::addSticker(Image &sticker, int x, int y) {
    unsigned int index = maxLayers_;
    for (unsigned int i = 0; i < stickers_.size(); ++i) {
        if (stickers_.at(i) == NULL) {
            index = i;
            break;
        }
    }

    // if all full
    if (index == maxLayers_) {
        changeMaxStickers(maxLayers_ + 1);
    }

    stickers_[index] = &sticker;
    locations_[index] = std::make_pair(x, y);       

    // // store indicies
    // if (x < leftMostPixel_) {
    //     leftMostPixel_ = x;
    // }
    // if (x + (int)sticker.width() > rightMostPixel_) {
    //     rightMostPixel_ = x + sticker.width();
    // }
    // if (y < topMostPixel_) {
    //     topMostPixel_ = y;
    // }
    // if (y + (int)sticker.height() > bottomMostPixel_) {
    //     bottomMostPixel_ = y + sticker.height();
    // }
    return index;
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
    if (layer >= maxLayers_) {
        return -1;
    }

    stickers_[layer] = &sticker;
    locations_[layer] = std::make_pair(x, y);

    // // store indicies
    // if (x < leftMostPixel_) {
    //     leftMostPixel_ = x;
    // }
    // if (x > rightMostPixel_) {
    //     rightMostPixel_ = x;
    // }
    // if (y < topMostPixel_) {
    //     topMostPixel_ = y;
    // }
    // if (y > bottomMostPixel_) {
    //     bottomMostPixel_ = y;
    // }
    return layer;
}

// TEST
bool StickerSheet::translate(unsigned index, int x, int y) {
    if (stickers_[index] == NULL || index >= maxLayers_) {
        return false;
    }
    locations_[index].first = x;
    locations_[index].second = y;
    return true;
}

void StickerSheet::removeSticker(unsigned index) {
    stickers_.erase(stickers_.begin() + index);
    stickers_.insert(stickers_.begin() + index, NULL);

    locations_.erase(locations_.begin() + index);

    locations_.insert(locations_.begin() + index, std::make_pair(0, 0));
}

Image * StickerSheet::getSticker(unsigned index) {
    if (index >= maxLayers_) {
        return NULL;
    }
    return stickers_[index];
}

int StickerSheet::layers() const {
    return maxLayers_;
}

Image StickerSheet::render() const {
    // Calculate dimensions
    int leftMostPixel = 0;
    int rightMostPixel = baseImage_.width();
    int topMostPixel = 0;
    int bottomMostPixel = baseImage_.height();

    for (unsigned int i = 0; i < stickers_.size(); ++i) {
        if (stickers_[i] != NULL) {
            if (locations_[i].first < leftMostPixel) {
                leftMostPixel = locations_[i].first;
            }
            if (locations_[i].first + (int)stickers_[i]->width() > rightMostPixel) {
                rightMostPixel = locations_[i].first + stickers_[i]->width();
            }
            if (locations_[i].second < topMostPixel) {
                topMostPixel = locations_[i].second;
            }
            if (locations_[i].second + (int)stickers_[i]->height() > bottomMostPixel) {
                bottomMostPixel = locations_[i].second + stickers_[i]->height();
            }
        }
    }

    int maxWidth = rightMostPixel - leftMostPixel;
    int maxHeight = bottomMostPixel - topMostPixel;
    Image img = Image(maxWidth, maxHeight);

    for (unsigned int x = 0; x < baseImage_.width(); ++x) {
        for (unsigned int y = 0; y < baseImage_.height(); ++y) {
            cs225::HSLAPixel pixel = baseImage_.getPixel(x, y);
            img.getPixel(x + abs(leftMostPixel), y + abs(topMostPixel)) = pixel;
        }
    }

    for (unsigned int i = 0; i < stickers_.size(); ++i) {
        if (stickers_[i] != NULL) {
            for (unsigned int x = 0; x < stickers_[i]->width(); ++x) {
                for (unsigned int y = 0; y < stickers_[i]->height(); ++y) {
                    cs225::HSLAPixel pixel = stickers_[i]->getPixel(x, y);
                    if (pixel.a != 0) {
                        img.getPixel(x + abs(leftMostPixel) + locations_[i].first, y + abs(topMostPixel) + locations_[i].second) = pixel;
                    }
                }
            }
        }
    }
    return img;
}