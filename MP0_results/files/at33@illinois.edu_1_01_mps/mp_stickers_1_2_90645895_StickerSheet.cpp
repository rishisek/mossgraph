// // #include "StickerSheet.h"
// // #include "Image.h"

// // using namespace cs225;

// // StickerSheet::StickerSheet(const Image & picture, unsigned max) {
// //     base_ = new Image(picture);
// //     max_ = max;
// //     sheet_ = new Image*[max_];
// //     count_ = 0;
// //     x_ = new unsigned[max_];
// //     y_ = new unsigned[max_];
// //     for (unsigned i = 0; i < max_; i++) {
// //         sheet_[i] = NULL;
// //     }
// // }

// // StickerSheet::StickerSheet(const StickerSheet &other) {
// //     _copy(other);
// // }

// // StickerSheet::~StickerSheet() {
// //     _delete();
// // }

// // void StickerSheet::_delete() {
// // 	for (unsigned i = 0; i < count_; i++) {
// // 		delete sheet_[i];
// // 		sheet_[i] = NULL;
// // 	}
// // 	delete base_;
// // 	delete[] sheet_;
// // 	delete[] x_;
// // 	delete[] y_;
// // }

// // void StickerSheet::_copy(const StickerSheet & other) {
// //     base_ = new Image(*(other.base_));
// //     max_ = other.max_;
// //     count_ = other.count_;
// //     x_ = new unsigned[max_];
// //     y_ = new unsigned[max_];
// //     sheet_ = new Image*[max_];
// //     // for (unsigned i = 0; i < max_; i++){
// //     //     sheet_[i] = NULL;
// //     // }
// //     for (unsigned i = 0; i < count_; i++){
// //         sheet_[i] = new Image();
// //         *(sheet_[i]) = *(other.sheet_[i]);
// //         x_[i] = other.x_[i];
// //         y_[i] = other.y_[i];
// //   }
// // }

// // const StickerSheet & StickerSheet::operator=(const StickerSheet &other) {
// //     _delete();
// //     _copy(other);
// //     return *this;
// // }

// // void StickerSheet::changeMaxStickers(unsigned max) {
// //     if (max != count_) {
// //         Image** new_sheet_ = new Image*[max];
// //         for(unsigned i = 0; i < max; i++) {
// //             new_sheet_[i] = NULL;
// //         }
// //         unsigned* new_x_ = new unsigned[max];
// //         unsigned* new_y_ = new unsigned[max];

// //         if (count_ > max) {
// //             for (unsigned i = 0; i < max; i++) {
// //                 new_sheet_[i] = new Image();
// //                 *new_sheet_[i] = *sheet_[i];
// //                 new_x_[i] = x_[i];
// //                 new_y_[i] = y_[i];
// //             }
// //         } else if (count_ < max) {
// //             for (unsigned i = 0; i < count_; i++) {
// //                 new_sheet_[i] = new Image();
// //                 *new_sheet_[i] = *sheet_[i];
// //                 new_x_[i] = x_[i];
// //                 new_y_[i] = y_[i];
// //             }
// //         }

// //         _delete();

// //         sheet_ = new_sheet_;
// //         new_sheet_ = NULL;
// //         x_ = new_x_;
// //         new_x_ = NULL;
// //         y_ = new_y_;
// //         new_y_ = NULL;
// //         max_ = max;
// //     }
// // }

// // int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
// //     for (unsigned i = 0; i < max_; i++) {
// //         if (i == count_) {
// //             sheet_[i] = new Image(sticker);
// //             x_[i] = x;
// //             y_[i] = y;
// //             count_++;
// //             return int(i);
// //         }
// //     }
// //     return -1;

// // //       if(count_ < max_){
// // //     if(sheet_[count_] == NULL){
// // //       sheet_[count_] = new Image();
// // //     }
// // //     *sheet_[count_] = sticker;
// // //     x_[count_] = x;
// // //     y_[count_] = y;
// // //     count_++;
// // //     return (count_ - 1);
// // //   }
// // //   return -1;
// // }

// // bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
// //     if (index < count_) {
// //         x_[index] = x;
// //         y_[index] = y;
// //         return true;
// //     }
// //     return false;
// // }

// // void StickerSheet::removeSticker(unsigned index) {
// // 	delete sheet_[index];
// // 	for (unsigned i = index; i < max_ - 1; i++) {
// // 		sheet_[i] = sheet_[i + 1];
// // 		x_[i] = x_[i + 1];
// // 		y_[i] = y_[i + 1];
// // 	}
// // 	sheet_[max_ - 1] = NULL;
// // 	x_[max_ - 1] = 0; 
// // 	y_[max_ - 1] = 0; 
// // 	count_--;   
// //     // if (index >= max_ || sheet_[index] == NULL) {
// //     //     return;
// //     // }
// //     // sheet_[index] = NULL;
// //     // delete sheet_[index];

