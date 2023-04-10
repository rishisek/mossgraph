/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"
#include "cs225/PNG.h"
#include <vector>

using namespace cs225;
using namespace std;

struct Sticker {
    Sticker(Image* new_img, int new_x, int new_y): img(new_img), x(new_x), y(new_y) {}
    Image* img;
    int x;
    int y;
};

class StickerSheet
{
	public:
        StickerSheet(const Image &picture, unsigned max);
        
        void changeMaxStickers(unsigned max);
        int addSticker(Image &sticker, int x, int y);
        int setStickerAtLayer (Image &sticker, unsigned layer, int x, int y);
        bool translate(unsigned index, int x, int y);
        void removeSticker(unsigned index);
        Image* getSticker(unsigned index);
        int layers() const;
        Image render() const;
        

	
        Image picture_;
        unsigned max_;
        vector<Sticker> stickers;

};

