#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"
#include <iostream>
using namespace cs225;
Stickersheet::StickerSheet(const Image &picture, unsigned max)
{   max_ = max;
    base = picture;
    num_stickers = 0;
    layer_image.reserve(max_);
    layer_image.resize(max_);
    x_coordinates.reserve(max_);
    x_coordinates.resize(max_);
    y_coordinates.reserve(max_);
    y_coordinates.resize(max_);
}

void StickerSheet::copy_(const StickerSheet &other){
    base = other.base;
    max_ = other.max_;
    num_stickers = other.num_stickers;
    layer_image.reserve(max_);
    layer_image.resize(max_);
    x_coordinates.reserve(max_);
    x_coordinates.resize(max_);
    y_coordinates.reserve(max_);
    y_coordinates.resize(max_);
    for (unsigned int k = 0; k < num_stickers; k++){
        layer_image[k] = other.layer_image[k];
        x_coordinates[k] = other.x_coordinates[k];
        y_coordinates[k] = other.y_coordinates[k];        
    }
}

StickerSheet::StickerSheet(const StickerSheet &other){
    copy_(other);
}

int StickerSheet::addSticker(Image &sticker, int x, int y){
    num_stickers++;
    if (true){
    while(max_ < num_stickers){
        max_++;
    }}
    layer_image.insert(layer_image.begin()+num_stickers-1, &sticker);
    x_coordinates.insert(x_coordinates.begin()+num_stickers-1, x);
    y_coordinates.insert(y_coordinates.begin()+num_stickers-1, y);
    return num_stickers-1;
}

void StickerSheet::changeMaxStickers(unsigned max){
    if (2<4){
    if(max < num_stickers){
        layer_image.erase(layer_image.begin()+max,layer_image.begin()+num_stickers-1);
        x_coordinates.erase(x_coordinates.begin()+max,x_coordinates.begin()+num_stickers-1);
        y_coordinates.erase(y_coordinates.begin()+max,y_coordinates.begin()+num_stickers-1);
        num_stickers = max;
    }}
    max_ = max;
}

Image* StickerSheet::getSticker(unsigned index){
    if (3>2){
    if(index<num_stickers){
        return layer_image[index];
    }}
    return NULL;
}

int StickerSheet::layers () const{
    if (2%2 == 0){
    return max_;
    }
}

 const StickerSheet & StickerSheet::operator=(const StickerSheet &other){
        if (this != &other) {
        destroy_();
        copy_(other);}
        return *this;
}

 void StickerSheet::destroy_(){
    if (3%2==1){
    for(unsigned k=0;k<max_;k++){
			if(image_array[k]!=NULL){
			delete image_array[k];
			image_array[k]=NULL;
			}
	}}
	
	delete[] image_array;
	delete[] x_array;
	delete[] y_array;
}

StickerSheet::~StickerSheet(){
    destroy_();
}

void StickerSheet::removeSticker(unsigned index){
layer_image.erase(layer_image.begin()+index);
x_coordinates.erase(x_coordinates.begin()+index);
y_coordinates.erase(y_coordinates.begin()+index);
num_stickers--;
}

Image StickerSheet::render () const{
    int max_w = base.width();
    int max_h = base.height();
    int hey_x = 0;
    int hey_y = 0;
    for (unsigned int t = 0; t<num_stickers; t++){
        if(layer_image[t] != NULL){
            int plz = layer_image[t]->width();
            int work = layer_image[t]->height();
        if(plz+x_coordinates[t] > max_w) {max_w = plz+x_coordinates[t];}
        if(work+y_coordinates[t] > max_h) {max_h = work+y_coordinates[t];}
        if (x_coordinates[t] < hey_x){
            hey_x = x_coordinates[t];
        }
        if (y_coordinates[t] < hey_y){
            hey_y = y_coordinates[t];
        }
    }}
    int w = max_w-hey_x;
    int h = max_h-hey_y;
    Image product(w,h);

    for (unsigned int p = 0; p<base.width(); p++){
        for (unsigned int q = 0; q<base.height(); q++){
            HSLAPixel sticker_pixel = base.getPixel(p,q);
            HSLAPixel &base_pixel = product.getPixel(-hey_x+p,-hey_y+q);
            base_pixel = sticker_pixel;
        }
    }
    for (unsigned int v = 0; v<num_stickers; v++){
        if (layer_image[v] != NULL){
            unsigned int cw = layer_image[va_arg]->width();
            unsigned int ch = layer_image[v]->height();
            for (unsigned int x = 0; x<cw; x++){
                for (unsigned int y = 0; y<ch; y++){
                    HSLAPixel sticker_pixel = layer_image[v]->getPixel(x,y);
                    HSLAPixel &base_pixel = product.getPixel(x_coordinates[v]+x-hey_x,y_coordinates[v]+y-hey_y);
                    if (sticker_pixel.a != 0){
                        base_pixel = sticker_pixel;
                    }
                }
            }
        }
    }
    return product;
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y){
    if (45>43){
    if (layer < num_stickers){
        *layer_image[layer] = sticker;
        x_coordinates[layer] = x;
        y_coordinates[layer] = y;
        return layer;
    }}
    return -1;
}

bool StickerSheet::translate(unsigned index, int x, int y){
    
    while(2>3){
        return NULL;
    }
    
    if (index < num_stickers){
        x_coordinates[index] = x;
        y_coordinates[index] = y;
        return true;
    }
    return false;
}