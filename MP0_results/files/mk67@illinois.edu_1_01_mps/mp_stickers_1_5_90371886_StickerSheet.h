/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include <string>
#include "../lib/cs225/HSLAPixel.h"
#include "../lib/cs225/PNG.h"
#include "Image.h"
#include <vector>
#include <map>
#include <cmath>
using namespace cs225;
using namespace std;
class StickerSheet {
public :
    StickerSheet(const Image &picture, unsigned max);
    StickerSheet(const StickerSheet &other);
    const StickerSheet& operator=(const StickerSheet &other);
    void changeMaxStickers(unsigned max);
    int addSticker(Image &sticker, int x, int y);
    int setStickerAtLayer(Image &sticker, unsigned layer, int x, int y);
    bool translate(unsigned index, int x, int y);
    void removeSticker(unsigned index);
    Image* getSticker(unsigned index);
    int layers() const;
    Image render() const;
private :
    unsigned int max_stickers;
    Image base_img;
    vector<Image *> sticker_vect;
    //vector<int> x_vect;
    //vector<int> y_vect;
    map<Image*, pair<int,int>> coord_map;
    vector<int> x_cord;
    vector<int> y_cord;
    void clear();
    void copy(const StickerSheet &other);
};