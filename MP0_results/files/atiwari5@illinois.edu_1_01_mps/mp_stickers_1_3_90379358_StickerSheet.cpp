#include <vector>
#include "StickerSheet.h"
using namespace cs225;
using namespace std;
#include "Image.h"
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <utility>


// ------------------------------------------------------------------------------------------------
// CONSTRUCTOR
// ------------------------------------------------------------------------------------------------
StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    max_ = max;
    for (unsigned int i = 0; i < max; i++) {
        stickers_.push_back(nullptr);
        x_cord.push_back(0);
        y_cord.push_back(0);
    }
    base_ = Image(picture);
    
}

// ------------------------------------------------------------------------------------------------
// COPY CONSTRUCTOR
// ------------------------------------------------------------------------------------------------
// StickerSheet::StickerSheet (const StickerSheet &other) {}

// ------------------------------------------------------------------------------------------------
// ASSIGNMENT OPERATOR
// ------------------------------------------------------------------------------------------------
// const StickerSheet::StickerSheet & operator= (const StickerSheet &other) {}

// ------------------------------------------------------------------------------------------------
// CHANGE MAX STICKERS
// ------------------------------------------------------------------------------------------------
void StickerSheet::changeMaxStickers(unsigned max) {
    if (max == max_) {
        return;
    }
    if (max > max_) {
        int add_layer = max - max_;
        for (int i = 0; i < add_layer; i++) {
            stickers_.push_back(nullptr);
            x_cord.push_back(0);
            y_cord.push_back(0);
        }
    } else {
        stickers_.erase(stickers_.begin() + max, stickers_.end());
        x_cord.erase(x_cord.begin() + max, x_cord.end());
        y_cord.erase(y_cord.begin() + max, y_cord.end());
       
    }
    max_ = max;
}

// ------------------------------------------------------------------------------------------------
// ADD STICKER
// ------------------------------------------------------------------------------------------------
int StickerSheet::addSticker(Image &sticker, int x, int y) {
    int ret_layer = 0; 
    bool change = false;
    for (unsigned int i = 0; i < stickers_.size(); i++) {
        if (stickers_.at(i) == nullptr) {
            ret_layer = i;
            change = true;
            stickers_.at(i) = &sticker;
            x_cord.at(i) = x;
            y_cord.at(i) = y;
            break;
        }
    }
    if (change == false) {
        stickers_.push_back(&sticker);
        ret_layer = max_;
        max_++;
        x_cord.push_back(x);
        y_cord.push_back(y);
    }
    return ret_layer;
}

// ------------------------------------------------------------------------------------------------
// SET STICKER AT LAYER
// Adds a sticker to the StickerSheet at layer, so that 
// the top-left of the sticker's Image is at (x, y) on the StickerSheet.
// ------------------------------------------------------------------------------------------------
int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
    if (layer < 0 || layer >= max_) {
        return -1;
    }
    stickers_.at(layer) = &sticker;
    x_cord.at(layer) = x;
    y_cord.at(layer) = y;
    return layer;
}

// ------------------------------------------------------------------------------------------------
// LAYERS
// ------------------------------------------------------------------------------------------------
int StickerSheet::layers() const {
    return max_;
    // int count = 0;
    // for (unsigned int i = 0; i < max_; i++) {
    //     if (stickers_.at(i) == nullptr) {
    //         count++;
    //     }
    // }
    // return count;
}

// ------------------------------------------------------------------------------------------------
// REMOVE STICKER
// ------------------------------------------------------------------------------------------------
void StickerSheet::removeSticker(unsigned index) {
    if (index < 0 || index >= max_) {
        return;
    }
    stickers_.at(index) = nullptr;
    x_cord.at(index) = 0; 
    y_cord.at(index) = 0;
}


// ------------------------------------------------------------------------------------------------
// TRANSLATE
// ------------------------------------------------------------------------------------------------
bool StickerSheet::translate(unsigned index, int x, int y) {
    if (index < 0 || index >= max_) {
        return false;
    }
    if (stickers_.at(index) == nullptr) {
        return false;
    }
    x_cord.at(index) = x;
    y_cord.at(index) = y;
    return true;
}


// ------------------------------------------------------------------------------------------------
// GET STICKER
// ------------------------------------------------------------------------------------------------
Image * StickerSheet::getSticker(unsigned index) {
    if (index < 0 || index >= max_) {
        return nullptr;
    }
    if (stickers_.at(index) != nullptr) {
        Image* ret_image = const_cast<Image*>(stickers_.at(index));
        return ret_image;
    } else {
        return nullptr;
    }
}

// ------------------------------------------------------------------------------------------------
// RENDER
// ------------------------------------------------------------------------------------------------
Image StickerSheet::render() const {
    // storing the Base image's dimensions

    int min_x = 0;
    int max_x = base_.width();
    int min_y = 0;
    int max_y = base_.height();
    // FIX RESIZE
    
    // Finding the min, max x and y values
    for (unsigned int each_stkr = 0; each_stkr < stickers_.size(); each_stkr++) {
        if (stickers_.at(each_stkr) != nullptr) {
            if ((x_cord.at(each_stkr) < min_x) && (x_cord.at(each_stkr) < 0)) {
                min_x = x_cord.at(each_stkr);
            }
            int current_xmax = x_cord.at(each_stkr) + stickers_.at(each_stkr)->width();
            if (current_xmax > max_x) {
                max_x = current_xmax;
            }
            if ((y_cord.at(each_stkr) < min_y) && (y_cord.at(each_stkr) < 0)) {
                min_y = y_cord.at(each_stkr);
            }
            int current_ymax = y_cord.at(each_stkr)+ stickers_.at(each_stkr)->height();
            if (current_ymax > max_y) {
                max_y = current_ymax;
            }
        }
    }
    // Calculating final width and height of new Image and creating:
    unsigned int new_width = max_x - min_x;
    unsigned int new_height = max_y - min_y;
    if ((new_width) < 0) {
       new_width *= -1;
    }
    if ((new_height) < 0) {
       new_height *= -1;
    }
    Image return_image = Image(new_width, new_height);
    // Absolute value function:
    unsigned int abs_min_x = min_x;
    unsigned int abs_min_y = min_y;
    if (min_x < 0) abs_min_x *= -1;
    if (min_y < 0) abs_min_y *= -1;
    // unsigned int base_x = 0;
    // unsigned int base_y = 0; 
    // Layering the base image onto the return_image
 

    for (unsigned int w = abs_min_x; w < abs_min_x + base_.width(); w++) {
        for (unsigned int h = abs_min_y; h < abs_min_y + base_.height(); h++) {
            return_image.getPixel(w, h) = base_.getPixel(w - abs_min_x, h - abs_min_y);
        }
    }

    // Layering the rest of the stickers onto the return_image
    for (unsigned int each_stkr = 0; each_stkr < stickers_.size(); each_stkr++) { // each sticker
        if (stickers_.at(each_stkr) != nullptr) {
            for (unsigned int w = 0; w < stickers_.at(each_stkr)->width(); w++) { // each sticker's width
                for (unsigned int h = 0; h < stickers_.at(each_stkr)->height(); h++) { // each sticker's height
                    if (stickers_.at(each_stkr)->getPixel(w, h).a != 0) { // checking alpha pixel
                        return_image.getPixel((x_cord.at(each_stkr) + w) - min_x, (y_cord.at(each_stkr) + h) - min_y) = 
                        stickers_.at(each_stkr)->getPixel(w, h);
                    }
                }
            }
        }
    }
    
    return return_image;
}
