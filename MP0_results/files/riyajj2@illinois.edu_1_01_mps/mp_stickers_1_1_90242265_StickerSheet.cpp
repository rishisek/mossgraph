#include <StickerSheet.h>

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    max_stickers_ = max;
    num_stickers_ = 0;
    base_ = new Image(picture);

    layers_ = std::vector<Layer*>();
    base_width_ = base_->width();
    base_height_ = base_->height();
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    _copy(other);
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other) {
    if(this != &other) {
        _destroy();
        _copy(other);
    }
    return *this;
}

StickerSheet::~StickerSheet() {
    _destroy();
}

void StickerSheet::_destroy() {
    if (base_ != NULL) {
        delete base_;
        base_ = NULL;
    }

    for (int i = 0; i < (int) layers_.size(); i++) {
        if (layers_.at(i) != NULL) {
           
            delete layers_.at(i);
            layers_.at(i) = NULL;
        }
    }
    layers_.clear();
}

void StickerSheet::_copy(const StickerSheet& other) {
    max_stickers_ = other.max_stickers_;
    base_ = new Image(*(other.base_));
    num_stickers_ = other.num_stickers_;
    base_width_ = other.base_width_;
    base_height_ = other.base_height_;

    layers_ = std::vector<Layer*>();

    for (const Layer* l : other.layers_) {
        Layer* n = new Layer();
        n->sticker = l->sticker;
        n->x_pos = l->x_pos;
        n->y_pos = l->y_pos;
        layers_.push_back(n);
    }
}

void StickerSheet::changeMaxStickers(unsigned max) {
    max_stickers_ = max;
    if ((int)layers_.size() > max_stickers_) {
        for (int i = layers_.size() - 1; i > (int)(max_stickers_) - 1; i--) {
            remove(i);
        }
        num_stickers_ = max_stickers_;
    }
}

void StickerSheet::remove(unsigned ind) {
    if (ind >= layers_.size() || ind < 0) {
        return;
    } 
    if (layers_.at(ind) != NULL) {
        delete layers_.at(ind);
        layers_.at(ind) = NULL;
        num_stickers_--;
    }
}
        // for (unsigned i = max; i < (unsigned) max_stickers_; i++) {
        //     if (layers_.at(i) != NULL) {
        //         delete layers_.at(i);
        //         layers_.at(i) = NULL;
        //     }
        //     num_stickers_ = max_stickers_;
        // }
        
