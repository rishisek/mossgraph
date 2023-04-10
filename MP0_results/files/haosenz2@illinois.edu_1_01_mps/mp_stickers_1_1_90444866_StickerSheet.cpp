#include "StickerSheet.h"
#include <iostream>
#include <vector>
// StickerSheet::StickerSheet (const Image &picture, unsigned max){
//     base_ = new Image(picture);
//     max_ = max;
//     std::vector<Image*> vect (max,NULL); 
//     allsticker = vect;
//     std::vector<int> vectx (max,-1);
//     xcor_ = vectx;
//     std::vector<int> vecty (max,-1);
//     ycor_ = vecty;
//     num_ = 0;
// }
StickerSheet::StickerSheet(const Image &picture, unsigned max) {
base_ = Image(picture);
max_ = max;
allsticker = std::vector<Image*>(max, NULL);
xcor_ = std::vector<int>(max, -1);
ycor_ = std::vector<int>(max, -1);
num_ = 0;
}

StickerSheet::~StickerSheet(){
    xcor_.clear();
    ycor_.clear();
    allsticker.clear ();
}
// StickerSheet::StickerSheet	(	const StickerSheet & 	other	){
    // this->base_ = other.base_;
    // this->max_ = other.max_;
    // for(unsigned int i = 0; i < other.allsticker.size(); i++){
    //     this->allsticker[i] = other.allsticker[i];
    // }
    // this->num_ = other.num_;
    // for(unsigned int i = 0; i < other.xcor_.size();i ++){
    //     this->xcor_[i] = other.xcor_[i];
    // }
    //   for(unsigned int i = 0; i < other.ycor_.size();i ++){
    //     this->ycor_[i] = other.ycor_[i];
    // }
StickerSheet::StickerSheet(const StickerSheet &other)
{
    base_ = Image(other.base_);
    max_ = other.max_;
    num_ = other.num_;

    for (int i = 0; i < max_; i++)
    {
        allsticker.push_back(other.allsticker[i]);
    }
    for (int j = 0; j < max_; j++)
    {
        xcor_.push_back(other.xcor_[j]);
        ycor_.push_back(other.ycor_[j]);
    }
};



int StickerSheet::addSticker(Image& sticker, int x, int y){

    int toreturn = -1;
    if(num_ == max_){
        allsticker.push_back(&sticker);
        xcor_.push_back(x);
        ycor_.push_back(y);
        num_++;
       toreturn = max_;
        max_++;
    }else{
        for(unsigned int i = 0; i < allsticker.size(); i++){
            if (allsticker[i] == NULL){
                allsticker[i] = &sticker;
                toreturn = i;
                xcor_[i] = x;
                ycor_[i] = y;
                num_++;
                break;
        }
    }
    }
return toreturn;
}

Image* StickerSheet::getSticker(unsigned index){
    if(allsticker[index]!= NULL){
        return allsticker[index];
    }
    return NULL;
}

int StickerSheet::setStickerAtLayer (Image &sticker, unsigned layer, int x, int y){
    if(layer >= allsticker.size()){
        return -1;
    }
    allsticker[layer] =&sticker;
    xcor_[layer] = x;
    ycor_[layer] = y;
    return layer;
}

void StickerSheet::changeMaxStickers(unsigned int max){
    if(allsticker.size() > max){
        std::vector<Image*> nallst (max,NULL);
        for(unsigned int i = 0; i < max; i++ ){
            nallst[i] = allsticker[i];
        }
        allsticker = nallst;
    }else{
        for(unsigned int i = 0 ; i < max-max_; i++){ 
        allsticker.push_back(NULL);
        xcor_.push_back(-1);
        ycor_.push_back(-1);
       }
    }
    
    max_ = max;
}

int StickerSheet::layers () const{
    return max_;
}

bool StickerSheet::translate(unsigned index, int x, int y){
    xcor_[index] = x;
    ycor_[index] = y;
    if(allsticker[index] == NULL || index > allsticker.size()){
        return false;
    }
    return true;
}

Image StickerSheet::render() const {
   int max_w = base_.width();
   int max_h = base_.height();
    int minw = 0;
    int minh = 0;

    for (int i = 0; i < max_; i++) {
        if (allsticker[i] != NULL) {
          for (int i=0;i<max_;i++){
     if(allsticker[i]!=NULL){
    if (xcor_[i]<minw)//         int k = xcor_[i]+allsticker[i]->width();
    minw=xcor_[i];       //         if(max_w<k)
    if (ycor_[i]<minh)//         {
    minh=ycor_[i];//         max_w=(xcor_[i]+allsticker[i]->width());
    int k = xcor_[i]+allsticker[i]->width();//         }
    int l = ycor_[i]+allsticker[i]->height();//         int l = ycor_[i]+allsticker[i]->height();
    if (k>max_w)//         if(max_h<l){
    max_w=k;//         max_h=(ycor_[i]+allsticker[i]->height());
    if (l>max_h)//         }
    max_h=l;//         if(xcor_[i]<minw){
     }
}//             minw = xcor_[i];
        }
    }

    Image img(max_w - minw, max_h - minh);

    for (unsigned i = 0; i < base_.width(); i++) {
        for (unsigned j = 0; j < base_.height(); j++) {
            img.getPixel(i - minw, j - minh) = base_.getPixel(i, j);
        }
    }

    for (int i = 0; i < max_; i++) {
        if (allsticker[i] != NULL) {
            for (unsigned w = 0; w < allsticker[i]->width(); w++) {
                for (unsigned h = 0; h < allsticker[i]->height(); h++) {
                    if (allsticker[i]->getPixel(w, h).a != 0) {
                        img.getPixel(w + xcor_[i] - minw, h + ycor_[i] - minh) = allsticker[i]->getPixel(w, h);
                    }
                }
            }
        }
    }

    return img;
}


void StickerSheet::removeSticker(unsigned index) {
    if(allsticker[index]!= NULL){
        allsticker[index] = NULL;
        xcor_[index] = -1;
        ycor_[index] = -1;
        num_--;
    }
}

const StickerSheet & StickerSheet::operator=(const StickerSheet &other) {
  if(this != &other) {
    xcor_.clear();
    ycor_.clear();
    allsticker.clear ();
    base_ = Image(other.base_);
    max_ = other.max_;
    num_ = other.num_;

    for (int i = 0; i < max_; i++)
    {
        allsticker.push_back(other.allsticker[i]);
    }
    for (int j = 0; j < max_; j++)
    {
        xcor_.push_back(other.xcor_[j]);
        ycor_.push_back(other.ycor_[j]);
    }
}
return *this;
}

// StickerSheet::~StickerSheet(){
//     destroy();
// }

// void StickerSheet::destroy(){
//     delete base_;
//     xcor_.clear();
//     ycor_.clear();
//     allsticker.clear ();
//     base_=NULL;
// }
