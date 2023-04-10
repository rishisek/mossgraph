#include "StickerSheet.h"



StickerSheet::StickerSheet (const Image &picture, unsigned max){
    base.resize(picture.width(),picture.height());
    for (unsigned int w = 0; w < base.width(); w++) {
        for (unsigned int h = 0; h < base.height(); h++) {
            base.getPixel(w,h) = picture.getPixel(w,h);
        }
    }
    maximum = max;
}
StickerSheet::~StickerSheet () {
    maximum = 0;
}
StickerSheet::StickerSheet (const StickerSheet &other){
    base = other.base;
    sheets.clear();
    for (unsigned int s = 0; s < other.sheets.size(); s++) {
        sheets.push_back(other.sheets[s]);
    }
    maximum = other.maximum;
}

int StickerSheet::addSticker (Image &sticker, int x, int y) {
    Image* stick = &sticker;
    if (sheets.size() >= maximum) {
        changeMaxStickers(maximum+1);
        sheets.push_back(std::pair(stick,std::pair(x,y)));
        return sheets.size() - 1;
    }
    for (unsigned int s = 0; s < sheets.size(); s++) {
        if(sheets[s].first == NULL) {
            sheets[s].first = stick;
            sheets[s].second = std::make_pair(x,y);
            return s;
        }
    }
    
    sheets.push_back(std::pair(stick,std::pair(x,y)));
    return sheets.size() - 1;
}
void StickerSheet::changeMaxStickers (unsigned max){
    maximum = max;
    if (sheets.size() > max) {
        sheets.erase(sheets.begin() + max,sheets.end());
    }
}

int StickerSheet::setStickerAtLayer (Image &sticker, unsigned layer, int x, int y) {
    if (layer < 0 || layer >= maximum || sheets[layer].first == NULL) {
        return -1;
    }
    sheets[layer].first = &sticker;
    sheets[layer].second = std::make_pair(x,y);
    return layer;
}
bool StickerSheet::translate (unsigned index, int x, int y){
    if (sheets.size() <= index) {
        return false;
    }
    sheets[index].second.first = x;
    sheets[index].second.second = y;
    return true;
}
void StickerSheet::removeSticker (unsigned index){
    sheets.erase(sheets.begin()+index);

}
Image* StickerSheet::getSticker (unsigned index){
    if (sheets.size() <= index) {
        return NULL;
    }
    return sheets[index].first;
}
int StickerSheet::layers () const{
        return maximum;
}
const StickerSheet& StickerSheet::operator=(const StickerSheet &other){
    base = other.base;
    sheets.clear();
    for (unsigned int s = 0; s < other.sheets.size(); s++) {
        sheets.push_back(other.sheets[s]);
    }
    maximum = other.maximum;
    return *this;
}
Image StickerSheet::render () const{
    Image image;
    int right_most = base.width();
    int bottom_most = base.height();
    int left_most = 0;
    int top_most = 0;
    // for (unsigned int i = 0; i < sheets.size(); i++) {
    //     if (sheets[i].first->width() + sheets[i].second.first > width) {
    //         width = sheets[i].first->width() + sheets[i].second.first;
    //     }
    //     if (sheets[i].first->height() + sheets[i].second.second > height) {
    //         height = sheets[i].first->height() + sheets[i].second.second;
    //     }
    // }
    
    
    
    for (unsigned int i = 0; (i < sheets.size()) && (sheets[i].first != NULL); i++) {
        if (sheets[i].second.first < left_most) {
            left_most = sheets[i].second.first;
        }
        if (sheets[i].second.first + (int)sheets[i].first->width() > right_most) {
            right_most = sheets[i].second.first + sheets[i].first-> width();
        }
        if (sheets[i].second.second < top_most) {
            top_most = sheets[i].second.second;
        }
        if (sheets[i].second.second + (int)sheets[i].first-> height() > bottom_most) {
            bottom_most = sheets[i].second.second +sheets[i].first-> height();
        }
    }
    image.resize(right_most - left_most,bottom_most - top_most);
    for (int w = 0; w < (int)base.width(); w++) {
        for (int h = 0; h < (int)base.height(); h++) {
            image.getPixel(w - left_most,h - top_most) = base.getPixel(w,h);
        }
    }
    
    for (int s = 0; (s < (int)sheets.size()) && (sheets[s].first != NULL); s++) {
        for ( int w = left_most; w < right_most; w++) {
            int tempx = sheets[s].second.first;
            for (int h = top_most; h < bottom_most; h++) {
                int tempy = sheets[s].second.second;
                if ( w >= tempx && w < tempx + (int)sheets[s].first -> width()
                && h >= tempy && h < tempy + (int)sheets[s].first -> height() 
                && sheets[s].first->getPixel(w - tempx, h - tempy).a > 0) {
                    image.getPixel(w - left_most, h - top_most) = sheets[s].first -> getPixel(w - tempx, h - tempy);
                } 
            }
        }
    }
    
    return image;
}


