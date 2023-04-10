#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    base = picture;
    max_layers = max;
    sticker_layers.resize(max);
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    this->_copy(other);
}

const StickerSheet & StickerSheet::operator=(const StickerSheet &other) {
    this->_copy(other);
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) { 
    if (max < max_layers) {
        sticker_layers.resize(max);
        sticker_layers.shrink_to_fit();
    }
    max_layers = max; 
}

int StickerSheet::addSticker(Image &sticker, int x, int y) {
    Image * psticker = &sticker;
    Sticker input = {x, y, psticker};
    int i = 0;
    for (Sticker &layer : sticker_layers) {
        if (layer.sticker == nullptr) {
            layer.sticker = psticker;
            layer.x = x;
            layer.y = y;
            return i;
        }
        i++;
    }
    sticker_layers.push_back(input);
    max_layers++;
    return sticker_layers.size() - 1;
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
    if (layer >= max_layers) {
        return -1;
    }
    Image * psticker = &sticker;
    Sticker input = {x, y, psticker};
    sticker_layers.at(layer) = input;
    return layer;
}

bool StickerSheet::translate(unsigned index, int x, int y) {
    if (max_layers <= index) {
        return false;
    } else {
        if (sticker_layers.at(index).sticker == nullptr) {
            return false;
        }
        sticker_layers.at(index).x = x;
        sticker_layers.at(index).y = y;
        return true;
    }
}

void StickerSheet::removeSticker(unsigned index) {
    sticker_layers.at(index).sticker = nullptr;
}

Image * StickerSheet::getSticker(unsigned index) {
    if (index < max_layers) {
        return sticker_layers.at(index).sticker;
    }
    return NULL;
}

int StickerSheet::layers() const {
    return max_layers;
}
/*
void StickerSheet::sticker_resize(unsigned int width, int x_dif, unsigned int height, int y_dif) {
    Image copy(width, height);
    if (x_dif)
        for (unsigned int col = x_dif; col < width; col++) {
            for (unsigned int row = y_dif; row < height; row++) {

            }
        }

}
*/
Image StickerSheet::render() const {
    Image output(base.width(), base.height());
    for (unsigned int row = 0; row < base.height(); row++) {
        for (unsigned int col = 0; col < base.width(); col++) {
            output.getPixel(col, row) = base.getPixel(col, row);
        }
    }
    //int x_dif = 
    //int y_dif = 
    for (Sticker layer: sticker_layers) {
        if (layer.sticker != nullptr) {
            for (unsigned col = layer.x; col < layer.x + layer.sticker->width(); col++) {
                for (unsigned row = layer.y; row < layer.y + layer.sticker->height(); row++) {                       
                    if (layer.sticker->getPixel(col - layer.x, row - layer.y).a != 0) {
                        output.getPixel(col,row) = layer.sticker->getPixel(col - layer.x, row - layer.y);
                    }    
                }
            } 
        }     
    }
    return output;
}

void StickerSheet::_copy(StickerSheet const & other) {
    this->max_layers = other.max_layers;
    this->base = other.base;
    this->sticker_layers.clear();
    for (Sticker layer : other.sticker_layers) {
        if (layer.sticker != nullptr) {
            Image & s = *(layer.sticker);
            Image * ps = &s;
            Sticker input = {layer.x, layer.y, ps};
            sticker_layers.push_back(input);
        } else {
            sticker_layers.push_back(layer);
        }
    }
}