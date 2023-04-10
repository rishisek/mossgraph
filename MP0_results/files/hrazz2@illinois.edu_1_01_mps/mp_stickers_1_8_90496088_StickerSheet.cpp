#include "StickerSheet.h"
#include "cs225/PNG.h"
#include"cs225/HSLAPixel.h"
#include <vector>

StickerSheet::StickerSheet(const Image & picture, unsigned max) {
    this -> base = picture;
    this -> max_ = max;
    numstickers.resize(max_, nullptr);
    xcoord.resize(max_);
    ycoord.resize(max_);
    // base = picture;

}

StickerSheet::StickerSheet(const StickerSheet & other) {
    this -> max_ = other.max_;
    this -> base = other.base;
    numstickers.resize(max_, nullptr);
    xcoord.resize(max_);
    ycoord.resize(max_);

    for (unsigned int i = 0; i < numstickers.size(); i++) {
        numstickers.at(i) = other.numstickers.at(i);
        xcoord.at(i) = other.xcoord.at(i);
        ycoord.at(i) = other.ycoord.at(i);
        // should i do this w x and y?
    }
    
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other) {
    if (this == &other) {
        return *this;
    } else {
        this -> max_ = other.max_;
        this -> base = other.base;
        numstickers.resize(max_, nullptr);
        xcoord.resize(max_);
        ycoord.resize(max_);

        for (unsigned int i = 0; i < numstickers.size(); i++) {
            numstickers.at(i) = other.numstickers.at(i);
            xcoord.at(i) = other.xcoord.at(i);
            ycoord.at(i) = other.ycoord.at(i);
        }
    }
    return *this;
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
    for (unsigned int i = 0; i < numstickers.size(); i++) {
        if (numstickers.at(i) == nullptr) {
            numstickers.at(i) = &sticker;
            xcoord.at(i) = x;
            ycoord.at(i) = y;
            return i;
        }
    }
    numstickers.push_back(&sticker);
    xcoord.push_back(x);
    ycoord.push_back(y);
    return numstickers.size() - 1;     
}

void StickerSheet::changeMaxStickers(unsigned max) {
    numstickers.resize(max);
    xcoord.resize(max);
    ycoord.resize(max);
}



bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (numstickers.at(index) == nullptr || numstickers.size() <= index) {
        return false;
    }
    xcoord.at(index) = x;
    ycoord.at(index) = y;
    return true;
}

void StickerSheet::removeSticker(unsigned index) {
        // int ind = int(index);
        //numstickers.at(index) = nullptr;
        numstickers.erase(numstickers.begin() + index);
        xcoord.erase(xcoord.begin() + index);
        ycoord.erase(ycoord.begin() + index);
}

Image* StickerSheet::getSticker(unsigned index) const {
    if (index >= numstickers.size()) {
        return NULL;
    } else {
        return numstickers.at(index);
    }
}

int StickerSheet::layers() const {
    return numstickers.size();
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
    if (numstickers.size() > layer) {
        numstickers.at(layer) = &sticker;
        xcoord.at(layer) = x;
        ycoord.at(layer) = y;
        return layer;
        
    }
    return -1;
}

Image StickerSheet::render() const {

    int mostnegx = 0;
    int biggestxcoord = base.width();
    int biggestycoord = base.height();
    int negycoord = 0;
    for (unsigned i =  0; i < xcoord.size(); i++) {
        if (mostnegx >= xcoord.at(i)) {
            mostnegx = xcoord.at(i);
        } else if (biggestxcoord <= (int) (xcoord.at(i) + numstickers.at(i) -> width())) {
            biggestxcoord = (int) (xcoord.at(i) + numstickers.at(i) -> width());
            // biggestw += numstickers.at(i) -> width();
        }
    }

    
    for (unsigned i =  0; i < ycoord.size(); i++) {
        if (negycoord >= ycoord.at(i)) {
            negycoord = ycoord.at(i);
        } else if (biggestycoord <= (int) (ycoord.at(i) + numstickers.at(i) -> height())) {
            biggestycoord = (int) (ycoord.at(i) + numstickers.at(i) -> height());
        }
    }

    unsigned newwidth = biggestxcoord - mostnegx;
    unsigned newheight = biggestycoord - negycoord;
    Image lastimage(newwidth, newheight);
    

    // lastimage.resize(newwidth, newheight);
    // std::cout << lastimage.width() << base.width() << std::endl;
    
    for (unsigned i = 0; i < base.width(); i++) {
        for (unsigned j = 0; j < base.height(); j++) {
            lastimage.getPixel(i - mostnegx, j - negycoord) = base.getPixel(i, j);
        }
    }
    for (unsigned z = 0; z < numstickers.size(); z++) {
        if (numstickers.at(z) != nullptr) {
            // std::cout << xcoord.at(z) << " " << ycoord.at(z) << std::endl;

            for (unsigned i = 0; i < numstickers.at(z) -> width(); i++) {
                for (unsigned j = 0; j < numstickers.at(z) -> height(); j++) {
                    if (numstickers.at(z) -> getPixel(i, j).a != 0) {
                        HSLAPixel &cpix = numstickers.at(z) -> getPixel(i, j);
                        //std::cout << i + xcoord.at(z) << " " << j + ycoord.at(z) << std::endl;
                        // cpix = lastimage.getPixel(j + ) //xcoord + originofx
                        HSLAPixel &pix = lastimage.getPixel(i + xcoord.at(z) - mostnegx, j + ycoord.at(z) - negycoord);
                        pix = cpix;
                    }
                }
            }
        }
    }

    
    return lastimage;
}





        // unsigned biggestw = 0;
    // unsigned biggesth = 0;

    // for (unsigned i = 0; i < numstickers.size(); i++) {
    //     if (biggestw < numstickers.at(i) -> width()) {
    //         biggestw = numstickers.at(i) -> width();
    //     }
    //     if (biggesth < numstickers.at(i) -> height()) {
    //         biggesth = numstickers.at(i) -> height();
    //     }
    // }

    // Image lastimage = base;