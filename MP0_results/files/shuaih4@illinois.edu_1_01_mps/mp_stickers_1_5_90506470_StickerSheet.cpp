#include <string>
#include <vector>
#include <math.h>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"
#include "StickerSheet.h"

using namespace std;

StickerSheet::StickerSheet(const Image & picture, unsigned max){
    maxSticker = max;
    vector<unsigned> cordX;
    vector<unsigned> cordY;
    basePicture = picture;
    vector<Image*> imagePictures;
}

StickerSheet::StickerSheet(const StickerSheet & other){
    maxSticker = other.maxSticker;
    basePicture = other.basePicture;

    cordX = other.cordX;
    cordY = other.cordY;
    imagePictures = other.imagePictures;
    
}

StickerSheet::~StickerSheet(){
    cordX.clear();
    cordY.clear();
    imagePictures.clear();

    cordX.shrink_to_fit();
    cordY.shrink_to_fit();
    imagePictures.shrink_to_fit();
}


int StickerSheet::addSticker(Image &sticker, int x, int y){
    if(imagePictures.size() == maxSticker){
        maxSticker += 1;
    }
    imagePictures.push_back(&sticker);
    cordX.push_back(x);
    cordY.push_back(y);
    return imagePictures.size() - 1;
}

void StickerSheet::changeMaxStickers (unsigned max){
    if (imagePictures.size() > max){
        vector<unsigned> tempX;
        vector<unsigned> tempY;
        vector<Image*> tempImagePictures;
        for (unsigned i = 0; i < max; i++){
            tempX.push_back(cordX[i]);
            tempY.push_back(cordY[i]);
            tempImagePictures.push_back(imagePictures[i]);
        }
        cordX = tempX;
        cordY = tempY;
        imagePictures = tempImagePictures;
        tempX.clear();
        tempY.clear();
        tempImagePictures.clear();

        tempX.shrink_to_fit();
        tempY.shrink_to_fit();
        tempImagePictures.shrink_to_fit();
    }
    maxSticker = max;

}

Image * StickerSheet::getSticker (unsigned index){
    if(index > maxSticker || index >= imagePictures.size()){return NULL;}
    return imagePictures[index];
}

int StickerSheet::layers () const{
    return maxSticker;
}

const StickerSheet & StickerSheet::operator= (const StickerSheet &other){
    cordX.clear();
    cordY.clear();
    imagePictures.clear();
    cordX.shrink_to_fit();
    cordY.shrink_to_fit();
    imagePictures.shrink_to_fit();
    maxSticker = other.maxSticker;
    basePicture = other.basePicture;

    cordX = other.cordX;
    cordY = other.cordY;
    imagePictures = other.imagePictures;
    return *this;
}

void StickerSheet::removeSticker (unsigned index){
    imagePictures.erase(imagePictures.begin()+index);
    cordX.erase(cordX.begin()+index);
    cordY.erase(cordY.begin()+index);
}

Image StickerSheet::render () const{
    Image result = basePicture;
    unsigned widthPic = basePicture.width();
    unsigned heightPic = basePicture.height();
    for (unsigned i = 0; i < imagePictures.size(); i++){
        unsigned w_ = cordX[i];
        unsigned h_ = cordY[i];
        if ((int)cordX[i] < 0){
            w_ = abs((int)cordX[i]);
            widthPic =  w_ + basePicture.width();
        }
        if ((int)cordY[i] < 0){
            h_ = abs((int)cordY[i]);
            heightPic = h_ + basePicture.height();
        }


        if(w_ + imagePictures[i]->width() > widthPic){
            cout<<"here"<<endl;
            widthPic = w_ + imagePictures[i]->width();
        }

        if(h_ + imagePictures[i]->height() > heightPic){
            cout<<"hi"<<endl;
            heightPic = h_ + imagePictures[i]->height();
        }
    }
    result.resize(widthPic, heightPic);
    
    for(unsigned int i = 0; i<widthPic; i++){
        for (unsigned int j = 0; j<heightPic; j++){
            HSLAPixel & resultPixel = result.getPixel(i, j);
            resultPixel = basePicture.getPixel(i, j);
        }
    }
    for (unsigned i = 0; i < imagePictures.size(); i++){
        for(unsigned int j = 0; j<imagePictures[i]->width(); j++){
            for (unsigned int k = 0; k<imagePictures[i]->height(); k++){
                unsigned x = j+cordX[i];
                unsigned y = k+cordY[i];
                if ((int)cordX[i] < 0){
                    x = result.width()-(cordX[i] + pow(2, 32))+j;
                }
                if ((int)cordY[i] < 0){
                    y = result.height()-(cordY[i] + pow(2, 32))+k;
                }
                HSLAPixel & resultPixel = result.getPixel(x, y);
                HSLAPixel & stickerPixel = imagePictures[i]->getPixel(j, k);
                if(stickerPixel.a != 0){
                    resultPixel = stickerPixel;
                }
            }
        }
    }

    return result;
}

int StickerSheet::setStickerAtLayer (Image &sticker, unsigned layer, int x, int y){
    if (layer < imagePictures.size()){
        imagePictures.at(layer) = &sticker;
        cordX.at(layer) = x;
        cordY.at(layer) = y;
        return layer;
    }
    return -1;
}

bool StickerSheet::translate (unsigned index, int x, int y){
    if(index<maxSticker && index < imagePictures.size()){
        cordX.at(index) = x;
        cordY.at(index) = y;
        return true;
    }
    return false;
}