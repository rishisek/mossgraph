/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include <vector>

class StickerSheet{
    public:
        void _copy(const StickerSheet &other);
        StickerSheet (const Image &picture, unsigned max);
        StickerSheet (const StickerSheet &other);
        const StickerSheet & 	operator= (const StickerSheet &other);
        // ~StickerSheet();
        void 	changeMaxStickers (unsigned max);
        int 	addSticker (Image &sticker, int x, int y);
        int 	setStickerAtLayer (Image &sticker, unsigned layer, int x, int y);
        bool 	translate (unsigned index, int x, int y);
        void 	removeSticker (unsigned index);
        Image * 	getSticker (unsigned index);
        int 	layers () const;
        Image 	render () const;

    private:
        // unsigned int max_;
        std::vector<Image*> stickers_;
        Image empty_sheet;
        // unsigned int layer_count_;
        std::vector<int> pos_x;
        std::vector<int> pos_y;

};