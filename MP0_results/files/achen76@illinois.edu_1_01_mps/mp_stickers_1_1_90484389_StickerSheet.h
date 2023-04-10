/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include <iostream>
#include "Image.h"

using namespace cs225;

class StickerSheet {
public:
    StickerSheet(const Image & picture, unsigned max);
    StickerSheet(const StickerSheet & other);
    StickerSheet const & operator=(const StickerSheet & other);
    ~StickerSheet();

    void changeMaxStickers(unsigned max);
    int addSticker(Image & sticker, unsigned x, unsigned y);
    bool translate(unsigned index, unsigned x, unsigned y);
    void removeSticker(unsigned index);
    Image * getSticker(unsigned index) const;
    Image render() const;

private:
    typedef struct {
        Image * image;
        unsigned x;
        unsigned y;
    } Sticker;

    void _copy(const StickerSheet & other);
    void _destroy();

    HSLAPixel & blend(const HSLAPixel & src, const HSLAPixel & dst) const;

    unsigned capacity_;
    Image * baseImage_;
    Image * renderImage_;
    Sticker * stickers_;

};
