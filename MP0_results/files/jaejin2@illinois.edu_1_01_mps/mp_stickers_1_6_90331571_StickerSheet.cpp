#include "StickerSheet.h"
#include <cstdlib>

StickerSheet::StickerSheet(const Image & picture, unsigned max){
    base_ = picture;
    changeMaxStickers(max);
}

StickerSheet::StickerSheet(const StickerSheet& other){
    base_ = other.base_;
    changeMaxStickers(other.max_);
    sticker_ = other.sticker_;
    x_ = other.x_;
    y_ = other.y_;
}

int StickerSheet::addSticker(Image& sticker, int x, int y){
    for(unsigned i=0; i<sticker_.size(); i++){
        if(sticker_[i] == NULL){
            sticker_[i] = &sticker;
            x_[i] = x;
            y_[i] = y;
            return i;
        }
    }
    changeMaxStickers(max_ +1);
    sticker_[max_ -1] = &sticker;
    x_[max_ - 1] = x;
    y_[max_ - 1] = y;
    return max_-1;
}

void StickerSheet::changeMaxStickers(unsigned max){
    max_ = max;
    sticker_.resize(max_);
    x_.resize(max_);
    y_.resize(max_);
}

Image* StickerSheet::getSticker(unsigned index){
    if(index > max_){
        return NULL;
    }
    return sticker_[index];
}

int StickerSheet::layers() const{
    return max_;
}

const StickerSheet& StickerSheet::operator=(const StickerSheet& other){
    if(this == &other){
        return *this;
    }
    else{
        base_ = other.base_;
        changeMaxStickers(other.max_);
        sticker_ = other.sticker_;
        x_ = other.x_;
        y_ = other.y_;
    }
    return *this;
}

void StickerSheet::removeSticker(unsigned index){
    if(index<sticker_.size() && sticker_[index] != NULL){
        sticker_[index] = NULL;
        x_[index] = -1;
        y_[index] = -1;
    }
    else{
        return;
    }
}

Image StickerSheet::render() const{
    Image blank;
    int neg_x = 0;
    int neg_y = 0;
    int pos_x = base_.width();
    int pos_y = base_.height();
    for(unsigned i=0; i<sticker_.size(); i++){
        if(sticker_[i] != NULL){
            int sh = sticker_[i]->height();
            int sw = sticker_[i]->width();
            neg_x = std::min(neg_x, x_[i]);
            neg_y = std::min(neg_y, y_[i]);
            pos_x = std::max(pos_x, x_[i] + sw);
            pos_y = std::max(pos_y, y_[i] + sh);
        }
    }
    blank.resize(pos_x-neg_x, pos_y-neg_y);
    for (unsigned a = 0; a < base_.width(); a++) {
        for (unsigned b = 0; b < base_.height(); b++) {
            blank.getPixel(a-neg_x, b-neg_y) = base_.getPixel(a, b);
        }
    }
    for(unsigned j=0; j<sticker_.size(); j++){
        if(sticker_[j] != NULL){
            int shj = sticker_[j]->height();
            int swj = sticker_[j]->width();
            for (int a = 0; a < swj; a++) {
                for (int b = 0; b < shj; b++) {
                    if (sticker_[j]->getPixel(a, b).a != 0) {
                        blank.getPixel(a+x_[j]-neg_x, b+y_[j]-neg_y) = sticker_[j]->getPixel(a, b);
                    }
                }
            }
        }
    }
    return blank;
}

int StickerSheet::setStickerAtLayer(Image& sticker, unsigned layer, int x, int y){
    if(layer>=sticker_.size() || layer<0){
        return -1;
    }
    sticker_[layer] = &sticker;
    x_[layer] = x;
    y_[layer] = y;
    return layer;
}

bool StickerSheet::translate(unsigned index, int x, int y){
    if(index>max_ || sticker_[index] == NULL){
        return false;
    }
    x_[index] = x;
    y_[index] = y;
    return true;
}