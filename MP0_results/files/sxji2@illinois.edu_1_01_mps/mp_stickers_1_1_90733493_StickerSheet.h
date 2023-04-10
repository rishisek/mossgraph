/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
/*
#pragma once
#include "Image.h" 

class StickerSheet {
    public:
    StickerSheet(const Image& picture, unsigned max);
    ~StickerSheet();
    void clear();
    StickerSheet(const StickerSheet& other);
    const StickerSheet& operator=(const StickerSheet& other);
    void changeMaxStickers(unsigned max);
    int addSticker(Image& sticker, int x_new, int y_new);
    bool translate(unsigned index, int x_new, int y_new);
    void removeSticker(unsigned index);
    Image* getSticker(unsigned index);
    //Image render() const;

    private:
    unsigned max_num;
    unsigned* x;
    unsigned* y;
    Image** sticker_sheet;
    Image base_sheet;
};*/

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
	private:
		unsigned max_;
		Image * base;
		Image ** Images;
		unsigned * XCoords;
		unsigned * YCoords;
		unsigned num_stickers_;
		void copy_(const StickerSheet & other);
		void clear_();
};