/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include <string>
#include <vector>
#include <StickerSheet.h>
#include <Image.h>
using namespace std;
using namespace cs225;
class StickerSheet {
    public:
        StickerSheet(const Image &picture, unsigned max);
        void changeMaxStickers(unsigned max);
        int addSticker(Image &sticker, int x, int y);
        int setStickerAtLayer(Image &sticker, unsigned layer, int x, int y);
        bool translate(unsigned index, int x, int y);
        void removeSticker(unsigned index);
        Image * getSticker(unsigned index);
        int layers() const;
        Image render() const;
    private:
        vector<Image*> stickerSheet_;
        vector<int>XCoord_;
        vector<int>YCoord_;
        Image bPicture;
        unsigned max_;
        vector<unsigned> layers_;
        
};



