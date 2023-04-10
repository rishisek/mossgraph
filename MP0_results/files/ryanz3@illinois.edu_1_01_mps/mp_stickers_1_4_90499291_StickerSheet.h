/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include <vector>


struct ImageSticker {
    int index;
    int x_coord;
    int y_coord;
};

class StickerSheet {
    public: 
        StickerSheet(const Image &picture, unsigned max);
        // StickerSheet(const StickerSheet &other) = default;
        // const StickerSheet & operator= (const StickerSheet &other) = default;
        void changeMaxStickers (unsigned max);
        int addSticker (Image &sticker, int x, int y);
        int setStickerAtLayer (Image &sticker, unsigned layer, int x, int y);
        bool translate (unsigned index, int x, int y);
        void removeSticker(unsigned index);
        Image* getSticker(unsigned index);
        int layers() const;
        Image render() const;
    
    private:
        
        std::vector<Image*> sticker_vect;
        std::vector<ImageSticker> sticker_info_vect;
        Image base;
        int max_;
};

