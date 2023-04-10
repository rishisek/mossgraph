#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"
#include <iostream>

using namespace std;

StickerSheet::StickerSheet(const Image& picture, unsigned max){
    max_ = max;
    base_ = Image(picture);
}

StickerSheet::StickerSheet(const StickerSheet& other){
    images_.clear();
    x_coord_.clear();
    y_coord_.clear();

    base_ = Image(other.base_);
    max_ = other.max_;
    for (unsigned int i = 0; i < other.images_.size(); i++) {
        images_.push_back(other.images_[i]);
        x_coord_.push_back(other.x_coord_[i]);
        y_coord_.push_back(other.y_coord_[i]);
    }

}

const StickerSheet& StickerSheet::operator=(const StickerSheet& other){
    images_.clear();
    x_coord_.clear();
    y_coord_.clear();

    base_ = Image(other.base_);
    max_ = other.max_;
    for (unsigned int i = 0; i < other.images_.size(); i++) {
        images_.push_back(other.images_[i]);
        x_coord_.push_back(other.x_coord_[i]);
        y_coord_.push_back(other.y_coord_[i]);
    }

    return *this;
}

// StickerSheet::~StickerSheet(){
//     delete base_;
//     for (unsigned int i = 0; i < images_.size(); i++) {
//         delete images_.at(i);
//         images_.at(i) = NULL;
//     }
// }

void StickerSheet::changeMaxStickers(unsigned max){
    max_ = max;

    if (images_.size() > max) {
        images_.resize(max);
        x_coord_.resize(max);
        y_coord_.resize(max);
    }
}

int StickerSheet::addSticker(Image& sticker, int x, int y){
    if (images_.size() >= max_) {
        changeMaxStickers(max_ + 1);
    }

    images_.push_back(&sticker);
    x_coord_.push_back(x);
    y_coord_.push_back(y);

    return images_.size() - 1;
}

int StickerSheet::setStickerAtLayer(Image& sticker, unsigned layer, int x, int y){
    if (layer >= images_.size()) {
        return -1;
    }

    images_.erase(images_.begin() + layer);
    x_coord_.erase(x_coord_.begin() + layer);
    y_coord_.erase(y_coord_.begin() + layer);

    images_.insert(images_.begin() + layer, &sticker);
    x_coord_.insert(x_coord_.begin() + layer, x);
    y_coord_.insert(y_coord_.begin() + layer, y);
    
    return layer;
}

bool StickerSheet::translate(unsigned index, int x, int y){
    if (index >= images_.size()) {
        return false;
    }

    x_coord_.at(index) = x;
    y_coord_.at(index) = y;
    
    return true;
}

void StickerSheet::removeSticker(unsigned index){
    if (index >= images_.size()) return;
    
    images_.erase(images_.begin() + index);
    x_coord_.erase(x_coord_.begin() + index);
    y_coord_.erase(y_coord_.begin() + index);
}

Image* StickerSheet::getSticker(unsigned index){
    if (index >= images_.size()) {
        return NULL;
    }
    return images_.at(index);
}

int StickerSheet::layers() const{
    return max_;
}

Image StickerSheet::render() const{
    int min_x = 0;
    int min_y = 0;
    int max_x = base_.width();
    int max_y = base_.height();

    for (size_t i = 0; i < images_.size(); i++) {
        int x = x_coord_[i];
        int y = y_coord_[i];
        Image* img = images_[i];

        if (min_x > x) min_x = x;
        if (min_y > y) min_y = y;
        if (max_x < x + (int)img->width()) max_x = x + (int)img->width();
        if (max_y < y + (int)img->height()) max_y = y + (int)img->height();
    }

    Image to_render(max_x - min_x, max_y - min_y);

    // cout << "width: " << max_x - min_x << " height: " << max_y - min_y << " base width: " << base_.width() << " base height: " << base_.height() << endl;

    // First render the base image
    for (unsigned x = 0; x < base_.width(); x++) {
        for (unsigned y = 0; y < base_.height(); y++) {
            // cout << "Getting pixel: " << x - min_x << " " << y - min_y << endl;
            cs225::HSLAPixel &to_render_pix = to_render.getPixel(x - min_x, y - min_y);
            const cs225::HSLAPixel &base_pix = base_.getPixel(x, y);

            to_render_pix = base_pix;
        }
    }

    // cout << "step A" << endl;

    // cout << images_.size() << endl;

    for (unsigned int i = 0; i < images_.size(); i++) {
        int img_x = x_coord_[i];
        int img_y = y_coord_[i];
        Image* img = images_[i];

        for (unsigned int x = 0; x < img->width(); x++) {
            for (unsigned int y = 0; y < img->height(); y++) {
                cs225::HSLAPixel& sticker_pix = img->getPixel(x, y);

                if (sticker_pix.a != 0) {
                    cs225::HSLAPixel& to_render_pix = to_render.getPixel(img_x + x - min_x, img_y + y - min_y);
                    to_render_pix = sticker_pix;
                }
            }
        }
    }

    // cout << "Step B" << endl;

    return to_render;
}
