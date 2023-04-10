/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "/workspaces/cs225/cs225git/mp_stickers/src/Image.h"

class StickerSheet{
public:
StickerSheet (const Image &picture, unsigned max);
StickerSheet (const StickerSheet &other);
const StickerSheet & operator= (const StickerSheet &other);
void changeMaxStickers (unsigned max);
int addSticker (Image &sticker, int x, int y);
int setStickerAtLayer (Image &sticker, unsigned layer, int x, int y);
bool translate (unsigned index, int x, int y);
void removeSticker (unsigned index);
Image * getSticker (unsigned index);
int layers () const;
Image render () const;
/*
private:
Image base_;
unsigned size_;
unsigned max_Images;
Image grid;
unsigned xco;
unsigned yco;
*/
};
