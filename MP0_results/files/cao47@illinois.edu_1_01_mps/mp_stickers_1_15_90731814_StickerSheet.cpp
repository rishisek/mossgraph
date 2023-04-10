#include "StickerSheet.h"
    StickerSheet::StickerSheet (const Image &picture, unsigned max){}
    StickerSheet::StickerSheet (const StickerSheet &other){}
    const StickerSheet& StickerSheet:: operator=(const StickerSheet &other){ 
    
    return *this;
    }
    void 	StickerSheet::changeMaxStickers (unsigned max){}
    int 	StickerSheet::addSticker (Image &sticker, int x, int y){return 1;}
    int 	StickerSheet::setStickerAtLayer (Image &sticker, unsigned layer, int x, int y){return 1;}
    bool 	StickerSheet::translate (unsigned index, int x, int y){return false;}
    void 	StickerSheet::removeSticker (unsigned index){}
    Image * 	StickerSheet::getSticker (unsigned index){return nullptr;}
    int 	StickerSheet::layers () const{return 3;}
    Image 	StickerSheet::render () const{return Image();}