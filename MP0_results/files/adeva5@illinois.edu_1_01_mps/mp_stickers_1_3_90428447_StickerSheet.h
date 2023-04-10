/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include <vector>
#include "Image.h"

class StickerSheet {
    public:
        StickerSheet(const Image&, unsigned);
        StickerSheet(const StickerSheet&);
        ~StickerSheet();
        const StickerSheet& operator=(const StickerSheet&);
        void changeMaxStickers(unsigned);
        int addSticker(Image&, int, int);
        int setStickerAtLayer(Image&, unsigned, int, int);
        bool translate(unsigned, int, int);
        void removeSticker(unsigned);
        Image* getSticker(unsigned);
        int layers() const;
        Image render() const;
    private:
        void _copy(const StickerSheet&);
        Image* base;
        std::vector<Image*> stickers;
        std::vector<int> xcoor;
        std::vector<int> ycoor;
};
