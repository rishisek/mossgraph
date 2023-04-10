/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#include "Image.h"
#include <iostream>
#include <vector>
#pragma once
class StickerSheet
{
    public:
 	StickerSheet (const Image &picture, unsigned max);
	StickerSheet (const StickerSheet &other);
	const StickerSheet & 	operator= (const StickerSheet &other);
	void 	changeMaxStickers (unsigned max);
	int 	addSticker (Image &sticker, int x, int y); 
	int 	setStickerAtLayer (Image &sticker, unsigned layer, int x, int y);
	bool 	translate (unsigned index, int x, int y); 
	void 	removeSticker (unsigned index);
	Image * 	getSticker (unsigned index);
	int 	layers () const;
	Image 	render () const;
	~StickerSheet();
	void destroy();
	void copy(const StickerSheet &other);

	private:
	std::vector<Image*> cover_;
	int max_;
	std::vector<int> x_;
	std::vector<int> y_;
	Image base_;
	int cur_ = 0;
};