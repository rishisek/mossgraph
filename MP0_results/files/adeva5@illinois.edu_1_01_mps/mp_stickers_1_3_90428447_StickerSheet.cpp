#include "StickerSheet.h"
#include <string>

StickerSheet::StickerSheet(const Image& picture, unsigned max) {
    base = new Image();
    *base = picture;
    //Image dupl = picture;
    //base = &dupl;
    stickers.clear();
    xcoor.resize(max);
    ycoor.resize(max);
    for(unsigned i = 0; i < max; i++) {
        stickers.push_back(NULL);
        //xcoor.push_back(NULL);
        //ycoor.push_back(NULL);
    }

}

StickerSheet::StickerSheet(const StickerSheet& other) {
    base = NULL;
    _copy(other);
}

StickerSheet::~StickerSheet() {
    delete base;
}

const StickerSheet& StickerSheet::operator=(const StickerSheet& other) {
    _copy(other);
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    unsigned int old = stickers.size();
    // if(max < old) {
    //     for(unsigned i = max; i < old; i++) {
    //         delete xcoor[i];
    //         delete ycoor[i];
    //     }
    // }
    stickers.resize(max);
    xcoor.resize(max);
    ycoor.resize(max);
    if(max > old) {
        for(unsigned i = old; i < max; i++) {
            stickers[i] = NULL;
            //xcoor[i] = NULL;
            //ycoor[i] = NULL;
        }
    }
}

int StickerSheet::addSticker(Image& sticker, int x, int y) {
    for(unsigned i = 0; i < stickers.size(); i++) {
        if(stickers[i] == NULL) {
            stickers[i] = &sticker;
            xcoor[i] = x;
            ycoor[i] = y;
            return i;
        }
    }
    stickers.push_back(&sticker);
    xcoor.push_back(x);
    ycoor.push_back(y);
    // xcoor.resize(xcoor.size() + 1);
    // ycoor.resize(ycoor.size() + 1);
    // xcoor[xcoor.size() - 1] = new int(x);
    // ycoor[ycoor.size() - 1] = new int(y);
    return stickers.size() - 1;
}

int StickerSheet::setStickerAtLayer(Image& sticker, unsigned layer, int x, int y) {
    if(layer >= stickers.size()) {
        return -1;
    }
    // for(unsigned int i = 0; i < stickers.size(); i++) {
    //     if(i != layer && stickers[i] == stickers[layer]) {
    //         stickers[layer] = NULL;
    //         break;
    //     }
    // }
    // if(stickers[layer] != NULL) {
    //     delete stickers[layer];
    // }
    //delete xcoor[layer];
    //delete ycoor[layer];
    stickers[layer] = &sticker;
    xcoor[layer] = x;
    ycoor[layer] = y;
    //xcoor[layer] = new int(x);
    //ycoor[layer] = new int(y);
    return layer;
}

bool StickerSheet::translate(unsigned index, int x, int y) {
    bool cond = index < stickers.size() && stickers[index] != NULL;
    if(cond) {
        // *xcoor[index] = x;
        // *ycoor[index] = y;
        xcoor[index] = x;
        ycoor[index] = y;
    }
    return cond;
}

void StickerSheet::removeSticker(unsigned index) {
    //for(auto x : stickers) {std::cout << x << " " << stickers[index]->width();}
    //std::cout << std::endl;
    if(getSticker(index) != NULL) {
        // for(unsigned int i = 0; i < stickers.size(); i++) {
        //     if(i != index && stickers[i] == stickers[index]) {
        //         stickers[index] = NULL;
        //         break;
        //     }
        // }
        // if(stickers[index] != NULL) {
        //     Image* temp = &*stickers[index];
        //     delete temp;
        //     stickers[index] = NULL;
        // }
        stickers[index] = NULL;
        // delete xcoor[index];
        // delete ycoor[index];
        // xcoor[index] = NULL;
        // ycoor[index] = NULL;
    }
}

Image* StickerSheet::getSticker(unsigned index) {
    if(index < stickers.size() && stickers[index] != NULL)
        return stickers[index];
    return NULL;
}

int StickerSheet::layers() const {
    // int count = 0;
    // for(unsigned i = 0; i < stickers.size(); i++) {
    //     if(stickers[i] == NULL)
    //         count++;
    // }
    return stickers.size();
}

