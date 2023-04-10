#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"
#include <iostream>

using namespace cs225;

void StickerSheet::copy_(const StickerSheet & other) {
	layers_ = other.layers_;
	base = new Image(*(other.base));
	stickers_ = other.stickers_;
	Images = new Image * [layers_];
	x_coord = new unsigned[layers_];
	y_coord = new unsigned[layers_];
	for (unsigned i = 0; i < stickers_; i++) {
		Images[i] = new Image();
		*(Images[i]) = *(other.Images[i]);
		x_coord[i] = other.x_coord[i];
		y_coord[i] = other.y_coord[i];
	}
}

void StickerSheet::clear_() {
	for (unsigned i = 0; i < stickers_; i++) {
		delete Images[i];
		Images[i] = NULL;
	}
	delete base;
	delete[] Images;
	delete[] x_coord;
	delete[] y_coord;
}

StickerSheet::StickerSheet(const Image & picture, unsigned max) {
	layers_ = max;
	stickers_ = 0;
	Images = new Image * [layers_];
	x_coord = new unsigned[layers_];
	y_coord = new unsigned[layers_];
	base = new Image(picture);
	x_coord[0] = 0; y_coord[0] = 0;
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
	Image ** temp_images = new Image * [stickers_];
	unsigned * temp_xc = new unsigned [stickers_];
	unsigned * temp_yc = new unsigned [stickers_];
	for (unsigned i = 0; i < stickers_; i++) {
		temp_images[i] = Images[i];
		temp_xc[i] = x_coord[i];
		temp_yc[i] = y_coord[i];
	}
	delete[] Images;
	delete[] x_coord;
	delete[] y_coord;
	Images = new Image * [max];
	x_coord = new unsigned[max];
	y_coord = new unsigned[max];

	if (max < stickers_) {
		for (unsigned i = max; i < stickers_; i++) {
			delete temp_images[i];
			temp_images[i] = NULL;
		}
		stickers_ = max;
		for (unsigned i = 0; i < stickers_; i++) {
			Images[i] = temp_images[i];
			x_coord[i] = temp_xc[i];
			y_coord[i] = temp_yc[i];
		}
	}
	else {
		for (unsigned i = 0; i < stickers_; i++) {
			Images[i] = temp_images[i];
			x_coord[i] = temp_xc[i];
			y_coord[i] = temp_yc[i];
		}
	}
	layers_ = max;
	delete[] temp_images;
	delete[] temp_xc;
	delete[] temp_yc;
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
	for (unsigned i = 0; i < layers_; i++) {
		if (i == stickers_) {
			Images[i] = new Image(sticker);
			x_coord[i] = x;
			y_coord[i] = y;
			stickers_++;
			return int(i);
		}
	}
	changeMaxStickers(layers_ + 1);
	Images[layers_] = new Image(sticker);
	x_coord[layers_] = x;
	y_coord[layers_] = y;
	stickers_++;
	return int(layers_);
}

int StickerSheet::setStickerAtLayer	(Image & sticker, unsigned layer, int x, int y) {
    for (unsigned i = 0; i < layers_; i++) {
		if (i == layer) {
			Images[i] = new Image(sticker);
			x_coord[i] = x;
			y_coord[i] = y;
			stickers_++;
			return int(layer);
		}
	}
	return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
	if (index < stickers_) {
		x_coord[index] = x;
		y_coord[index] = y;
		return true;
	}
	return false;
}

void StickerSheet::removeSticker(unsigned index) {
	delete Images[index];
	for (unsigned i = index; i < layers_ - 1; i++) {
		Images[i] = Images[i + 1];
		x_coord[i] = x_coord[i + 1];
		y_coord[i] = y_coord[i + 1];
	}
	Images[layers_ - 1] = NULL;
	x_coord[layers_ - 1] = 0; 
	y_coord[layers_ - 1] = 0; 
	stickers_--;
}

Image * StickerSheet::getSticker(unsigned index) const {
	if (index >= stickers_) {return NULL;}
	return Images[index];
}

Image StickerSheet::render() const {
	Image result(*base);
	for (unsigned i = 0; i < stickers_; i++) {
		unsigned curw = Images[i]->width();
		unsigned curh = Images[i]->height();
		// Resize image accordingly
		if ((curw + x_coord[i]) > result.width()) {
			result.resize(curw + x_coord[i], result.height());
		}
		if ((curh + y_coord[i]) > result.height()) {
			result.resize(result.width(), curh + y_coord[i]);
		}
		// Overwrite necessary pixels
		for (unsigned x = 0; x < curw; x++) {
			for (unsigned y = 0; y < curh; y++) {
				HSLAPixel & cur_result_pixel = result.getPixel(x + x_coord[i], y + y_coord[i]);
				HSLAPixel & cur_image_pixel = Images[i]->getPixel(x, y);
				if (cur_image_pixel.a != 0) {
					cur_result_pixel = cur_image_pixel;
				}
			}
		}
	}
	return result;
}

int StickerSheet::layers () const {
    return layers_;
}


