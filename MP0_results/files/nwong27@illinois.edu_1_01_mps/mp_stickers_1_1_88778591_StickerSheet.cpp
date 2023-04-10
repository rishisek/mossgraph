#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"
#include <iostream>

using namespace cs225;

void StickerSheet::copy_(const StickerSheet & other) {
	max_ = other.max_;
	image_base = new Image(*(other.image_base));
	num_stickers_ = other.num_stickers_;
	Images = new Image * [max_];
	CoordinateX = new unsigned[max_];
	CoordinateY = new unsigned[max_];
	for (unsigned i = 0; i < num_stickers_; i++) {
		Images[i] = new Image();
		*(Images[i]) = *(other.Images[i]);
		CoordinateX[i] = other.CoordinateX[i];
		CoordinateY[i] = other.CoordinateY[i];
	}
}

void StickerSheet::clear_() {
	for (unsigned i = 0; i < num_stickers_; i++) {
		delete Images[i];
		Images[i] = NULL;
	}
	delete image_base;
	delete[] Images;
	delete[] CoordinateX;
	delete[] CoordinateY;
}

StickerSheet::StickerSheet(const Image & picture, unsigned max) {
	max_ = max;
	num_stickers_ = 0;
	Images = new Image * [max_];
	CoordinateX = new unsigned[max_];
	CoordinateY = new unsigned[max_];
	image_base = new Image(picture);
	CoordinateX[0] = 0; CoordinateY[0] = 0;
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
	Image ** images_temp = new Image * [num_stickers_];
	unsigned * xc_temp = new unsigned [num_stickers_];
	unsigned * yc_temp = new unsigned [num_stickers_];
	for (unsigned i = 0; i < num_stickers_; i++) {
		images_temp[i] = Images[i];
		xc_temp[i] = CoordinateX[i];
		yc_temp[i] = CoordinateY[i];
	}
	delete[] Images;
	delete[] CoordinateX;
	delete[] CoordinateY;
	Images = new Image * [max];
	CoordinateX = new unsigned[max];
	CoordinateY = new unsigned[max];
	if (max < num_stickers_) {
		for (unsigned i = max; i < num_stickers_; i++) {
			delete images_temp[i];
			images_temp[i] = NULL;
		}
		num_stickers_ = max;
		for (unsigned i = 0; i < num_stickers_; i++) {
			Images[i] = images_temp[i];
			CoordinateX[i] = xc_temp[i];
			CoordinateY[i] = yc_temp[i];
		}
	}
	else {
		for (unsigned i = 0; i < num_stickers_; i++) {
			Images[i] = images_temp[i];
			CoordinateX[i] = xc_temp[i];
			CoordinateY[i] = yc_temp[i];
		}
	}
	max_ = max;
	delete[] images_temp;
	delete[] xc_temp;
	delete[] yc_temp;
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
	for (unsigned i = 0; i < max_; i++) {
		if (i == num_stickers_) {
			Images[i] = new Image(sticker);
			CoordinateX[i] = x;
			CoordinateY[i] = y;
			num_stickers_++;
			return int(i);
		}
	}
	return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
	if (index < num_stickers_) {
		CoordinateX[index] = x;
		CoordinateY[index] = y;
		return true;
	}
	return false;
}

void StickerSheet::removeSticker(unsigned index) {
	delete Images[index];
	for (unsigned i = index; i < max_ - 1; i++) {
		Images[i] = Images[i + 1];
		CoordinateX[i] = CoordinateX[i + 1];
		CoordinateY[i] = CoordinateY[i + 1];
	}
	Images[max_ - 1] = NULL;
	CoordinateX[max_ - 1] = 0; 
	CoordinateY[max_ - 1] = 0; 
	num_stickers_--;
}

Image * StickerSheet::getSticker(unsigned index) const {
	if (index >= num_stickers_) {return NULL;}
	return Images[index];
}

Image StickerSheet::render() const {
	Image result(*image_base);
	for (unsigned i = 0; i < num_stickers_; i++) {
		unsigned wcur = Images[i]->width();
		unsigned hcur = Images[i]->height();
		if ((wcur + CoordinateX[i]) > result.width()) {
			result.resize(wcur + CoordinateX[i], result.height());
		}
		if ((hcur + CoordinateY[i]) > result.height()) {
			result.resize(result.width(), hcur + CoordinateY[i]);
		}
		for (unsigned x = 0; x < wcur; x++) {
			for (unsigned y = 0; y < hcur; y++) {
				HSLAPixel & pixel_result_cur = result.getPixel(x + CoordinateX[i], y + CoordinateY[i]);
				HSLAPixel & pixel_image_cur = Images[i]->getPixel(x, y);
				if (pixel_image_cur.a != 0) {
					pixel_result_cur = pixel_image_cur;
				}
			}
		}
	}
	return result;
}