// //     // if (index >= count_) {
// //     //     return;
// //     // } else {
// //     //     for (unsigned i = index; i < (count_ - 1); i++) {
// //     //         *sheet_[i] =  *sheet_[i + 1];   
// //     //         x_[i] = x_[i + 1];
// //     //         y_[i] = y_[i + 1];
// //     //     }
// //     //     delete sheet_[count_ - 1]; 
// //     //     sheet_[count_] = NULL;
// //     //     count_--;
// //     // }
// // }


// // Image* StickerSheet::getSticker(unsigned index) const {
// //     if (index >= count_) {
// //         return NULL;
// //     }
// //     return sheet_[index];
    
// //     // if (index >= count_) {
// //     //     return NULL;
// //     // }
// //     // return sheet_[index];
// // }

// // Image StickerSheet::render() const {
// //     // //Image output;

// //     // unsigned max_w = base_.width();
// //     // unsigned max_h = base_.height();

// //     // for (unsigned i = 0; i < count_; i++) {
// //     //     // unsigned max_w = sheet_[i]->width();
// //     //     // unsigned max_h = sheet_[i]->height();
// //     //     if (sheet_[i] != NULL) {
// //     //         unsigned max_w = sheet_[i]->width();
// //     //         unsigned max_h = sheet_[i]->height();
// //     //         if (x_[i] + sheet_[i]->width() > base_.width()) {
// //     //             max_w = x_[i] + sheet_[i]->width();
// //     //         } else {
// //     //             max_w = base_.width();
// //     //         }
// //     //         if (y_[i] + sheet_[i]->height() > base_.height()) {
// //     //             max_h = y_[i] + sheet_[i]->height();
// //     //         } else {
// //     //             max_h = base_.height();
// //     //         }
// //     //     }
// //     // }

// //     // Image output(base_);
// //     // output.resize(max_w, max_h);

// //     // for (unsigned i = 0; i < count_; i++) {
// //     //     if (sheet_[i] != NULL) {
// //     //         for (unsigned w = x_[i]; w < (x_[i] + sheet_[i]->width()); w++) {
// //     //             for (unsigned h = y_[i]; h < (y_[i] + sheet_[i]->height()); h++) {
// //     //                 if(sheet_[i]->getPixel((w - x_[i]), (h - y_[i])).a != 0) {
// //     //                     output.getPixel(w, h) = sheet_[i]->getPixel((w - x_[i]), (h - y_[i]));
// //     //                 }
// //     //             }
// //     //         }
// //     //     }
// //     // }

// //     // return output;

// //     	Image result(*base_);
// // 	for (unsigned i = 0; i < count_; i++) {
// // 		unsigned curw = sheet_[i]->width();
// // 		unsigned curh = sheet_[i]->height();
// // 		// Resize image accordingly
// // 		if ((curw + x_[i]) > result.width()) {
// // 			result.resize(curw + x_[i], result.height());
// // 		}
// // 		if ((curh + y_[i]) > result.height()) {
// // 			result.resize(result.width(), curh + y_[i]);
// // 		}
// // 		// Overwrite necessary pixels
// // 		for (unsigned x = 0; x < curw; x++) {
// // 			for (unsigned y = 0; y < curh; y++) {
// // 				HSLAPixel & cur_result_pixel = result.getPixel(x + x_[i], y + y_[i]);
// // 				HSLAPixel & cur_image_pixel = sheet_[i]->getPixel(x, y);
// // 				if (cur_image_pixel.a != 0) {
// // 					cur_result_pixel = cur_image_pixel;
// // 				}
// // 			}
// // 		}
// // 	}
// // 	return result;
// // }

// // int StickerSheet::layers() const {
// //     return (int)(max_);
// // }

// // int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
// //     return 0;
// // }



// #include "StickerSheet.h"
// #include "cs225/HSLAPixel.h"
// #include <iostream>

// using namespace cs225;

// void StickerSheet::copy_(const StickerSheet & other) {
// 	max_ = other.max_;
// 	base = new Image(*(other.base));
// 	num_stickers_ = other.num_stickers_;
// 	Images = new Image * [max_];
// 	XCoords = new unsigned[max_];
// 	YCoords = new unsigned[max_];
// 	for (unsigned i = 0; i < num_stickers_; i++) {
// 		Images[i] = new Image();
// 		*(Images[i]) = *(other.Images[i]);
// 		XCoords[i] = other.XCoords[i];
// 		YCoords[i] = other.YCoords[i];
// 	}
// }

