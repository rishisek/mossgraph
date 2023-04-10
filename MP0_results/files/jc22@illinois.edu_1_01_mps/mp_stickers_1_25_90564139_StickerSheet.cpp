#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"

#include <iostream>
#include "StickerSheet.h"

using namespace std;
   
StickerSheet::StickerSheet(const Image & picture, unsigned max) {
    base_image_ = picture; 
    max_ = max; 
    Xcoord.resize(max);
    Ycoord.resize(max); 
    sticker_.resize(max); 
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    base_image_ = other.base_image_; 
    max_ = other.max_; 
    Xcoord = other.Xcoord; 
    Ycoord = other.Ycoord; 
    sticker_ = other.sticker_; 
}

const StickerSheet& StickerSheet::operator=(const StickerSheet & other){
    if (this == &other) {
        return *this;
    } else {
        base_image_ = other.base_image_; 
        max_ = other.max_; 
        Xcoord = other.Xcoord; 
        Ycoord = other.Ycoord; 
        sticker_ = other.sticker_; 

        return *this;
    }
}

void StickerSheet::changeMaxStickers(unsigned max){
    max_ = max; 
    Xcoord.resize(max); 
    Ycoord.resize(max); 
    for (unsigned int i = 0; i < sticker_.size(); i++) {
        if (sticker_[i] == nullptr) {
            sticker_[i] = nullptr; 
        }
    }
    sticker_.resize(max); 
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y){
    for (unsigned int i = 0; i < sticker_.size(); i++) {
        if (sticker_[i] == nullptr) {
            Xcoord[i] = x; 
            Ycoord[i] = y; 
            sticker_[i] = &sticker; 
            return i; 
        }
    }
    max_ += 1; 
    sticker_.push_back(&sticker); 
    Xcoord.push_back(x); 
    Ycoord.push_back(y); 
    return sticker_.size() - 1; 
}


bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
    if (index >= sticker_.size() || sticker_[index]== nullptr) {
        return false; 
    }

    Xcoord[index] = x;
    Ycoord[index] = y;
    return true;
}

void StickerSheet::removeSticker(unsigned index){
    if (!(index >= sticker_.size())){
        if (sticker_[index] != nullptr) {
            sticker_[index] = nullptr; 
        }
        Xcoord[index] = 0; 
        Ycoord[index] = 0;
    }
}

Image * StickerSheet::getSticker(unsigned index) {
    if (index >= sticker_.size() || sticker_[index] == nullptr) {
        return NULL;
    }
    return sticker_[index];
}

Image StickerSheet::render() const {
    int max_x = int(base_image_.width());
    int max_y = int(base_image_.height());
    int min_x = 0;
    int min_y = 0;

    for (unsigned int i = 0; i < sticker_.size(); i++) {
        if (sticker_[i] == nullptr) {
            continue;
        }
        Image * temp = sticker_[i];

        if ((Xcoord[i] + int(temp->width())) > max_x) {
            max_x = Xcoord[i] + int(temp->width());
        }
        
        if (Ycoord[i] + int(temp->height()) > max_y) {
            max_y = Ycoord[i] + int(temp->height());
        }
        
        if (Xcoord[i] < min_x) {
            min_x = Xcoord[i];
        }
        
        if (Ycoord[i] < min_y) {
            min_y = Ycoord[i];
        }
    }
    unsigned int width_ = max_x + abs(min_x);
    unsigned int height_ = max_y + abs(min_y);
    Image image;
    image.resize(width_, height_);

    for (unsigned int i = 0; i < base_image_.width(); i++) {
        for (unsigned int j = 0; j < base_image_.height(); j++) {
            int curr_x = i + abs(min_x); 
            int curr_y = j + abs(min_y); 
            image.getPixel(curr_x, curr_y) = base_image_.getPixel(i,j);
        }
    }

    for (unsigned int i = 0; i < sticker_.size(); i++) {
        if (sticker_[i] == nullptr) {
            continue;
        }
        Image * curr_sticker = sticker_[i];
        int curr_x = Xcoord[i] + abs(min_x); 
        int curr_y = Ycoord[i] + abs(min_y); 

        for (unsigned int x = 0; x < curr_sticker->width(); x++) {
            for (unsigned int y = 0; y < curr_sticker->height(); y++) {
                if (curr_sticker->getPixel(x, y).a != 0) {
                    image.getPixel(x + curr_x, y + curr_y) = curr_sticker->getPixel(x, y);
                }
            }
        }

    }
    return image;
}

int StickerSheet::setStickerAtLayer(Image& sticker, unsigned layer, int x, int y) {
     if (!(layer >= sticker_.size())) {
        sticker_[layer] = &sticker;
        Xcoord[layer] = x;
        Ycoord[layer] = y;
        return layer; 
    }
    return -1;
}

int StickerSheet::layers() const {
    return max_;
}

