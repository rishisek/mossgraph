#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max){
    base_ = Image(picture);
    nextLayer_ = 0;
    max_ = max;
    stickers_ = new Image*[max_]; // image arr changed to image ptr arr
    x_ = new int[max_];
    y_ = new int[max_];
}

StickerSheet::StickerSheet(const StickerSheet &other){
    _copy(other);
}

// supposed to actually add sticker  ???
int StickerSheet::addSticker(Image& sticker, int x, int y){
    // find lowest available empty layer
    if (nextLayer_ == max_)
        changeMaxStickers(nextLayer_ + 1);

    stickers_[nextLayer_] = &sticker; // operator = not working, use constructor instead
    x_[nextLayer_] = x;
    y_[nextLayer_] = y;

    nextLayer_++;

    return nextLayer_-1;
}

void StickerSheet::changeMaxStickers(unsigned max){
    Image **temp = stickers_;
    int *x_temp = x_;
    int *y_temp = y_;

    if (max < max_){
        stickers_ = new Image*[max];

        for (unsigned i = 0; i < max; i++){ // revise?
            stickers_[i] = temp[i];
            x_[i] = x_temp[i];
            y_[i] = y_temp[i];
        }
    
    }

    else if (max > max_){
        stickers_ = new Image*[max];

        for (unsigned i = 0; i < max_; i++){ // revise?
            stickers_[i] = temp[i];
            x_[i] = x_temp[i];
            y_[i] = y_temp[i];
        }

    }

    max_ = max;
    delete[] temp;
}

Image* StickerSheet::getSticker(unsigned index){
    if (index >= nextLayer_) return NULL;
    else return stickers_[index];
}

int StickerSheet::layers() const{
    // instead of layers with stickers, 
    // returns total numbers of layers

    return max_;
}
const StickerSheet& StickerSheet::operator=(const StickerSheet &other){
    if (this != &other){
        _delete();
        _copy(other);
    }
    
    return *this;
}

void StickerSheet::removeSticker(unsigned index){
    nextLayer_--;

    Image **temp = stickers_;
    int *x_temp = x_;
    int *y_temp = y_;

    stickers_ = new Image*[max_];

    unsigned i = 0;

    while (i < index){
        stickers_[i] = temp[i];
        x_[i] = x_temp[i];
        y_[i] = y_temp[i];  
        i++;      
    }

    while (i < max_){
        stickers_[i] = temp[i];
        x_[i] = x_temp[i+1];
        y_[i] = y_temp[i+1];  
        i++;           
    }

    delete[] temp;
}

Image StickerSheet::render() const{
    Image ret = Image(base_); // seg fault removed when changed to just img

    // revise
    unsigned width_ = ret.width();
    unsigned height_ = ret.height();
    int x_max = width_ + abs(x_[0]);
    int y_max = height_ + abs(y_[0]);

    for (unsigned i = 0; i < max_; i++){
        if (abs(x_[i]) > abs(x_[0]))
            x_max = width_ + abs(x_[i]);
        if (abs(y_[i]) > abs(y_[0]))
            y_max = width_ + abs(y_[i]);
    }

    unsigned n = 0;
    while (n < nextLayer_){
        if ((0 <= x_[n] <= width_ - (stickers_[n])->width()) && // problematic
            (0 <= y_[n] <= height_ - (stickers_[n])->height())){

                for (unsigned x = 0; x < (stickers_[n])->width(); x++){
                    for (unsigned y = 0; y < (stickers_[n])->height(); y++){
                        if((stickers_[n])->getPixel(x,y).a){
                            ret.getPixel(x+x_[n], y+y_[n]) = (stickers_[n])->getPixel(x,y);
                        }
                    }
                }

        }
        
        else{
            ret.resize(x_max, y_max);
            for (unsigned x = 0; x < (stickers_[n])->width(); x++){
                for (unsigned y = 0; y < (stickers_[n])->height(); y++){
                    if((stickers_[n])->getPixel(x,y).a){
                        ret.getPixel(x+x_[n], y+y_[n]) = (stickers_[n])->getPixel(x,y);
                    }
                }
            }
        }

        n++;
    }

    return ret;
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y){
    if (max_ <= layer) return -1;
    
    *stickers_[layer] = sticker;
    translate(layer, x, y);

    return layer;
}

bool StickerSheet::translate(unsigned index, int x, int y){
    if (stickers_[index] == NULL || max_ <= index)
        return false;
    else{
        x_[index] = x;
        y_[index] = y;
        return true;
    }
}

void StickerSheet::_copy(const StickerSheet &other) {
    base_ = other.base_;
    nextLayer_ = other.nextLayer_;
    max_ = other.max_;
    
    stickers_ = new Image*[max_];
    x_ = new int[max_];
    y_ = new int[max_];

    for (unsigned i = 0; i < max_; i++){
        stickers_[i] = other.stickers_[i];
        x_[i] = other.x_[i];
        y_[i] = other.y_[i];
    }
}

void StickerSheet::_delete(){
    if (stickers_ != NULL)
        delete[] stickers_;
}