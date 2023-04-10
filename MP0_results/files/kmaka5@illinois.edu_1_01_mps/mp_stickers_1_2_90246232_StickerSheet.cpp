#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image& image, unsigned max): max_stickers_(max), base_(image) {
    layers_ = std::vector<Layer*>();
    stickers_ = 0;
    width_ = image.width();
    height_ = image.height();
}

void StickerSheet::_copy(StickerSheet const & other) {
    max_stickers_ = other.max_stickers_;
    stickers_ = other.stickers_;
    Image base_(other.base_);
    width_ = other.width_;
    height_ = other.height_;
    layers_ = std::vector<Layer*>();
    
    for (const Layer* laid: other.layers_) {
        layers_.push_back(new Layer{laid->image, laid->x, laid->y});
    }
}

void StickerSheet::_destroy() {
    for (size_t i = 0; i < layers_.size(); i++) {
        if (layers_.at(i) != NULL) {
            delete layers_.at(i);  
        }
    }
    layers_.clear();
}

const StickerSheet& StickerSheet::operator=(const StickerSheet& other) {
    _destroy();
    _copy(other);
    return *this;
}

StickerSheet::~StickerSheet() {
    _destroy();
}


StickerSheet::StickerSheet(const StickerSheet& other) : base_(other.base_) {
    _copy(other);
}

int StickerSheet::addSticker(Image& sticker, int x, int y) {
    for (size_t i = 0; i < layers_.size(); i++) {
        if (layers_.at(i) == NULL) {
            layers_.at(i) = new Layer{&sticker, x, y};
            stickers_++;
            return i;
        }
    }
    
    if (stickers_ == max_stickers_) {
        max_stickers_++;
    }

    layers_.push_back(new Layer{&sticker, x, y});
    stickers_++;
    return layers_.size()-1;

}

void StickerSheet::changeMaxStickers(unsigned num) {
    max_stickers_ = num;
    if (layers_.size() > max_stickers_) {
        for (int i = layers_.size() - 1; i > (int)(max_stickers_)-1; i--) {
            removeSticker(i);
        }
        stickers_ = max_stickers_;
    }
}

void StickerSheet::removeSticker(unsigned layer) {
    if (layer >= layers_.size() || layer < 0) {
        return;
    }

    if (layers_.at(layer) != NULL) {
        delete layers_.at(layer);
        layers_.at(layer) = NULL;
        stickers_--;
    }
}

Image* StickerSheet::getSticker(unsigned layer) {
    if (layer < 0 || layer >= layers_.size() || layers_.at(layer) == NULL) {
        return NULL;
    }
    return layers_.at(layer)->image;
}

int StickerSheet::layers() const {
    return max_stickers_;
}

Image StickerSheet::render() const {
    int max_neg_x = 0;
    int max_neg_y = 0;
    int max_pos_x = base_.width();
    int max_pos_y = base_.height();

    for (const Layer* layer: layers_) {
        if (layer == NULL) { continue; }
        if (layer->x < max_neg_x) {
            max_neg_x = layer->x;
        } else if (layer->x + (int)layer->image->width() > max_pos_x) {
            max_pos_x = layer->x + (int)layer->image->width();
        }

        if (layer->y < max_neg_y) {
            max_neg_y = layer->y;
        } else if (layer->y + (int)layer->image->height()> max_pos_y) {
            max_pos_y = layer->y + (int)layer->image->height();
        }
    }

    Image res = Image(max_pos_x - max_neg_x, max_pos_y - max_neg_y);
    
    max_neg_x *= -1;
    max_neg_y *= -1;

    for (int x = 0; x < (int)base_.width(); x++) {
        for (int y = 0; y < (int)base_.height(); y++) {
            res.getPixel(x + max_neg_x, y + max_neg_y) = base_.getPixel(x, y);
        }
    }

    for (size_t i = 0; i < layers_.size(); i++) {
        if (layers_.at(i) == NULL) { continue; }
        for (int x = 0; x < (int)(layers_.at(i)->image->width()); x++) {
            for (int y = 0; y < (int)(layers_.at(i)->image->height()); y++) {
                if (layers_.at(i)->image->getPixel(x, y).a != 0) {
                    res.getPixel(layers_.at(i)->x + x + max_neg_x, layers_.at(i)->y + y + max_neg_y) = layers_.at(i)->image->getPixel(x, y);
                }
            } 
        }
    }

    return res;
}

int StickerSheet::setStickerAtLayer(Image& sticker, unsigned layer, int x, int y) {
    if (layer >= layers_.size() || layer < 0) {
        return -1;
    }

    if (layers_.at(layer) != NULL) {
        delete layers_.at(layer);
        layers_.at(layer) = NULL;
    }

    layers_.at(layer) = new Layer{&sticker, x, y};
    return layer;
}

bool StickerSheet::translate(unsigned layer, int x, int y) {
    if (layer >= layers_.size() || layer < 0) {
        return false;
    }

    if (layers_.at(layer) != NULL) {
        layers_.at(layer)->x = x;
        layers_.at(layer)->y = y;
        return true;
    }
    
    return false;
}