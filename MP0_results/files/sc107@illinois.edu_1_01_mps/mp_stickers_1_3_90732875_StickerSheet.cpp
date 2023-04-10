#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image& picture, unsigned max){
    basepic = Image(picture);
    stickermax_ = max;
    nextLayer_ = 0;
    maxsheets = new Image*[stickermax_];
    x_ = new int[stickermax_];
    y_ = new int[stickermax_];
}


StickerSheet::StickerSheet(const StickerSheet& other){
    _copy(other);
}

void StickerSheet::_copy(const StickerSheet& other){
    basepic = other.basepic;
    stickermax_ = other.stickermax_;
    nextLayer_ = other.nextLayer_;

    maxsheets = new Image*[stickermax_];
    x_ = new int[stickermax_];
    y_ = new int[stickermax_];

    for (unsigned i = 0; i < stickermax_; i++){
        maxsheets[i] = other.maxsheets[i];
        x_[i] = other.x_[i];
        y_[i] = other.y_[i];
    }
}

void StickerSheet::_delete(){
    if (maxsheets != NULL)
        delete[] maxsheets;
}

int StickerSheet::addSticker(Image& sticker, int x, int y){

    if (nextLayer_ == stickermax_){
        changeMaxStickers(nextLayer_ + 1);
    }

    maxsheets[nextLayer_]= &sticker;
    x_[nextLayer_] = x;
    y_[nextLayer_] = y;

    nextLayer_++;
    return nextLayer_-1;
}

void StickerSheet::changeMaxStickers(unsigned max){
    Image** temp = maxsheets;
    int *x_temp = x_;
    int *y_temp = y_;

    if (max < stickermax_){
        maxsheets = new Image*[max];

        for (unsigned i = 0; i < max; i++){
                maxsheets[i] = temp[i];
                x_[i] = x_temp[i];
                y_[i] = y_temp[i];
        }
        
    }

    else if (max > stickermax_){
        maxsheets = new Image*[max];

        for (unsigned i = 0; i < stickermax_; i++){
            maxsheets[i] = temp[i];
            x_[i] = x_temp[i];
            y_[i] = y_temp[i];
        }
        
    }

    
    stickermax_ = max;
    delete[] temp;

}

Image* StickerSheet::getSticker(unsigned index){
    if (index >= nextLayer_) return NULL;
    
    else return maxsheets[index];
}

int StickerSheet::layers() const{
    return stickermax_;
}

const StickerSheet& StickerSheet::operator=(const StickerSheet& other){
    if (this != &other){
        _delete();
        _copy(other);
    }

    return *this;
}

void StickerSheet::removeSticker(unsigned index){
    nextLayer_ -= 1;
    Image** temp = maxsheets;
    int* x_temp = x_;
    int* y_temp = y_;
    maxsheets = new Image*[stickermax_];
    unsigned i = 0;

    while (i < index){
        maxsheets[i] = temp[i];
        x_[i] = x_temp[i];
        y_[i] = y_temp[i];
        i++;
    }

    while (i < stickermax_){
        maxsheets[i] = temp[i+1];
        x_[i] = x_temp[i+1];
        y_[i] = y_temp[i+1];
        i++;
    }

    delete[] temp;
    
}

Image StickerSheet::render() const{
    Image result = Image(basepic);
    unsigned n = 0;
    // find max_x & max_y
    unsigned width_ = result.width();
    unsigned height_ = result.height();
    int max_x = width_+ abs(x_[0]);        // width + absolute value of x_
    int max_y = height_ + abs(y_[0]);      // height + absolute value of y_

    for (unsigned i = 0; i < stickermax_; i++){
        if (abs(x_[i]) > abs(x_[0])) max_x = width_ + abs(x_[i]);
        if (abs(y_[i]) > abs(y_[0])) max_y = height_ + abs(y_[i]);
    }

    while (n < nextLayer_){
        //check boundary conditions
        if ((0 <= x_[n] <= width_ - (maxsheets[n])->width()) && 
            0 <= y_[n] <= height_ - (maxsheets[n])->height()){
            // copy stickers onto sheet
                for (unsigned x = 0; x < (maxsheets[n])->width(); x++){
                    for (unsigned y = 0; y < (maxsheets[n])->height(); y++ ){
                        if ((maxsheets[n])->getPixel(x,y).a)
                            result.getPixel(x+x_[n],y+y_[n]) = (maxsheets[n])->getPixel(x,y);
                    }
                }
            }

        else{
            result.resize(max_x, max_y);
            for (unsigned x = 0; x < (maxsheets[n])->width(); x++){
                for (unsigned y = 0; y < (maxsheets[n])->height(); y++ ){          
                    if ((maxsheets[n])->getPixel(x,y).a)
                        result.getPixel(x+x_[n],y+y_[n]) = (maxsheets[n])->getPixel(x,y);
                }
            }
        } 
        n++;
    }   

    return result;
}

int StickerSheet::setStickerAtLayer(Image& sticker, unsigned layer, int x, int y){
    if (layer >= stickermax_) return -1;

    *maxsheets[layer] = sticker;
    translate(layer, x, y);


    return layer;

}

bool StickerSheet::translate(unsigned index, int x, int y){
    if (maxsheets[index] == NULL || index >= stickermax_)
        return false;

    else{
        x_[index] = x;
        y_[index] = y;
        return true;
    }

}