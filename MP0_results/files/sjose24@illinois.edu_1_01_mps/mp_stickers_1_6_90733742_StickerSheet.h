/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include <vector>
using namespace std;
#include <cmath>
#include "Image.h"

class StickerSheet {
    public:
    //constructors
    StickerSheet(const Image &picture, unsigned max);
    StickerSheet(const StickerSheet &other);
    ~StickerSheet();

    //functions
    void clear();
    const StickerSheet& operator=(const StickerSheet & other);
    void changeMaxStickers(unsigned max);
    int addSticker(Image &sticker, int x, int y);
    int setStickerAtLayer (Image &sticker, unsigned layer, int x, int y);
    bool translate (unsigned index, int x, int y);
    void removeSticker (unsigned index);
    Image * getSticker (unsigned index);
    int layers () const;
    Image render () const;

    //helper


    private:
    Image *base_ = nullptr;
    vector<Image *> stickers_;
    vector<pair<int,int>> cord;
    unsigned int maxstickers_;
    

};

