/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include <vector>
#include "Image.h"
#include "../lib/cs225/PNG.h"

struct Layer {
    Image* image = NULL;
    int x = 0;
    int y = 0;
};

class StickerSheet {
    private:
    void _copy(StickerSheet const &);
    void _destroy();
    std::vector<Layer*> layers_;
    unsigned max_stickers_ = 0;
    unsigned stickers_ = 0;
    const Image& base_;
    int width_;
    int height_;
    public:
    StickerSheet(const Image&, unsigned);
    StickerSheet(const StickerSheet&);
    int addSticker(Image&, int, int);
    void changeMaxStickers(unsigned);
    Image* getSticker(unsigned); //return NULL if invalid
    int layers() const;
    const StickerSheet& operator=(const StickerSheet&);
    ~StickerSheet();
    void removeSticker(unsigned);
    Image render() const;
    int setStickerAtLayer(Image&, unsigned, int, int);
    bool translate(unsigned, int, int);
};