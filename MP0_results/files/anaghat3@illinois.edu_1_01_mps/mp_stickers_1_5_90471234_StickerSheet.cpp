#include "StickerSheet.h"
#include <utility>
#include <vector>
#include <iostream>
#include <cmath>
//Initializes this StickerSheet with a deep copy of the base picture and the ability to hold a max number of stickers (Images) with indices 0 through max - 1. More...
StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    max_ = max;
    for (unsigned int x = 0; x < max; x++) {
        stickers.push_back(nullptr);
        location.push_back(std::make_pair(0,0));
    }
    base = Image(picture);
}


//Modifies the maximum number of stickers that can be stored on this StickerSheet without 
//changing existing stickers' indices. More...
void StickerSheet::changeMaxStickers(unsigned max) {
    if (max == max_) {return;}
    if (max >= max_) {
        // max = 5, max_=10
        for (unsigned int x = max_; x < max; x++) {
            stickers.push_back(nullptr);
            location.push_back(std::make_pair(0, 0));
        }
    } else {
            stickers.erase(stickers.begin() + max, stickers.end());
            location.erase(location.begin() + max, location.end());
        
        
    }
    max_ = max;

 }

//Adds a sticker to the StickerSheet, so that the top-left of the sticker's 
//Image is at (x, y) on the StickerSheet. lowest possible, else more layer
int StickerSheet::addSticker(Image &sticker, int x, int y) {
    int layer = -1;
    for (unsigned int x_ = 0; x_ < stickers.size(); x_++) {
        if (stickers.at(x_) == nullptr) {
            stickers.at(x_) = &sticker;
            location.at(x_).first = x;
            location.at(x_).second = y;
            layer = x_;
            return layer;
        }
    }
    stickers.push_back(&sticker);
    max_++;
    std::pair<int, int> coor= std::make_pair(x,y);
    location.push_back(coor);
    location.at(max_ -1).first = x;
    location.at(max_ - 1).second = y;
    return (max_ - 1);
        //    pairs.push_back(std::make_pair(7, 8));
}

//Adds a sticker to the StickerSheet at layer layer, so that the top-left of the 
//sticker's Image is at (x, y) on the StickerSheet. More...
int StickerSheet::setStickerAtLayer (Image &sticker, unsigned layer, int x, int y) {
    if (layer > max_ - 1) {
        return -1;
    }
    if (layer < 0) {
        return -1;
    }
    
    for (unsigned int x_ = 0; x_ < stickers.size(); x_++) {
        if (x_ == layer) {
            stickers.at(x_) = &sticker;
            location.at(x_).first = x;
            location.at(x_).second = y;
            return layer;
        }
    }
    return -1;

}

//Changes the x and y coordinates of the Image in the specified layer. More...
bool StickerSheet::translate (unsigned index, int x, int y) {
    if (index > max_ - 1) {
        return false;
    }
    if (index < 0) {
        return false;
    }
    if (stickers.at(index) != nullptr) {
        location.at(index).first = x;
        location.at(index).second = y;
        return true;
    }
    
    return false;
}

//Removes the sticker at the given zero-based layer index. More...
void StickerSheet::removeSticker (unsigned index) {
    for (unsigned int x = 0; x < stickers.size(); x++) {
        if (x == index) {
            stickers.at(x) = nullptr;
            location.at(x).first = 0;
            location.at(x).second = 0;
        }
    }
}

//Returns a pointer to the sticker at the specified index, not a copy of it. More...
Image* StickerSheet::getSticker (unsigned index) {
    if (index > max_ - 1) {
        return nullptr;
    }
    if (index < 0) {
        return nullptr;
    }
    for (unsigned int x = 0; x < stickers.size(); x++) {
        if (x == index) {
            // Image* ptr = stickers.at(x);
            if (stickers.at(x) != nullptr) {
                return const_cast<Image *> (stickers.at(x));
            }
        }
    }
    return nullptr;
}

//Returns the total number of layers available on the Stickersheet. More...
int StickerSheet::layers () const {
    return max_;
}

