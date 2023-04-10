/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"
#include "cs225/PNG.h"
#include <vector>

using namespace std;

class StickerSheet {
  public:
    StickerSheet(const Image &picture, unsigned max);
    StickerSheet(const StickerSheet &other);
    ~StickerSheet();
    const StickerSheet & operator=(const StickerSheet &other);
    void changeMaxStickers(unsigned max);
    int addSticker(Image &sticker, int x, int y);
    int setStickerAtLayer(Image &sticker, unsigned layer, int x, int y);
    bool translate(unsigned index, int x, int y);
    void removeSticker(unsigned index);
    Image * getSticker(unsigned index) const;
    int layers() const;
    Image render() const;

    private:
      void _copy(const StickerSheet &other);
      Image base_;
      vector<Image*> stickers_;
      vector<int> xcord_;
      vector<int> ycord_;
      unsigned int max_;
};