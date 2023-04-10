
#include "StickerSheet.h"
#include <iostream>




StickerSheet::StickerSheet(const Image &picture, unsigned max){
    image_ = picture;
    max_ = max;
    layer_ = 0;
}

void StickerSheet::changeMaxStickers(unsigned max){
    if(image_vectors_.size() != max_){
        max_ = image_vectors_.size();
    }
    while(max < max_ && !image_vectors_.empty()){
        image_vectors_.pop_back();
        image_location_.pop_back();
        max_--;
    }
    max_ = max;
}


int StickerSheet::addSticker(Image &sticker, int x, int y){
    if(layer_ == max_) max_ +=1;
    layer_++;
    image_vectors_.push_back(&sticker);
    image_location_.push_back(std::make_pair(x,y));
    
    return layer_ - 1;
}
int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y){
    if(layer >= max_){
        return -1;
    }
    image_vectors_.at(layer) = &sticker;
    image_location_.at(layer) = std::make_pair(x,y);
    return layer;
}
bool StickerSheet::translate(unsigned index, int x, int y){
    if(index >= max_ || index >= image_vectors_.size() || index < 0){
        return false;
    }
    if(x < 0){
        unsigned int oldWidth = image_.width();
        unsigned int oldHeight = image_.height();
        image_.resize(abs(x) + image_.width(), image_.height());
        Image copy = image_;
        x = abs(x);
        for(unsigned int i = 0; i < unsigned(x); ++i){
            for(unsigned int j = 0; j < oldHeight; ++j){
                copy.getPixel(i,j).h = 0;
                copy.getPixel(i,j).s = 0;
                copy.getPixel(i,j).l = 1;
            }
        }
        for(unsigned int i = 0; i < oldWidth; ++i){
            for (unsigned int j = 0; j < oldHeight; ++j){
                copy.getPixel(i + x,j).h = image_.getPixel(i,j).h;
                copy.getPixel(i + x,j).s = image_.getPixel(i,j).s;
                copy.getPixel(i + x,j).l = image_.getPixel(i,j).l;
            }
        }
        image_ = copy;
        x = 0;
    }
    if(y < 0){
        unsigned int oldWidth = image_.width();
        unsigned int oldHeight = image_.height();
        image_.resize(image_.width(), image_.height() + abs(y));
        Image copy = image_;
        y = abs(y);
        for(unsigned int i = 0; i < oldWidth; ++i){
            for(unsigned int j = 0; j < unsigned(y); ++j){
                copy.getPixel(i,j).h = 0;
                copy.getPixel(i,j).s = 0;
                copy.getPixel(i,j).l = 1;
            }
        }
        for(unsigned int i = 0; i < oldWidth; ++i){
            for (unsigned int j = 0; j < oldHeight; ++j){
                copy.getPixel(i,j+y).h = image_.getPixel(i,j).h;
                copy.getPixel(i,j+y).s = image_.getPixel(i,j).s;
                copy.getPixel(i,j+y).l = image_.getPixel(i,j).l;
            }
        }
        image_ = copy;
        y = 0;
    }
    image_location_.at(index).first = x;
    image_location_.at(index).second = y;
    return true;
}
void StickerSheet::removeSticker(unsigned index){
    image_vectors_.erase(image_vectors_.begin() + index);
    image_location_.erase(image_location_.begin() + index);
}
Image* StickerSheet::getSticker(unsigned index){
    if(index >= image_vectors_.size() || index < 0){
        return NULL;
    }
    return image_vectors_.at(index);
}
int StickerSheet::layers() const{
    return max_;
}
Image StickerSheet::render() const{
    Image rendered = image_;
    std::vector<std::pair<int, int>> copy_location;
    for (unsigned int i = 0; i < image_vectors_.size(); ++i){
        int x = image_location_.at(i).first;
        int y = image_location_.at(i).second;
        if((x + image_vectors_.at(i)->width()) > rendered.width()){
            rendered.resize((x + image_vectors_.at(i)->width()), rendered.height());
        }
        if((y  + image_vectors_.at(i)->height()) > rendered.height()){
            rendered.resize(rendered.width(), (y  + image_vectors_.at(i)->height()));
        } 
        if(x < 0){
            unsigned int oldWidth = rendered.width();
            unsigned int oldHeight = rendered.height();
            rendered.resize(abs(x) + rendered.width(), rendered.height());
            Image copy = rendered;
            x = abs(x);
            for(unsigned int i = 0; i < unsigned(x); ++i){
                for(unsigned int j = 0; j < oldHeight; ++j){
                    copy.getPixel(i,j).h = 0;
                    copy.getPixel(i,j).s = 0;
                    copy.getPixel(i,j).l = 1;
                }
            }
            for(unsigned int i = 0; i < oldWidth; ++i){
                for (unsigned int j = 0; j < oldHeight; ++j){
                    copy.getPixel(i + x,j).h = rendered.getPixel(i,j).h;
                    copy.getPixel(i + x,j).s = rendered.getPixel(i,j).s;
                    copy.getPixel(i + x,j).l = rendered.getPixel(i,j).l;
                }
            }
            rendered = copy;
            x = 0;
        }
        if(y < 0){
            unsigned int oldWidth = rendered.width();
            unsigned int oldHeight = rendered.height();
            rendered.resize(rendered.width(), rendered.height() + abs(y));
            Image copy = rendered;
            y = abs(y);
            for(unsigned int i = 0; i < oldWidth; ++i){
                for(unsigned int j = 0; j < unsigned(y); ++j){
                    copy.getPixel(i,j).h = 0;
                    copy.getPixel(i,j).s = 0;
                    copy.getPixel(i,j).l = 1;
                }
            }
            for(unsigned int i = 0; i < oldWidth; ++i){
                for (unsigned int j = 0; j < oldHeight; ++j){
                    copy.getPixel(i,j+y).h = rendered.getPixel(i,j).h;
                    copy.getPixel(i,j+y).s = rendered.getPixel(i,j).s;
                    copy.getPixel(i,j+y).l = rendered.getPixel(i,j).l;
                }
            }
            rendered = copy;
            y = 0;
        }
        copy_location.push_back(std::pair(x,y));


        for(unsigned int j = 0; j < image_vectors_.at(i)->width(); ++j){
            for (unsigned int k = 0; k < image_vectors_.at(i)->height(); ++k){
                int x_cord = copy_location.at(i).first;
                int y_cord = copy_location.at(i).second;
                if(image_vectors_.at(i)->getPixel(j,k).a != 0){
                    rendered.getPixel(j + x_cord, k + y_cord).h = image_vectors_.at(i)->getPixel(j,k).h;
                    rendered.getPixel(j + x_cord, k + y_cord).s = image_vectors_.at(i)->getPixel(j,k).s;
                    rendered.getPixel(j + x_cord, k + y_cord).l = image_vectors_.at(i)->getPixel(j,k).l;
                }
            }   
     }
    }
    
    return rendered;
}