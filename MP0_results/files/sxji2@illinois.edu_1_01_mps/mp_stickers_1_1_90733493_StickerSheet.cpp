/*#include "StickerSheet.h"
#include "Image.h" 

StickerSheet::StickerSheet(const Image& picture, unsigned max) {
    base_sheet = picture;
    max_num = max;
    sticker_sheet = new Image*[max_num];
    x = new unsigned[max_num];
    y = new unsigned[max_num];
    for (unsigned i = 0; i < max; i++) {
        sticker_sheet[i] = NULL;
    }
}

StickerSheet::~StickerSheet() {
    clear();
}

void StickerSheet::clear() {
    delete[] x;
    x = NULL;
    delete[] y;
    y = NULL;
    delete[] sticker_sheet;
    sticker_sheet = NULL;
}

StickerSheet::StickerSheet(const StickerSheet& other) {
    base_sheet = other.base_sheet;
    max_num = other.max_num;
    sticker_sheet = new Image*[max_num];
    x = new unsigned[max_num];
    y = new unsigned[max_num];
    for (unsigned i = 0; i < max_num; i++) {
        if (other.sticker_sheet[i] != NULL) {
            sticker_sheet[i] = other.sticker_sheet[i];
        }
        else {
            sticker_sheet[i] = NULL;
        }
        x[i] = other.x[i];
        y[i] = other.y[i];
    }
}

const StickerSheet& StickerSheet::operator=(const StickerSheet& other) {
    clear();
    base_sheet = other.base_sheet;
    max_num = other.max_num;
    sticker_sheet = new Image*[max_num];
    x = new unsigned[max_num];
    y = new unsigned[max_num];
    for (unsigned i = 0; i < other.max_num; i++) {
        if (other.sticker_sheet[i] != NULL) {
            sticker_sheet[i] = other.sticker_sheet[i];
        }
        else {
            sticker_sheet[i] = NULL;
        }
        x = &other.x[i];
        y = &other.y[i];
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    if (max == max_num) {
        return;
    }
    else {
        Image** temp = new Image*[max];
        unsigned *temp_x = new unsigned[max];
        unsigned *temp_y = new unsigned[max];
        for (unsigned i = 0; i < max; i++) {
            temp[i] = sticker_sheet[i];
            temp_x = &x[i];
            temp_y = &y[i];
        }
        if (max > max_num) {
            for (unsigned i = max_num; i < max; i++) {
                temp[i] = NULL;
            }
        }
        clear();
        sticker_sheet = temp;
        x = temp_x;
        y = temp_y;
        max_num = max;
    }
}

int StickerSheet::addSticker(Image& sticker, int x_new, int y_new) {
    for (unsigned i = 0; i < max_num; i++) {
        if (sticker_sheet[i] == NULL) {
            sticker_sheet[i] = &sticker;
            x[i] = x_new;
            y[i] = y_new;
            return i;
        }
    }
    return -1;
}

bool StickerSheet::translate(unsigned index, int x_new, int y_new) {
    if (sticker_sheet[index] == NULL || index >= max_num) {
        return false;
    } else {
        x[index] = x_new;
        y[index] = y_new;
        return true;
    }
}

void StickerSheet::removeSticker(unsigned index) {
    if (index < max_num && sticker_sheet[index] != NULL) {
        sticker_sheet[index] = NULL;
        delete sticker_sheet[index];
    }
}

Image* StickerSheet::getSticker(unsigned index) {
    if (sticker_sheet[index] == NULL) {
        return nullptr;
    }
    if (index > max_num) {
        return nullptr;
    }
    return sticker_sheet[index];
}

Image StickerSheet::render() const {
    unsigned w_ = 0;
    unsigned h_ = 0;
    for (unsigned i = 0; i < max_num; i++) {
        if (sticker_sheet[i] != NULL) {
            w_ = (x[i]+sticker_sheet[i]->width() > base_sheet.width()) ? x[i] + sticker_sheet[i]->width() : base_sheet.width();
            h_ = (x[i]+sticker_sheet[i]->height() > base_sheet.height()) ? y[i] + sticker_sheet[i] ->height() : base_sheet.height();
        }
    }
    if (w_ == 0 || h_ == 0) {
        return base_sheet;
    }
    Image final_image(w_, h_);
    for (unsigned i = 0; i < w_; i++) {
        for (unsigned j = 0; j < h_; j++) {
            HSLAPixel& pixel = final_image.getPixel(i, j);
            pixel = base_sheet.getPixel(i, j);
        }
    }
    for (unsigned i = 0; i < max_num; i++) {
        if (sticker_sheet[i] != NULL) {
            for (unsigned a = 0; a < sticker_sheet[i]->width(); a++) {
                for (unsigned b = 0; b < sticker_sheet[i]->height(); b++) {
                    HSLAPixel& basePixel = final_image.getPixel(x[i] + a, y[i] + b);
                    HSLAPixel& stickerPixel = final_image[i]->getPixel(a, b);
                    if (stickerPixel.a != 0) {
                        basePixel = stickerPixel;
                    }
                }
            }
        }
    }
    return final_image;
}*/


