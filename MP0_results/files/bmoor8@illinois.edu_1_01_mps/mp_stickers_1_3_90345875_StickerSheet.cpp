#include "StickerSheet.h"
#include "Image.h"
#include "cs225/RGB_HSL.h"

#include <cmath>

using namespace cs225;

StickerSheet::StickerSheet(const Image & picture, unsigned max) {
    capacity_ = max;                    // set the maximum size
    baseImage_ = new Image(picture);    // make a copy of the base image
    renderImage_ = new Image();
    stickers_ = new Sticker[max]();     // create an array for the stickers
}

StickerSheet::StickerSheet(const StickerSheet & other) {
    _copy(other);
}

StickerSheet const & StickerSheet::operator=(const StickerSheet & other) {
    if (this != &other) {
        _destroy();
        _copy(other);
    }
    return *this;
}

StickerSheet::~StickerSheet() {
    _destroy();
}

void StickerSheet::_copy(const StickerSheet & other) {
    capacity_ = other.capacity_;
    baseImage_ = new Image(*(other.baseImage_));
    renderImage_ = new Image(*(other.renderImage_));
    stickers_ = new Sticker[capacity_]();
    for (unsigned i = 0; i < capacity_; i ++) {
        if (other.stickers_[i].image != NULL) {
            stickers_[i].image = new Image(*(other.stickers_[i].image));
            stickers_[i].x = other.stickers_[i].x;
            stickers_[i].y = other.stickers_[i].y;
        }
    }
}

void StickerSheet::_destroy() {
    if (baseImage_ != NULL) {
        delete baseImage_;
        baseImage_ = NULL;
    }
    if (renderImage_ != NULL) {
        delete renderImage_;
        renderImage_ = NULL;
    }
    if (stickers_ != NULL) {
        // free all the stickers in the sheet
        for (unsigned i = 0; i < capacity_; i ++) {
            if (stickers_[i].image != NULL) {
                delete stickers_[i].image;
                stickers_[i].image = NULL;
            }
        }
        // free the actual sticker array
        delete[] stickers_;
        stickers_ = NULL;
    }
}

void StickerSheet::changeMaxStickers(unsigned max) {
    // create a new array to store the stickers
    Sticker * newStickers = new Sticker[max]();

    // copy each sticker to the new array
    for (unsigned i = 0; i < capacity_; i ++) {
        // for elements that will exist in the new array, copy the image pointers
        if (i < max) {
            newStickers[i].image = stickers_[i].image;
            newStickers[i].x = stickers_[i].x;
            newStickers[i].y = stickers_[i].y;
        }
        else {
            // these stickers are outside the range of the new max
            // size, so they will not be copied.  They were created
            // with new, so we must delete them
            if (stickers_[i].image != NULL) {
                delete stickers_[i].image;
                stickers_[i].image = NULL;
            }
        }
    }

    // free the old array memory and reassign the pointer
    delete[] stickers_;
    stickers_ = newStickers;
    capacity_ = max;
}
int StickerSheet::setStickerAtLayer(Image & sticker, unsigned index, unsigned x, unsigned y){
    if (index >= capacity_){
        return -1;
    }
    else {
            stickers_[index].image = new Image(sticker);
            stickers_[index].x = x;
            stickers_[index].y = y;
        
        return index;
    }
}
int StickerSheet::layers(){
return capacity_;
}

int StickerSheet::addSticker(Image & sticker, signed x, signed y) {
  if (x<0){
    int offset_ = 0-x;
    for (unsigned i = 0; i < capacity_; i++){
      stickers_[i].x= stickers_[i].x + offset_;
    }
    x = 0;
  }
  if (y<0){
    int offset2 = 0-y;
    for (unsigned i = 0; i < capacity_; i++){
      stickers_[i].y= stickers_[i].y + offset2;
    }
    y = 0;
  }
    for (unsigned i = 0; i < capacity_; i ++) {
      
        if (stickers_[i].image == NULL) {
            stickers_[i].image = new Image(sticker);
            stickers_[i].x = x;
            stickers_[i].y = y;
            return i;
        }
        
    }
  changeMaxStickers(capacity_+1);  
  for (unsigned i = 0; i < capacity_; i ++) {
      
        if (stickers_[i].image == NULL) {
            stickers_[i].image = new Image(sticker);
            stickers_[i].x = x;
            stickers_[i].y = y;
            return i;
        }
        
    }
    return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    // make sure index is valid
    if (index < capacity_) {
        // and that the layer contains a sticker
        if (stickers_[index].image != NULL) {
            stickers_[index].x = x;
            stickers_[index].y = y;
            return true;
        }
    }
    return false;
}

