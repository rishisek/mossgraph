#include "StickerSheet.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <iostream>
#include <sstream>
#include <cmath>

using namespace cs225;

StickerSheet::StickerSheet (const Image &picture, unsigned max) {
  max_stickers = max;
  sticker_image = picture;
  emptyVectors();
}

StickerSheet::~StickerSheet () {
  this->emptyVectors();
}

StickerSheet::StickerSheet (const StickerSheet& other) {
  this->sticker_image = other.sticker_image;
  this->max_stickers = other.max_stickers;
  this->emptyVectors();
  for (int i = 0; i < (int) other.stickers.size(); i++) {
    this->x_coords.push_back(other.x_coords.at(i));
    this->y_coords.push_back(other.y_coords.at(i));
    this->stickers.push_back(other.stickers.at(i));
  }
}

const StickerSheet & StickerSheet::operator= (const StickerSheet& other) {
  this->max_stickers = other.max_stickers;
  this->sticker_image = other.sticker_image;
  this->emptyVectors();
  for (int i = 0; i < (int) other.stickers.size(); i++) {
    this->x_coords.push_back(other.x_coords.at(i));
    this->y_coords.push_back(other.y_coords.at(i));
    this->stickers.push_back(other.stickers.at(i));
  }
  return* this;
}

void StickerSheet::changeMaxStickers (unsigned max) {
  if ((int) max < max_stickers) {
    while ((int) max < (int) stickers.size()) {
      x_coords.pop_back();
      y_coords.pop_back();
      stickers.pop_back();
    }
  }
  max_stickers = max;
}

int StickerSheet::addSticker (Image& sticker, int x, int y) {
  if (max_stickers != (int) stickers.size()) {
    stickers.push_back(&sticker);
    x_coords.push_back(x);
    y_coords.push_back(y);
    return stickers.size() - 1;
  }
  return -1;
}

int StickerSheet::setStickerAtLayer (Image &sticker, unsigned layer, int x, int y) {

  if ((int) layer >= 0 and (int) layer < max_stickers) {
    stickers.at(layer) = &sticker;
    x_coords.at(layer) = x;
    y_coords.at(layer) = y;
    return stickers.size();
  }
  return -1;
}

bool StickerSheet::translate (unsigned index, int x, int y) {
  if (!(index < stickers.size()) or !(index >= 0)) {
    return false;
  }
  y_coords.at(index) = y;
  x_coords.at(index) = x;
  return true;
}

void StickerSheet::removeSticker (unsigned index) {
  if (index < stickers.size() and index >= 0) {
    this->stickers.erase(this->stickers.begin() + index);
    this->x_coords.erase(this->x_coords.begin() + index);
    this->y_coords.erase(this->y_coords.begin() + index);
  }
}

Image* StickerSheet::getSticker (unsigned index) {
  if (!(index < stickers.size()) or !(index >= 0)) {
    return nullptr;
  }
  return stickers.at(index);
}

int StickerSheet::layers () const {
  return max_stickers;
}

Image StickerSheet::render () const {
  int max_width = 0;
  int max_height = 0;
  int temp = 0;
  for (int i = 0; i < (int) this->stickers.size(); i++) {
    int x = x_coords.at(i);
    int y = y_coords.at(i);
    int image_width = this->stickers.at(i)->width();
    int image_height = this->stickers.at(i)->height();
    if (max_width < image_width + x) {
      max_width = image_width + x;
      temp++;
    }
    if (max_height < image_height + y) {
      max_height = image_height + y;
      temp--;
    } 
  }
  Image stickerSheet = this->sticker_image;

  if (int (this->sticker_image.width()) < max_width and int (this->sticker_image.height()) < max_height) {
    stickerSheet.resize(max_width, max_height);
  } else if (int (this->sticker_image.width()) < max_width) {
    stickerSheet.resize(max_width, this->sticker_image.height());
  } else if (int (this->sticker_image.height()) < max_height) {
    stickerSheet.resize(this->sticker_image.width(), max_height);
  }
  for (int i = 0; i < int(stickers.size()); i++) {
    int x_origin = this->x_coords.at(i);
    int y_origin = this->y_coords.at(i);
    temp++;

    int sticker_height = this->stickers.at(i)->height();
    int sticker_width = this->stickers.at(i)->width();

    for (int y = y_origin; y < sticker_height + y_origin; y++) {
      for (int x = x_origin; x < sticker_width + x_origin; x++){
        HSLAPixel& sticker_pixel = stickerSheet.getPixel(x, y);
        HSLAPixel& image_pixel = this->stickers.at(i)->getPixel(x - x_origin, y - y_origin);
        if (image_pixel.a == 0) {
          int set = 0;
        } else {
          sticker_pixel.h = image_pixel.h;
          sticker_pixel.s = image_pixel.s;
          sticker_pixel.l = image_pixel.l;
          sticker_pixel.a = image_pixel.a;
        }
      }
    }
  }
  return stickerSheet;
}

void StickerSheet::emptyVectors() {
  for (int i = 0; i < (int) this->stickers.size(); i++) {
    this->x_coords.pop_back();
    this->y_coords.pop_back();
    this->stickers.pop_back();
  }
}