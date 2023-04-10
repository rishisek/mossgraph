#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    base_ = picture;
    max_ = max;
    for (unsigned int i=0; i < max_; i++) {
        layers_.push_back(NULL);
        x_coords_.push_back(0);
        y_coords_.push_back(0);
    }
 }

void StickerSheet::changeMaxStickers(unsigned max) {
    if (max_ < max) {
        for (unsigned int i=max_; i < max; i++) {
            layers_.push_back(NULL);
            x_coords_.push_back(0);
            y_coords_.push_back(0);
        }
    } else if (max_ > max) {
        for (unsigned int i=max_; i > max; i--) {
            layers_.pop_back();
            x_coords_.pop_back();
            y_coords_.pop_back();
        }
    }
    max_ = max;
}
int StickerSheet::addSticker(Image &sticker, int x, int y) {
    int index = -1;
    for (unsigned int i=0; i < max_; i++) {
        if (layers_.at(i) == NULL && index == -1) {
            layers_.at(i) = &sticker;
            x_coords_.at(i) = x;
            y_coords_.at(i) = y;
            index = i;
        }
    }
    if (index == -1) {
        layers_.push_back(&sticker);
        x_coords_.push_back(x);
        y_coords_.push_back(y);
        index = max_;
        max_++;
    }
    return index;
}
int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
    if (layer >= max_) {
        return -1;
    }
    layers_.at(layer) = &sticker;
    x_coords_.at(layer) = x;
    y_coords_.at(layer) = y;
    return layer;
}
bool StickerSheet::translate(unsigned index, int x, int y) {
    if (layers_.at(index) == NULL || index >= max_) {
        return false;
    }
    x_coords_.at(index) = x;
    y_coords_.at(index) = y;
    return true;
}
void StickerSheet::removeSticker(unsigned index) {
    layers_.at(index) = NULL;
    x_coords_.at(index) = 0;
    y_coords_.at(index) = 0;
}
Image * StickerSheet::getSticker(unsigned index) {
    if (index >= max_) {
        return NULL;
    }
    return layers_.at(index);
}
int StickerSheet::layers() const {
    return max_;
}
Image StickerSheet::render() const {
    Image output = base_;
    /*int neg_x = 0;
    int neg_y = 0;
    for (unsigned int i=0; i < max_; i++) {
        if (x_coords_.at(i) < neg_x) {
            neg_x = x_coords_.at(i);
        }
        if (y_coords_.at(i) < neg_y) {
            neg_y = y_coords_.at(i);
        }
    }
    if (neg_x < 0 || neg_y < 0) {
        resizeNeg(output, output.width() - neg_x, output.height() - neg_y);
    }*/
    for (unsigned int i=0; i < max_; i++) {
        if (layers_.at(i) != NULL) {
            for (unsigned int x=0; x < layers_.at(i)->width(); x++) {
                for (unsigned int y=0; y < layers_.at(i)->height(); y++) {
                    cs225::HSLAPixel & current = layers_.at(i)->getPixel(x, y);
                    if (current.a != 0) {
                        output.getPixel(x_coords_.at(i) + x, y_coords_.at(i) + y) = current;
                    }
                }
            }
        }
    }
    return output;
}

/*void StickerSheet::resizeNeg(Image &output, int width, int height) const {
    output.resize(width, height);
    unsigned int p = width - 1;
    unsigned int q;
    for (unsigned int x=base_.width()-1; x >= 0; x--) {
        q = height - 1;
        for (unsigned int y=base_.height()-1; y >= 0; y--) {
            output.getPixel(p, q) = base_.getPixel(x, y);
            q--;
        }
        p--;
    }
}*/