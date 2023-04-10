/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include <vector>

class StickerSheet {
    public:
    
    StickerSheet(const Image &picture, unsigned max);
    void changeMaxStickers(unsigned max);
    int addSticker(Image &sticker, int x, int y);
    int setStickerAtLayer(Image &sticker, unsigned layer, int x, int y);
    bool translate(unsigned index, int x, int y);
    void removeSticker(unsigned index);
    Image* getSticker(unsigned index);
    int layers() const;
    Image render() const;
    
    private:
    void copy(const StickerSheet &other);
    void clear();
    std::vector<Image*> stickers_;
    std::vector<int> pos_x_;
    std::vector<int> pos_y_;
    Image image_;
    unsigned max_stickers_;

};