#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"
#include <iostream>

using namespace cs225;

void StickerSheet::copy_(const StickerSheet & other) {
	max_ = other.max_;
	base_var = new Image(*(other.base_var));
	num_of_stickers_ = other.num_of_stickers_;
	Images = new Image * [max_];
	XCoordinates = new unsigned[max_];
	YCoordinates = new unsigned[max_];
	for (unsigned i = 0; i < num_of_stickers_; i++) {
		Images[i] = new Image();
		*(Images[i]) = *(other.Images[i]);
		XCoordinates[i] = other.XCoordinates[i];
		YCoordinates[i] = other.YCoordinates[i];
	}
}

void StickerSheet::clear_() {
	for (unsigned i = 0; i < num_of_stickers_; i++) {
		delete Images[i];
		Images[i] = NULL;
	}
	delete base_var;
	delete[] Images;
	delete[] XCoordinates;
	delete[] YCoordinates;
}

StickerSheet::StickerSheet(const Image & picture, unsigned max) {
	max_ = max;
	num_of_stickers_ = 0;
	Images = new Image * [max_];
	XCoordinates = new unsigned[max_];
	YCoordinates = new unsigned[max_];
	base_var = new Image(picture);
	XCoordinates[0] = 0; YCoordinates[0] = 0;
}

StickerSheet::~StickerSheet() {
	clear_();
}

StickerSheet::StickerSheet(const StickerSheet & other) {
	copy_(other);
}

int StickerSheet::setStickerAtLayer(Image & sticker, unsigned layer, int x, int y) {
    return 0;
}

int StickerSheet::layers() const {
    return num_of_stickers_;
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other) {
	if (this != &other) {
		clear_();
		copy_(other);
	}
	return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
	Image ** temp_var_images = new Image * [num_of_stickers_];
	unsigned * temp_var_xcoords = new unsigned [num_of_stickers_];
	unsigned * temp_var_ycoords = new unsigned [num_of_stickers_];
	for (unsigned i = 0; i < num_of_stickers_; i++) {
		temp_var_images[i] = Images[i];
		temp_var_xcoords[i] = XCoordinates[i];
		temp_var_ycoords[i] = YCoordinates[i];
	}
	delete[] Images;
	delete[] XCoordinates;
	delete[] YCoordinates;
	Images = new Image * [max];
	XCoordinates = new unsigned[max];
	YCoordinates = new unsigned[max];

	if (max < num_of_stickers_) {
		for (unsigned i = max; i < num_of_stickers_; i++) {
			delete temp_var_images[i];
			temp_var_images[i] = NULL;
		}
		num_of_stickers_ = max;
		for (unsigned i = 0; i < num_of_stickers_; i++) {
			Images[i] = temp_var_images[i];
			XCoordinates[i] = temp_var_xcoords[i];
			YCoordinates[i] = temp_var_ycoords[i];
		}
	}
	else {
		for (unsigned i = 0; i < num_of_stickers_; i++) {
			Images[i] = temp_var_images[i];
			XCoordinates[i] = temp_var_xcoords[i];
			YCoordinates[i] = temp_var_ycoords[i];
		}
	}
	max_ = max;
	delete[] temp_var_images;
	delete[] temp_var_xcoords;
	delete[] temp_var_ycoords;
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
	for (unsigned i = 0; i < max_; i++) {
		if (i == num_of_stickers_) {
			Images[i] = new Image(sticker);
			XCoordinates[i] = x;
			YCoordinates[i] = y;
			num_of_stickers_++;
			return int(i);
		}
	}
	return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
	if (index < num_of_stickers_) {
		XCoordinates[index] = x;
		YCoordinates[index] = y;
		return true;
	}
	return false;
}

void StickerSheet::removeSticker(unsigned index) {
	delete Images[index];
	for (unsigned i = index; i < max_ - 1; i++) {
		Images[i] = Images[i + 1];
		XCoordinates[i] = XCoordinates[i + 1];
		YCoordinates[i] = YCoordinates[i + 1];
	}
	Images[max_ - 1] = NULL;
	XCoordinates[max_ - 1] = 0; 
	YCoordinates[max_ - 1] = 0; 
	num_of_stickers_--;
}

Image * StickerSheet::getSticker(unsigned index) const {
	if (index >= num_of_stickers_) {return NULL;}
	return Images[index];
}

Image StickerSheet::render() const {
	Image result(*base_var);
	for (unsigned i = 0; i < num_of_stickers_; i++) {
		unsigned current_width = Images[i]->width();
		unsigned current_height = Images[i]->height();
		if ((current_width + XCoordinates[i]) > result.width()) {
			result.resize(current_width + XCoordinates[i], result.height());
		}
		if ((current_height + YCoordinates[i]) > result.height()) {
			result.resize(result.width(), current_height + YCoordinates[i]);
		}
		for (unsigned x = 0; x < current_width; x++) {
			for (unsigned y = 0; y < current_height; y++) {
				HSLAPixel & current_result_pixel = result.getPixel(x + XCoordinates[i], y + YCoordinates[i]);
				HSLAPixel & current_image_pixel = Images[i]->getPixel(x, y);
				if (current_image_pixel.a != 0) {
					current_result_pixel = current_image_pixel;
				}
			}
		}
	}
	return result;
}