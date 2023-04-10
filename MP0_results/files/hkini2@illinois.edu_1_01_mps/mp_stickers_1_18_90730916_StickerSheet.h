/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"

class StickerSheet 
{
	public:
		StickerSheet(const Image &picture, unsigned max);
		StickerSheet(const StickerSheet &other);
		~StickerSheet() = default;
		const StickerSheet& operator=(const StickerSheet &other);
		void changeMaxStickers(unsigned max);
		int addSticker(Image &sticker, int x, int y);
        int setStickerAtLayer (Image &sticker, unsigned layer, int x, int y);
		bool translate(unsigned index, int x, int y);
		void removeSticker(unsigned index);
		Image* getSticker(unsigned index);
        int layers() const;
		Image render() const;
	private:
		Image baseImage;
		Image **stickers;
		unsigned *x_;
		unsigned *y_;
		unsigned int max_;
		unsigned int num_;
        void copy_(const StickerSheet & other);
        void clear_();

};