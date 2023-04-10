#include "StickerSheet.h"
#include "Image.h"

StickerSheet::StickerSheet(const Image & picture, unsigned max) {
    baseSheet = picture;
    maxStickers = max;
    imageSheet = new Image*[maxStickers];
    positionX = new unsigned[maxStickers];
    positionY = new unsigned[maxStickers];
    for (unsigned int i = 0; i < max; i++) {
        imageSheet[i] = nullptr;
    }
}

StickerSheet::~StickerSheet(){
    clear();
}

void StickerSheet::clear() {
    delete[] positionX;
    delete[] positionY;
    delete[] imageSheet;
    positionX = nullptr;
    positionY = nullptr;
    imageSheet = nullptr;
}

StickerSheet::StickerSheet(const StickerSheet & other) {
    copy(other);
    for (unsigned i = 0; i < maxStickers; i++) {
        if(other.imageSheet[i] != nullptr) {
        imageSheet[i] = other.imageSheet[i];
        } else {
        imageSheet[i] = nullptr;
        }
        positionX[i] = other.positionX[i];
        positionY[i] = other.positionY[i];
    }
}

void StickerSheet::copy(const StickerSheet & other) {
    // copies everything but the positions
    baseSheet = other.baseSheet;
    maxStickers = other.maxStickers;
    imageSheet = new Image*[maxStickers];
    positionX = new unsigned[maxStickers];
    positionY = new unsigned[maxStickers];
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other) {
    clear();
    copy(other);
    for (unsigned i = 0; i < other.maxStickers; i++) {
        if(other.imageSheet[i] != nullptr) {
            imageSheet[i] = other.imageSheet[i];
        } else {
            imageSheet[i] = nullptr;
        }
        positionX[i] = other.positionX[i];
        positionY[i] = other.positionY[i];
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
        tempImage[i] = imageSheet[i];
        tempX[i] = positionX[i];
        tempY[i] = positionY[i];
    }
    if (max > maxStickers) {
        for (unsigned int i = 0; i < max; i++) {
            tempImage[i] = nullptr;
        }
    }
    clear();
    imageSheet = tempImage;
    positionX = tempX;
    positionY = tempY;
    maxStickers = max;
}

int StickerSheet::addSticker(Image &sticker, int x, int y) {
    for (unsigned i = 0; i < maxStickers; i++) {
        if (imageSheet[i] == nullptr) {
            imageSheet[i] = &sticker;
            positionX[i] = x;
            positionY[i] = y;
            return i;
        }
    }
    changeMaxStickers(maxStickers);
    setStickerAtLayer(sticker, maxStickers, x, y);
    // addSticker(&sticker, x, y);
    return maxStickers;
}

bool StickerSheet::translate(unsigned index, int x, int y) {
    if (imageSheet[index] == nullptr || index >= maxStickers) {
        return false;
    }
    positionX[index] = x;
    positionY[index] = y;
    return true;
}

void StickerSheet::removeSticker(unsigned index) {
    if (index < maxStickers && imageSheet[index] != nullptr) {
        imageSheet[index] = nullptr;
        delete imageSheet[index];
    }
}

Image* StickerSheet::getSticker(unsigned index) {
    if (imageSheet[index] == nullptr || index > maxStickers) {
        return nullptr;
    }
    return imageSheet[index];
}

int StickerSheet::layers() const {
    int count = 0;
    for (unsigned i = 0; i < maxStickers; i++) {
        if (imageSheet[i] == nullptr) {
            count++;
        }
    }
    return count;
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
    if (imageSheet[layer] != nullptr) {
        return -1;
    }
    if (layer > maxStickers) {
        addSticker(sticker, x, y);
        return layer;
    }
    imageSheet[layer] = &sticker;
    positionX[layer] = x;
    positionY[layer] = y;
    return layer;
}

Image StickerSheet::render() const {
    unsigned w = 0;
    unsigned h = 0;
    for (unsigned i = 0; i < maxStickers; i++) {
        if (imageSheet[i] != nullptr) {
            w = (positionX[i] + imageSheet[i]->width() > baseSheet.width()) ? positionX[i] + 
            imageSheet[i]->width() : baseSheet.width();
            h = (positionY[i] + imageSheet[i]->height() > baseSheet.height()) ? positionY[i] + 
            imageSheet[i]->height() : baseSheet.height();
        }
    }
    if (w == 0 || h == 0) {
        return baseSheet;
    }
    Image returnImage(w, h);
    for (unsigned x = 0; x < w; x++) {
        for (unsigned y = 0; y < h; y++) {
            HSLAPixel & pixel = returnImage.getPixel(x, y);
            pixel = baseSheet.getPixel(x, y);
        }
    }
    for (unsigned i = 0; i < maxStickers; i++) {
        if (imageSheet[i] != nullptr) {
            for (unsigned x = 0; x < imageSheet[i]->width(); x++) {
                for (unsigned y = 0; y < imageSheet[i]->height(); y++) {
                    HSLAPixel & basepix = returnImage.getPixel(positionX[i] + x, positionY[i] + y);
                    HSLAPixel & stickPix = imageSheet[i]->getPixel(x, y);
                    if (stickPix.a != 0) {
                        basepix = stickPix;
                    }
                }
            }
        }
    }
    return returnImage;
}