/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"
#include <vector>

using namespace std;

class StickerSheet {
    public:
        StickerSheet(const Image &picture, unsigned max);
		StickerSheet(const StickerSheet &other);
		const StickerSheet& operator=(const StickerSheet &other);
		void changeMaxStickers(unsigned max);
		int addSticker(Image &sticker, unsigned x, unsigned y);
		bool translate(unsigned index, unsigned x, unsigned y);
		void removeSticker(unsigned index);
		Image * getSticker(unsigned index);
		Image render() const;
        int layers() const; 
        int setStickerAtLayer(Image& sticker, unsigned layer, int x, int y);

    private:
		unsigned int max_; 
		Image base_image_; 
		vector<int> Xcoord; 
		vector<int> Ycoord; 
		vector<Image*> sticker_; 
       

};