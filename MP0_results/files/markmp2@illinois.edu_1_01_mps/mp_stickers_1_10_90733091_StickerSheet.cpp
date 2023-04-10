#include "StickerSheet.h"
#include "Image.h"
#include <algorithm>
#include <iostream>

StickerSheet::StickerSheet(const Image & picture, unsigned max) {
    image = picture;
    maxStickers = max;
    stickerSheet = new Image*[maxStickers];
    xPos = new unsigned[maxStickers];
    yPos = new unsigned[maxStickers];
    for (unsigned int i = 0; i < max; i++) {
        stickerSheet[i] = nullptr;
    }
}

void StickerSheet::clear() {
    delete[] xPos;
    delete[] yPos;
    delete[] stickerSheet;
    xPos = nullptr;
    yPos = nullptr;
    stickerSheet = nullptr;
}

StickerSheet::StickerSheet(const StickerSheet & other) {
    copy(other);
    for (unsigned i = 0; i < maxStickers; i++) {
        if(other.stickerSheet[i] != nullptr) {
        stickerSheet[i] = other.stickerSheet[i];
        } else {
        stickerSheet[i] = nullptr;
        }
        xPos[i] = other.xPos[i];
        yPos[i] = other.yPos[i];
    }
}

void StickerSheet::copy(const StickerSheet & other) {
    // copies everything but the positions
    image = other.image;
    maxStickers = other.maxStickers;
    stickerSheet = new Image*[maxStickers];
    xPos = new unsigned[maxStickers];
    yPos = new unsigned[maxStickers];
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other) {
    clear();
    copy(other);
    for (unsigned i = 0; i < other.maxStickers; i++) {
        if(other.stickerSheet[i] != nullptr) {
            stickerSheet[i] = other.stickerSheet[i];
        } else {
            stickerSheet[i] = nullptr;
        }
        xPos[i] = other.xPos[i];
        yPos[i] = other.yPos[i];
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    if (max == maxStickers) {
        return;
    }
    Image **tempImage = new Image*[max];
    unsigned *tempX = new unsigned[max];
    unsigned *tempY = new unsigned[max];
    for (unsigned int i = 0; i < max; i++) {
        tempImage[i] = stickerSheet[i];
        tempX[i] = xPos[i];
        tempY[i] = yPos[i];
    }
    if (max > maxStickers) {
        for (unsigned int i = 0; i < max; i++) {
            tempImage[i] = nullptr;
        }
    }
    clear();
    stickerSheet = tempImage;
    xPos = tempX;
    yPos = tempY;
    maxStickers = max;
}

int StickerSheet::addSticker(Image &sticker, int x, int y) {
    for (unsigned int i = 0; i <= maxStickers; i++) {
        if (stickerSheet[i] == nullptr) {
            stickerSheet[i] = &sticker;
            xPos[i] = x;
            yPos[i] = y;
            layer++;
            return i;
        }
    }
    return -1;
}

bool StickerSheet::translate(unsigned index, int x, int y) {
    if (stickerSheet[index] == nullptr || index >= maxStickers) {
        return false;
    }
    xPos[index] = x;
    yPos[index] = y;
    return true;
}

void StickerSheet::removeSticker(unsigned index) {
    if (index < maxStickers && stickerSheet[index] != nullptr) {
        stickerSheet[index] = nullptr;
        delete stickerSheet[index];
        layer--;
    }
}

Image* StickerSheet::getSticker(unsigned index) {
    if (stickerSheet[index] == nullptr || index > maxStickers) {
        return nullptr;
    }
    return stickerSheet[index];
}

int StickerSheet::layers() const {
    return maxStickers;
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
    if (stickerSheet[layer] != nullptr || layer > maxStickers) {
        return -1;
    }
    return layer;
}

Image StickerSheet::render() const {
    unsigned w = image.width();
    unsigned h = image.height();
    for (unsigned i = 0; i < maxStickers; i++) {
        if (stickerSheet[i] != nullptr) {
            w = std::max(image.width(), xPos[i] + stickerSheet[i]->width());
            h = std::max(image.height(), yPos[i] + stickerSheet[i]->height());
        }
    }
    Image returnImage(w, h);
    for (unsigned x = 0; x < image.width(); x++) {
        for (unsigned y = 0; y < image.height(); y++) {
            cs225::HSLAPixel & pixel = returnImage.getPixel(x, y);
            pixel = image.getPixel(x, y);
        }
    }
    for (unsigned i = 0; i < maxStickers; i++) {
        if (stickerSheet[i] != nullptr) {
          unsigned int stickerWidth = stickerSheet[i]->width();
          unsigned int stickerHeight = stickerSheet[i]->height();
          unsigned int stickerX = xPos[i];
          unsigned int stickerY = yPos[i];
          for (unsigned x = 0; x < stickerSheet[i]->width(); x++) {
                for (unsigned y = 0; y < stickerSheet[i]->height(); y++) {
                    cs225::HSLAPixel & basepix = returnImage.getPixel(xPos[i] + x, yPos[i] + y);
                    cs225::HSLAPixel & stickPix = stickerSheet[i]->getPixel(x, y);
                    if (stickPix.a != 0) {
                        basepix = stickPix;
                    }
                }
            }
        }
    }
    return returnImage;
}