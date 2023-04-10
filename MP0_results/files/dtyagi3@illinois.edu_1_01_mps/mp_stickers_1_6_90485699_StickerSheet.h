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
        int setStickerAtLayer(Image & sticker, unsigned layer, int x, int y);
        int layers() const;
		Image * getSticker(unsigned index) const;
		Image render () const;
	private:
		unsigned max_;
		Image * base_var;
		Image ** Images;
		unsigned * XCoordinates;
		unsigned * YCoordinates;
		unsigned num_of_stickers_;
		void copy_(const StickerSheet & other);
		void clear_();
};