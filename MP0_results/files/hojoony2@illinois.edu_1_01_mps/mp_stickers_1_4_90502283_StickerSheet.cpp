#include <StickerSheet.h>
#include <vector>
#include <cstdlib>

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    picture_ = picture;
    max_ = max;
    
    // first.resize(max_, NULL);
    // xcoord.resize(max_);
    // ycoord.resize(max_);
}
StickerSheet::StickerSheet(const StickerSheet &other) {
    picture_ = other.picture_;
    max_ = other.max_;

    for (unsigned int i = 0; i < other.first.size(); i++) {
        // first.push_back(new Image(*other.first[i]));
        first.push_back(other.first[i]);
        xcoord.push_back(other.xcoord[i]);
        ycoord.push_back(other.ycoord[i]);
    }
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other) {
    if (this == &other) {
        return *this;
    }
    // write the code from copy constructor
    picture_ = other.picture_;
    max_ = other.max_;
    for (unsigned int i = 0; i < other.first.size(); i++) {
        // first.push_back(new Image(*other.first[i]));
        first.push_back(other.first[i]);
        xcoord.push_back(other.xcoord[i]);
        ycoord.push_back(other.ycoord[i]);
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    //current max = max_
    // new max = max
    max_ = max;
    if (max < first.size()) {
        first.erase(first.begin() + max, first.end());
        xcoord.erase(xcoord.begin() + max, xcoord.end());
        ycoord.erase(ycoord.begin() + max, ycoord.end());
    }
}

int StickerSheet::addSticker(Image &sticker, int x, int y) {
    // int index = 0; 
    Image* astick = &sticker;
    
    if (first.size() == max_) {
        ++max_;
    }
    first.push_back(astick); 
    xcoord.push_back(x); 
    ycoord.push_back(y);

    // for (unsigned int i = 0; i < first.size(); i++) {
    //     if (first[i] == NULL) {
    //         first[i] = &sticker;
    //         xcoord[i] = x; 
    //         ycoord[i] = y;
    //         index = i;
    //     }
    // }
    return first.size() -1; 
}
int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
    // add a sticker to the Skicker at Layer. 
    if (layer > first.size()) {
        return -1; 
    }
    first[layer] = &sticker; 
    xcoord[layer] = x; 
    ycoord[layer] = y; 
    return layer;
}

bool StickerSheet::translate(unsigned index, int x, int y) {
    if (first.size() <= index) { // check
        return false; 
    } 
    xcoord[index] = x;
    ycoord[index] = y;
    return true;
}
void StickerSheet::removeSticker(unsigned index) {
    if (first.size() > index) {
        first.erase(first.begin() + index);
        xcoord.erase(xcoord.begin() + index);
        ycoord.erase(ycoord.begin() + index);
    }    // index change (error can occur her)
}

Image* StickerSheet::getSticker(unsigned index) {
    if (index >= first.size()) {
        return NULL;
    }
    return first[index];
}

// not sure with this function
int StickerSheet::layers() const {
    return max_; // or first.size();
}

Image StickerSheet::render() const {
    /* find the right width and height */
    // unsigned int w;
    // unsigned int h;
    // // /* make an empty image */
    // Image img(w, h);

    /* paste the base image */
    Image irender = picture_;

    /* each sticker */
    // coord of base image -> will be updating it (updated image)
    int minx = 0;
    int maxx = irender.width(); 
    int miny = 0; 
    int maxy = irender.height(); 

    for (unsigned int z = 0; z < first.size(); z++) {
        // updating the size of width and height of image
        int udx = xcoord[z] + first[z] -> width(); 
        int udy = ycoord[z] + first[z] -> height();
        if (udx > maxx) {
            maxx = udx;
        } 
        if (udy > maxy) {
            maxy = udy;
        }
    } 

    // when the stickers are at negative coordinates
    // for (unsigned int m = 0; m < xcoord.size(); m++) {
    //     if (xcoord[m] < 0) {
    //         irender.resize(abs(xcoord[m]) + irender.width(), irender.height());
    //         for (unsigned x = irender.width() - abs(xcoord.at(m))-1; x >= 0; x--) {
    //             for (unsigned y = 0; y < irender.height(); y++) {
    //                 auto & anam = irender.getPixel(x + abs(xcoord[m]),y);
    //                 auto & basepix = irender.getPixel(x, y);
    //                 cs225::HSLAPixel tmpvariable(basepix.h,basepix.s, basepix.l,basepix.a);
    //                 basepix = anam;
    //                 anam = tmpvariable; 
    //             }
    //         }
    //     }
    // }

    // for (unsigned int k = 0; k < ycoord.size(); k++) {
    //     if (ycoord[k] < 0) {
    //         irender.resize(irender.width(), abs(ycoord[k]) + irender.height());
    //         for (unsigned x = 0; x < irender.width(); x++) {
    //             for (unsigned y = irender.height() - abs(ycoord.at(k)) -1; y >= 0; y--) {
    //                 auto & anam = irender.getPixel(x,y + abs(ycoord[k]));
    //                 auto & basepix = irender.getPixel(x, y);
    //                 cs225::HSLAPixel tmpvariable(basepix.h,basepix.s, basepix.l,basepix.a); 
    //                 basepix = anam;
    //                 anam = tmpvariable;
    //             }
    //         }
    //     } 
    // }

    for (unsigned int i = 0; i < first.size(); i++) {
        for (unsigned int x = 0; x < first[i] -> width(); x++) {
            for (unsigned int y = 0; y < first[i] -> height(); y++) {
                // edge cases    
                if (xcoord[i] + first[i] -> width() > irender.width()) {
                    irender.resize(xcoord[i] + first[i] -> width(), irender.height());
                }
                if (ycoord[i] + first[i] -> height() > irender.height()) {
                    irender.resize(irender.width(), ycoord[i] + first[i] -> height());
                }
                if (xcoord[i] < 0) {
                    irender.resize(abs(xcoord[i]) + irender.width(), irender.height());
                    for (unsigned x = irender.width() - abs(xcoord.at(i))-1; x >= 0; x--) {
                        for (unsigned y = 0; y < irender.height(); y++) {
                        auto & anam = irender.getPixel(x + abs(xcoord[i]),y);
                        auto & basepix = irender.getPixel(x, y);
                        cs225::HSLAPixel tmpvariable(basepix.h,basepix.s, basepix.l,basepix.a);
                        basepix = anam;
                        anam = tmpvariable; 
                         }
                     }
                }
                if (ycoord[i] < 0) {
                    irender.resize(irender.width(), abs(ycoord[i]) + irender.height());
                    for (unsigned x = 0; x < irender.width(); x++) {
                        for (unsigned y = irender.height() - abs(ycoord.at(i)) -1; y >= 0; y--) {
                        auto & anam = irender.getPixel(x,y + abs(ycoord[i]));
                        auto & basepix = irender.getPixel(x, y);
                        cs225::HSLAPixel tmpvariable(basepix.h,basepix.s, basepix.l,basepix.a); 
                        basepix = anam;
                        anam = tmpvariable;
                        }
                    }
                } 
                if (first.at(i)->getPixel(x,y).a > 0.0) {
                    auto anam = first.at(i)->getPixel(x,y);
                    auto & basepix = irender.getPixel((xcoord[i] + abs(xcoord[i]))/2 + x, (ycoord[i] + abs(ycoord[i]))/2 + y);
                    basepix = anam;
                }

            }
        }
    }
    return irender;
}