int StickerSheet::addSticker(Image &sticker, int x, int y) {
    for (size_t i = 0; i < layers_.size(); i++) {
        if (layers_.at(i) == NULL) {
            layers_.at(i) = new Layer{&sticker, x, y};
            num_stickers_++;
            return i;
        } 
    }
    if (num_stickers_ == max_stickers_) {
        max_stickers_++;
    }

    layers_.push_back(new Layer{&sticker, x, y});
    num_stickers_++;
    return layers_.size() - 1;
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
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

bool StickerSheet::translate(unsigned index, int x, int y) {
    if (index >= layers_.size() || index < 0 || layers_.at(index) == NULL) {
        return false;
    }
    layers_.at(index)->x_pos = x;
    layers_.at(index)->y_pos = y;
    return true;
    
}

        
void StickerSheet::removeSticker(unsigned index) {
    if (layers_.at(index) != NULL) {
        // if (layers_.at(index)->sticker != NULL) {
        //     delete layers_.at(index)->sticker;
        //     layers_.at(index)->sticker = NULL;
        // }
        delete layers_.at(index);
        layers_.at(index) = NULL;
    }
    num_stickers_--;
}
        
Image* StickerSheet::getSticker(unsigned index) {
    if (index < 0 || index >= layers_.size() || layers_.at(index) == NULL) {
        return NULL;
    } 
    return layers_.at(index)->sticker;
}
        
int StickerSheet::layers() const {
    return max_stickers_;
}

Image StickerSheet::render() const {
    //1: calculate new width and new height
    //2: reposition all stickers + base in accordance with this width and height
    //3: create new image, currently blank
    //4: start with base, then loop through all layers and change pixels accordingly
    
    int min_x = 0;
    int min_y = 0;
    int max_x = base_width_;
    int max_y = base_height_;

    for (const Layer* lay: layers_) {
        if (lay == NULL) {
            continue;
        }
        if (lay->x_pos < min_x) {
            min_x = lay->x_pos;
        } else if (lay->x_pos + (int)lay->sticker->width() > max_x){
            max_x = lay->x_pos + (int) lay->sticker->width();
        }
        if (lay->y_pos < min_y) {
            min_y = lay->y_pos;
        } else if (lay->y_pos + (int) lay->sticker->height() > max_y) {
            max_y = lay->y_pos + (int) lay->sticker->height();
        }
    }
    int new_width = max_x - min_x;
    int new_height = max_y - min_y;

    Image output = Image(new_width, new_height);

    min_x *= -1;
    min_y *= -1;

    for (int x = 0; x < (int)base_->width(); x++) {
        for (int y = 0; y < (int)base_->height(); y++) {
            output.getPixel(x + min_x, y + min_y) = base_->getPixel(x,y);
        }
    }

    for (size_t i = 0; i < layers_.size(); i++) {
        if (layers_.at(i) == NULL) {continue;}
         for (int w = 0; w < (int) (layers_.at(i)->sticker->width()); w++) {
            for (int h = 0; h < (int) (layers_.at(i)->sticker->height()); h++) {
                if (layers_.at(i)->sticker->getPixel(w, h).a != 0) {
                    output.getPixel(w + layers_.at(i)->x_pos + min_x, h + layers_.at(i)->y_pos +min_y) = layers_.at(i)->sticker->getPixel(w, h);
                }
            }
        }
    }
    return output;
}


// for (int i = 0; i < (int)max_stickers_; i++) {
//         if (layers_.at(i) != NULL && layers_.at(i)->sticker != NULL) {
//             if (layers_.at(i)->x_pos < min_x) {
//                 min_x = layers_.at(i)->x_pos;
//             }
//             if (layers_.at(i)->y_pos < min_y) {
//                 min_y = layers_.at(i)->y_pos;
//             }
//             if ((int)layers_.at(i)->x_pos + (int)(layers_.at(i)->sticker)->width() > max_x) {
//                 max_x = layers_.at(i)->x_pos + (int) (layers_.at(i)->sticker)->width();
//             }
//             if ((int) layers_.at(i)->y_pos + (int) (layers_.at(i)->sticker)->height() > max_y) {
//                 max_x = layers_.at(i)->y_pos + (int) (layers_.at(i)->sticker)->height();
//             }
//         }
//     }
// for (int i = 0; i < (int)layers_.size(); i++) {
//         if (layers_.at(i) != NULL && layers_.at(i)->sticker != NULL) {
//            layers_.at(i)->x_pos = layers_.at(i)->x_pos - min_x;
//            layers_.at(i)->y_pos = layers_.at(i)->y_pos - min_y;
//         }
//     }

//     for(int i = 0; i < base_width_; i++) {
//         for (int j = 0; j < base_height_; j++) {
//             output.getPixel(i + base_image_x, j + base_image_y) = base_->getPixel(i, j);
//         }
//     }

//     for (int i = 0; i < (int) layers_.size(); i++) {
//         if (layers_.at(i) != NULL && layers_.at(i)->sticker != NULL) {
//             for (int w = 0; w < (int) (layers_.at(i)->sticker)->width(); w++) {
//                 for (int h = 0; h < (int) (layers_.at(i)->sticker)->height(); h++) {
//                     output.getPixel(w + layers_.at(i)->x_pos, h + layers_.at(i)->y_pos) = (layers_.at(i)->sticker)->getPixel(w, h);
//                 }
//             }
//         }
//     }