#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"
#include <iostream>

using namespace cs225;

void StickerSheet::copy_(const StickerSheet & other) {
	max_ = other.max_;
	base = new Image(*(other.base));
	num_stickers_ = other.num_stickers_;
	Images = new Image * [max_];
	XCoords = new unsigned[max_];
	YCoords = new unsigned[max_];
	for (unsigned i = 0; i < num_stickers_; i++) {
		Images[i] = new Image();
		*(Images[i]) = *(other.Images[i]);
		XCoords[i] = other.XCoords[i];
		YCoords[i] = other.YCoords[i];
	}
}

void StickerSheet::clear_() {
	for (unsigned i = 0; i < num_stickers_; i++) {
		delete Images[i];
		Images[i] = NULL;
	}
	delete base;
	delete[] Images;
	delete[] XCoords;
	delete[] YCoords;
}

StickerSheet::StickerSheet(const Image & picture, unsigned max) {
	max_ = max;
	num_stickers_ = 0;
	Images = new Image * [max_];
	XCoords = new unsigned[max_];
	YCoords = new unsigned[max_];
	base = new Image(picture);
	XCoords[0] = 0; YCoords[0] = 0;
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
		temp_xc[i] = XCoords[i];
		temp_yc[i] = YCoords[i];
	}
	delete[] Images;
	delete[] XCoords;
	delete[] YCoords;
	Images = new Image * [max];
	XCoords = new unsigned[max];
	YCoords = new unsigned[max];

	if (max < num_stickers_) {
		for (unsigned i = max; i < num_stickers_; i++) {
			delete temp_images[i];
			temp_images[i] = NULL;
		}
		num_stickers_ = max;
		for (unsigned i = 0; i < num_stickers_; i++) {
			Images[i] = temp_images[i];
			XCoords[i] = temp_xc[i];
			YCoords[i] = temp_yc[i];
		}
	}
	else {
		for (unsigned i = 0; i < num_stickers_; i++) {
			Images[i] = temp_images[i];
			XCoords[i] = temp_xc[i];
			YCoords[i] = temp_yc[i];
		}
	}
	max_ = max;
	delete[] temp_images;
	delete[] temp_xc;
	delete[] temp_yc;
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
	for (unsigned i = 0; i < max_; i++) {
		if (i == num_stickers_) {
			Images[i] = new Image(sticker);
			XCoords[i] = x;
			YCoords[i] = y;
			num_stickers_++;
			return int(i);
		}
	}
	return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
	if (index < num_stickers_) {
		XCoords[index] = x;
		YCoords[index] = y;
		return true;
	}
	return false;
}

void StickerSheet::removeSticker(unsigned index) {
	delete Images[index];
	for (unsigned i = index; i < max_ - 1; i++) {
		Images[i] = Images[i + 1];
		XCoords[i] = XCoords[i + 1];
		YCoords[i] = YCoords[i + 1];
	}
	Images[max_ - 1] = NULL;
	XCoords[max_ - 1] = 0; 
	YCoords[max_ - 1] = 0; 
	num_stickers_--;
}

Image * StickerSheet::getSticker(unsigned index) const {
	if (index >= num_stickers_) {return NULL;}
	return Images[index];
}

Image StickerSheet::render() const {
	Image result(*base);
	for (unsigned i = 0; i < num_stickers_; i++) {
		unsigned curw = Images[i]->width();
		unsigned curh = Images[i]->height();
		// Resize image accordingly
		if ((curw + XCoords[i]) > result.width()) {
			result.resize(curw + XCoords[i], result.height());
		}
		if ((curh + YCoords[i]) > result.height()) {
			result.resize(result.width(), curh + YCoords[i]);
		}
		// Overwrite necessary pixels
		for (unsigned x = 0; x < curw; x++) {
			for (unsigned y = 0; y < curh; y++) {
				HSLAPixel & cur_result_pixel = result.getPixel(x + XCoords[i], y + YCoords[i]);
				HSLAPixel & cur_image_pixel = Images[i]->getPixel(x, y);
				if (cur_image_pixel.a != 0) {
					cur_result_pixel = cur_image_pixel;
				}
			}
		}
	}
	return result;
}