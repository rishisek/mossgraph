/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
//7:24pm@13th

#pragma once
#include <string>
using namespace std;
#include "Image.h"
#include <vector>

class StickerSheet {

public:

StickerSheet(const Image & picture, unsigned max);
StickerSheet(const StickerSheet & other); // copy constructor
// ~StickerSheet(); // destructor
StickerSheet& operator= (const StickerSheet & other); // copy assignment operator

int addSticker(Image & sticker, int x, int y);
void changeMaxStickers(unsigned max);
Image* getSticker(unsigned index);
int layers() const;
void removeSticker(unsigned index);
Image render() const;
int setStickerAtLayer(Image & sticker, unsigned layer, int x, int y);
bool translate(unsigned index, int x, int y);
// void destroy();
void copy(const StickerSheet & other);


private:

unsigned max_;
struct layerstruct{
    Image* sticker;
    int x;
    int y;
    //~layerstruct(){
        //delete sticker;}
    }; // struct for a layer

vector <layerstruct> layersv; // vector stores structs
Image base_image;

};



