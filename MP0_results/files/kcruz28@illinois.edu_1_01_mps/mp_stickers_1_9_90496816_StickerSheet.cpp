#include "StickerSheet.h"
#

StickerSheet::StickerSheet (const Image &picture, unsigned int max) : base_image_(picture), max_(max) {
    stickers_.resize(max, nullptr);
    x_.resize(max);
    y_.resize(max);
}

StickerSheet::StickerSheet (const StickerSheet &other) {
    
    max_ = other.max_;
    x_ = other.x_;
    y_ = other.y_;
    base_image_ = other.base_image_;
    stickers_ = other.stickers_;
    // for (unsigned int i = 0; i < other.max_; i++) {
    //    stickers_.at(i) = other.stickers_.at(i);
    // }
}

const StickerSheet & StickerSheet::operator= (const StickerSheet &other) {
    if (this == &other) return *this;

    max_ = other.max_;
    x_ = other.x_;
    y_ = other.y_;
    base_image_ = other.base_image_;
    stickers_ = other.stickers_;
    // for (unsigned int i = 0; i < other.max_; i++) {
    //     stickers_.at(i) = other.stickers_.at(i);
    // }
    return *this;
}

void StickerSheet::changeMaxStickers (unsigned int max) {
    stickers_.resize(max);
    x_.resize(max);
    y_.resize(max);
    max_ = max;
}

int StickerSheet::addSticker (Image &sticker, int x, int y) {

    for (unsigned int index = 0; index < stickers_.size(); index++) {
        if (stickers_.at(index) ==  NULL) {
            stickers_.at(index) = &sticker;
            x_.at(index) = x;
            y_.at(index) = y;
            return index;
        }
    }

    if (stickers_.size() - 1 != max_) {
        stickers_.push_back(&sticker);
        x_.push_back(x);
        y_.push_back(y);
        return stickers_.size() - 1;
    }
    return stickers_.size() - 1;
}

int StickerSheet::setStickerAtLayer (Image &sticker, unsigned layer, int x, int y) {
    if (layer >= 0 && stickers_.size() > layer) {
        stickers_.at(layer) = &sticker;
        x_.at(layer) = x;
        y_.at(layer) = y;
        return layer;
    }
    return -1;
}

bool StickerSheet::translate (unsigned index, int x, int y) {
    if (stickers_.size() > index && stickers_.at(index) != NULL) {
        x_.at(index) = x;
        y_.at(index) = y;
        return true;
    }
    return false;
}

void StickerSheet::removeSticker (unsigned index) {
    if (index >= 0 && stickers_.size() > index) {
        stickers_.at(index) = NULL;
    }
}

Image* StickerSheet::getSticker (unsigned index) {
    if (index >= 0 && index <= stickers_.size() - 1 ) return stickers_.at(index);
    return NULL;
}

int StickerSheet::layers() const{
    return stickers_.size();
}

Image StickerSheet::render () const {
    // Image copy = base_image_;

    int min_x = 0;
    int min_y = 0;

    int max_x = base_image_.width();
    int max_y = base_image_.height();

    for (unsigned int i = 0; i < stickers_.size(); i++) {
        if (stickers_.at(i) != NULL) {
            if (x_.at(i) < min_x) {
                min_x =(int)x_.at(i);
            }
            if (max_x < x_.at(i) + (int)stickers_.at(i)-> width()) {
                max_x = x_.at(i) + (int)stickers_.at(i)-> width();
            }

            if (y_.at(i) < min_y) {
                min_y =  (int)y_.at(i);
            }
            if (max_y < y_.at(i) + (int)stickers_.at(i)-> height()) {
                max_y = y_.at(i) + (int)stickers_.at(i)-> height();
            }
        }      
     }
     int the_new_width = abs(max_x) + abs(min_x);
     int the_new_height = abs(max_y) + abs(min_y);
    
    Image copied_(the_new_width, the_new_height);

    // copy.resize(the_new_width, the_new_height);

    for(unsigned i = 0; i < base_image_.width(); i++) {
        for (unsigned j = 0; j < base_image_.height(); j++) {
            copied_.getPixel(i - min_x, j - min_y) =  base_image_.getPixel(i, j);
        }
    }

    for (unsigned int sticker = 0; sticker < stickers_.size(); sticker++) {
        if (stickers_.at(sticker) != NULL) {
            for (int x = 0; x < (int)stickers_.at(sticker) -> width(); x++) {
                for (int y = 0; y < (int)stickers_.at(sticker) -> height(); y++) {
//                     std::cout << x << std::endl;
// std::cout << x_.at(sticker) << std::endl;
                    cs225::HSLAPixel & the_pixel = copied_.getPixel(x + x_.at(sticker) - min_x, y + y_.at(sticker) - min_y);
                    
                    cs225::HSLAPixel & sticker_pixel = stickers_.at(sticker)->getPixel(x, y);
                    if (sticker_pixel.a != 0) {
                        the_pixel =  sticker_pixel;
                    }
                }
            }
        }
    } 
    return copied_;
}