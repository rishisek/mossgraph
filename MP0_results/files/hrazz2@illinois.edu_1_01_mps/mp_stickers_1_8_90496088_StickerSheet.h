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
		StickerSheet(const StickerSheet & other);
		const StickerSheet & operator=(const StickerSheet & other);
		void changeMaxStickers(unsigned max);
		int addSticker(Image & sticker, unsigned x, unsigned y);
        int setStickerAtLayer(Image &sticker, unsigned layer, int x, int y);
		bool translate(unsigned index, unsigned x, unsigned y);
		void removeSticker(unsigned index);
		Image* getSticker(unsigned index) const;
        int layers() const;
		Image render() const;

    private:
        unsigned int max_;
        Image base;
        std::vector<int> xcoord;
        std::vector<int> ycoord;
        std::vector<Image*> numstickers;
    //list of stickers
    //list of coord for stickers
    //base image
    //Image** Images; might need

};
