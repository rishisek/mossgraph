#include "StickerSheet.h"
#include "workspace/cs225/cs225git/mp_stickers/lib/cs225/HSLAPixel.h"
#include <iostream>

using namespace cs225;
StickerSheet::StickerSheet(const Image & picture, unsigned max) {
	max_ = max;
	num_stickers_ = 0;
	Images = new Image * [max_];
	x_ = new unsigned[max_];
	y_ = new unsigned[max_];
	base = new Image(picture);
	x_[0] = 0; y_[0] = 0;
}

StickerSheet::StickerSheet(const StickerSheet & other) {
	copy_(other);
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
	for (unsigned i = 0; i < max_; i++) {
		if (i == num_stickers_) {
			Images[i] = new Image(sticker);
			x_[i] = x;
			y_[i] = y;
			num_stickers_++;
			return int(i);
		}
	}
	return -1;
}

void StickerSheet::changeMaxStickers(unsigned max) {
	Image **tempStickerArray = new Image *[max_];
	unsigned *temp_x_coord = new unsigned [max_];
	unsigned *temp_y_coord = new unsigned [max_];

	unsigned int tempMaxSticker = max_;
	unsigned int tempNumSticker = max_;

	for(unsigned i = 0; i < tempNumSticker; i++){

		tempStickerArray[i] = Images[i];
		temp_x_coord[i] = x_[i];
		temp_y_coord[i] = y_[i];

	}
	delete [] x_;
	delete [] y_;
	delete [] Images;
	if (tempMaxSticker < max){
		Images = new Image *[max];
		x_ = new unsigned [max];
		y_ = new unsigned [max];
		for (unsigned int i = 0; i < tempNumSticker; i++){
			Images[i] = tempStickerArray[i];
			x_[i] = temp_x_coord[i];
			y_[i] = temp_y_coord[i];
		}
		max_ = max;

	} else {

		Images = new Image *[max];
		x_ = new unsigned [max];
		y_ = new unsigned [max];

		for (unsigned int i = 0; i < max; i++){
			Images[i] = tempStickerArray[i];
			x_[i] = temp_x_coord[i];
			y_[i] = temp_y_coord[i];
		}
		max_ = max;
	}
	if(max < num_stickers_){
		num_stickers_ = max;
    }
	delete [] tempStickerArray;
	delete [] temp_x_coord;
	delete [] temp_y_coord;
}

Image * StickerSheet::getSticker(unsigned index) const {
	if (index >= num_stickers_) {return NULL;}
	return Images[index];
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other) {
	if (this != &other) {
		destroy_();
		copy_(other);
	}
	return *this;
}

void StickerSheet::removeSticker(unsigned index) {
	delete Images[index];
	for (unsigned i = index; i < max_ - 1; i++) {
		Images[i] = Images[i + 1];
		x_[i] = x_[i + 1];
		y_[i] = y_[i + 1];
	}
	Images[max_ - 1] = NULL;
	x_[max_ - 1] = 0; 
	y_[max_ - 1] = 0; 
	num_stickers_--;
}

Image StickerSheet::render() const {
	Image result(*base);
	for (unsigned i = 0; i < num_stickers_; i++) {
		unsigned curw = Images[i]->width();
		unsigned curh = Images[i]->height();
		// Resize image accordingly
		if ((curw + x_[i]) > result.width()) {
			result.resize(curw + x_[i], result.height());
		}
		if ((curh + y_[i]) > result.height()) {
			result.resize(result.width(), curh + y_[i]);
		}
		// Overwrite necessary pixels
		for (unsigned x = 0; x < curw; x++) {
			for (unsigned y = 0; y < curh; y++) {
				HSLAPixel & cur_result_pixel = result.getPixel(x + x_[i], y + y_[i]);
				HSLAPixel & cur_image_pixel = Images[i]->getPixel(x, y);
				if (cur_image_pixel.a != 0) {
					cur_result_pixel = cur_image_pixel;
				}
			}
		}
	}
	return result;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
	if (index < num_stickers_) {
		x_[index] = x;
		y_[index] = y;
		return true;
	}
	return false;
}