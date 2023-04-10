#include <StickerSheet.h>
#include<vector>
#include <iostream>
using namespace std;

StickerSheet::StickerSheet(const Image &picture, unsigned max){
    sticker_max = max;
    sticker_count = 0;
    picture_ = picture;
    sheet_.resize(max);
    x_coord_.resize(max);
    y_coord_.resize(max);
}
StickerSheet::StickerSheet(const StickerSheet &other){
    sticker_max = other.sticker_max;
    sticker_count = other.sticker_count;
    picture_ = other.picture_;
    sheet_.resize(other.sticker_max);
    x_coord_.resize(other.sticker_max);
    y_coord_.resize(other.sticker_max);
    for(unsigned i = 0; i < sticker_max; i++){
        if(other.sheet_[i] != NULL){
            sheet_[i] = other.sheet_[i];
            x_coord_[i] = other.x_coord_[i];
            y_coord_[i] = other.y_coord_[i];
        }
    }
}

/*StickerSheet::~StickerSheet(){
    destroy(other);
}*/

/*void StickerSheet::destroy(const StickerSheet &other){
    sticker_max = 0;
    sticker_count = 0;
    for(unsigned i = 0; i < sticker_max; i++){
        if(other.sheet_[i] != NULL){
            sheet_[i] = 0;
            x_coord_[i] = 0;
            y_coord_[i] = 0;
        }
    }
}*/

const StickerSheet & StickerSheet::operator=(const StickerSheet &other){
    picture_ = other.picture_;
    sticker_max = other.sticker_max;
    sheet_.resize(other.sticker_max);
    x_coord_.resize(other.sticker_max);
    y_coord_.resize(other.sticker_max);
        for (unsigned i = 0; i < sticker_max; i++) {
            if(other.sheet_[i] != NULL) {
                sheet_[i] = other.sheet_[i];
                x_coord_[i] = other.x_coord_[i];
                y_coord_[i] = other.y_coord_[i];
            }
        }
    return *this;
}


void StickerSheet::changeMaxStickers(unsigned max){
    if(max < sticker_count){
        sticker_count = max;
        sticker_max = max;
        sheet_.resize(sticker_max);
        x_coord_.resize(sticker_max);
        y_coord_.resize(sticker_max);
    }
    sticker_max = max;
    sheet_.resize(sticker_max);
    x_coord_.resize(sticker_max);
    y_coord_.resize(sticker_max);
}

int StickerSheet::addSticker(Image &sticker, int x, int y){
  for(unsigned i = 0; i < sticker_max; i++){
    if (sheet_[i] == NULL) {
      sheet_[i] = &sticker;
      x_coord_[i] = x;
      y_coord_[i] = y;
      sticker_count++;
      return i;
    }
  }
  sticker_max++;
  sheet_.resize(sticker_max);
  x_coord_.resize(sticker_max);
  y_coord_.resize(sticker_max);
  sheet_[sticker_max-1] = &sticker;
  x_coord_[sticker_max-1] = x;
  y_coord_[sticker_max-1] = y;
  sticker_count = sticker_max;
  return int(sticker_count-1);
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y){
  if (layer >= sticker_max || layer < 0) {
    return -1;
  }
  sheet_[layer] = &sticker;
  x_coord_[layer] = x;
  y_coord_[layer] = y;
  sticker_count++;
  return layer;
}

bool StickerSheet::translate(unsigned index, int x, int y){
  if (index >= sheet_.size() || sheet_[index] == NULL){
  return false;
  }
  x_coord_[index] = x;
  y_coord_[index] = y;
  return true;
}

void StickerSheet::removeSticker(unsigned index){
  if(index < 0 || index >= sticker_max){
    return;
  }
  sheet_[index] = NULL;
  x_coord_[index] = 0;
  y_coord_[index] = 0;
  sticker_count--;
}

Image * StickerSheet::getSticker(unsigned index){
  if (index < 0 || index >= sticker_max || (sheet_[index] == NULL)) {
    return NULL;
  }
  return sheet_[index];
}

int StickerSheet::layers() const{
  return sticker_max;
}

Image StickerSheet::render () const{
  int low_x = 0;
  int up_x = picture_.width();
  int low_y = 0;
  int up_y = picture_.height();
  for (int i =0; i < (int)sticker_max; i++) {   // resize sheet
    if (sheet_[i] != NULL) {
      if (x_coord_[i] < low_x) {
        low_x = x_coord_[i];
      }
      if ((int)(x_coord_[i] + sheet_[i]->width( )) > up_x) {
        up_x = x_coord_[i] + sheet_[i]->width( );
        }
        if (y_coord_[i] < low_y) {
          low_y = y_coord_[i];
        }
        if ((int)(y_coord_[i] + sheet_[i]->height()) > up_y) {
          up_y = y_coord_[i] + sheet_[i]->height();
        }
      }
  }

  Image returnImage = Image(up_x - low_x, up_y - low_y); 
  for (unsigned i = 0; i < picture_.width(); i++) {
    for (unsigned j = 0; j < picture_.height(); j++) {
      returnImage.getPixel((int)(i-low_x), (int)(j-low_y)) = picture_.getPixel((int)i, (int)j);
      }
  }

  for (unsigned index = 0; index < sheet_.size(); index++) {
    if (sheet_[index] != NULL) {
      int new_w = sheet_[index]->width();
      int new_h = sheet_[index]->height();
      for (int i = 0; i < new_w; i++) {
        for (int j = 0; j < new_h; j++) {
          if (sheet_[index]->getPixel(i, j).a != 0) {
            returnImage.getPixel(i+(x_coord_[index]-low_x), j+(y_coord_[index]-low_y))= sheet_[index]->getPixel(i, j);
          }
        }
      }
    }
  }
  return returnImage;
}




