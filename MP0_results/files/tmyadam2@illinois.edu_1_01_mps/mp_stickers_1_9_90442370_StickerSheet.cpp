#include "StickerSheet.h"
#include <iostream>

using namespace cs225;

StickerSheet::StickerSheet(const Image &picture, unsigned max){
    maxValue = max;
    _bImage = picture;
    _img.resize(max);
    _xCoord.resize(max);
    _yCoord.resize(max);
}

    // StickerSheet::StickerSheet(const StickerSheet &other){
    
    // }

    // const StickerSheet & StickerSheet::operator=(const StickerSheet &other) {
    //     return *this;
    // }
    
    void StickerSheet::changeMaxStickers(unsigned max){
        if(_img.size()>max){
            _img.erase(_img.begin()+max,_img.end());
            //_CoordinateXY.erase(_CoordinateXY.begin()+max, _CoordinateXY.end());
            _xCoord.erase(_xCoord.begin()+max, _xCoord.end());
            _yCoord.erase(_yCoord.begin()+max, _yCoord.end());
        }
        else{
            _img.resize(max);
            _xCoord.resize(max);
            _yCoord.resize(max);
        }
        maxValue = max;
    }
    int StickerSheet::addSticker(Image &sticker, int x, int y){
        for(unsigned int i = 0; i < _img.size(); i++){
            if(_img[i]==NULL){
                _img[i] = &sticker;
                _xCoord[i] = x;
                _yCoord[i] = y;
                return i;
            }
        }
        _img.push_back(&sticker);
                _xCoord.push_back(x);
                _yCoord.push_back(y);
                maxValue++;

        return _img.size()-1;
       

    }
    int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y){
        if(layer<maxValue){
            _img[layer] = &sticker;
            _xCoord[layer] = x;
            _yCoord[layer] = y;
            return layer;
        }
        return -1;
        
    }
    bool StickerSheet::translate(unsigned index, int x, int y) {
        if(index < _img.size() && _img[index] != NULL){
            _xCoord[index] = x;
            _yCoord[index] = y;
            //return true;
        }
        return (index < _img.size() && _img[index] != NULL);
    }


    void StickerSheet::removeSticker(unsigned index) {
        if(index<_img.size()){
            _img[index] = NULL;
            _xCoord[index] = 0;
            _yCoord[index] = 0;
        }
        // if(index<_img.size()){
        //     _img[index] = NULL;
        //     delete _xCoord[index];
        //     delete _yCoord[index];
        //     _xCoord[index] = NULL;
        //     _yCoord[index] = NULL;
        // }
    }
    Image* StickerSheet::getSticker(unsigned index) {
        // Image* yes;
        if(index >= _img.size()){
            return NULL;
        }
        else{
            return _img[index];
        }
    }
    int StickerSheet::layers() const{
        return maxValue;
    }

    Image StickerSheet::render() const {
         int minX = 0;
         int maxX = _bImage.width();
         int minY = 0;
         int maxY = _bImage.height();
        
        for(unsigned int i = 0; i < _img.size(); i++){
            if(_img[i] != NULL){
                if((int)_img[i]->width()+_xCoord[i]>maxX){
                maxX = (int)_img[i]->width()+_xCoord[i];
                }
                if((int)_img[i]->height()+_yCoord[i]>maxY){
                maxY = (int)_img[i]->height()+_yCoord[i];
                }

                if(_xCoord[i]<minX){
                minX = _xCoord[i];
                }
                if(_yCoord[i]<minY){
                minY = _yCoord[i];
                }
            }
        }
        int Xcoord = maxX - minX;
        int Ycoord = maxY - minY;

        Image cop = Image(Xcoord,Ycoord);


        int delX = minX + 0;
        int delY = minY-0;
        for (unsigned int x = 0; x < _bImage.width(); x++) {
            for (unsigned int y = 0; y < _bImage.height(); y++) {
                cop.getPixel(x-delX, y-delY) = _bImage.getPixel(x, y);
            } 
        }
    for (unsigned int i = 0; i < _img.size(); i++) {
        if(_img[i] != NULL){
        for (int x = 0; x < (int)_img[i]->width(); x++) {
            for (int y = 0; y < (int)_img[i]->height(); y++) {
                    HSLAPixel& outputPixel = cop.getPixel(abs(_xCoord[i] + x - delX), abs(_yCoord[i] + y - delY));
                    HSLAPixel& stickerPixel = _img[i]->getPixel(x,y);
                if (stickerPixel.a != 0) {
                    outputPixel = stickerPixel;
                    //stickerPixel = outputPixel;
                    }
                } 
            }
        }
  }
  return cop;   
    }