void StickerSheet::removeSticker(unsigned index) {
    if (index < capacity_) {
        // if the sticker exists, delete it
        if (stickers_[index].image != NULL) {
            delete stickers_[index].image;
            stickers_[index].image = NULL;
            stickers_[index].x = 0;
            stickers_[index].y = 0;
        }
    }
}

Image * StickerSheet::getSticker(unsigned index) const {
    if (index < capacity_) {
        return stickers_[index].image;
    }
    return NULL;
}

Image StickerSheet::render() const {
    unsigned max_width = baseImage_->width();
    unsigned max_height = baseImage_->height();

    // loop through the stickers to find the size of the bounding box
    for (unsigned i = 0; i < capacity_; i ++) {
        Sticker s = stickers_[i];

        if (s.image != NULL) {
            max_width = fmax(max_width, s.x + s.image->width());
            max_height = fmax(max_height, s.y + s.image->height());
        }
    }

    // copy the base and resize it to the computed bounding box
    *renderImage_ = *baseImage_;
    renderImage_->resize(max_width, max_height);

    // set all the pixels to the right of the base image to transparent
    for (unsigned x = baseImage_->width(); x < max_width; x ++) {
        for (unsigned y = 0; y < max_height; y ++) {
            HSLAPixel & pixel = renderImage_->getPixel(x, y);
            pixel.a = 0;
        }
    }
    // set all the pixels directly underneath the base image transparent
    for (unsigned x = 0; x < baseImage_->width(); x ++) {
        for (unsigned y = baseImage_->height(); y < max_height; y ++) {
            HSLAPixel & pixel = renderImage_->getPixel(x, y);
            pixel.a = 0;
        }
    }

    // loop through the stickers
    for (unsigned i = 0; i < capacity_; i ++) {
        if (stickers_[i].image != NULL) {
            Sticker s = stickers_[i];

            // iterate over the sticker, modifying the base pixels
            for (unsigned x = 0; x < s.image->width(); x ++) {
                for (unsigned y = 0; y < s.image->height(); y ++) {
                    // std::cout << "Return Image (" << x + s.x << ", " << y + s.y << "),    Sticker (" << x << ", " << y << ")" << std::endl;
                    HSLAPixel & basePixel = renderImage_->getPixel(x + s.x, y + s.y);
                    HSLAPixel & stickerPixel = s.image->getPixel(x,y);
                    // if (stickerPixel.a != 0) {
                    //     basePixel = stickerPixel;
                    // }
                    basePixel = blend(basePixel, stickerPixel);
                }
            }
        }
    }

    return *renderImage_;
}

HSLAPixel & StickerSheet::blend(const HSLAPixel & dst, const HSLAPixel & src) const{
    hslaColor src_hsl, dst_hsl, out_hsl;
    rgbaColor src_rgb, dst_rgb, out_rgb;

    // grab the HSL components from the two input pixels
    src_hsl.h = src.h;
    src_hsl.s = src.s;
    src_hsl.l = src.l;

    dst_hsl.h = dst.h;
    dst_hsl.s = dst.s;
    dst_hsl.l = dst.l;

    // convert the input HSL colors to RGB
    src_rgb = hsl2rgb(src_hsl);
    dst_rgb = hsl2rgb(dst_hsl);

    // compute the alpha channel based on the input alphas
    // this is not included in the HSL->RGB conversion because
    // the formula requires alpha to be [0,1]
    double out_a = src.a + dst.a * (1 - src.a);

    // compute the output RGB components
    out_rgb.r = (int)((src_rgb.r * src.a + (dst_rgb.r * dst.a * (1 - src.a))) / out_a);
    out_rgb.g = (int)((src_rgb.g * src.a + (dst_rgb.g * dst.a * (1 - src.a))) / out_a);
    out_rgb.b = (int)((src_rgb.b * src.a + (dst_rgb.b * dst.a * (1 - src.a))) / out_a);

    // convert the output RGB back to HSL
    out_hsl = rgb2hsl(out_rgb);

    HSLAPixel * blendedPixel = new HSLAPixel(out_hsl.h, out_hsl.s, out_hsl.l, out_a);
    return *blendedPixel;
}