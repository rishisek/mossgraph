#include "StickerSheet.h"
#include "iostream"

using namespace cs225;

/*    Image picture_;
    unsigned max_;
    vector <Image*> stickerlist_;
    vector <int> left_edge;
    vector <int> upper_edge;*/

StickerSheet::StickerSheet	(const Image & picture,unsigned max)	{
    max_ = max;
    /*
    Image* picture = new Image(picture_.width(), picture_.height());
    for (unsigned i = 0; i < picture->width(); i++) {
        for (unsigned j = 0; j < picture->height(); j++) {
            picture->getPixel(i,j) = picture_.getPixel(i,j);
        }
    } */
    picture_ = Image(picture);
    stickerlist_ = {};
    left_edge = {};
    upper_edge = {};
}

StickerSheet::StickerSheet	(const StickerSheet & 	other	)	{
    picture_ = Image(other.picture_);
    max_ = other.max_;
    for (unsigned i=0; i < other.stickerlist_.size(); i++) {
        stickerlist_.push_back(other.stickerlist_[i]);
        left_edge.push_back(other.left_edge[i]);
        upper_edge.push_back(other.upper_edge[i]);
    }
}

StickerSheet::~StickerSheet	() {
    stickerlist_.clear();
    left_edge.clear();
    upper_edge.clear();
}


const StickerSheet & StickerSheet::operator=(const StickerSheet & 	other){
    stickerlist_.clear();
    left_edge.clear();
    upper_edge.clear();
    picture_ = Image(other.picture_);
    max_ = other.max_;
    for (unsigned i=0; i < other.stickerlist_.size(); i++) {
        stickerlist_.push_back(other.stickerlist_[i]);
        left_edge.push_back(other.left_edge[i]);
        upper_edge.push_back(other.upper_edge[i]);
    }
    return *this;
}


void StickerSheet::changeMaxStickers(unsigned max)	 {
    while (max < stickerlist_.size()) {
        stickerlist_.pop_back();
        left_edge.pop_back();
        upper_edge.pop_back();
    } 
    max_ = max;
}

int StickerSheet::addSticker	(Image & sticker_, int x, int y ) {
    
    stickerlist_.push_back(& sticker_);
    left_edge.push_back(x);
    upper_edge.push_back(y);
    if (stickerlist_.size() > max_) {
        max_ ++;
    }
    return stickerlist_.size()-1;
}

int StickerSheet::setStickerAtLayer	(Image & sticker_, unsigned layer, int 	x, int 	y )	{
    if (layer < 0 || layer >= stickerlist_.size()) {
        return -1;
    } 
    stickerlist_.at(layer) = & sticker_;
    left_edge.at(layer) = x;
    upper_edge.at(layer) = y;
    return layer;
}

bool StickerSheet::translate(unsigned layer, int x, int y) {
    if (layer < 0 || layer >= stickerlist_.size()) {
        return false;
    }
    left_edge.at(layer) = x;
    upper_edge.at(layer) = y;
    return true;
}

void StickerSheet::removeSticker	(unsigned index) {
    stickerlist_.erase(stickerlist_.begin() + index);
    left_edge.erase(left_edge.begin() + index);
    upper_edge.erase(upper_edge.begin() + index);
}	


Image * StickerSheet::getSticker	(unsigned index) {
    if (index < 0 || index >= stickerlist_.size()) {
        return NULL;
    }
    return stickerlist_.at(index);
}

int StickerSheet::layers	()	const {
    return max_;
}

Image StickerSheet::render	()	const {
    int leftedge = 0;
    int rightedge = picture_.width();
    int upperedge = 0;
    int loweredge = picture_.height();
    for (unsigned i = 0; i < stickerlist_.size(); i++) {
        if (left_edge[i] < leftedge) {
            leftedge = left_edge[i];
        }
        if (left_edge[i] + (int)stickerlist_.at(i) -> width() > rightedge) {
            rightedge = left_edge[i] + stickerlist_.at(i) -> width();
        }
        if (upper_edge[i] < upperedge) {
            upperedge = upper_edge[i];
        }
        if (upper_edge[i] + (int)stickerlist_.at(i)->height() > loweredge) {
            loweredge = upper_edge[i] + stickerlist_.at(i)->height();
        }
    }
    
    
    Image canvas = Image(rightedge - leftedge, loweredge - upperedge);
    if (picture_.width() != 0 && picture_.height() != 0) {
        for (unsigned i = 0; i < picture_.width(); i++) {
            for (unsigned j = 0; j < picture_.height(); j++) {
                if (picture_.getPixel(i, j).a != 0) {
                    canvas.getPixel(-leftedge + i, -upperedge + j) = picture_.getPixel(i, j);
                } //(-leftedge + i, -upperedge + j) ,(rightedge - leftedge, loweredge - upperedge)
            }
        }
    }
    
    for (int layer = 0; layer < (int)stickerlist_.size(); layer++) {
        if (stickerlist_.at(layer) != NULL) {
        for (int i = 0; i < (int)stickerlist_.at(layer) -> width(); i++) {
            for (int j = 0; j < (int)stickerlist_.at(layer) -> height(); j++) {
                if (stickerlist_.at(layer)->getPixel(i, j).a != 0) {
                    canvas.getPixel(-leftedge + left_edge.at(layer) + i, -upperedge + upper_edge.at(layer) + j) = stickerlist_.at(layer) -> getPixel(i, j);
                }
            }
        }
    }
    }
    
    return canvas;
}







