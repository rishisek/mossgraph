/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

using namespace std;

namespace cs225 {
    class StickerSheet {
        StickerSheet(const Image & picture, unsigned max);
        StickerSheet(const StickerSheet & other);

        int addSticker(Image & sticker, unsigned x, unsigned y);
        void changeMaxStickers(unsigned max);
        Image* getSticker(unsigned index) const;
        const StickerSheet& operator=(const StickerSheet & other);
        void removeSticker(unsigned index);
        Image render() const;
        bool translate(unsigned index, unsigned x, unsigned y);
    };
};