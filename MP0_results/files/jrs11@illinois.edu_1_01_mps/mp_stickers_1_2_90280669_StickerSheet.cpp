#include "StickerSheet.h"
using namespace cs225;

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    max_ = max;
    Image base = Image(picture);
    backdrop_ = base;
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    max_ = other.max_;
    backdrop_ = other.backdrop_;
    coordinates_ = other.coordinates_;
    stickers_ = other.stickers_;
}

const StickerSheet& StickerSheet::operator= (const StickerSheet &other) {
    if (this == &other) {
        return *this;
    }

    max_ = other.max_;
    backdrop_ = other.backdrop_;
    coordinates_ = other.coordinates_;
    stickers_ = other.stickers_;

    return *this;
}

void StickerSheet::changeMaxStickers (unsigned max) {
    if (max < stickers_.size()) {
        while (stickers_.size() > max) {
            stickers_.pop_back();
            coordinates_.pop_back();
        }
    }
    max_ = max;
}

int StickerSheet::addSticker(Image &sticker, int x, int y) {
    stickers_.push_back(&sticker);
    coordinates_.push_back(std::make_pair(x,y));
    if (int(stickers_.size()) > max_) {
        max_ = stickers_.size();
    }
    return(stickers_.size() - 1);
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
    if (int(layer) >= max_) {
        return -1;
    }
    //delete stickers_.at(layer);
    
    stickers_.at(layer) = &sticker;
    coordinates_.at(layer) = std::make_pair(x,y);
    return layer;
}

bool StickerSheet::translate (unsigned index, int x, int y) {
    if (index >= stickers_.size()) {
        return false;
    }
    coordinates_.at(index) = std::make_pair(x,y);
    return true;
}

void StickerSheet::removeSticker(unsigned index) {
    stickers_.erase(stickers_.begin() + index);
    coordinates_.erase(coordinates_.begin() + index);
}

Image *	StickerSheet::getSticker (unsigned index) {
    if (index >= stickers_.size()) {
        return NULL;
    }
    return stickers_.at(index);
}

int StickerSheet::layers() const {
    return(max_);
}

Image StickerSheet::render () const { //right now this is written without accounting for out of bounds
    Image sheet = Image(backdrop_);
    int most_leftward = 0;
    int most_upward = 0;
    for (int current_sticker = 0; current_sticker < int(stickers_.size()); current_sticker++) {
        // see if boundary needs expanding, and adjust first   
        //find how much to shift
        if (coordinates_.at(current_sticker).first < most_leftward) { //if x coord is most negative 
            most_leftward = coordinates_.at(current_sticker).first; 
        }
        if (coordinates_.at(current_sticker).second < most_upward) { //if y coord is negative
            most_upward = coordinates_.at(current_sticker).second;  
        }
    }
    //then resize
    sheet.resize(sheet.width() + (-1)*most_leftward, sheet.height());
    sheet.resize(sheet.width(), sheet.height() + (-1)*most_upward);

    // now make canvas white
    for (unsigned int x = 0; x < sheet.width(); x++) {
        for (unsigned int y = 0; y < sheet.height(); y++) {
            sheet.getPixel(x, y).l = 1;
        }
    }  

    // now adjust picture
    for (unsigned int x = 0; x < backdrop_.width(); x++) {
        for (unsigned int y = 0; y < backdrop_.height(); y++) {
            sheet.getPixel(x - most_leftward, y - most_upward) = backdrop_.getPixel(x, y);
        }
    }  

    for (int current_sticker = 0; current_sticker < int(stickers_.size()); current_sticker++) {
        int additional_x = coordinates_.at(current_sticker).first - most_leftward;
        int additional_y = coordinates_.at(current_sticker).second - most_upward;
        
        if ((additional_x + stickers_.at(current_sticker)->width()) > sheet.width()) {
            sheet.resize(additional_x + stickers_.at(current_sticker)->width(), sheet.height());
        }
        if ((additional_y + stickers_.at(current_sticker)->height()) > sheet.height()) {
            sheet.resize(sheet.width(), additional_y + stickers_.at(current_sticker)->height());
        }

        for (unsigned int x = 0; x < stickers_.at(current_sticker)->width(); x++) {
            for (unsigned int y = 0; y < stickers_.at(current_sticker)->height(); y++) {
                if (stickers_.at(current_sticker)->getPixel(x,y).a != 0) {
                    sheet.getPixel(x + additional_x, y + additional_y) = stickers_.at(current_sticker)->getPixel(x,y);
                }
                
            }
        } 
    }
    
    
    return sheet;
}
