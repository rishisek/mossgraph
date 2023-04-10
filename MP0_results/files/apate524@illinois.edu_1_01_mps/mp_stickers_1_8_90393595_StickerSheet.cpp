#include "StickerSheet.h"
#include "math.h"

//////////////////////////////////

StickerSheet::StickerSheet(const Image &picture, unsigned max) { // Initializes this StickerSheet with a deep copy of the base picture and the ability to hold a max number of stickers (Images) with indices 0 through max - 1.
  image_ = picture;
  maxStickers_ = max;
  stickers_ = std::vector<Image*>(maxStickers_);
  locations_ = std::vector<std::pair<int, int>>(maxStickers_);
}

//////////////////////////////////

void StickerSheet::changeMaxStickers(unsigned max) { // Modifies the maximum number of stickers that can be stored on this StickerSheet without changing existing stickers' indices.
  maxStickers_ = max;
  stickers_.resize(maxStickers_);
  locations_.resize(maxStickers_);
}

//////////////////////////////////
  
int StickerSheet::addSticker(Image &sticker, int x, int y) { // Adds a sticker to the StickerSheet, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet.
  unsigned int layer = 0;

  for (unsigned int i = 0; i < maxStickers_; i++) {
    layer = i;
    if (stickers_.at(i) == NULL) {
      break;
    }
  }

  if (layer == maxStickers_ - 1 && stickers_.at(layer) != NULL) {
    layer++;
    maxStickers_++;
    changeMaxStickers(maxStickers_);
  }

  stickers_.at(layer) = &sticker;
  locations_.at(layer) = {x, y};

  return layer;
}

//////////////////////////////////

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) { // Adds a sticker to the StickerSheet at layer layer, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet.
  if (layer >= maxStickers_ || layer < 0) {
    return -1;
  }

  if (layer == maxStickers_ - 1 && stickers_.at(layer) != NULL) {
    layer++;
    maxStickers_++;
    changeMaxStickers(maxStickers_);
  }

  stickers_.at(layer) = &sticker;
  locations_.at(layer) = {x, y};

  return layer;
}

//////////////////////////////////

bool StickerSheet::translate(unsigned index, int x, int y) { // Changes the x and y coordinates of the Image in the specified layer.
  if (index >= maxStickers_ || index < 0 || stickers_.at(index) == NULL) {
    return false;
  }
  locations_.at(index) = {x, y};
  return true;
}

//////////////////////////////////

void StickerSheet::removeSticker(unsigned index) { // Removes the sticker at the given zero-based layer index.
  stickers_.at(index) = NULL;
  locations_.at(index) = {NULL, NULL};
}

//////////////////////////////////

Image* StickerSheet::getSticker(unsigned index) { // Returns a pointer to the sticker at the specified index, not a copy of it.
  if (index >= maxStickers_ || index < 0 || stickers_.at(index) == NULL) {
    return NULL;
  }
  return stickers_.at(index);
}

//////////////////////////////////

int StickerSheet::layers() const { // Returns the total number of layers available on the Stickersheet.
  return maxStickers_;
}

//////////////////////////////////

Image StickerSheet::render() const { // Renders the whole StickerSheet on one Image and returns that Image.

  Image temp = image_;

  int minOffsetX = 0;
  int maxOffsetX = 0;
  int minOffsetY = 0;
  int maxOffsetY = 0;

  for (unsigned int i = 0; i < maxStickers_; i++) {
    if (stickers_.at(i) != NULL) {
      if (locations_.at(i).first < 0 && locations_.at(i).first < minOffsetX) {
        minOffsetX = locations_.at(i).first;
      }
      if (locations_.at(i).second < 0 && locations_.at(i).second < minOffsetY) {
        minOffsetY = locations_.at(i).second;
      }
      if (((locations_.at(i).first + stickers_.at(i)->width() > temp.width()) || (unsigned int)locations_.at(i).first > temp.width()) && locations_.at(i).first > maxOffsetX) {
        maxOffsetX = locations_.at(i).first + stickers_.at(i)->width();
      }
      if ((locations_.at(i).second + stickers_.at(i)->height() > temp.height() || (unsigned int)locations_.at(i).second > temp.height()) && locations_.at(i).second > maxOffsetY) {
        maxOffsetY = locations_.at(i).second + stickers_.at(i)->height();
      }
    }
  }

  if ((unsigned int)maxOffsetX > temp.width()) {
    temp.resize(temp.width() + abs(minOffsetX) + (maxOffsetX - temp.width()), temp.height());
  } else {
    temp.resize(temp.width() + abs(minOffsetX), temp.height());
  }
  if ((unsigned int)maxOffsetY > temp.height()) {
    temp.resize(temp.width(), temp.height() + abs(minOffsetY) + (maxOffsetY - temp.height()));
  } else {
    temp.resize(temp.width(), temp.height() + abs(minOffsetY));
  }

  Image temp2;

  temp2.resize(temp.width(), temp.height());

  for (unsigned int i = 0; i < temp.width() - abs(minOffsetX); i++) {
    for (unsigned int j = 0; j < temp.height() - abs(minOffsetY); j++) {
      cs225::HSLAPixel & oldPixel = temp.getPixel(i, j);
      cs225::HSLAPixel & newPixel = temp2.getPixel(i + abs(minOffsetX), j + abs(minOffsetY));
      newPixel = oldPixel;
    }
  }

  for (unsigned int k = 0; k < maxStickers_; k++) {
    if (stickers_.at(k) != NULL) {
      for (unsigned int i = 0; i < stickers_.at(k)->width(); i++) {
        for (unsigned int j = 0; j < stickers_.at(k)->height(); j++) {
          cs225::HSLAPixel & oldPixel = temp2.getPixel(locations_.at(k).first + abs(minOffsetX) + i, locations_.at(k).second + abs(minOffsetY) + j);
          cs225::HSLAPixel & newPixel = stickers_.at(k)->getPixel(i, j);
          if (newPixel.a != 0) {
            oldPixel = newPixel;
          }
        }
      }
    }
  }

  return temp2;
}

//////////////////////////////////
