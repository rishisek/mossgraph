/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include <vector>

class StickerSheet {
    public:
        Image image_;
        vector<Image*> layers_;
        vector<int> xCoords_;
        vector<int> yCoords_;

        StickerSheet(const Image &picture, unsigned max);
        int addSticker(Image &sticker, int x, int y);
        void changeMaxStickers(unsigned int max);
        Image *getSticker(unsigned int index);
        int layers() const;
        void removeSticker(unsigned int index);
        Image render() const;
        int setStickerAtLayer(Image &sticker, unsigned int layer, int x, int y);
        bool translate(unsigned int index, int x, int y);
};