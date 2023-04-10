/**

 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "cs225/PNG.h"
#include "Image.h"
#include <vector>


class StickerSheet {

    public:
        StickerSheet(const Image &picture, unsigned max);
        StickerSheet(const StickerSheet &other);
        int addSticker(Image &sticker, int x, int y);
        void changeMaxStickers(unsigned max);
        Image * getSticker(unsigned index);
        int layers();
        const StickerSheet & operator=(const StickerSheet &other);
        //  ~StickerSheet();
        void removeSticker(unsigned index);
        Image render();
        int setStickerAtLayer(Image &sticker, unsigned layer, int x, int y);
        bool translate(unsigned index, unsigned x, unsigned y);


        private:
            unsigned int max_;
            Image base;
            std::vector<int> xcoordinate;
            std::vector<int> ycoordinate;
            std::vector<Image*> num_stickers;
    


};

