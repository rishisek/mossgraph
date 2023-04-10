#include "StickerSheet.h"
// mem vars :
//    unsigned max_stickers
//    Image *base_img    ->   pointer to base image
//    vector<*Image> sticker_vect     ->    vector of stickers each entry is a layer
//    vector<int> x_vect      
//    vector<int> y_vect

// upper left of base == 0,0

// stickers placed on base
// base image om inf. white canvas
// stickers placed one layer at a time starting at layer zero-max
// if there is no sticker on a lyaer dont do anything for that layer
// stickers can be added and removed
// we can produce the samllest rectangular image that contains base & all stickers 


StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    max_stickers = max;
    base_img = picture;
    clear();
    //changeMaxStickers(max_stickers);
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    this->base_img = other.base_img;
    this->max_stickers = other.max_stickers;
    this->clear(); 
    
    for (int i = 0; i < int(other.sticker_vect.size()); i++) {
        (this->sticker_vect).push_back(other.sticker_vect.at(i));
        (this->x_cord).push_back(other.x_cord.at(i));
        (this->y_cord).push_back(other.y_cord.at(i));
    }
}

int StickerSheet::addSticker(Image &sticker, int x, int y) {
    // maybe delete inital loop???????????
    if (sticker_vect.size() >= (max_stickers)) {
        changeMaxStickers(max_stickers + 1);
    }
    if (int(sticker_vect.size()) != int(max_stickers)) {
        sticker_vect.push_back(&sticker);
        x_cord.push_back(x);
        y_cord.push_back(y);
        return sticker_vect.size() - 1;
    }
    return -1;
        //Image* img = &sticker;
        //sticker_vect.push_back(img);
        //coord_map.insert({img, make_pair(x,y)});
        //return sticker_vect.size() - 1;
}
int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
    if (layer >= max_stickers || layer < 0) {
        return -1;
    }

    sticker_vect.at(layer) = &sticker;
    x_cord.at(layer) = x;
    y_cord.at(layer) = y;
    

   return layer; 
}
void StickerSheet::changeMaxStickers(unsigned max) {
    if (max < max_stickers) {
        while (max < sticker_vect.size())
        {
            sticker_vect.pop_back();
            x_cord.pop_back();
            y_cord.pop_back();
        }
        //sticker_vect.erase(sticker_vect.begin() + max, sticker_vect.end());
    }
    max_stickers = max;
    //sticker_vect.resize(max);
}

Image* StickerSheet::getSticker(unsigned index) {
    if (index < 0 || index >= sticker_vect.size()) return NULL;
    Image* rtrn = sticker_vect[index];
    return rtrn;
}
int StickerSheet::layers() const {
    return max_stickers;
}
const StickerSheet& StickerSheet::operator=(const StickerSheet &other) {
    this->base_img = other.base_img;
    this->max_stickers = other.max_stickers;
    this->clear(); 
    
    for (int i = 0; i < int(other.sticker_vect.size()); i++) {
        (this->sticker_vect).push_back(other.sticker_vect.at(i));
        (this->x_cord).push_back(other.x_cord.at(i));
        (this->y_cord).push_back(other.y_cord.at(i));
    }
    return *this;
}
void StickerSheet::removeSticker(unsigned index) {
    if (index >= 0 && index < sticker_vect.size()) {
        (this-> sticker_vect).erase((this->sticker_vect).begin() + index);
        (this->x_cord).erase((this->x_cord).begin() + index);
        (this->y_cord ).erase((this->y_cord).begin() + index);
    }
}

Image StickerSheet::render() const {

    int f_w = 0;
    int f_h = 0;
    for (int i = 0; i < int(this->sticker_vect.size()); i++) {
        int tmp_x = x_cord.at(i); 
        int tmp_y = y_cord.at(i);
        int imgW = this->sticker_vect.at(i)->width();
        int imgH = this->sticker_vect.at(i)->height();
        if (tmp_x+imgW > f_w) {
            f_w = tmp_x + imgW;
        }
        if (tmp_y+imgH > f_h) {
            f_h = tmp_y + imgH;
        }
    }
    Image full_img = this->base_img;
    if (f_w > int(this->base_img.width()) && f_h > int(this->base_img.height())) {
        full_img.resize(f_w, f_h);
    } else if (f_w > int(this->base_img.width())) {
        full_img.resize(f_w , this->base_img.height());
    } else if (f_h > int(this->base_img.height())) {
            full_img.resize(this->base_img.width(),f_h);
    }
    for (int i = 0; i < int(sticker_vect.size()); i++) {
        int x_0 = this->x_cord.at(i);
        int y_0 = this->y_cord.at(i);
        int stkr_w = this->sticker_vect.at(i)->width();
        int stkr_h = this->sticker_vect.at(i)->height();

        for (int j = x_0; j < (x_0 + stkr_w); j++) {
            for (int k = y_0; k < (y_0 + stkr_h); k++) {
                cs225::HSLAPixel & image_p = this->sticker_vect.at(i)->getPixel(j-x_0, k-y_0);
                cs225::HSLAPixel & stkr_p = full_img.getPixel(j,k);
                if (image_p.a != 0) {
                    stkr_p.h = image_p.h;
                    stkr_p.s = image_p.s;
                    stkr_p.l = image_p.l;
                    stkr_p.a = image_p.a;
                }
            }
        }
    }
    return full_img;
}

bool StickerSheet::translate(unsigned index, int x, int y) {
    if (index >= 0 && index < sticker_vect.size()) {
        x_cord.at(index) = x;
        y_cord.at(index) = y;
        //Image* stkr = sticker_vect.at(index);
        //coord_map.find(stkr)->second = make_pair(x,y);
        return true;
    }
    return false;
}
void StickerSheet::copy(const StickerSheet &other) {
    base_img = other.base_img;
    max_stickers = other.max_stickers;
    coord_map.clear();
    for (Image* img : other.sticker_vect) {
        addSticker(*img, other.coord_map.find(img)->second.first, other.coord_map.find(img)->second.second);
    }
}
void StickerSheet::clear() {
    for (int i = 0; i < int(this->sticker_vect.size()); i++) {
        this->sticker_vect.pop_back();
        this->x_cord.pop_back();
        this->y_cord.pop_back();
    }
}