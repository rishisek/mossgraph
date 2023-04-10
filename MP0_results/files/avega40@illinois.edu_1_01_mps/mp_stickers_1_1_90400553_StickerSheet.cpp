#include "Image.h"
#include "StickerSheet.h"

using namespace std;

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    image_ = picture;
    layers_.resize(max);
    xCoords_.resize(max);
    yCoords_.resize(max);
}

int StickerSheet::addSticker(Image &sticker, int x, int y) {
    for (unsigned int l = 0; l < layers_.size(); l++) {
        if (layers_[l] == NULL) {
            layers_[l] = &sticker;
            xCoords_[l] = x;
            yCoords_[l] = y;
            return l;
        }
    }
    layers_.push_back(&sticker);
    xCoords_.push_back(x);
    yCoords_.push_back(y);
    return layers_.size() - 1;
}

void StickerSheet::changeMaxStickers(unsigned int max) {
    layers_.resize(max);
    xCoords_.resize(max);
    yCoords_.resize(max);
}

Image *StickerSheet::getSticker(unsigned int index) {
    if (index >= layers_.size()) {
        return NULL;
    }
    return layers_[index];
}

int StickerSheet::layers() const {
    return layers_.size();
}

void StickerSheet::removeSticker(unsigned int index) {
    if (index < layers_.size()) {
        layers_[index] = NULL;
    }
}

Image StickerSheet::render() const {
    int minX = 0;
    int minY = 0;
    int maxX = image_.width();
    int maxY = image_.height(); 
    for (unsigned int i = 0; i < layers_.size(); i++) {
        if (layers_[i] != NULL) {
            int curMinX = xCoords_[i];
            int curMinY = yCoords_[i];
            int curMaxX = layers_[i]->width();
            int curMaxY = layers_[i]->height();
            minX = min(minX, curMinX);
            minY = min(minY, curMinY);
            if (curMinX + curMaxX - 1 > maxX) {
                maxX = max(maxX, curMinX + curMaxX);
            }
            if (curMinY + curMaxY - 1 > maxY) {
                maxY = max(maxY, curMinY + curMaxY);
            }
        }
    }
    Image image(maxX-minX, maxY-minY);
    for (unsigned int x = 0; x < image_.width(); x++) {
        for(unsigned int y = 0; y < image_.height(); y++) {
            image.getPixel(x-minX, y-minY) = image_.getPixel(x,y);
        }
    }
    for (unsigned int i = 0; i < layers_.size(); i++) {
        if (layers_[i] == NULL) {
            continue;
        }
        for (unsigned int x = 0; x < layers_[i]->width(); x++) {
            for(unsigned int y = 0; y < layers_[i]->height(); y++) {
                if (layers_[i]->getPixel(x,y).a != 0) {
                    image.getPixel(x+xCoords_[i]-minX, y+yCoords_[i]-minY) = layers_[i]->getPixel(x,y);
                }
            }
        }
    }
    return image;
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned int layer, int x, int y) {
    if (layer >= layers_.capacity()) {
        return -1;
    }
    layers_[layer] = &sticker;
    xCoords_[layer] = x;
    yCoords_[layer] = y;
    return layer;
}

bool StickerSheet::translate(unsigned int index, int x, int y) {
    if (layers_[index] == NULL || index >= layers_.size()) {
        return false;
    }
    xCoords_[index] = x;
    yCoords_[index] = y;
    return true;
}