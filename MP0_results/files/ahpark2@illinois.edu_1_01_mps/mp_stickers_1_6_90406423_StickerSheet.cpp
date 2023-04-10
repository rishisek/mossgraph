#include <StickerSheet.h>
#include <cmath>
#include <iostream>
using namespace cs225;

StickerSheet::StickerSheet(const Image & picture, unsigned max){
    bPicture.resize(picture.width(),picture.height());
    for (unsigned x = 0; x < picture.width(); x++) {
        for (unsigned y = 0; y < picture.height(); y++) {
            bPicture.getPixel(x,y) = picture.getPixel(x,y);
        } 
    }
    max_ = max;
}
void StickerSheet::changeMaxStickers(unsigned max) {
    if (max < max_) {
        while(max < stickerSheet_.size()) {
            stickerSheet_.pop_back();
            XCoord_.pop_back();
            YCoord_.pop_back();
        }
    }
    max_ = max;
}
int StickerSheet::addSticker(Image &sticker, int x, int y) {
    // cout << "stickersheet size:" << stickerSheet_.size() << endl;
    // cout <<"max_ size: " << max_ <<endl;
    // cout << "Before pushback!" <<endl;
    stickerSheet_.push_back(&sticker);
    XCoord_.push_back(x);
    YCoord_.push_back(y);
    // cout << "After pushback!" <<endl;
    if (stickerSheet_.size() >= max_+1) {
        //  cout << "before changeMaxStickers!" <<endl;
         changeMaxStickers(max_+1);
        //  cout<< "newmaxstickers:" << max_ << endl;
        //  cout << "after changeMaxStickers!" <<endl;
    }
    layers_.push_back(stickerSheet_.size()-1);
    // cout << "layerindexincrease!!!!!!!!!: " << layers_.size() << endl;
    // cout << "stickersheet size after adjustment: " << stickerSheet_.size() << endl;
    //  cout << "END OF ADDSTICKER!" <<endl;
    return stickerSheet_.size() - 1;
}
int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
    // cout << "layer:" << layer << endl;
    // cout << "comparing it to: " << max_ << endl;
    if (layer >= max_) {
        return -1;
    }
    // cout << "layers_[layer] value:" << layers_[layer] << endl;
    stickerSheet_[layers_[layer]] = &sticker;
    layers_[layer] = layer;
    // cout<<"xcord"<<endl;
    XCoord_[layer] = x;
    // cout<<"ycord"<<endl;
    YCoord_[layer] = y;
    return layers_[layer];
}
bool StickerSheet::translate(unsigned index, int x, int y) {
    if (index >= stickerSheet_.size() || index < 0) {
        return false;
    }
    XCoord_[index] = x;
    YCoord_[index] = y;
    return true;
}
void StickerSheet::removeSticker(unsigned index) {
    if (index >= layers_.size()) {
        return;
    }
    if (stickerSheet_.at(index) != nullptr) {
        stickerSheet_.erase(stickerSheet_.begin()+index);
        XCoord_.erase(XCoord_.begin()+index);
        YCoord_.erase(YCoord_.begin()+index);
    }
}
Image * StickerSheet::getSticker(unsigned index) {
    if (index >= stickerSheet_.size() || index < 0) {
        return NULL;
    }
    return stickerSheet_[index];
}
int StickerSheet::layers() const {
    // cout << "max: " << max_ << endl;
    // cout << "size: " << stickerSheet_.size() << endl;
    return (max_);
}
Image StickerSheet::render() const{
    int xMin = 0; 
    int yMin = 0;
    int maxWidth = bPicture.width();
    int maxHeight = bPicture.height();
    for (unsigned i= 0; i < this->stickerSheet_.size(); i++) {
        int x = XCoord_[i];
        int y = YCoord_[i];
        if (stickerSheet_[i] != nullptr) {
            int imageWidth = this->stickerSheet_[i]->width();
            int imageHeight = this->stickerSheet_[i]->height();

            if ((x+imageWidth) > maxWidth) {
                maxWidth = x + imageWidth;
            }
            if ((y+imageHeight) > maxHeight) {
                maxHeight = y + imageHeight;
            }
            if (x < xMin) {
                xMin = x;
            }
            if (y < yMin) {
                yMin = y;
            }
         }
    }
    //create image
    Image sheet_;
    //resize that image with the new coords
    sheet_.resize(maxWidth - xMin, maxHeight - yMin);
    for (unsigned x = 0; x < bPicture.width(); x++) {
        for(unsigned y = 0; y < bPicture.height(); y++) {
            cs225::HSLAPixel & ssPixel= sheet_.getPixel(x-xMin, y-yMin);
            cs225::HSLAPixel picturePixel = this->bPicture.getPixel(x,y);
            ssPixel = picturePixel;
        }
    }
    //paste the new stickers on the brand new image
    for(unsigned i = 0; i < stickerSheet_.size(); i++) {
        if (stickerSheet_[i] != nullptr) {
            int xStart = this->XCoord_[i]-xMin;
            int yStart = this->YCoord_[i]-yMin;
            int stickerH = this->stickerSheet_[i]->height();
            int stickerW = this->stickerSheet_[i]->width();
            for (int x = xStart; x < (xStart + stickerW); x++) {
                for (int y = yStart; y < (yStart + stickerH); y++) {
                    cs225::HSLAPixel & ssPixel = sheet_.getPixel(x,y);
                    cs225::HSLAPixel picturePixel = this->stickerSheet_[i]->getPixel(x-xStart,y-yStart);
                    if (picturePixel.a != 0) {
                        ssPixel.h = picturePixel.h;
                        ssPixel.s = picturePixel.s;
                        ssPixel.l = picturePixel.l;
                        ssPixel.a = picturePixel.a;
                    }
                }
            }
        }
    }
    return sheet_;
}
