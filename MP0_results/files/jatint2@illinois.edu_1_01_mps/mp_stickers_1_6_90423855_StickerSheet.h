/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

 #include <string>
 #include "Image.h"
 #include <vector>
 using namespace std;

 class StickerSheet{
     public:
         StickerSheet(const Image &picture, unsigned max);
         StickerSheet(const StickerSheet &other);
         const StickerSheet& operator=(const StickerSheet &other);
         void changeMaxStickers(unsigned max);
        int addSticker(Image &sticker, int x, int y);
         int setStickerAtLayer(Image &sticker, unsigned layer, int x, int y);
         bool translate(unsigned index, int x, int y);
        void removeSticker(unsigned index);
        Image* getSticker(unsigned index);
         int layers () const;
         Image render() const;

     private:
         Image baseimage_;
         vector<int> xcoord_;
         vector<int> ycoord_;
         unsigned int max_;
         vector <Image*> paper_;
         unsigned int numberoflayers;
 };
