/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
 
#pragma once
#include "Image.h"
#include <vector>

class StickerSheet { 
    public: 
    StickerSheet(const Image & picture, unsigned max);
	~StickerSheet();
	StickerSheet(const StickerSheet & other);
	const StickerSheet & operator=(const StickerSheet & other);
	void changeMaxStickers(unsigned max);
	int addSticker(Image & sticker, unsigned x, unsigned y);
	bool translate(unsigned index, unsigned x, unsigned y);
	void removeSticker(unsigned index);
	Image * getSticker(unsigned index) const;
	Image render () const;
	int layers() const; 
	int setStickerAtLayer(Image &sticker, unsigned layer, int x, int y); 
    private: 
    unsigned max_;
	Image * base;
	Image ** Images;
	unsigned * xcoord;
	unsigned * ycoord;
	unsigned num_stickers_;
	void copy_(const StickerSheet & other);
	void clear_();
}; 


