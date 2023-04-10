/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include <vector>
#include "../lib/cs225/PNG.h"
#include "../src/Image.h"

struct Layer {
    Image* sticker = NULL;
    int x_pos = 0;
    int y_pos = 0;
};

class StickerSheet {
    public:
        StickerSheet(const Image &picture, unsigned max);
        StickerSheet(const StickerSheet &other);
        const StickerSheet& operator=(const StickerSheet &other);
        void changeMaxStickers(unsigned max);
        int addSticker(Image &sticker, int x, int y);
        int setStickerAtLayer(Image &sticker, unsigned layer, int x, int y);
        bool translate(unsigned index, int x, int y);
        void removeSticker(unsigned index);
        Image * getSticker(unsigned index);
        int layers() const;
        Image render() const;
        ~StickerSheet();

    private:
        std::vector<Layer*> layers_;
        int max_stickers_ = 0;
        int num_stickers_ = 0;
        Image* base_;
        int base_width_;
        int base_height_;

        void _destroy();
        void _copy(const StickerSheet& other);
        void remove(unsigned ind);

};

