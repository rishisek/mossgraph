#include "StickerSheet.h"
#include "Image.h"
#include <vector>
using namespace std;

StickerSheet::StickerSheet(const Image & picture, unsigned max) {
    base_image = picture;
    max_ = max;
    x_coor.resize(max);
    y_coor.resize(max); 
    sticker_vect.resize(max);
}

StickerSheet::StickerSheet(const StickerSheet & other) {
    base_image = other.base_image;
    max_ = other.max_;
    x_coor = other.x_coor;
    y_coor = other.y_coor;
    sticker_vect = other.sticker_vect;
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other) {
    if (this == & other) {
        return * this;
    }

    base_image = other.base_image;
    max_ = other.max_;
    x_coor = other.x_coor;
    y_coor = other.y_coor;
    sticker_vect = other.sticker_vect;

    return * this;
    
}

void StickerSheet::changeMaxStickers(unsigned max) {
    max_ = max;
    x_coor.resize(max);
    y_coor.resize(max);

    for (unsigned int i = 0; i < sticker_vect.size(); i++) {
        if (sticker_vect.at(i) == nullptr) {
            sticker_vect.at(i) = nullptr;
        }
    }

    sticker_vect.resize(max);
}

int StickerSheet::addSticker(Image & sticker, int x, int y) {
    for (unsigned int i = 0; i < sticker_vect.size(); i++) {
        if (sticker_vect.at(i) == nullptr) {
            x_coor.at(i) = x;
            y_coor.at(i) = y;
            sticker_vect.at(i) = & sticker;
            return i;
        }
    }
    max_ += 1;
    sticker_vect.push_back(&sticker);
    x_coor.push_back(x);
    y_coor.push_back(y);
    return sticker_vect.size() - 1;
}

void StickerSheet::removeSticker(unsigned index) { 
    if (!(index >= sticker_vect.size())) {
        if (sticker_vect.at(index) != nullptr) {
            sticker_vect.at(index) = nullptr;
        }
        x_coor.at(index) = 0;
        y_coor.at(index) = 0;
    }
}


Image * StickerSheet::getSticker(unsigned index) {
    if (index >= sticker_vect.size()) {
        return NULL;
    }
    if (sticker_vect.at(index) == nullptr) {
        return NULL;
    }

    return sticker_vect.at(index);
}

int StickerSheet::layers() const {
    return max_;
}

int StickerSheet::setStickerAtLayer(Image & sticker, unsigned layer, int x, int y) {
    if (!(layer >= sticker_vect.size())) {
        sticker_vect.at(layer) = &sticker;
        x_coor.at(layer) = x;
        y_coor.at(layer) = y;
        return layer; 
    }
    return -1;
}

bool StickerSheet::translate(unsigned index, int x, int y) {
    if (index >= sticker_vect.size() || sticker_vect.at(index) == nullptr) {
        return false;
    }
    x_coor.at(index) = x;
    y_coor.at(index) = y;
    return true;
}

Image StickerSheet::render() const {
    int max_x = int(base_image.width());
    int max_y = int(base_image.height());
    int min_x = 0;
    int min_y = 0;

    //dimensions for white sheet
    for (unsigned int i = 0; i < sticker_vect.size(); i++) {
        if (sticker_vect.at(i) == nullptr) {
            continue;
        }

        Image * temp = sticker_vect.at(i);
        

        //check max_x
        if ((x_coor.at(i) + int(temp->width())) > max_x) {
            max_x = x_coor.at(i) + int(temp->width());
        }
        //check max_y
        if (y_coor.at(i) + int(temp->height()) > max_y) {
            max_y = y_coor.at(i) + int(temp->height());
        }
        //check min_x
        if (x_coor.at(i) < min_x) {
            min_x = x_coor.at(i);
        }
        //check min_y
        if (y_coor.at(i) < min_y) {
            min_y = y_coor.at(i);
        }
    }

    unsigned int width_ = max_x + abs(min_x);
    unsigned int height_ = max_y + abs(min_y);
    Image whitesheet;
    whitesheet.resize(width_, height_);


    for (unsigned int i = 0; i < base_image.width(); i++) {
        for (unsigned int j = 0; j < base_image.height(); j++) {
            int curr_xcoor = i + abs(min_x); //shift x
            int curr_ycoor = j + abs(min_y); //shift y
            whitesheet.getPixel(curr_xcoor, curr_ycoor) = base_image.getPixel(i,j);
        }
    }



    for (unsigned int i = 0; i < sticker_vect.size(); i++) {

        if (sticker_vect.at(i) == nullptr) {
            continue;
        }

        Image * curr_sticker = sticker_vect.at(i);

        int curr_xcoor = x_coor.at(i) + abs(min_x); //shift x
        int curr_ycoor = y_coor.at(i) + abs(min_y); //shift y

        for (unsigned int x = 0; x < curr_sticker->width(); x++) {
            for (unsigned int y = 0; y < curr_sticker->height(); y++) {
                if (curr_sticker->getPixel(x, y).a != 0) {
                    whitesheet.getPixel(x + curr_xcoor, y + curr_ycoor) = curr_sticker->getPixel(x, y);
                }
            }
        }
        

    }
    
    return whitesheet;
}