/*so basically that part is saying that if the pixel's alpha channel 
is 0 then dont draw that pixel because it should be transparent
//Renders the whole StickerSheet on one Image and returns that Image. More...
*/

/* The base picture is drawn first and then each sticker is drawn in order starting with layer zero 
(0), then layer one (1), and so on. If a pixel's alpha channel in a sticker is zero (0), no pixel 
is drawn for that sticker at that pixel. If the alpha channel is non-zero, a pixel is drawn. 
(Alpha blending is awesome, but not required.)
The returned image always includes the full contents of the picture and all stickers. 
It should expand in each corresponding direction if stickers go beyond the edge of the picture.
*/


Image StickerSheet::render() const {
    //Resizing image to account for stickers
    int min_x = 0;
    // + stickers.at(0)->width()
    int max_x = base.width();
    int min_y = 0;
    //+ stickers.at(0)->height()
    int max_y = base.height();
    // int max_height = base.height();
    for (unsigned int x = 0; x < stickers.size(); x++) {
        if (stickers.at(x) != nullptr) {
            // if (initialized == false) {
            //     min_x = location.at(x).first;
            //     min_y = location.at(x).second;
            //     initialized = true;
            // }
            int cmin_x = location.at(x).first;
            int cmax_x = location.at(x).first + stickers.at(x)->width();
            int cmin_y = location.at(x).second;
            int cmax_y = location.at(x).second + stickers.at(x)->height();
            if ((cmin_x < 0) && (cmin_x <= min_x)) {
                min_x = cmin_x;
            }
            if (cmax_x >= max_x) {
                max_x = cmax_x;
            }
            if ((cmin_y < 0) && (cmin_y <= min_y)) {
                min_y = cmin_y;
            }
            if (cmax_y >= max_y) {
                max_y = cmax_y;
            }
        }
    }

    int m_width = std::abs(max_x - min_x);
    int m_height = std::abs(max_y - min_y);
    unsigned int max_width = (unsigned int) (m_width);
    unsigned int max_height = (unsigned int) (m_height);
   
    Image result = Image(max_width, max_height);
    //traversing through big canvas
            
    
    for (unsigned int x = abs(min_x); x < base.width() + abs(min_x); x++) {
        for (unsigned int y = abs(min_y); y < base.height() + abs(min_y); y++) {
            //use .GetPixel() for large canvas and base image
            //SEG FAULT??
            result.getPixel(x,y) = base.getPixel(x - std::abs(min_x), y - std::abs(min_y));
        }
        //not use bx and by
    }
    //traversing through stickers
    
    for (unsigned int x = 0; x < stickers.size(); x++) {
        //seing if a sticker even exists!
        if (stickers.at(x) != nullptr) {
            //traversing through pixels of sticker image
            for (unsigned int w = 0; w < stickers.at(x)->width(); w++) {
                for (unsigned int h = 0; h < stickers.at(x)->height(); h++) {
                    //seeing if alpha value != 0 (pixel can be)
                    if (stickers.at(x)->getPixel(w,h).a != 0) {
                        result.getPixel(location.at(x).first + w - min_x,location.at(x).second + h - min_y) = stickers.at(x)->getPixel(w, h);
                    }
                }
            }
        }
    }
    return result;

}

// for (int w = location.at(x).first; w < location.at(x).first + stickers.at(x)->width(); w++) {
//     for (int h = location.at(x).second; h < location.at(x).second + stickers.at(x)->height(); h++) {
//         //seeing if alpha value != 0 (pixel can be)
//         if (stickers.at(x)->getPixel(w,h).a != 0) {
//             result.getPixel(w + std::abs(min_x),h + std::abs(min_y)) = stickers.at(x)->getPixel(w,h);
//         }
//     }
// for (unsigned int w = location.at(x).first + std::abs(min_x); w < location.at(x).first + std::abs(min_x) + stickers.at(x)->width(); w++) {
//                 for (unsigned int h = location.at(x).second + std::abs(min_y); h < location.at(x).second + std::abs(min_y) + stickers.at(x)->height(); h++) {
// }

// storing the Base image's dimensions
