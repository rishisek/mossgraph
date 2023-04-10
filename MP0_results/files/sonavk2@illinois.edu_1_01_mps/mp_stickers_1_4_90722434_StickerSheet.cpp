#include "Image.h"
#include <iostream>
#include <cmath>
#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    base_ = new Image(picture);
    max_ = max;
}

StickerSheet::~StickerSheet() {
    delete base_;
    stickers_.clear();
    xCoord.clear();
    yCoord.clear();
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    max_ = other.max_;
    base_ = new Image(*other.base_);
    stickers_.resize(other.stickers_.size());
    xCoord.resize(other.xCoord.size());
    yCoord.resize(other.yCoord.size());
    for (unsigned int i = 0 ; i < other.stickers_.size(); i++) {
        stickers_[i] = other.stickers_[i];
        xCoord[i] = other.xCoord[i];
        yCoord[i] = other.yCoord[i];
    }
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other) {
    if (this == &other) {
       return *this;
    }
    delete base_;
    stickers_.clear();
    xCoord.clear();
    yCoord.clear();
    max_ = other.max_;
    base_ = new Image(*(other.base_));

    stickers_.resize(other.stickers_.size());
    xCoord.resize(other.xCoord.size());
    yCoord.resize(other.yCoord.size());
        for (unsigned int i =0; i < stickers_.size(); i++) {
            stickers_[i] = other.stickers_[i];
            xCoord[i] = other.xCoord[i];
            yCoord[i] = other.yCoord[i];
        }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    if (max == max_) {
        return;
    } else if (max < stickers_.size()) {
        stickers_.resize(max);
        xCoord.resize(max);
        yCoord.resize(max);
    }
    max_ = max;
}

int StickerSheet::addSticker(Image &sticker, int x, int y) {
    stickers_.push_back(&sticker);
    xCoord.push_back(x);
    yCoord.push_back(y);
    if (stickers_.size() > max_) {
        max_++;
    }
    return stickers_.size() -1;
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
    if (layer >= max_ || layer < 0) {
        return -1;
    }

    stickers_[layer] = &sticker;
    xCoord[layer] = x;
    yCoord[layer] = y;

    return layer;

}

bool StickerSheet::translate(unsigned index, int x, int y) {
    if (index >= stickers_.size() || stickers_[index] == NULL || index < 0) {
        return false;
    } else {
        xCoord[index] = x;
        yCoord[index] = y;
        return true;
    }
}

void StickerSheet::removeSticker(unsigned index) {
    if (index >= stickers_.size()) {
        return;
    }
    xCoord.erase(xCoord.begin() + index);
    yCoord.erase(yCoord.begin() + index);

    stickers_.erase(stickers_.begin() + index);
}

Image* StickerSheet::getSticker(unsigned index) {
    if (index >= stickers_.size() || stickers_[index] == NULL || index < 0) {
        return NULL;
    }
    return stickers_[index];
}

int StickerSheet::layers() const {
    return max_;
}

Image StickerSheet::render() const {
    unsigned int maxPosX = base_->width();
    unsigned int maxPosY = base_->height();
    int maxNegX = 0;
    int maxNegY = 0;
    for (unsigned int i = 0; i < stickers_.size(); i++) {
        if ((xCoord[i] + stickers_[i]->width()) >= maxPosX) {
            maxPosX = stickers_[i]->width() + xCoord[i];
        }
        if ((yCoord[i] + stickers_[i]->height()) >= maxPosY) {
            maxPosY = stickers_[i]->height() + yCoord[i];
        }
        if (xCoord[i] <= maxNegX) {
            maxNegX = xCoord[i];
        }
        if (yCoord[i] <= maxNegY) {
            maxNegY = yCoord[i];
        }
    }
    Image output(*base_);
    output.resize(maxPosX + abs(maxNegX), maxPosY + abs(maxNegY));

    // for (unsigned int i = 0; i < base_->width(); i++) {
    //     for (unsigned int j = 0; j < base_->height(); j++) {
    //         output.getPixel(i + abs(maxNegX), j + abs(maxNegY)) = base_->getPixel(i,j);      
    //     }
    // }

    for (unsigned int i = 0; i < stickers_.size(); i++) {
        if (stickers_[i] == nullptr) {
            continue;
        }
        int x = xCoord[i];
        int y = yCoord[i];
        for (unsigned int j = 0; j < stickers_[i]->width(); j++) {
            for (unsigned int k = 0; k < stickers_[i]->height(); k++) {    
                cs225::HSLAPixel &resultingPixel = output.getPixel(x + j + abs(maxNegX), y + k + abs(maxNegY));
                cs225::HSLAPixel &stickerPixel = stickers_[i]->getPixel(j,k);
                if (stickerPixel.a != 0) {
                    resultingPixel = stickerPixel;
                }  
            }
        }     
    }
    return output;
} 

