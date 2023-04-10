#include "StickerSheet.h"
#include <vector>
 

StickerSheet::StickerSheet (const Image &picture, unsigned max) {
    baseimage = picture;
    max_st = max;
    
}
StickerSheet::StickerSheet (const StickerSheet &other) {
     baseimage = other.baseimage;
     max_st = other.max_st;

     for (unsigned i = 0; i < other.image_d.size(); i++) {
        image_d.push_back(other.image_d[i]);
        thevector.push_back(other.thevector[i]);
     }
}
const StickerSheet & StickerSheet::operator= (const StickerSheet &other){
    if (this == &other) return *this;
    baseimage = other.baseimage;
     max_st = other.max_st;

     for (unsigned i = 0; i < other.image_d.size(); i++) {
        image_d.push_back(other.image_d[i]);
        thevector.push_back(other.thevector[i]);
     }
    return *this;
}
void StickerSheet::changeMaxStickers (unsigned max){ 
    max_st = max;
    image_d.resize(std::min(max_st, image_d.size()));
    thevector.resize(std::min(max_st, thevector.size()));
}
int StickerSheet::addSticker (Image &sticker, int x, int y) {
    if (image_d.size() >= max_st) {
        max_st++;
    }
     image_d.push_back(&sticker);
     thevector.push_back(std::make_pair(x, y));
     return image_d.size() - 1;
}
int StickerSheet::setStickerAtLayer (Image &sticker, unsigned layer, int x, int y){
    if (layer >= max_st) {
        return -1;
    }
     image_d[layer] = &sticker;
     thevector[layer] = std::make_pair(x, y);
     return layer;
}
bool StickerSheet::translate (unsigned index, int x, int y){
 if (index >= image_d.size()) {
    return false;
 }
 thevector[index] = std::make_pair(x, y);
 return true;
}
void StickerSheet::removeSticker (unsigned index){
    image_d.erase(image_d.begin() + index);
    thevector.erase(thevector.begin() + index);
}
Image * StickerSheet::getSticker (unsigned index){
 if (index>= image_d.size()) {
    return NULL;
 }
 return image_d[index];
}
int StickerSheet::layers () const{
   return max_st;
}
Image StickerSheet::render () const{
    Image ret(baseimage);
    int x = 0, y = 0;

    for (unsigned i = 0; i < image_d.size(); i++) {
        int w = image_d[i]->width();
        int h = image_d[i]->height();

        if (thevector[i].first < 0 || thevector[i].second < 0) {
            x = std::max(x, -thevector[i].first);
            y = std::max(y, -thevector[i].second);
            ret.enlarge(ret.width() + x, ret.height() + y, x, y);
        }
        if (x + w + thevector[i].first >= (int) ret.width() || y + h + thevector[i].second >= (int) ret.height())
            ret.enlarge(std::max((int) ret.width(), x + w + thevector[i].first), std::max(y + h + thevector[i].second, (int) ret.height()), x, y);

        for (int j = 0; j < w; j++) {
            for (int k = 0; k < h; k++) {
                if (image_d[i]->getPixel(j, k).a != 0)
                ret.getPixel(j + thevector[i].first + x, k + thevector[i].second + y) = image_d[i]->getPixel(j, k);
            }
        }
    }

    return ret;
}