#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"
#include <iostream> 

using namespace std; 

void StickerSheet::copy_(const StickerSheet & other){
    max_ = other.max_;
	base = new Image(*(other.base));
	num_stickers_ = other.num_stickers_;
	Images = new Image * [max_];
	xcoord = new unsigned[max_];
	ycoord = new unsigned[max_];
	for (unsigned i = 0; i < num_stickers_; i++) {
		Images[i] = new Image();
		*(Images[i]) = *(other.Images[i]);
		xcoord[i] = other.xcoord[i];
		ycoord[i] = other.ycoord[i];
	}
}

void StickerSheet::clear_() {
	/*
    for (unsigned i = 0; i < num_stickers_; i++) {
		delete Images[i];
		Images[i] = NULL;
	}*/
	delete base;
	delete[] Images;
	delete[] xcoord;
	delete[] ycoord;
}

StickerSheet::StickerSheet(const Image & picture, unsigned max) {
	max_ = max;
	num_stickers_ = 0;
	Images = new Image * [max_];
	xcoord = new unsigned[max_];
	ycoord = new unsigned[max_];
	base = new Image(picture);
	xcoord[0] = 0; ycoord[0] = 0;
}

StickerSheet::~StickerSheet() {
	clear_();
}

StickerSheet::StickerSheet(const StickerSheet & other) {
	copy_(other);
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other) {
	if (this != &other) {
		clear_();
		copy_(other);
	}
	return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
	//Image ** temp_images = new Image * [max_];
	Image ** temp_images = new Image * [num_stickers_];
	unsigned * temp_xc = new unsigned [num_stickers_];
	unsigned * temp_yc = new unsigned [num_stickers_];
	for (unsigned i = 0; i < num_stickers_; i++) {
		temp_images[i] = Images[i];
		temp_xc[i] = xcoord[i];
		temp_yc[i] = ycoord[i];
	}
	delete[] Images;
	delete[] xcoord;
	delete[] ycoord;
	Images = new Image * [max];
	xcoord = new unsigned[max];
	ycoord = new unsigned[max];

	if (max < num_stickers_) {
		for (unsigned i = max; i < num_stickers_; i++) {
			delete temp_images[i];
			temp_images[i] = NULL;
		}
		num_stickers_ = max;
		for (unsigned i = 0; i < num_stickers_; i++) {
			Images[i] = temp_images[i];
			xcoord[i] = temp_xc[i];
			ycoord[i] = temp_yc[i];
		}
	}
	else {
		for (unsigned i = 0; i < num_stickers_; i++) {
			Images[i] = temp_images[i];
			xcoord[i] = temp_xc[i];
			ycoord[i] = temp_yc[i];
		}
	}
	max_ = max;
	delete[] temp_images;
	delete[] temp_xc;
	delete[] temp_yc;
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
	if(num_stickers_ >= max_){
        return -1; 
    }
    Images[num_stickers_] = &sticker;
    xcoord[num_stickers_] = x;
	ycoord[num_stickers_] = y;
	num_stickers_++;
	return num_stickers_ - 1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
	if (index < num_stickers_) {
		xcoord[index] = x;
		ycoord[index] = y;
		return true;
	}
	return false;
}

void StickerSheet::removeSticker(unsigned index) {
	delete Images[index];
	for (unsigned i = index; i < max_ - 1; i++) {
		Images[i] = Images[i + 1];
		xcoord[i] = xcoord[i + 1];
		ycoord[i] = ycoord[i + 1];
	}
	Images[max_ - 1] = NULL;
	xcoord[max_ - 1] = 0; 
	ycoord[max_ - 1] = 0; 
	num_stickers_--;
}

Image * StickerSheet::getSticker(unsigned index) const {
	if (index >= num_stickers_ ) {return NULL;}
	return Images[index];
}

Image StickerSheet::render() const {
	Image result(*base);
	for (unsigned i = 0; i < num_stickers_; i++) {
		unsigned curw = Images[i]->width();
		unsigned curh = Images[i]->height();
		if ((curw + xcoord[i]) > result.width()) {
			result.resize(curw + xcoord[i], result.height());
		} 
		if ((curh + ycoord[i]) > result.height()) {
			result.resize(result.width(), curh + ycoord[i]);    
		}
		for (unsigned x = 0; x < curw; x++) {
			for (unsigned y = 0; y < curh; y++) {
				HSLAPixel & cur_result_pixel = result.getPixel(x + xcoord[i], y + ycoord[i]);
				HSLAPixel & cur_image_pixel = Images[i]->getPixel(x, y);
				if (cur_image_pixel.a != 0) {
					cur_result_pixel = cur_image_pixel;
				}
			}
		}
	}
	return result;
}


int StickerSheet::layers() const{
    return max_; 
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y){
    for(unsigned i = 0; i < num_stickers_; i++){
        if(i == layer){
            Images[i] = new Image(sticker);
            xcoord[i] = x;
			ycoord[i] = y;
			return int(i);
		}
	}
	return -1;

}

 