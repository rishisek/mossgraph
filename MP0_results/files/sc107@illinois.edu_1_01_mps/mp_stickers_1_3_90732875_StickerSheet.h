/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"

class StickerSheet{
    public:
        StickerSheet(const Image&, unsigned);
        StickerSheet(const StickerSheet&);

        int addSticker(Image&, int, int);
        void changeMaxStickers(unsigned);
        Image* getSticker(unsigned);
        int layers() const;
        const StickerSheet& operator=(const StickerSheet&);
        void removeSticker(unsigned);
        Image render() const;
        int setStickerAtLayer(Image&, unsigned, int, int);
        bool translate(unsigned, int, int);


    private:
        Image basepic;
        Image** maxsheets;
        unsigned stickermax_;
        unsigned nextLayer_;
        int* x_;
        int* y_;
        void _copy(const StickerSheet&);
        void _delete();

};