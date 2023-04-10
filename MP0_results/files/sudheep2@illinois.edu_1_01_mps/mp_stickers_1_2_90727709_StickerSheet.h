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
        int layers() const;
		Image render () const;
	private:
		unsigned max_;
		//int layer_;
		Image * base;
		Image ** Sheet;
		unsigned * X;
		unsigned * Y;
		unsigned sticker_count_;
		void copy_(const StickerSheet & other);
		void clear_();
		// std::vector<Image*> Sheet;
		// Image base;
		// std::vector<unsigned int> X;
		// std::vector<unsigned int> Y;
		
};