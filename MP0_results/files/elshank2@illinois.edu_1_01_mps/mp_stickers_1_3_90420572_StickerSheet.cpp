// not empty!

#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"
#include <iostream>

using namespace cs225;

void StickerSheet::copy(const StickerSheet & other){
    max_ = other.max_;
    x_cord = new unsigned[max_];
    y_cord = new unsigned[max_];
    base = new Image(*(other.base));
    number_of_stickers = other.number_of_stickers;
    Image_array = new Image * [max_];
        for (unsigned i = 0; i < number_of_stickers; i++){
            Image_array[i] = new Image();
            x_cord[i] = other.x_cord[i];
            y_cord[i] = other.y_cord[i];
            *(Image_array[i]) = *(other.Image_array[i]);
        }
}
void StickerSheet::clear(){
    for (unsigned i = 0; i < number_of_stickers; i++){
        delete Image_array[i];
        Image_array[i] = NULL;
    }
    delete[] Image_array;
    delete[] x_cord;
    delete[] y_cord;
    delete base;
}
StickerSheet::~StickerSheet(){
    clear();

}

StickerSheet::StickerSheet(const Image & picture, unsigned max){
    max_ = max;
    number_of_stickers = 0;
    x_cord = new unsigned[max_];
    y_cord = new unsigned[max_];
    Image_array = new Image *[max_];
    base = new Image(picture);
    x_cord[0] = 0;
    y_cord[0] = 0;

}
StickerSheet::StickerSheet(const StickerSheet & other){
    copy(other);
}
const StickerSheet & StickerSheet::operator=(const StickerSheet & other){
if (this != &other) { 

            clear();

            copy(other);
        }

        return *this;
}
void StickerSheet::changeMaxStickers(unsigned max){
    max_ = max;
    Image ** TempImage_array = new Image * [number_of_stickers];
    unsigned * temp_x_cord = new unsigned[number_of_stickers];
    unsigned * temp_y_cord = new unsigned[number_of_stickers];
        for (unsigned i = 0; i < number_of_stickers; i++){
            TempImage_array[i] = Image_array[i];
            temp_x_cord[i] = x_cord[i];
            temp_y_cord[i] = y_cord[i];
        }
    clear();
    Image_array = new Image * [max];
    x_cord = new unsigned[max];
    y_cord = new unsigned[max];

    if (max < number_of_stickers){
        for (unsigned i = max; i < number_of_stickers; i++){ // get rid of extra
            delete TempImage_array[i];
            TempImage_array[i] = NULL;
        }
        //copy into image
        number_of_stickers = max;
        for (unsigned i = 0; i < max; i++){
            Image_array[i] = TempImage_array[i];
            x_cord[i] = temp_x_cord[i];
            y_cord[i] = temp_y_cord[i];
        }
    }
    else{
        for (unsigned i = 0; i < number_of_stickers; i++){
            Image_array[i] = TempImage_array[i];
            x_cord[i] = temp_x_cord[i];
            y_cord[i] = temp_y_cord[i];
        }
    }
    delete[] TempImage_array;
    delete[] temp_y_cord;
    delete[] temp_x_cord;
}
int StickerSheet::addSticker(Image & sticker, int x, int y){
    for (unsigned i = 0; i < max_; i++){
        if (i == number_of_stickers){
            Image_array[i] = new Image(sticker);
            x_cord[i] = x;
            y_cord[i] = y;
            number_of_stickers = number_of_stickers + 1;
            return int(i);
        }
    }
    return -1;
}
int StickerSheet::setStickerAtLayer(Image & sticker, unsigned layer, int x, int y){
        if (Image_array[layer] == nullptr){
            Image_array[layer] = new Image(sticker);
            x_cord[layer] = x;
            y_cord[layer] = y;
            number_of_stickers = number_of_stickers + 1;
            return int(layer);
        }
    
    return -1;
}
bool StickerSheet::translate(unsigned index, int x, int y){
    if (Image_array[index] != nullptr && index < number_of_stickers){
        x_cord[index] = x;
        y_cord[index] = y;
        return true;
    }
    else
        return false;
}
void StickerSheet::removeSticker(unsigned index){
    delete Image_array[index];
    for (unsigned i = 0; i < max_ - 1; i++){
        Image_array[i] = Image_array[i + 1];
        x_cord[i] = x_cord[i+1];
        y_cord[i] = y_cord[i+1];
    }
    Image_array[max_ - 1] = NULL;
    x_cord[max_ - 1] = 0;
    y_cord[max_ - 1] = 0;
    number_of_stickers = number_of_stickers - 1;
}
Image * StickerSheet::getSticker(unsigned index){
    if (index >= number_of_stickers){
        return NULL;
    }
    else{
        return Image_array[index];
    }
}
int StickerSheet::layers() const{
    return int(max_); // or number of stickers??
}
Image StickerSheet::render() const{ //wrong
    Image returnImage(*base);
    unsigned maxHeight = returnImage.height();
    unsigned maxWidth = returnImage.width();

    for (unsigned i = 0; i < number_of_stickers; i++){
        if ((x_cord[i] + Image_array[i]->width()) > maxWidth){
            returnImage.resize(x_cord[i] + Image_array[i]->width(), returnImage.height());
        }
        if ((y_cord[i] + Image_array[i]->height()) > maxHeight){
            returnImage.resize(returnImage.width(), y_cord[i] + Image_array[i]->height());
        }
        for (unsigned j = 0; j < Image_array[i]->width(); j++){
            for (unsigned k = 0; k < Image_array[i]->height(); j++){
                HSLAPixel & curReturnPixel = returnImage.getPixel(j + x_cord[i], k + y_cord[i]);
                HSLAPixel & curImagePixel = Image_array[i]->getPixel(j, k);
                if (curImagePixel.a != 0){
                    curReturnPixel = curImagePixel;
                }
            }
        }
    }
    return returnImage;
}