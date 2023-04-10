#include "StickerSheet.h"
#include "Image.h"
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"


#include <vector>
#include <iostream>
using namespace std;

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
   base = picture;
   max_ = max;
}


void StickerSheet::changeMaxStickers (unsigned max) {
    
    if (max < unsigned (max_) && max < sticker_vect.size()) {
        sticker_vect.resize(max);
        
    }
    max_ = max;

    
}
   
int StickerSheet::addSticker (Image &sticker, int x, int y) {
   sticker_vect.push_back(&sticker);

   struct ImageSticker img;
   img.index = sticker_vect.size() - 1;
   img.x_coord = x;
   img.y_coord = y;

   sticker_info_vect.push_back(img);

   size_t t_max = max_;

   if (sticker_vect.size() == t_max + 1) {
    max_ += 1;
   }

   return img.index;
}
int StickerSheet::setStickerAtLayer (Image &sticker, unsigned layer, int x, int y) {
    if (layer < 0 || layer > sticker_vect.size()) {
        return -1;
    }

    sticker_vect.at(layer) = &sticker;

    struct ImageSticker img;
    img.index = layer;
    img.x_coord = x;
    img.y_coord = y;

    sticker_info_vect.at(layer) = img;
    
    return layer;
}
bool StickerSheet::translate (unsigned index, int x, int y) {
    if (index < 0 || index >= sticker_vect.size()) {
        return false;
    }

    sticker_info_vect.at(index).y_coord = y;
    sticker_info_vect.at(index).x_coord = x;

    return true;
}
void StickerSheet::removeSticker(unsigned index) {
    if (index < 0 || index >= sticker_vect.size()) {
        return;
    }
    // for (unsigned int j = 0; j < (sticker_vect.at(index))->width(); j++) {
            
    //         for (unsigned int k = 0; k < (sticker_vect.at(index))->height(); k++) {
    //             sticker_vect.at(index)->getPixel(j,k).a = 0;
    //         }
    // }
   sticker_vect.erase(sticker_vect.begin() + index);
   sticker_info_vect.erase(sticker_info_vect.begin() + index);
   

}
Image* StickerSheet::getSticker(unsigned index) {
    if (index < 0 || index >= sticker_vect.size()) {
        return NULL;
    }
  
    return sticker_vect.at(index);
}
int StickerSheet::layers() const {
    return max_;
}
Image StickerSheet::render() const {

    Image img = base;

    

    for (unsigned int i = 0; i < sticker_vect.size(); i++) {
        
        for (unsigned int j = 0; j < (sticker_vect.at(i))->width(); j++) {
            
            for (unsigned int k = 0; k < (sticker_vect.at(i))->height(); k++) {

                
                if (sticker_vect.at(i)->getPixel(j, k).a == 0) {
                    
                } else {
                    int x = j + sticker_info_vect.at(i).x_coord;
                    int max_neg_x = 0;
                    int y = k + sticker_info_vect.at(i).y_coord;
                    int max_neg_y = 0;

                    // if (y < 0 && y < max_neg_y && x < 0 && x < max_neg_x) {
                    //     img.resize(-x + width(), -y + height());
                    //     max_neg_x = x;
                    //     max_neg_y = y;
                    // } else if (x < 0 && x < max_neg_x) {
                    //     img.resize(-x + width(), height());
                    //     max_neg_x = x;
                    // } else if (y < 0 && y < max_neg_y) {
                    //     img.resize(width(), -y + height());
                    //     max_neg_y = y;
                    // }
                    img.getPixel(x,y) = sticker_vect.at(i)->getPixel(j, k);
                }
            }
        }

        
    }
    
    
    return img;
}