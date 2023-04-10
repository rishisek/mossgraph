/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <vector>

class StickerSheet {

  public:

    StickerSheet(const Image &picture, unsigned max); // Initializes this StickerSheet with a deep copy of the base picture and the ability to hold a max number of stickers (Images) with indices 0 through max - 1.

    void changeMaxStickers(unsigned max); // Modifies the maximum number of stickers that can be stored on this StickerSheet without changing existing stickers' indices.

    int addSticker(Image &sticker, int x, int y); // Adds a sticker to the StickerSheet, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet.

    int setStickerAtLayer(Image &sticker, unsigned layer, int x, int y); // Adds a sticker to the StickerSheet at layer layer, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet.

    bool translate(unsigned index, int x, int y); // Changes the x and y coordinates of the Image in the specified layer.

    void removeSticker(unsigned index); // Removes the sticker at the given zero-based layer index.

    Image* getSticker(unsigned index); // Returns a pointer to the sticker at the specified index, not a copy of it.

    int layers() const; // Returns the total number of layers available on the Stickersheet.

    Image render() const; // Renders the whole StickerSheet on one Image and returns that Image.
  
  private:
    unsigned int maxStickers_;
    Image image_;
    std::vector<Image*> stickers_;
    std::vector<std::pair<int, int>> locations_;
};