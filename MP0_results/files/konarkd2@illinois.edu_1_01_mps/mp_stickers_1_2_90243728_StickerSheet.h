/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include <vector>

class Stickersheet{
    public://sort till here

    unsigned int max_;//done  
    Image base;    
    vector<Image*> layer_image;
    vector<int> x_coordinates;
    vector<int> y_coordinates;
    unsigned int num_stickers;
    void destroy_();//done
    StickerSheet(const Image &picture, unsigned max);//done
    ~StickerSheet();//done
    StickerSheet(const StickerSheet &other);//done
    const StickerSheet & operator=(const StickerSheet &other);//done
    void changeMaxStickers(unsigned max);//done
    int addSticker(Image &sticker, unsigned int x, unsigned int y);//done
    int setStickerAtLayer(Image &sticker, unsigned layer, int x, int y);//done
    bool translate(unsigned index, unsigned int x, unsigned int y);//done
    void removeSticker(unsigned index);//done
    Image render () const;//done
    Image* getSticker(unsigned index);//done
    int layers () const;//done
    void copy_(const StickerSheet &other);//done
};