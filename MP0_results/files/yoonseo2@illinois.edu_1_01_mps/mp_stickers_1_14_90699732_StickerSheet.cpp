#include "StickerSheet.h"

using namespace std;

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
  base_ = picture;
  max_ = max;
  stickers_.assign(max_, NULL);
  xcord_.assign(max_, 0);
  ycord_.assign(max_, 0);
}

StickerSheet::StickerSheet(const StickerSheet &other) {
  _copy(other);
}

void StickerSheet::_copy(const StickerSheet &other) {
  if (this == &other) { return; }
  base_ = other.base_;
  max_ = other.max_;
  stickers_ = other.stickers_;
  xcord_ = other.xcord_;
  ycord_ = other.ycord_;
  // stickers_.assign(max_, NULL);
  // xcord_.assign(max_, 0);
  // ycord_.assign(max_, 0);

  // for (unsigned int idx = 0; idx < max_; ++idx) {
  //     stickers_.at(idx) = (other.stickers_.at(idx));
  //     xcord_.at(idx) = other.xcord_.at(idx);
  //     ycord_.at(idx) = other.ycord_.at(idx);
  // }
}

StickerSheet::~StickerSheet() {
  max_ = 0;
}

const StickerSheet & StickerSheet::operator=(const StickerSheet &other) {
  if (this == &other) { return *this; }
  _copy(other);
  return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
  vector<Image*> tmp_stickers_(max_, NULL);
  vector<int> tmp_xcord_(max_, 0);
  vector<int> tmp_ycord_(max_, 0);
  if (max_ == max) { 
    return;
  } else if (max_ < max) {
      for (unsigned i = 0; i < max_; ++i) {
        tmp_stickers_.at(i) = stickers_.at(i);
        tmp_xcord_.at(i) = xcord_.at(i);
        tmp_ycord_.at(i) = ycord_.at(i);     
      }
      tmp_stickers_.resize(max);
      tmp_xcord_.resize(max);
      tmp_ycord_.resize(max);
  } else { // max < max_
    for (unsigned int i = 0; i < max; ++i) {
      tmp_stickers_.at(i) = stickers_.at(i);
      tmp_xcord_.at(i) = xcord_.at(i);
      tmp_ycord_.at(i) = ycord_.at(i);
    }
  }
  max_ = max;
  stickers_ = tmp_stickers_;
  xcord_ = tmp_xcord_;
  ycord_ = tmp_ycord_;
}

int StickerSheet::addSticker(Image &sticker, int x, int y) {
  for (unsigned int idx = 0; idx < stickers_.size(); ++idx) 
  {
    if (stickers_.at(idx) == NULL) 
    {
        stickers_.at(idx) = &sticker; 
        xcord_.at(idx) = x;
        ycord_.at(idx) = y;
        return idx;      
    }
  }
  if (stickers_.size() >= max_) { max_++; }
    stickers_.push_back(&sticker);
    xcord_.push_back(x);
    ycord_.push_back(y);
    return stickers_.size() - 1;
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
  if (layer >= stickers_.size()) { // check if layer is within bound
    return -1;
  }

  if (stickers_.at(layer) != NULL) {
    removeSticker(layer);
  }

  stickers_.at(layer) = &sticker;
  xcord_.at(layer) = x;
  ycord_.at(layer) = y;
  return (int)layer;
}

bool StickerSheet::translate(unsigned index, int x, int y) {
  if (index > max_ || stickers_.at(index) == NULL)
  {
    return false;
  }
  xcord_.at(index) = x;
  ycord_.at(index) = y;
  return true;
}

void StickerSheet::removeSticker(unsigned index) {
  if (!(stickers_.at(index))|| index >= stickers_.size()) {
    return;
  }
  stickers_.at(index) = NULL;
  xcord_.at(index) = 0;
  ycord_.at(index) = 0;
}

Image * StickerSheet::getSticker(unsigned index) const {
  if((stickers_.at(index) == NULL) || (index >= stickers_.size())){
      return NULL;
  }
  return stickers_.at(index);
}

int StickerSheet::layers() const {
 return stickers_.size();
}

Image StickerSheet::render() const {
  int new_W = base_.width();
  int new_H = base_.height(); 
  int negative_x = 0;
  int negative_y = 0;
  for(unsigned int i = 0; i < stickers_.size(); ++i){
    int sticker_X = xcord_.at(i);
    int sticker_Y = ycord_.at(i);
    
    if(stickers_.at(i) != NULL){
      int sticker_W = stickers_.at(i)->width();
      int sticker_H = stickers_.at(i)->height();
      
      if(sticker_X < negative_x)
      {
        negative_x = base_.width() + abs(sticker_X); // when canvas is enlarged with white space on the left of base_
      }
      
      if(sticker_Y < negative_y)
      {
        negative_y = base_.height() + abs(sticker_Y); // when canvas is enlarged with white space on the top of base_
      }
      
      if((sticker_X + sticker_W) > new_W)
      {
        new_W = sticker_X + sticker_W; // when canvas is enlarged with white space on the right of base_
      }
      
      if((sticker_Y + sticker_H) > new_H)
      {
        new_H = sticker_Y + sticker_H; // when canvas is enlarged with white space on the bottom of base_
      }
    }
  }
  // either new_W or negative_x is changed
  // either new_H or negative_y is changed
  Image new_image(unsigned(new_W) + abs(negative_x), unsigned(new_H) + abs(negative_y));

  // starts from the negative_x and negative_y bc they are either 0 or enlarged
  for(unsigned int w = abs(negative_x); w < base_.width() + abs(negative_x); ++w)
  {
      for(unsigned int h = abs(negative_y); h < base_.height() + abs(negative_y); ++h)
      {
        new_image.getPixel(w, h) = base_.getPixel(w - negative_x, h - negative_y);
      }
  }

  for(unsigned int i = 0; i < stickers_.size(); ++i)
  {
      if(stickers_.at(i) != NULL)
      {
          int sticker_W = stickers_.at(i)->width();
          int sticker_H = stickers_.at(i)->height();
          int sticker_X = xcord_.at(i) - negative_x;
          int sticker_Y = ycord_.at(i) - negative_y;
          // starts at sticker_x and sticker_y and they are scaled accordingly with negative checking logic above
          for(int x = sticker_X; x < sticker_X + sticker_W; ++x)
          {
              for(int y = sticker_Y; y < sticker_Y + sticker_H; ++y)
              {
                  cs225::HSLAPixel &sticker_pixel = stickers_.at(i)->getPixel(x - sticker_X, y - sticker_Y);
                  cs225::HSLAPixel &image_pixel = new_image.getPixel(x, y);
                  if(sticker_pixel.a != 0)
                  {
                      image_pixel = sticker_pixel;
                  }
              }
          }
      }
  }
  return new_image;
}