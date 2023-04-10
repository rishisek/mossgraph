#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    image_ = picture;
    max_stickers_ = max;
}


void StickerSheet::copy(const StickerSheet &other) {
    image_ = other.image_;
    max_stickers_ = other.max_stickers_;
    for (unsigned i = 0; i < other.stickers_.size(); ++i) {
        stickers_.push_back(other.stickers_.at(i));
        pos_x_ = other.pos_x_;
        pos_y_ = other.pos_y_;
    }    
}

void StickerSheet::clear() {
    stickers_.clear();
    pos_x_.clear();
    pos_y_.clear();
}

void StickerSheet::changeMaxStickers(unsigned max) {
    unsigned diff = 0;
    max_stickers_ = max;
    if (max_stickers_ < stickers_.size()) {
        diff =  stickers_.size() - max_stickers_;
    }
    for(unsigned i = 0; i < diff; ++i) {
        stickers_.pop_back();
        pos_x_.pop_back();
        pos_y_.pop_back();
    }
}

int StickerSheet::addSticker(Image &sticker, int x, int y) {
    if (stickers_.size() >= max_stickers_) {
        max_stickers_++;
    }    
    stickers_.push_back(&sticker);
    pos_x_.push_back(x);
    pos_y_.push_back(y);
    return stickers_.size() - 1;
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
    if (layer >= stickers_.size()) {
        return -1;
    }
    stickers_.at(layer) = &sticker;
    pos_x_.at(layer) = x;
    pos_y_.at(layer) = y;
    return layer; 
}

bool StickerSheet::translate(unsigned index, int x, int y) {
    if (index >= stickers_.size()) return false;
    pos_x_.at(index) = x;
    pos_y_.at(index) = y;
    return true;
}

void StickerSheet::removeSticker(unsigned index) {
    if (index >= stickers_.size()) return;
    stickers_.erase(stickers_.begin() + index);
    pos_x_.erase(pos_x_.begin() + index);
    pos_y_.erase(pos_y_.begin() + index);
}

Image* StickerSheet::getSticker(unsigned index) {
    if (index >= stickers_.size()) return NULL;
    return stickers_.at(index);
}

int StickerSheet::layers() const {
    return max_stickers_;
}

// Image StickerSheet::render() const {
//     Image output(image_);
//     for(unsigned i = 0; i < stickers_.size(); ++i) {
//         unsigned width = stickers_.at(i)->width();
//         unsigned height = stickers_.at(i)->height();
//         if (pos_x_.at(i) < 0) {
//             output.resize(output.width() - pos_x_.at(i), output.width());
//         }
//         if (pos_y_.at(i) < 0) {
//             output.resize(output.width(), output.height() - pos_y_.at(i));
//         }
//         if (pos_x_.at(i) + width > output.width()) {
//             output.resize(pos_x_.at(i)+width, output.height());
//         }
//         if (pos_y_.at(i) + height > output.height()) {
//             output.resize(output.width(), pos_y_.at(i) + height);
//         }
//         for (unsigned x = pos_x_.at(i); x < pos_x_.at(i) + width; ++x) {
//             for (unsigned y = pos_y_.at(i); y < pos_y_.at(i) + height; ++y) {
//                 HSLAPixel& og_pixel = output.getPixel(x,y);
//                 HSLAPixel& new_pixel = stickers_.at(i)->getPixel(x - pos_x_.at(i), y-pos_y_.at(i));
//                 if (new_pixel.a != 0) og_pixel = new_pixel; 
//             }
//         }
//     }
//     return output;
// }

Image StickerSheet::render() const {
    int xmin = 0;
    int xmax = image_.width();
    int ymin = 0;
    int ymax = image_.height();
    for(unsigned i = 0; i < stickers_.size(); ++i) {
        if (pos_y_.at(i) < ymin) ymin = pos_y_.at(i);
        if (pos_x_.at(i) < xmin) xmin = pos_x_.at(i);
        if (pos_x_.at(i) + (int) stickers_.at(i)->width() > xmax) xmax = pos_x_.at(i) + (int) stickers_.at(i)->width();
        if (pos_y_.at(i) + (int) stickers_.at(i)->height() > ymax) ymax = pos_y_.at(i) + (int) stickers_.at(i)->height();
    }
    unsigned canvaswidth = xmax-xmin;
    unsigned canvasheight = ymax-ymin;
    Image output;
    output.resize(canvaswidth, canvasheight);
    Image copy(image_);
    unsigned newx0 = 0-xmin;
    unsigned newy0 = 0-ymin;

    for (unsigned x = 0; x < image_.width(); ++x) {
        for (unsigned y = 0; y < image_.height(); ++y) {
            HSLAPixel& og_pixel = copy.getPixel(x,y);
            HSLAPixel& output_pixel = output.getPixel(x+newx0, y+newy0);
            output_pixel = og_pixel;
        }
    }
    // for (unsigned x = 0; x < newx0; ++x) {
    //     for (unsigned y = 0; y < newy0; ++y) {
    //        HSLAPixel& pixel = output.getPixel(x,y);
    //        pixel.a = 0;
    //     }
    // }
    for(unsigned i = 0; i < stickers_.size(); ++i) {
        for (unsigned x = 0; x < stickers_.at(i)->width(); ++x) {
            for (unsigned y = 0; y < stickers_.at(i)->height(); ++y) {
                HSLAPixel& og_pixel = output.getPixel(pos_x_.at(i) + x + newx0, pos_y_.at(i) + y + newy0);
                HSLAPixel& new_pixel = stickers_.at(i)->getPixel(x , y);
                if (new_pixel.a != 0) og_pixel = new_pixel; 
            }
        }
    }
    return output;
}