
#include "StickerSheet.h"
using namespace std;
using namespace cs225;


StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    max_ = max;
    picture_ = picture;

}


void StickerSheet::changeMaxStickers(unsigned max){
    max_ = max;
    if (max_ < stickers.size()){

        stickers.erase(stickers.begin()+max_, stickers.end());
    
        
    }    
}
int StickerSheet::addSticker(Image &sticker, int x, int y){
    if (stickers.size() + 1 > max_){
        Sticker n = Sticker(&sticker, x, y);
        stickers.push_back(n);
        max_++;
        return stickers.size() - 1;
    }
    
    Sticker n = Sticker(&sticker, x, y);
    stickers.push_back(n);
    return stickers.size()-1;

}
int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y){
    if (layer >= max_){
        return -1;
    }
    
    Sticker n = Sticker(&sticker, x, y);
    stickers.erase(stickers.begin()+ layer);
    stickers.insert(stickers.begin() + layer,n);
    return layer;
}
bool StickerSheet::translate(unsigned index, int x, int y){
    if (index >= stickers.size()) {
        return false;
    }
    Sticker s = stickers.at(index);

    Sticker n = Sticker(s.img, x, y);
    stickers.erase(stickers.begin()+ index);
    stickers.insert(stickers.begin() + index,n);
    
    return true;
}
void StickerSheet::removeSticker(unsigned index){
    stickers.erase(stickers.begin() + index);
}
Image* StickerSheet::getSticker(unsigned index){
    if (index >= stickers.size()) {
        return nullptr;
    }
    return stickers.at(index).img;
}
int StickerSheet::layers() const{
    return max_;
}
Image StickerSheet::render() const{
    int x_max = picture_.width();
    int y_max = picture_.height();
    int x_min = 0;
    int y_min = 0;

    

    for (Sticker s : stickers){
        int a = int(s.img->width());
        int b = int(s.img->height());
        int c = s.y;
        int d = int(s.y);


        x_max = max(x_max, s.x + int(s.img->width()));
        y_max = max(y_max, s.y + int(s.img->height()));
        x_min = min(x_min, s.x);
        y_min = min(y_min, s.y);
    }
    if (x_min < 0){
        x_min *= -1;
    }
    unsigned x_off = x_min;
    if (y_min < 0){
        y_min *= -1;
    }
    unsigned y_off = y_min;

    Image result;

    result.resize(x_max + x_off,y_max + y_off);

    for (unsigned i = 0; i < picture_.width(); i++) {
            for (unsigned j = 0; j < picture_.height(); j++) {
                result.getPixel(i + x_off, j + y_off) = picture_.getPixel(i,j);  
            }
    }

    for (Sticker s : stickers){
        for (unsigned k = 0; k < s.img->width() ; k++){
            for (unsigned l = 0; l < s.img->height() ; l++){

                HSLAPixel & pixel = s.img->getPixel(k, l);

                if(pixel.a!=0){
                    unsigned x_ = s.x + x_off;
                    unsigned y_ = s.y + y_off;
                    

                    result.getPixel(x_ + k, y_ + l) = pixel;
                    
                }
            }
        }
        
    } 
    return result;
    
}