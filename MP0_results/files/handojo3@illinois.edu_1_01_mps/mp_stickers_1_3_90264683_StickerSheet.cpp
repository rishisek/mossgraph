#include "StickerSheet.h"
#include "Image.h"
using namespace std;

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    base = picture;
    changeMaxStickers(max);
    stickers = std::vector<Image*> (max, NULL);
}


StickerSheet::StickerSheet(const StickerSheet &other) {
    for (unsigned int i = 0; i < other.stickers.size(); i++) {
        stickers.push_back(other.stickers[i]);
        x_coord.push_back(other.x_coord[i]);
        y_coord.push_back(other.y_coord[i]);
    }
    base = other.base;
    max_ = other.max_;
}


const StickerSheet & StickerSheet::operator=(const StickerSheet &other) {
    if (this != &other) {
        stickers = other.stickers;
        x_coord = other.x_coord;
        y_coord = other.y_coord;
        base = other.base;
        max_ = other.max_;
    }
    return *this;
}


void StickerSheet::changeMaxStickers(unsigned max) {
    max_ = max;
    stickers.resize(max);
    x_coord.resize(max);
    y_coord.resize(max);
}


int StickerSheet::addSticker(Image &sticker, int x, int y) {
    for (unsigned int i = 0; i < stickers.size(); i++) {
        if (stickers[i] == NULL) {
            stickers[i] = &sticker;
            x_coord[i] = x;
            y_coord[i] = y;
            return i;
        }
    }

    // [sticker1, sticker2]
    changeMaxStickers(max_ + 1);
    stickers[max_-1] = &sticker;
    x_coord[max_ -1] =x;
    y_coord[max_-1]=y; 
    // 

    return max_ - 1;
}


int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
    if (layer >= stickers.size() || layer < 0) {
        return -1;
    }
    stickers[layer] = &sticker;
    x_coord[layer] = x;
    y_coord[layer] = y;
    return layer;
}


bool StickerSheet::translate (unsigned index, int x, int y) {
    if (index < 0 || index >= stickers.size() || stickers[index] == NULL) {
        return false;
    }
    x_coord[index] = x;
    y_coord[index] = y; 
    return true;
}


void StickerSheet::removeSticker (unsigned index) {
    stickers.erase(stickers.begin() + index);
    x_coord.erase(x_coord.begin() + index);
    y_coord.erase(y_coord.begin() + index);
}


Image * StickerSheet::getSticker (unsigned index) {
    if (index >= stickers.size() || index < 0) {
        return NULL;
    } 
    return stickers[index];
}


int StickerSheet::layers() const {
    return stickers.size();
}


Image StickerSheet::render() const {
    int num = layers();
    if (stickers.size() == 0 || x_coord.size() == 0 || y_coord.size() == 0) {
        return base;
    }
    // traverse thru x_coord and find smallest value, biggest
    // traverse thru y_coord and find smallest value, biggest
    int xmax = *(max_element(x_coord.begin(), x_coord.end()));
    int xmin = *(min_element(x_coord.begin(), x_coord.end())) < 0 ? *(min_element(x_coord.begin(), x_coord.end())) : 0;
    int ymax = *(max_element(y_coord.begin(), y_coord.end()));
    int ymin = *(min_element(y_coord.begin(), y_coord.end())) < 0 ? *(min_element(y_coord.begin(), y_coord.end())) : 0;
    if (xmax < (int)base.width()) {
        xmax = base.width();
    }
    if (ymax < (int)base.height()) {
        ymax = base.height();
    }
    unsigned int width = xmax - xmin;
    unsigned int height = ymax - ymin;
    Image canvas;
    canvas.resize(width,height);
    for (unsigned int i = 0; i < base.width(); i++) {
        for (unsigned int j = 0; j < base.height(); j++) {
            canvas.getPixel(i-xmin,j-ymin) = base.getPixel(i,j);
        }
    }
    for (int sticker = 0; sticker < num; sticker++) {
        if (stickers[sticker] != NULL) {
            Image &temp = *(stickers[sticker]);
            unsigned int width = x_coord[sticker] + temp.width() - xmin;
            if (width > canvas.width()) {
                canvas.resize(width, canvas.height());
            }
            unsigned int height = y_coord[sticker] + temp.height() - ymin;
            if (height > canvas.height()) {
                canvas.resize(canvas.width(), height);
            }
            for (unsigned int i = 0; i < temp.width(); i++) {
                for (unsigned int j = 0; j < temp.height(); j++) {
                    if (temp.getPixel(i,j).a != 0) {
                        canvas.getPixel(x_coord[sticker] + i - xmin,y_coord[sticker]+ j - ymin) = temp.getPixel(i,j);
                    } 
                }
            }
        }
    }
    return canvas;
}


