/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "cs225/PNG.h"
#include "Image.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace cs225;

class StickerSheet{

    public:

        StickerSheet (const Image &picture, unsigned max);

        StickerSheet(const StickerSheet & other);

        int addSticker(Image & sticker, int x, int y);

        void changeMaxStickers(unsigned max);

        Image *getSticker(unsigned index);

        int layers() const;

        const StickerSheet & operator=(const StickerSheet & other);


        void removeSticker(unsigned index);

        Image render() const;

        int setStickerAtLayer(Image & sticker, unsigned layer, int x, int y);

        bool translate(unsigned index, int x, int y);

    private:
        vector<int> x_component_;
        vector<int> y_component_;
        vector<Image*> stickerVector_; // stores the stickers
        Image base_;

        int max_; // max number of stickers 

};