// void StickerSheet::clear_() {
// 	for (unsigned i = 0; i < num_stickers_; i++) {
// 		delete Images[i];
// 		Images[i] = NULL;
// 	}
// 	delete base;
// 	delete[] Images;
// 	delete[] XCoords;
// 	delete[] YCoords;
// }

// StickerSheet::StickerSheet(const Image & picture, unsigned max) {
// 	max_ = max;
// 	num_stickers_ = 0;
// 	Images = new Image * [max_];
// 	XCoords = new unsigned[max_];
// 	YCoords = new unsigned[max_];
// 	base = new Image(picture);
// 	XCoords[0] = 0; YCoords[0] = 0;
// }

// StickerSheet::~StickerSheet() {
// 	clear_();
// }

// StickerSheet::StickerSheet(const StickerSheet & other) {
// 	copy_(other);
// }

// const StickerSheet & StickerSheet::operator=(const StickerSheet & other) {
// 	if (this != &other) {
// 		clear_();
// 		copy_(other);
// 	}
// 	return *this;
// }

// void StickerSheet::changeMaxStickers(unsigned max) {
// 	//Image ** temp_images = new Image * [max_];
// 	Image ** temp_images = new Image * [num_stickers_];
// 	unsigned * temp_xc = new unsigned [num_stickers_];
// 	unsigned * temp_yc = new unsigned [num_stickers_];
// 	for (unsigned i = 0; i < num_stickers_; i++) {
// 		temp_images[i] = Images[i];
// 		temp_xc[i] = XCoords[i];
// 		temp_yc[i] = YCoords[i];
// 	}
// 	delete[] Images;
// 	delete[] XCoords;
// 	delete[] YCoords;
// 	Images = new Image * [max];
// 	XCoords = new unsigned[max];
// 	YCoords = new unsigned[max];

// 	if (max < num_stickers_) {
// 		for (unsigned i = max; i < num_stickers_; i++) {
// 			delete temp_images[i];
// 			temp_images[i] = NULL;
// 		}
// 		num_stickers_ = max;
// 		for (unsigned i = 0; i < num_stickers_; i++) {
// 			Images[i] = temp_images[i];
// 			XCoords[i] = temp_xc[i];
// 			YCoords[i] = temp_yc[i];
// 		}
// 	}
// 	else {
// 		for (unsigned i = 0; i < num_stickers_; i++) {
// 			Images[i] = temp_images[i];
// 			XCoords[i] = temp_xc[i];
// 			YCoords[i] = temp_yc[i];
// 		}
// 	}
// 	max_ = max;
// 	delete[] temp_images;
// 	delete[] temp_xc;
// 	delete[] temp_yc;
// }

// int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
// 	for (unsigned i = 0; i < max_; i++) {
// 		if (i == num_stickers_) {
// 			Images[i] = new Image(sticker);
// 			XCoords[i] = x;
// 			YCoords[i] = y;
// 			num_stickers_++;
// 			return int(i);
// 		}
// 	}
// 	return -1;
// }

// bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
// 	if (index < num_stickers_) {
// 		XCoords[index] = x;
// 		YCoords[index] = y;
// 		return true;
// 	}
// 	return false;
// }

// void StickerSheet::removeSticker(unsigned index) {
// 	delete Images[index];
// 	for (unsigned i = index; i < max_ - 1; i++) {
// 		Images[i] = Images[i + 1];
// 		XCoords[i] = XCoords[i + 1];
// 		YCoords[i] = YCoords[i + 1];
// 	}
// 	Images[max_ - 1] = NULL;
// 	XCoords[max_ - 1] = 0; 
// 	YCoords[max_ - 1] = 0; 
// 	num_stickers_--;
// }

// Image * StickerSheet::getSticker(unsigned index) const {
// 	if (index >= num_stickers_) {return NULL;}
// 	return Images[index];
// }

// Image StickerSheet::render() const {
// 	Image result(*base);
// 	for (unsigned i = 0; i < num_stickers_; i++) {
// 		unsigned curw = Images[i]->width();
// 		unsigned curh = Images[i]->height();
// 		// Resize image accordingly
// 		if ((curw + XCoords[i]) > result.width()) {
// 			result.resize(curw + XCoords[i], result.height());
// 		}
// 		if ((curh + YCoords[i]) > result.height()) {
// 			result.resize(result.width(), curh + YCoords[i]);
// 		}
// 		// Overwrite necessary pixels
// 		for (unsigned x = 0; x < curw; x++) {
// 			for (unsigned y = 0; y < curh; y++) {
// 				HSLAPixel & cur_result_pixel = result.getPixel(x + XCoords[i], y + YCoords[i]);
// 				HSLAPixel & cur_image_pixel = Images[i]->getPixel(x, y);
// 				if (cur_image_pixel.a != 0) {
// 					cur_result_pixel = cur_image_pixel;
// 				}
// 			}
// // 		}
// // 	}
// // 	return result;
// // }

