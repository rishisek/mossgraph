#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image& picture, unsigned max){
    picture_ = picture;
    max_ = max;
    for (unsigned x = 0; x < max_; x++){
        new_sticker.push_back(NULL);
        x_cd.push_back(0);
        y_cd.push_back(0);
    }
}

StickerSheet::StickerSheet(const StickerSheet& other){
    _copy(other);
}

StickerSheet::~StickerSheet(){
    return;
}

int StickerSheet::addSticker(Image& sticker, int x, int y){
    for (unsigned int i = 0; i < max_; i++){
        if (new_sticker.at(i) == NULL){
            new_sticker.at(i) = &sticker;
            x_cd.at(i) = x;
            y_cd.at(i) = y;
            return i;
        }
    }
    changeMaxStickers(max_ + 1);
    x_cd.at(max_-1) = x;
    y_cd.at(max_-1) = y;
    new_sticker.at(max_-1) = &sticker;
    return max_-1;
}
   

void StickerSheet::changeMaxStickers(unsigned max){
    if (max > 0 && max < new_sticker.size()){
        max_ = max;
        x_cd.erase(x_cd.begin()+max_,x_cd.end());
        y_cd.erase(y_cd.begin()+max_,y_cd.end());
        new_sticker.erase(new_sticker.begin()+max_,new_sticker.end());
    }
    else if (max > new_sticker.size()){
        for (unsigned i = max_; i < max; i++){
            new_sticker.push_back(NULL);
            x_cd.push_back(0);
            y_cd.push_back(0);
        }
        max_ = max;
    }
    else{
        _erase();
        max_ = 0;
    }
}

Image* StickerSheet::getSticker(unsigned index){
    if (index < 0 || index >= max_ || new_sticker[index] == NULL){return NULL;}
    Image* ptr;
    ptr = new_sticker[index];  
    return ptr; 
}

int StickerSheet::layers() const{
    return max_;
}

const StickerSheet& StickerSheet::operator=(const StickerSheet& other){
    if (this != &other){
        _erase();
        _copy(other);
    }
    return *this;
}

void StickerSheet::_erase(){
    y_cd.clear();
    x_cd.clear();
    new_sticker.clear();
}

void StickerSheet::removeSticker(unsigned index){
    if (index >= 0 && index < max_){
        new_sticker[index] = NULL;
        x_cd[index] = 0;
        y_cd[index] = 0;
    }
}

Image StickerSheet::render() const{
    Image img_blank = picture_;
    unsigned int img_height = picture_.height();
    unsigned int img_width = picture_.width();

    for (unsigned x = 0; x < (unsigned)layers(); x++){
        if (new_sticker[x] != NULL && (x_cd[x] + new_sticker[x]->width() > img_width)){
            img_width = x_cd[x] + new_sticker[x]->width();
        }
        if (new_sticker[x] != NULL && (y_cd[x] + new_sticker[x]->height() > img_height)){
            img_height = y_cd[x] + new_sticker[x]->height();
        }
    }
    img_blank.resize(img_width, img_height);

    for (unsigned x = 0; x < (unsigned)layers(); x++){
        if (new_sticker[x] != NULL){
            for (unsigned i = 0; i < new_sticker[x]->width(); i++){
                for (unsigned j = 0; j < new_sticker[x]->height(); j++){
                    if (new_sticker[x]->getPixel(i,j).a == 1){
                        img_blank.getPixel(x_cd[x] + i, y_cd[x] + j) = new_sticker[x]->getPixel(i,j);
                    }
                }
            }
        }
    }
    return img_blank;
}

int StickerSheet::setStickerAtLayer(Image& sticker, unsigned layer, int x, int y){
    if (layer < 0 || layer >= max_){return -1;}
    new_sticker.at(layer) = &sticker; //check
    x_cd.at(layer) = x;
    y_cd.at(layer) = y;
    return layer;
}

bool StickerSheet::translate(unsigned index, int x, int y){
    if (index < 0 || index >= max_ || new_sticker.at(index) == NULL){return false;}
    x_cd.at(index) = x;
    y_cd.at(index) = y;
    return true;
}

void StickerSheet::_copy(const StickerSheet& other){
    picture_ = other.picture_;
    max_ = other.max_;
    new_sticker = other.new_sticker;
    x_cd = other.x_cd;
    y_cd = other.y_cd;
}
