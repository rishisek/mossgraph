#include "StickerSheet.h"
#include <iostream>

    StickerSheet::StickerSheet(const Image & picture, unsigned max) {
        picture_ = picture;
        max_ = max;
        stickers.resize(max);
        x_coords.resize(max);
        y_coords.resize(max);
    }

    StickerSheet::StickerSheet(const StickerSheet & other) {
        this->stickers = other.stickers;
        this->x_coords = other.x_coords;
        this->y_coords = other.y_coords;
        this->max_ = other.max_;
        this->picture_ = other.picture_;
    }

    const StickerSheet & StickerSheet::operator=(const StickerSheet & other) {
        this->stickers = other.stickers;
        this->x_coords = other.x_coords;
        this->y_coords = other.y_coords;
        this->max_ = other.max_;
        this->picture_ = other.picture_;
        return *this;
    }

    int StickerSheet::addSticker(Image & sticker, int x, int y) {
        int index = 0;
        int inserted = 0;
        while(inserted == 0) {
            if(index == (int)max_) {
                stickers.push_back(&sticker);
                x_coords.push_back(x);
                y_coords.push_back(y);
                inserted++;
                max_++;
                return index;
            }
            else if(stickers[index] == NULL)
            {
                stickers[index] = &sticker;
                x_coords[index] = x;
                y_coords[index] = y;
                inserted++;
                return index;
            }
            index++;
        }
        return index;
    }
    void StickerSheet::changeMaxStickers(unsigned max) {
        stickers.resize(max);
        x_coords.resize(max);
        y_coords.resize(max);
        max_ = max;
    }
    Image * StickerSheet::getSticker(unsigned index) {
        return stickers[index];
    }
    int StickerSheet::layers() const {
        return max_;
    }
    void StickerSheet::removeSticker(unsigned index) {
        stickers[index] = NULL;
    }
    Image StickerSheet::render() const {
        unsigned int image_w = picture_.width();
        unsigned int image_h = picture_.height();
        Image copy = Image(picture_);

        unsigned int up = 0;
        unsigned int left = 0;
        int left_border = 0;
        int up_border = 0;
        int right = (int)image_w;
        int down = (int)image_h;
        for(unsigned int d = 0; d < max_; d++) {
            if(stickers[d] != NULL) {
                int left_edge = x_coords[d];
                int up_edge = y_coords[d];
                int right_edge = x_coords[d] + (int)stickers[d]->width();
                int down_edge = y_coords[d] + (int)stickers[d]->height();
                if(left_edge < left_border) {
                    left_border = left_edge;
                    left = abs(left_border);
                }
                if(right_edge >= right)
                {
                    right = right_edge;
                }
                if(up_edge < up_border) {
                    up_border = up_edge;
                    up = abs(up_border);
                }
                if(down_edge >= down) {
                    down = down_edge;
                }
            }
        }

        unsigned int final_width = left + right;
        unsigned int final_height = up + down;
        Image combined = Image(picture_);
        combined.resize(final_width,final_height);
        for(unsigned int a = 0; a < image_w; a++) {
            for(unsigned int b = 0; b < image_h; b++) {
                combined.getPixel(a+left, b+up) = picture_.getPixel(a, b);
            }
        }
        for(unsigned int m = 0; m < combined.width(); m++) {
            for(unsigned int n = 0; n < up; n++) {
                combined.getPixel(m,n) = cs225::HSLAPixel();
            }
        }
        for(unsigned int o = 0; o < left; o++) {
            for(unsigned int p = 0; p < combined.height(); p++) {
                cs225::HSLAPixel* pixel = &combined.getPixel(o, p);
                *pixel = cs225::HSLAPixel();
            }
        }

        for(unsigned int i = 0; i < max_; i++) {
            if(stickers[i] != NULL) {
                for(unsigned int j = 0; j < stickers[i]->width(); j++) {
                    for(unsigned int k = 0; k < stickers[i]->height(); k++) {
                        if(stickers[i]->getPixel(j,k).a != 0) {
                            int x = x_coords[i] + j + left;
                            int y = y_coords[i] + k + up;
                            combined.getPixel(x,y) = stickers[i]->getPixel(j,k);
                        }
                    }
                }
            }
        }
        return combined;
    }

    int StickerSheet::setStickerAtLayer(Image & sticker, unsigned layer, int x, int y) {
        if(layer > (max_ - 1) || layer < 0) {
            return -1;
        }
        else {
            stickers[layer] = &sticker;
            x_coords[layer] = x;
            y_coords[layer] = y;
            return layer;
        }
    }
    bool StickerSheet::translate(unsigned index, int x, int y) {
        if(stickers[index] == NULL || index >= max_ || index < 0) {
            return false;
        }
        else {
            x_coords[index] = x;
            y_coords[index] = y;
            return true;
        }
    }