// int StickerSheet::layers() const {
//     return (int)(max_);
// }

// int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
//     return 0;
// }

#include "StickerSheet.h"

using namespace cs225;

StickerSheet::StickerSheet(const Image & picture, unsigned max) {
	capacity = max;
	sheet = new Image*[max];
	x_array = new unsigned[max];
	y_array = new unsigned[max];
	base = new Image(picture);
	count = 0;
	x_array[0] = 0; y_array[0] = 0;
}

StickerSheet::StickerSheet(const StickerSheet & other) {
	copy_(other);
}

StickerSheet::~StickerSheet() {
	delete_();
}

void StickerSheet::copy_(const StickerSheet & other) {
	base = new Image(*(other.base));
	capacity = other.capacity;
	count = other.count;
	sheet = new Image*[capacity];
	x_array = new unsigned[capacity];
	y_array = new unsigned[capacity];
	for (unsigned i = 0; i < count; i++) {
		sheet[i] = new Image();
		*(sheet[i]) = *(other.sheet[i]);
		x_array[i] = other.x_array[i];
		y_array[i] = other.y_array[i];
	}
}

void StickerSheet::delete_() {
	for (unsigned i = 0; i < count; i++){
    	delete sheet[i];
    	sheet[i] = NULL;
  	}
  	delete[] sheet;
  	sheet = NULL;
  	delete[] x_array;
  	x_array = NULL;
  	delete[] y_array;
  	y_array = NULL;
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other) {
	if (this != &other) {
		delete_();
		copy_(other);
	}
	return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
	if (max != capacity) {
		Image** temp = new Image*[max];
    	unsigned *x_ = new unsigned[max];
    	unsigned *y_ = new unsigned[max];
    	for (unsigned i = 0; i < max; i++) {
      		temp[i] = sheet[i];
      		x_[i] = x_array[i];
      		y_[i] = y_array[i];
    	}	
    	if (max > capacity) {
      		for (unsigned i = capacity; i < max; i++) temp[i] = nullptr;
    	}
    	delete_();
    	sheet = temp;
    	x_array = x_;
    	y_array = y_;
    	capacity = max;
	}
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
	for (unsigned i = 0; i < count; i++) {
		if (i == count) {
			sheet[i] = new Image(sticker);
			x_array[i] = x;
			y_array[i] = y;
			count++;
			return int(i);
		}
	}
	return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
	if (index >= count) {
		return false;
	}
	x_array[index] = x;
	y_array[index] = y;
	return true;
}

void StickerSheet::removeSticker(unsigned index) {
	delete sheet[index];
	for (unsigned i = index; i < count - 1; i++) {
		sheet[i] = sheet[i + 1];
		x_array[i] = x_array[i + 1];
		y_array[i] = y_array[i + 1];
	}
	sheet[capacity - 1] = NULL;
	x_array[capacity - 1] = 0; 
	y_array[capacity - 1] = 0; 
	count--;
}

Image * StickerSheet::getSticker(unsigned index) const {
	if (sheet[index] == nullptr || index > count) return nullptr;
	return sheet[index];
}

Image StickerSheet::render() {
	Image output(*base);
	

	for (unsigned i = 0; i < count; i++) {
		unsigned wid = sheet[i]->width();
		unsigned hei = sheet[i]->height();
		int a = 0;

		if ((sheet[i]->height() + y_array[i]) <= output.height()) {
			a++;
		} else {
			output.resize(output.width(), hei + y_array[i]);
		}
		
		if ((sheet[i]->width() + x_array[i]) <= output.width()) {
			a++;
		} else {
			output.resize(wid + x_array[i], output.height());
		}
		
		for (unsigned x = 0; x < sheet[i]->width(); x++) {
			for (unsigned y = 0; y < sheet[i]->height(); y++) {
				HSLAPixel & output_pixel = output.getPixel(x + x_array[i], y + y_array[i]);
				HSLAPixel & image_pixel = sheet[i]->getPixel(x, y);
				if (sheet[i]->getPixel(x, y).a != 0) {
					output_pixel = image_pixel;
				}
			}
		}
	}

	return output;
}

int StickerSheet::layers() const {
    return (int)(capacity - count);
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
    return 0;
}