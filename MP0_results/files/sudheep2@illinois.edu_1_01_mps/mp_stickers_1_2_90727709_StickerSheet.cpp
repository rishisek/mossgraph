#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"
#include <iostream>

using namespace cs225;

void StickerSheet::copy_(const StickerSheet & other) {
	max_ = other.max_;
	base = new Image(*(other.base));
	sticker_count_ = other.sticker_count_;
	Sheet = new Image * [max_];
	X = new unsigned[max_];
	Y = new unsigned[max_];
	for (unsigned layer = 0; layer < sticker_count_; layer++) {
		Sheet[layer] = new Image();
		*(Sheet[layer]) = *(other.Sheet[layer]);
		X[layer] = other.X[layer];
		Y[layer] = other.Y[layer];
	}
}

void StickerSheet::clear_() {
	for (unsigned layer = 0; layer < sticker_count_; layer++) {
		//delete Sheet[layer];
		Sheet[layer] = NULL;
	}
	delete base;
	delete[] Sheet;
	delete[] X;
	delete[] Y;
}

StickerSheet::StickerSheet(const Image & picture, unsigned max) {
	max_ = max;
	sticker_count_ = 0;
	Sheet = new Image * [max_];
	X = new unsigned[max_];
	Y = new unsigned[max_];
	base = new Image(picture);
	X[0] = 0; Y[0] = 0;
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
	
}

int StickerSheet::addSticker(Image & sticker, int x, int y) {
	for (unsigned layer = 0; layer < max_; layer++) {
		if(layer == sticker_count_){
			Image * stickerptr = &sticker;
			Sheet[layer] = stickerptr;
			Y[layer] = y;
			X[layer] = x;

		// if (Sheet[layer] == nullptr) {
			
		// 	X[layer] = x;
		// 	Y[layer] = y;
		// 	Sheet[layer] = &sticker;
			sticker_count_++;
			return layer;
		}
	}
	return -1;
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y){
		if(layer < max_){
			Image* stickerptr = &sticker;
			Sheet[layer] = stickerptr;
			X[layer] = x;
			Y[layer] = y;
			return layer;
		}
	return -1;
}

bool StickerSheet::translate(unsigned index, int x, int y) {
	if (index < sticker_count_) {
		X[index] = x;
		Y[index] = y;
		return true;
	}
	return false;
}

void StickerSheet::removeSticker(unsigned index) {
	delete Sheet[index];
	for (unsigned layer = index; layer < max_ - 1; layer++) {
		Sheet[layer] = Sheet[layer + 1];
		X[layer] = X[layer + 1];
		Y[layer] = Y[layer + 1];
	}
	Sheet[max_ - 1] = NULL;
	X[max_ - 1] = 0; 
	Y[max_ - 1] = 0; 
	sticker_count_--;
}

Image * StickerSheet::getSticker(unsigned index) const {
	if (index >= sticker_count_) {return NULL;}
	return Sheet[index];
}

int StickerSheet::layers() const{
	 return max_;
}

Image StickerSheet::render() const {
	Image comb(*base);
	for(unsigned layer = 0; layer< sticker_count_; layer++){
		unsigned w_min = 0;
		unsigned w_max = 0;
		unsigned h_min = 0;
		unsigned h_max = 0;
		if(X[layer] < w_min){
			w_min = X[layer];
		}
		if(X[layer] > w_max){
			w_max = X[layer];
		}
		if(Y[layer] < h_min){
			h_min = Y[layer];
		}
		if(Y[layer] < h_min){
			h_min = Y[layer];
		}
		if ((w_max + X[layer]) > comb.width()) {
			comb.resize(w_max + X[layer], comb.height());
		}
		if ((h_max + Y[layer]) > comb.height()) {
			comb.resize(comb.width(), h_max + Y[layer]);
		}
		if ((X[layer] - w_min) < comb.width()) {
			comb.resize(X[layer]-w_min, comb.height());
		}
		if ((Y[layer]-h_min) < comb.height()) {
			comb.resize(comb.width(), Y[layer]-h_min);
		}
		for (unsigned x = w_min; x < w_max; x++) {
			for (unsigned y = h_min; y < h_max; y++) {
				HSLAPixel & curr_comb_px = comb.getPixel(x + X[layer], y + Y[layer]);
				HSLAPixel & curr_img_px = Sheet[layer]->getPixel(x, y);
				if (curr_img_px.a != 0) {
					curr_comb_px = curr_img_px;
				}
			}
		}
	}
	return comb;
}

