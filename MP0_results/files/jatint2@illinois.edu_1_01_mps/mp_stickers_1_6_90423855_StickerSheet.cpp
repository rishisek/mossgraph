#include "StickerSheet.h"
#include <vector>
using namespace std;

StickerSheet::StickerSheet(const Image & picture, unsigned max){
    baseimage_ = picture;
    max_ = max;
    paper_.resize(max_);
    xcoord_.resize(max_);
    ycoord_.resize(max_); 
    numberoflayers=0;
}

StickerSheet::StickerSheet(const StickerSheet & other){
    baseimage_=other.baseimage_;
    max_=other.max_;
    paper_.resize(other.paper_.size());
    for(unsigned int i=0; i<paper_.size();i++){
        paper_[i]=other.paper_[i];
    }
    xcoord_.resize(other.xcoord_.size());
    for(unsigned int i=0; i<xcoord_.size();i++){
        xcoord_[i]=other.xcoord_[i];
    }
    ycoord_.resize(other.ycoord_.size());
    for(unsigned int i=0; i<ycoord_.size();i++){
        ycoord_[i]=other.ycoord_[i];
    }
}

int StickerSheet::addSticker(Image & sticker, int x, int y){
    for(unsigned int i=0; i<paper_.size();i++){
        if(paper_[i]==NULL){
            paper_[i]=&sticker;
            xcoord_[i]=x;
            ycoord_[i]=y;
            return i;
        }
    }
    paper_.push_back(&sticker);
    xcoord_.push_back(x);
    ycoord_.push_back(y);
    max_ += 1;
    return paper_.size()-1;
}

void StickerSheet::changeMaxStickers(unsigned max){
    if(max<=max_){
        paper_.resize(max);
        xcoord_.resize(max);
        ycoord_.resize(max);
    }
    else{
        paper_.resize(max);
        xcoord_.resize(max);
        ycoord_.resize(max);
    }
    max_=max;
}

Image * StickerSheet::getSticker(unsigned index){
    if(index>=0 && index<paper_.size()){
        return paper_[index];
    }
    else{return NULL;}
}

int StickerSheet::layers() const{
    return max_;
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other){
    baseimage_=other.baseimage_;
    max_=other.max_;
    paper_.resize(other.paper_.size());
    for(unsigned int i=0; i<paper_.size();i++){
        paper_[i]=other.paper_[i];
    }
    xcoord_.resize(other.xcoord_.size());
    for(unsigned int i=0; i<xcoord_.size();i++){
        xcoord_[i]=other.xcoord_[i];
    }
    ycoord_.resize(other.ycoord_.size());
    for(unsigned int i=0; i<ycoord_.size();i++){
        ycoord_[i]=other.ycoord_[i];
    }
    return *this;
}

void StickerSheet::removeSticker(unsigned index){
    if(index<max_ && paper_[index]!=NULL){
        //paper_.erase(paper_.begin()+index);
        paper_[index]=NULL;
        // xcoord_[index]=0;
        // ycoord_[index]=0;
    }
    else{return;}
}

Image StickerSheet::render() const{
// Image temp;
//  temp = baseimage_;
  int tempwidth = baseimage_.width();
  int tempheight = baseimage_.height();

  int maximum_x_pos = tempwidth; 
  int maximum_y_pos = tempheight;
  int minimum_x_pos = 0; 
  int minimum_y_pos = 0; 

    
  for (unsigned int i = 0; i < max_; i++){
    if(paper_[i] != NULL){
        int w = xcoord_[i] + paper_[i]->width();
        int h = ycoord_[i] + paper_[i]->height();
      if(w > maximum_x_pos){
        maximum_x_pos = w;
      }
      if(h > maximum_y_pos){
        maximum_y_pos = h;
      }
      if(xcoord_[i]<minimum_x_pos){
        minimum_x_pos=xcoord_[i];
      }
      if(ycoord_[i]<minimum_y_pos){
        minimum_y_pos=ycoord_[i];
      }
    }
  }
//   temp = baseimage_;
//   temp.resize(tempwidth, tempheight);
// cout << tempwidth << endl;
// cout << tempheight << endl;
// cout <<minimum_x_pos << endl;
// cout <<minimum_y_pos <<  endl;
// cout << maximum_x_pos << endl;
// cout << maximum_y_pos << endl;
unsigned int x = maximum_x_pos - minimum_x_pos;
unsigned int y = maximum_y_pos - minimum_y_pos;

Image temp(x,y);
for (int e=0;e<tempwidth;e++){
    for(int f=0;f<tempheight;f++){
        temp.getPixel(e-minimum_x_pos, f-minimum_y_pos) = baseimage_.getPixel(e,f);
    }
}

  for(unsigned int j = 0; j < max_; j++){
    if(paper_[j] != NULL){
      for(unsigned int a = xcoord_[j]; a < (xcoord_[j] + paper_[j]->width()); a++){
        for(unsigned int b = ycoord_[j]; b < (ycoord_[j] + paper_[j]->height()); b++){
          if(paper_[j]->getPixel((a - xcoord_[j]), (b - ycoord_[j])).a != 0){
            temp.getPixel(a - minimum_x_pos, b - minimum_y_pos) = paper_[j]->getPixel((a - xcoord_[j]), (b - ycoord_[j]));
          }
        }
      }
    }
  }
  return temp;
   
}

int StickerSheet::setStickerAtLayer(Image & sticker, unsigned layer, int x, int y){
    if(layer<0 || layer> max_ - 1){
        return -1;
    }
    paper_[layer] = &sticker;
    xcoord_[layer] = x;
    ycoord_[layer] = y;
    return layer;
}

bool StickerSheet::translate(unsigned index, int x, int y){
    if(index>=0 && index<paper_.size() && paper_[index]!=NULL){
        xcoord_[index]=x;
        ycoord_[index]=y;
        return true;
    }
    return false;
}