#include "StickerSheet.h"
#include "Image.h"
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"

using namespace cs225;

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    picture_ = picture;
    max_ = max;
    //? = Image(picture)
}

StickerSheet::StickerSheet(const StickerSheet &other) {

}

StickerSheet::~StickerSheet() {
    
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other) {
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    if (max == maxPic) {
        return;
    }
}

int StickerSheet::addSticker(Image &sticker, int x, int y) {
    return -1;
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
    return -1;
}

bool StickerSheet::translate(unsigned index, int x, int y) {
    return false;
}

void StickerSheet::removeSticker(unsigned index) {

}

Image* StickerSheet::getSticker(unsigned index) {
    return NULL;
}

int StickerSheet::layers() const {
    return -1;
}

Image StickerSheet::render() const {
Image result;
return result;
}