Image StickerSheet::render() const {
    int maxX = base->width() - 1;
    int minX = 0;
    int maxY = base->height() - 1;
    int minY = 0;
    for(unsigned i = 0; i < stickers.size(); i++) {
        if(stickers[i] != NULL) {
            //std::cout << *ycoor[i] << " " << stickers[i]->height() << std::endl;
            if(xcoor[i] + (int)stickers[i]->width() - 1 > maxX)
                maxX = xcoor[i] + stickers[i]->width() - 1;
            else if(xcoor[i] < minX)
                minX = xcoor[i];
            if(ycoor[i] + (int)stickers[i]->height() - 1 > maxY)
                maxY = ycoor[i] + stickers[i]->height() - 1;
            else if(ycoor[i] < minY)
                minY = ycoor[i];
        }
    }
    unsigned int width = maxX - minX + 1;
    unsigned int height = maxY - minY + 1;
    //std::cout << maxX << " " << minX << " " << width << std::endl;
    //std::cout << maxY << " " << minY << " " << height << std::endl;
    Image canvas = *base;
    canvas.resize(width, height);
    cs225::HSLAPixel* whitePixel = new cs225::HSLAPixel();
    for(unsigned int i = 0; i < canvas.height(); i++) {
        for(unsigned int j = 0; j < canvas.width(); j++) {
            canvas.getPixel(j, i) = *whitePixel;
        }
    }
    for(unsigned int i = 0; i < base->height(); i++) {
        for(unsigned int j = 0; j < base->width(); j++) {
            cs225::HSLAPixel& basePixel = base->getPixel(j, i);
            cs225::HSLAPixel& canvasPixel = canvas.getPixel(j - minX, i - minY);
            canvasPixel = basePixel;
        }
    }
    for(unsigned i = 0; i < stickers.size(); i++) {
        if(stickers[i] != NULL) {
            //stickers[i]->writeToFile("render" + std::to_string(i) + ".png");
            //std::cout << stickers[i]->height() << " " << stickers[i]->width() << std::endl;
            //std::cout << *xcoor[i] << " " << *ycoor[i] << std::endl;
            for(unsigned int j = 0; j < stickers[i]->height(); j++) {
                for(unsigned int k = 0; k < stickers[i]->width(); k++) {
                    cs225::HSLAPixel& stickerPixel = stickers[i]->getPixel(k, j);
                    //std::cout << stickerPixel.h << std::endl;
                    //std::cout << stickerPixel.a << std::endl;
                    //std::cout << stickerPixel.h << stickerPixel.s << stickerPixel.l << stickerPixel.a << std::endl;
                    //std::cout << i << " " << j << " " << k << std::endl;
                    //std::cout << *ycoor[i] << " " << minY << " " << *xcoor[i] << " " << minX << " " << maxX << " " << maxY << std::endl;
                    //std::cout << *ycoor[i] - minY << " " << *xcoor[i] - minX << std::endl;
                    cs225::HSLAPixel& canvasPixel = canvas.getPixel(xcoor[i] - minX + k, ycoor[i] - minY + j);
                    //std::cout << *xcoor[i] - minX + k << " " << *ycoor[i] - minY + j << std::endl;
                    //std::cout << canvasPixel.h << canvasPixel.s << canvasPixel.l << canvasPixel.a << std::endl;
                    if(stickerPixel.a != 0) {
                        canvasPixel = stickerPixel;
                    }
                }
            }
        }
    }
    //canvas.writeToFile("render.png");
    delete whitePixel;
    return canvas;
}

void StickerSheet::_copy(const StickerSheet& other) {
    delete base;
    // for(unsigned i = 0; i < stickers.size(); i++) {
    //     delete xcoor[i];
    //     delete ycoor[i];
    // }
    // stickers.clear();
    // xcoor.clear();
    // ycoor.clear();
    base = new Image();
    *base = *other.base;
    stickers = other.stickers;
    xcoor = other.xcoor;
    ycoor = other.ycoor;
    // for(unsigned i = 0; i < other.stickers.size(); i++) {
    //     stickers.push_back(other.stickers[i]);
    //     if(other.xcoor[i] != NULL && other.ycoor[i] != NULL) {
    //         xcoor.push_back(new int(*other.xcoor[i]));
    //         ycoor.push_back(new int(*other.ycoor[i]));
    //     }
    //     else {
    //         xcoor.push_back(NULL);
    //         ycoor.push_back(NULL);
    //     }
    // }
}



