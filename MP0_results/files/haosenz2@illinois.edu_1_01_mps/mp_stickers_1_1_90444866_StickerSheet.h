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
	~StickerSheet(); 
	const StickerSheet & 	operator= (const StickerSheet &other);
	void 	changeMaxStickers (unsigned max);
	int 	addSticker (Image &sticker, int x, int y); 
	int 	setStickerAtLayer (Image &sticker, unsigned layer, int x, int y);
	bool 	translate (unsigned index, int x, int y); 
	void 	removeSticker (unsigned index);
	Image * 	getSticker (unsigned index);
	int 	layers () const;
	Image 	render () const;
	// ~StickerSheet();
	// void destroy();

	private:
	std::vector<Image*> allsticker;
	int max_;
	std::vector<int> xcor_;
	std::vector<int> ycor_;
	Image base_;
	int num_ = 0;

};