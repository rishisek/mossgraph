#include <iostream>
#include <vector>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "StickerSheet.h"
#include "Image.h"

using namespace cs225;

StickerSheet::StickerSheet(const Image &picture, unsigned max){
    pic = new Image(picture);
    maxVal = max;
}

StickerSheet::StickerSheet(const StickerSheet &other){
    maxVal = other.maxVal;
    pic = new Image(*other.pic);
    x_coords = other.x_coords;
    y_coords = other.y_coords;
    pics = other.pics;
}

const StickerSheet & StickerSheet::operator =(const StickerSheet &other){
    if(&other == this){
        return *this;
    } else {
        delete pic;

        maxVal = other.maxVal;
        pic = new Image(*other.pic);
        x_coords = other.x_coords;
        y_coords = other.y_coords;
        pics = other.pics;

        return *this;
    }
}

void StickerSheet::changeMaxStickers(unsigned max){
    maxVal = max;
    while(maxVal < pics.size()){
        pics.pop_back();
        x_coords.pop_back();
        y_coords.pop_back();
    }
}

int StickerSheet::addSticker(Image &sticker, int x, int y){
    if(maxVal <= pics.size()){
        maxVal = maxVal + 1;
    }

    x_coords.push_back(x);
    y_coords.push_back(y);
    pics.push_back(&sticker);

    return pics.size()-1;
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y){
    if(pics.size() <= layer){
        return -1;
    }

    x_coords[layer] = x;
    y_coords[layer] = y;
    pics[layer] = &sticker;

    return layer;
}

bool StickerSheet::translate(unsigned index, int x, int y){
    if(0 > index || pics.size() <= index){
        return false;
    }

    x_coords[index] = x;
    y_coords[index] = y;
    return true;
}

void StickerSheet::removeSticker(unsigned index){
    x_coords.erase(x_coords.begin() + index);
    y_coords.erase(y_coords.begin() + index);
    pics.erase(pics.begin() + index);
}

Image * StickerSheet::getSticker(unsigned index){
    if(0 > index || pics.size() <= index){
        return NULL;
    } else {
        return pics[index];
    }
}

int StickerSheet::layers() const{
    return maxVal;
}

Image StickerSheet::render() const{

    Image outputImage(*pic);

    unsigned int testWidth = 0;
    unsigned int testHeight = 0;

    for(unsigned int i = 0; i < pics.size(); i++){
        testWidth = pics[i] -> width() + x_coords[i];
        testHeight = pics[i] -> height() + y_coords[i];
        if(testWidth > outputImage.width()){
            outputImage.resize(testWidth, outputImage.height());
        } else if (testHeight > outputImage.height()){
            outputImage.resize(outputImage.width(), testHeight);
        }
    }

    for(unsigned int j = 0; j < pics.size(); j++){
        testWidth = pics[j] -> width();
        testHeight = pics[j] -> height();
        for(unsigned int k = 0; k < testWidth; k++){
            for(unsigned int l = 0; l < testHeight; l++){
                HSLAPixel & curPix = outputImage.getPixel(k + x_coords[j], l + y_coords[j]);
                if(pics[j] -> getPixel(k, l).a != 0){
                    curPix = pics[j] -> getPixel(k, l);
                }
            }
        }
    }
    return outputImage;
}




