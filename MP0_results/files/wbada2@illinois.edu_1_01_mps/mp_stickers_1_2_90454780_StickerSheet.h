/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "cs225/PNG.h"
#include <iostream>
#include <algorithm>
#include "Image.h"
#include <cmath>
#include <vector>





using namespace std;
using namespace cs225;

class StickerSheet{

    public:

        StickerSheet(const Image &picture, unsigned max);

        StickerSheet(const StickerSheet & other);

        int addSticker(Image& sticker, int x, int y);

        void changeMaxStickers(unsigned max);

        Image* getSticker(unsigned index);

        int layers()const;

        const StickerSheet & operator= (const StickerSheet& other);

        void removeSticker(unsigned index);

        Image render()const;

        int setStickerAtLayer(Image & sticker, unsigned layer, int x, int y);

        bool translate (unsigned index, int x, int y);


    private:
        vector<int> x_comp_;
        vector<int> y_comp_;
        vector<Image*> stickerVector_;
       

        
        Image base_;
        int max_;
        //int layers_; // stores the numberof times the image is filled with stickers

        //int index;

        //vectors image ,x, y




};
