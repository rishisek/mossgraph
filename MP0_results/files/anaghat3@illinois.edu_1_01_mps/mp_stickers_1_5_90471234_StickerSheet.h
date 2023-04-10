/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include <iostream>
#include "Image.h"
#include <vector>
#include<utility>

class StickerSheet {
    public:
 	    //Initializes this StickerSheet with a deep copy of the base picture and the ability to hold a max number of stickers (Images) with indices 0 through max - 1. More...
        StickerSheet(const Image &picture, unsigned max);
 
 	
 
 	    //Modifies the maximum number of stickers that can be stored on this StickerSheet without changing existing stickers' indices. More...
        void changeMaxStickers(unsigned max);
 
 	    //Adds a sticker to the StickerSheet, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet. More...
        int addSticker(Image &sticker, int x, int y);
 
 	    //Adds a sticker to the StickerSheet at layer layer, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet. More...
        int setStickerAtLayer(Image &sticker, unsigned layer, int x, int y);
 
 	    //Changes the x and y coordinates of the Image in the specified layer. More...
        bool translate(unsigned index, int x, int y);
 
 	    //Removes the sticker at the given zero-based layer index. More...
        void removeSticker(unsigned index);
 
 	    //Returns a pointer to the sticker at the specified index, not a copy of it. More...
        Image * getSticker(unsigned index);
 
 	    //Returns the total number of layers available on the Stickersheet. More...
        int layers() const;
 
 	    //Renders the whole StickerSheet on one Image and returns that Image. More...
        Image render() const;



    private:
        std::vector<const Image*> stickers;
        unsigned int max_;
        Image base;
        std::vector<std::pair<int, int>> location;

};