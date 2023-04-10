#include "StickerSheet.h"
#include <iostream>
#include <vector>

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
base_ = Image(picture);
max_ = max;
cover_ = std::vector<Image*>(max, NULL);
x_ = std::vector<int>(max, -1);
y_ = std::vector<int>(max, -1);
cur_ = 0;
}

StickerSheet::StickerSheet	(	const StickerSheet & 	other	){
  copy(other);
}
int StickerSheet::addSticker(Image& sticker, int x, int y) {
    if (cur_ == max_) {
        cover_.push_back(&sticker);
        x_.push_back(x);
        y_.push_back(y);
        cur_++;
        max_++;
        return max_ - 1;
    } 
    else {
        for (unsigned int i = 0; i < cover_.size(); i++) {
            if (cover_[i] == NULL) {
                cover_[i] = &sticker;
                x_[i] = x;
                y_[i] = y;
                cur_++;
                return i;
            }
        }
    }
    return -1;
}
Image* StickerSheet::getSticker(unsigned index){
    if(cover_[index]!= NULL){
        return cover_[index];
    }
    return NULL;
}

int StickerSheet::setStickerAtLayer (Image &sticker, unsigned layer, int x, int y){
    if(layer >= cover_.size()){
        return -1;
    }
    cover_[layer] =&(sticker);
    x_[layer] = x;
    y_[layer] = y;
    return layer;
}

void StickerSheet::changeMaxStickers(unsigned int max){
    if(cover_.size() > max){
        std::vector<Image*> temp (max,NULL);
        for(unsigned int i = 0; i < max; i++ ){
            temp[i] = cover_[i];
        }
        cover_ = temp;
    }
    else{
        for(unsigned int i = 0 ; i < max-max_; i++){ 
        cover_.push_back(NULL);
        x_.push_back(-1);
        y_.push_back(-1);
       }
    }
    max_ = max;
}

int StickerSheet::layers () const{
    return max_;
}

bool StickerSheet::translate(unsigned index, int x, int y){
    if(cover_[index] == NULL || index > cover_.size())
        return false;
    x_[index] = x;
    y_[index] = y;
    return true;
}

Image StickerSheet:: render () const{  
int max_w=base_.width();
int max_h=base_.height();
int minw = 0;
int minh = 0;
for (int i=0;i<max_;i++){
    if(cover_[i]!=NULL){
      if (x_[i]<minw)
        minw=x_[i];    
    if (y_[i]<minh)
        minh=y_[i];
    int k = x_[i]+cover_[i]->width();
    int l = y_[i]+cover_[i]->height();
    if (k>max_w)
      max_w=k;       
    if (l>max_h)
      max_h=l;
    }
}

Image img(unsigned (-minw+max_w), (-minh+max_h));
for (unsigned i=0;i<base_.width();i++){
  for (unsigned j=0;j<base_.height();j++){
    img.getPixel(i-minw,j-minh)= base_.getPixel(i,j);
  }
}    
for (int i = 0; i < max_; i++) 
    {
      if(cover_[i]!=NULL){
        for (unsigned w = 0; w < cover_[i]->width(); w++){
            for (unsigned h = 0; h < cover_[i]->height(); h++){
                if (cover_[i]->getPixel(w, h).a != 0)
                    img.getPixel(w + x_[i] - minw, h + y_[i] - minh) = cover_[i]->getPixel(w, h); 
            }
        }
      }
    } 
 return img;
}

void StickerSheet::removeSticker(unsigned index) {
    if(cover_[index]!= NULL){
        cover_[index] = NULL;
        x_[index] = -1;
        y_[index] = -1;
        cur_--;
    }
}

const StickerSheet & StickerSheet::operator=(const StickerSheet &other) {
  if(this != &other) {
  destroy();
  copy(other);
}
  return *this;
}

StickerSheet::~StickerSheet(){
  destroy();
}

void StickerSheet::destroy(){
    x_.clear();
    y_.clear();
    cover_.clear ();
}

void StickerSheet::copy(const StickerSheet &other){
  base_ = Image(other.base_);
  max_ = other.max_;
  cur_=other.cur_;
  for (int i = 0; i < max_; i++) {
    cover_.push_back(other.cover_[i]);
  }
  for (int i=0;i<max_;i++){
    x_.push_back(other.x_[i]);
    y_.push_back(other.y_[i]);
  }
}