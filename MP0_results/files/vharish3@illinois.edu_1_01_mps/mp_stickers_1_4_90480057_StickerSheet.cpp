#include "StickerSheet.h"


StickerSheet::StickerSheet(const Image &picture, unsigned max) {

    picture_ = picture;
    nth = max;
    for (unsigned int i = 0; i < nth; i++) {
        Stickers.push_back(NULL);
        x_coord.push_back(0);
        y_coord.push_back(0);
    }
    
}

StickerSheet::StickerSheet(const StickerSheet &other) {

    nth = other.nth;
    picture_ = other.picture_;
    Stickers = other.Stickers;
    x_coord = other.x_coord;
    y_coord = other.y_coord;


    /*
    _destroy();

    for (unsigned i = 0; i < sizeof(Stickers); i++) {
        x_coord.at(i) = other.x_coord.at(i);
    }

    for (unsigned j = 0; j < sizeof(Stickers); j++) {
        y_coord.at(j) = other.y_coord.at(j);
    }

    for (unsigned k = 0; k < sizeof(Stickers); k++) {
        Stickers.at(k) = other.Sticker.at(k);
    }
    */
}

StickerSheet::~StickerSheet() {

    return;

}

const StickerSheet & StickerSheet::operator=(const StickerSheet &other) {

    if (this != &other) { 

        _destroy();

        nth = other.nth;
        picture_ = other.picture_;
        Stickers = other.Stickers;
        x_coord = other.x_coord;
        y_coord = other.y_coord;
    }

    return *this;

}

void StickerSheet::changeMaxStickers(unsigned max) {

    if (max >= Stickers.size()) {

       for (unsigned i = nth; i < max; i++) {
            Stickers.push_back(NULL);
            x_coord.push_back(0);
            y_coord.push_back(0);
       }
       nth = max;
    }
    else if (max == 0) {

        Stickers.clear();
        x_coord.clear();
        y_coord.clear();

        nth = 0;
    }
    else {

        if(max < Stickers.size()) {
            Stickers.erase(Stickers.begin() + max, Stickers.end());
            x_coord.erase(x_coord.begin() + max, x_coord.end());
            y_coord.erase(y_coord.begin() + max, y_coord.end());

            nth = max;
        }
    }
}

int StickerSheet::addSticker(Image &sticker, int x, int y) {

    for (unsigned int i = 0; i < nth; i++) {
        if(Stickers[i] == NULL) {
            Stickers[i] = &sticker;
            x_coord[i] = x;
            y_coord[i] = y;
            // x_coord[i] = x;
            // y_coord[i] = y;
            // Stickers[i] = &sticker;
            return i;
        }
    }

    changeMaxStickers(nth + 1);
    x_coord[nth - 1] = x;
    y_coord[nth - 1] = y;
    Stickers[nth - 1] = &sticker;

    return nth - 1;
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {

    if (layer >= 0 && layer < nth) { 
        Stickers[layer] = &sticker;
        x_coord[layer] = x;
        y_coord[layer] = y;

        return layer;
    }
    else {
        return -1;
    }

}

bool StickerSheet::translate(unsigned index, int x, int y) {

    if(index >= 0 && index < nth && Stickers[index] != NULL) {
        x_coord[index] = x;
        y_coord[index] = y;
        return true;
    }
    else{
        return false;
    }
}

void StickerSheet::removeSticker(unsigned index) {

    if (index >= 0 && index < nth) {
        Stickers[index] = NULL;
    }
}

Image * StickerSheet::getSticker(unsigned index) {
   
    if (Stickers[index] == NULL) {
        return NULL;
    }
    else if (index < nth) {
        Image* dummy;
        dummy = Stickers[index];
        return dummy;
    }
    else{
        return NULL;
    }
}

int StickerSheet::layers() const {
    return nth;

}

Image StickerSheet::render() const {

    Image blankCanvas = picture_;
    //std::cout<<"check a"<<std::endl;
    unsigned totalW = blankCanvas.width();
    unsigned totalH = blankCanvas.height();
    //std::cout<<"the totalW is " << totalW <<std::endl;

    //std::cout<<"the size fo stickers is " << Stickers.size() <<std::endl;

   // std::cout<<"sticekr at index i is " << Stickers.at(i) <<std::endl;

    for (unsigned i = 0; i < nth; i++) {
        if (Stickers[i] != NULL) {
            if (x_coord[i] + (Stickers[i]-> width()) > totalW) {
                totalW = x_coord[i] + Stickers[i]->width();
            }

            if (y_coord[i] + (Stickers[i]->height()) > totalH) {
                totalH = y_coord[i] + Stickers[i]->height();
            }
        }
    }

    blankCanvas.resize(totalW, totalH);

    for (unsigned i = 0; i < nth; i++) {
        //std::cout << "x coord is " << x_coord[i] << " and y coord is " << y_coord[i] << std::endl;
        if (Stickers[i] != NULL){
            for (unsigned x = 0; (x < Stickers[i]->width()); x++){
                for (unsigned y = 0; y < Stickers[i]->height() ; y++) {
                    //std::cout << "x is " << x << "and y is " << y << std::endl;
                    if (Stickers[i]->getPixel(x,y).a == 1.0){
                    blankCanvas.getPixel(x_coord[i] + x, y_coord[i] + y) = Stickers[i]->getPixel(x,y);
                    
                    }
                }
            }
        }
    }

    return blankCanvas;
    
}

void StickerSheet::_destroy() {

    Stickers.clear();
    x_coord.clear();
    y_coord.clear();
}


