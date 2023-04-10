/*
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */

#pragma once
#include "Image.h"
#include <vector>
using namespace std;
using namespace cs225;


using namespace cs225;
class StickerSheet{
    public:
    	StickerSheet (const Image &picture, unsigned max_); //done
        StickerSheet (const StickerSheet &other); //done
        void copySticker(const StickerSheet &other); //done
        //const StickerSheet & operator= (const StickerSheet &other); 
        void changeMaxStickers (unsigned newmax);//done
        int addSticker (Image &sticker, int x, int y); //done
        int setStickerAtLayer (Image &sticker, unsigned layer, int x, int y); //done
        bool translate (unsigned index, int x, int y); //done
        void removeSticker (unsigned index); //done
        Image * getSticker (unsigned index); //done
        int layers() const; //done
        Image render() const;
        void deleteMemory();
        const StickerSheet & operator= (const StickerSheet &other);
        //unsigned max_;
        struct StickerDetails{
            int xCoord;
            int yCoord;
            Image* stickerImage;
        };
        int count;
        vector<StickerDetails> v;
        //Image *renderedPicture;
        unsigned int H;
        unsigned int W;
    private:
        Image pic;
        unsigned maxsize;
        //Image renderedPicture;


};
