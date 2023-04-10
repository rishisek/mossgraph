/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#ifndef STICKERSHEET_H
#define STICKERSHEET_H

#include <vector>
#include "cs225/PNG.h"
#include "Image.h"

using namespace std;

class StickerSheet
{
    public:
        //Constructors
        StickerSheet(const Image &picture, unsigned max);
        StickerSheet (const StickerSheet &other);
        ~StickerSheet();//added
        //Methods
        const StickerSheet & operator=(const StickerSheet &other);
        void changeMaxStickers (unsigned max);
        int addSticker (Image &sticker, int x, int y);
        int setStickerAtLayer (Image &sticker, unsigned layer, int x, int y);
        bool translate (unsigned index, int x, int y);
        void removeSticker (unsigned index);
        Image *getSticker (unsigned index);
        int layers () const;
        Image render () const;
        void Clear_sheet();//added

    private:
        Image base_image; 
        vector<int> xpos;
        vector<int> ypos;
        vector<Image*> stickers;
        unsigned max_stickers;
};
#endif
