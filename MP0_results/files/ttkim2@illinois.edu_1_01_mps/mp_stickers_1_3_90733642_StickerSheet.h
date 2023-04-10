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
		int addSticker(Image & sticker, int x, int y);
        int setStickerAtLayer(Image &sticker, unsigned layer, int x, int y);
		bool translate(unsigned index, int x, int y);
		void removeSticker(unsigned index);
		Image * getSticker(unsigned index) const;
        int layers() const {
			return (max_);
		}
		Image render () const;
	private:
		unsigned max_;
		Image * base;
		Image ** pic_;
		unsigned * xCord;
		unsigned * yCord;
		unsigned num;
		void copy_(const StickerSheet & other);
		void clear_();
};