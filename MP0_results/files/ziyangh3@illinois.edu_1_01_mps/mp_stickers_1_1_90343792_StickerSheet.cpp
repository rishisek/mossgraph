#include <StickerSheet.h>
#include<vector>
#include <iostream>
using namespace std;

StickerSheet::StickerSheet(const Image &picture, unsigned max){
    max_ = max;
    num_ =  0;
    picture_ = picture;
    sheet_.resize(max);
    xcoord_.resize(max);
    ycoord_.resize(max);
}
StickerSheet::StickerSheet(const StickerSheet &other){
    max_ = other.max_;
    num_ = other.num_;
    picture_ = other.picture_;
    sheet_.resize(other.max_);
    xcoord_.resize(other.max_);
    ycoord_.resize(other.max_);
    for(unsigned i = 0; i < max_; i++){
        if(other.sheet_[i] != NULL){
            sheet_[i] = other.sheet_[i];
            xcoord_[i] = other.xcoord_[i];
            ycoord_[i] = other.ycoord_[i];
        }
    }
}

/*StickerSheet::~StickerSheet(){
    clear(other);
}*/

/*void StickerSheet::clear(const StickerSheet &other){
    max_ = 0;
    num_ = 0;
    for(unsigned i = 0; i < max_; i++){
        if(other.sheet_[i] != NULL){
            sheet_[i] = 0;
            xcoord_[i] = 0;
            ycoord_[i] = 0;
        }
    }
}*/

const StickerSheet & StickerSheet::operator= (const StickerSheet &other){
    picture_ = other.picture_;
    max_ = other.max_;
    sheet_.resize(other.max_);
    xcoord_.resize(other.max_);
    ycoord_.resize(other.max_);
        for (unsigned i = 0; i < max_; i++) {
            if(other.sheet_[i] != NULL) {
                sheet_[i] = other.sheet_[i];
                xcoord_[i] = other.xcoord_[i];
                ycoord_[i] = other.ycoord_[i];
            }
        }
    return *this;
}


void StickerSheet::changeMaxStickers(unsigned max){
    if(max < num_){
        num_ = max;
        max_ = max;
        sheet_.resize(max_);
        xcoord_.resize(max_);
        ycoord_.resize(max_);
    }
    max_ = max;
    sheet_.resize(max_);
    xcoord_.resize(max_);
    ycoord_.resize(max_);
}

int StickerSheet::addSticker(Image &sticker, int x, int y){
    // Image *p = &sticker;
    // if(num_ == max_){
    //     max_++;
    //     sheet_.push_back(p);
    //     xcoord_.push_back((unsigned)x);
    //     ycoord_.push_back((unsigned)y);
    // } else if(num_+1 ==  max_){
    //     sheet_.push_back(p);
    //     xcoord_.push_back((unsigned)x);
    //     ycoord_.push_back((unsigned)y);
    // }else {
    //     sheet_[num_]=p;
    //     xcoord_[num_]=((unsigned)x);
    //     ycoord_[num_]=((unsigned)y);
    // }
    // num_++;
    // return num_-1;
    for(int i = 0; i < (int)max_; i++){
            if (sheet_[i] == NULL) {
                sheet_[i] = &sticker;
                xcoord_[i] = x;
                ycoord_[i] = y;
                num_++;
                return i;
        }
    }
    max_++;
    sheet_.resize(max_);
    xcoord_.resize(max_);
    ycoord_.resize(max_);
    sheet_[max_-1] = &sticker;
    xcoord_[max_-1] = x;
    ycoord_[max_-1] = y;
    num_ = max_;
    return int(num_-1);

}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y){
    if (layer >= max_ || layer < 0) {
        return -1;
    }
    sheet_[layer] = &sticker;
    xcoord_[layer] = x;
    ycoord_[layer] = y;
    num_++;
    return layer;
}

bool StickerSheet::translate(unsigned index, int x, int y){
    if((sheet_[index] != NULL)&&(index >= 0)&&(index < max_)){
        xcoord_[index] = x;
        ycoord_[index] = y;
        return true;
    }
    else{
        return false;
    }

}

void StickerSheet::removeSticker(unsigned index){
    if(index < 0 || index >= max_) return;
    sheet_[index] = NULL;
    xcoord_[index] = 0;
    ycoord_[index] = 0;
    num_--;
}

Image * StickerSheet::getSticker(unsigned index){
    if (index < 0 || index >= max_ || (sheet_[index] == NULL)) {
        return NULL;
    }
    return sheet_[index];
}

int StickerSheet::layers() const{
    return max_;
}

Image StickerSheet::render () const{
    int lower_w_bound = 0;
    int upper_w_bound = picture_.width();
    int lower_h_bound = 0;
    int upper_h_bound = picture_.height();

    for (int i =0; i < (int)max_; i++) {
        if (sheet_[i] != NULL) {
            if (xcoord_[i] < lower_w_bound) {
                lower_w_bound = xcoord_[i];
            }
            if ((int)(xcoord_[i] + sheet_[i]->width( )) > upper_w_bound) {
                upper_w_bound = xcoord_[i] + sheet_[i]->width( );
            }
            if (ycoord_[i] < lower_h_bound) {
                lower_h_bound = ycoord_[i];
            }
            if ((int)(ycoord_[i] + sheet_[i]->height()) > upper_h_bound) {
                upper_h_bound = ycoord_[i] + sheet_[i]->height();
            }
        }
    }

    Image scene = Image(upper_w_bound - lower_w_bound, upper_h_bound - lower_h_bound);
        
    for (unsigned i = 0; i < picture_.width(); i++) {
        for (unsigned j = 0; j < picture_.height(); j++) {
            scene.getPixel((int)(i-lower_w_bound), (int)(j-lower_h_bound)) = picture_.getPixel((int)i, (int)j);
        }
    }

    for (unsigned index = 0; index < sheet_.size(); index++) {
        if (sheet_[index] != NULL) {
            int new_w = sheet_[index]->width();
            int new_h = sheet_[index]->height();
            for (int i = 0; i < new_w; i++) {
                for (int j = 0; j < new_h; j++) {
                    if (sheet_[index]->getPixel(i, j).a != 0) {
                        scene.getPixel(i+(xcoord_[index]-lower_w_bound), j+(ycoord_[index]-lower_h_bound))= sheet_[index]->getPixel(i, j);
                    }
                }
            }
        }
    }
    return scene;
}