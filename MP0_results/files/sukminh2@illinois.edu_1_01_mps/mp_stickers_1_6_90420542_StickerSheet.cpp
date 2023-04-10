#include "StickerSheet.h"

void StickerSheet::_copy(const StickerSheet &that) {
    base_.resize(that.base_.width(), that.base_.height());
    /*for(unsigned int i=0; i<that.base_.width(); i++)
    {
        for(unsigned int j=0; j<that.base_.height(); j++)
        {
            base_.getPixel(i,j) = that.base_.getPixel(i,j);
        }
    }*/
    base_ = that.base_;
    
    // Insert elements from that.stickers_, that.xcoor_, and that.ycoor_ into stickers_, xcoor_, and ycoor_ vectors
    stickers_.insert(stickers_.end(), that.stickers_.begin(), that.stickers_.end());
    xcoor.insert(xcoor.end(), that.xcoor.begin(), that.xcoor.end());
    ycoor.insert(ycoor.end(), that.ycoor.begin(), that.ycoor.end());

    // Copy max_ 
    max_ = that.max_;
}

StickerSheet::StickerSheet(const Image &p, unsigned m) {
    base_.resize(p.width(), p.height());
    for(unsigned int i=0; i<p.width(); i++)
    {
        for(unsigned int j=0; j<p.height(); j++)
        {
            base_.getPixel(i,j) = p.getPixel(i,j);
        }
    }
    max_ = m;
}

StickerSheet::StickerSheet(const StickerSheet & other) {
    _copy(other);
}

const StickerSheet & StickerSheet::operator= (const StickerSheet &other) {
    _copy(other);
    return *this;
}

void StickerSheet::changeMaxStickers (unsigned omax) {
    if(omax < stickers_.size()) {
        stickers_.erase(stickers_.begin()+omax, stickers_.end());
        xcoor.erase(xcoor.begin()+omax, xcoor.end());
        ycoor.erase(ycoor.begin()+omax, ycoor.end());
        for(unsigned int i=omax; i<stickers_.size(); i++) {
            delete stickers_[i];
        }
    }
    max_ = omax;
}

int StickerSheet::addSticker (Image &sticker, int x, int y) {
    for(unsigned int i=0; i<stickers_.size(); i++) {
        if(stickers_[i]==NULL)
        {
            stickers_[i] = &sticker;
            xcoor[i] = x;
            ycoor[i] = y;
            return i;
        }
    }
    xcoor.push_back(x);
    ycoor.push_back(y);
    stickers_.push_back(&sticker);
    if(stickers_.size() > max_) {
        max_ = stickers_.size();
        return max_-1;
    }
    return stickers_.size()-1;
}

int StickerSheet::setStickerAtLayer (Image &sticker, unsigned layer, int x, int y) {
    if(layer > max_-1) {
        return -1;
    }
    xcoor[layer] = x;
    ycoor[layer] = y;
    stickers_[layer] = &sticker; 
    return layer;
}

bool StickerSheet::translate (unsigned index, int x, int y) {
    if(index > stickers_.size()-1) {
        return false;
    }
    xcoor[index] = x;
    ycoor[index] = y;
    return true;
}

void StickerSheet::removeSticker (unsigned index) {
    if (index >= 0 && index < stickers_.size()) {
        stickers_[index] = NULL;
        xcoor[index] = 0;
        ycoor[index] = 0;
    }
}

Image * StickerSheet::getSticker (unsigned index) {
    if(index+1 > stickers_.size()) {
        return NULL;
    }
    return stickers_[index];
}

int StickerSheet::layers () const {
    return max_;
}

Image StickerSheet::render () const {
    int leftx = 0;
    int rightx = (signed)(base_.width());
    int topy = 0;
    int boty = (signed)(base_.height());
    for(unsigned int i=0; i<stickers_.size(); i++) {
        if(stickers_[i]!=NULL){
            if(leftx>xcoor[i]) {
                leftx = xcoor[i];
            }
            if(rightx<(signed)(xcoor[i]+stickers_[i]->width())) {
                rightx = xcoor[i]+stickers_[i]->width();
            }
            if(topy>ycoor[i]) {
                topy = ycoor[i];
            }
            if(boty<(signed)(ycoor[i]+stickers_[i]->height())) {
                boty = ycoor[i]+stickers_[i]->height();
            }
        }
    }
    Image* result = new Image((signed)(rightx - leftx), (signed)(boty - topy));
    for(unsigned int i=0; i<base_.width(); i++) {
        for(unsigned int j=0; j<base_.height(); j++) {
            result->getPixel((signed)(i-leftx),(signed)(j-topy)) = base_.getPixel(i,j);
        }
    }
    for(unsigned int i=0; i<stickers_.size(); i++) {
        if(stickers_[i] != NULL) {
            for(unsigned int x=0; x<stickers_[i]->width(); x++) {
                for(unsigned int y=0; y<stickers_[i]->height(); y++) {
                    if(stickers_[i]->getPixel(x,y).a != 0) {
                        result->getPixel((signed)(xcoor[i]+x-leftx), (signed)(ycoor[i]+(signed)y-topy)) = stickers_[i]->getPixel(x,y);
                    }
                }
            }
        }
    }
    Image tmp = *result;
    delete result;
    return tmp;
}