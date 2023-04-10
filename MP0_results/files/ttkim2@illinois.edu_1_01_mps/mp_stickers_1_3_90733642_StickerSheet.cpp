#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"
#include <iostream>

using namespace cs225;

void StickerSheet::copy_(const StickerSheet & other) {
	max_ = other.max_;
	base = new Image(*(other.base));
	num = other.num;
	pic_ = new Image * [max_];
	xCord = new unsigned[max_];
	yCord = new unsigned[max_];
	unsigned i = 0;
	while (i < num) {
		pic_[i] = new Image();
		*(pic_[i]) = *(other.pic_[i]);
		xCord[i] = other.xCord[i];
		yCord[i] = other.yCord[i];
		i++;
	}
}

void StickerSheet::clear_() {
	unsigned i = 0;
	while (i < num) {
		delete pic_[i];
		pic_[i] = nullptr;
		i++;
	}
	delete base;
	delete[] pic_;
	delete[] xCord;
	delete[] yCord;
}

StickerSheet::StickerSheet(const Image & picture, unsigned max) {
	max_ = max;
	xCord = new unsigned[max_];
	yCord = new unsigned[max_];
	num = 0;
	pic_ = new Image * [max_];
	base = new Image(picture);
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
  Image** copy = new Image*[max];
  unsigned* new_x = new unsigned[max];
  unsigned* new_y = new unsigned[max];

  unsigned new_num = min(num, max);
  for (unsigned i = 0; i < new_num; i++) {
    copy[i] = pic_[i];
    new_x[i] = xCord[i];
    new_y[i] = yCord[i];
  }

  for (unsigned i = new_num; i < num; i++) {
    delete pic_[i];
  }

  delete[] pic_;
  delete[] xCord;
  delete[] yCord;

  pic_ = copy;
  xCord = new_x;
  yCord = new_y;
  num = new_num;
  max_ = max;
}

int StickerSheet::addSticker(Image & sticker, int x, int y) {
	// if (x > (int)(base -> width()) || y > (int)(base -> height())) {
	// 	return -1;
	// }
	// for (unsigned i = 0; i < max_; i++) {
	// 	if (i == num) {
	// 		pic_[i] = new Image(sticker);
	// 		xCord[i] = abs(x);
	// 		yCord[i] = abs(y);
	// 		num++;
	// 		return int(i);
	// 	}
	// }
	// return -1;
	if (num < max_) {
        xCord[num] = x;
		yCord[num] = y;
		pic_[num] = new Image(sticker);
		int tmp = num;
		num++;
		return tmp;
    }

    return -1;
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y){
	if (x < 0 || y > 0) {
		return -1;
	}
	if (x > (int)(base -> width()) || y > (int)(base -> height())) {
		return -1;
	}
	if (layer < max_) {
		pic_[layer] = new Image(sticker);
		xCord[layer] = x;
		yCord[layer] = y;
		return layer;
	} 
    // for (unsigned i = 0; i < max_; i++) {
	// 	if (i == layer) {
	// 		pic_[i] = new Image(sticker);
	// 		xCord[i] = abs(x);
	// 		yCord[i] = abs(y);
	// 		num++;
	// 		return int(i);
	// 	}
	// }
	return -1;
}

bool StickerSheet::translate(unsigned index, int x, int y) {
	if (index < num) {
		xCord[index] = abs(x);
		yCord[index] = abs(y);
		return true;
	}
	return false;
}

void StickerSheet::removeSticker(unsigned index) {
	delete pic_[index];
	for (unsigned i = index; i < max_ - 1; i++) {
		pic_[i] = pic_[i + 1];
		xCord[i] = xCord[i + 1];
		yCord[i] = yCord[i + 1];
	}
	pic_[max_ - 1] = NULL;
	xCord[max_ - 1] = 0; 
	yCord[max_ - 1] = 0; 
	num--;
}

Image * StickerSheet::getSticker(unsigned index) const {
	if (index >= num) {
		return nullptr;
	}
	return pic_[index];
}

Image StickerSheet::render() const {
	Image stickersheet(*base);
    unsigned xMax = stickersheet.width();
    unsigned yMax = stickersheet.height();

    for (unsigned i = 0; i < num; i++) {
        if (pic_[i] != nullptr) {
            unsigned x = xCord[i] + pic_[i]->width();
            unsigned y = yCord[i] + pic_[i]->height();

            if (x > xMax) {
                xMax = x;
            }

            if (y > yMax) {
                yMax = y;
            }
        }
    }

    stickersheet.resize(xMax, yMax);

    for (unsigned i = 0; i < num; i++) {
        if (pic_[i] != nullptr) {
            for (unsigned x = xCord[i]; x < (xCord[i] + pic_[i]->width()); x++) {
                for (unsigned y = yCord[i]; y < (yCord[i] + pic_[i]->height()); y++) {
                    HSLAPixel& base = stickersheet.getPixel(x, y);
                    HSLAPixel& final = pic_[i]->getPixel(x - xCord[i], y - yCord[i]);

                    if (final.a != 0) {
                        base.h = final.h;
                        base.s = final.s;
                        base.l = final.l;
                        base.a = final.a;
                    }
                }
            }
        }
    }

    return stickersheet;
}