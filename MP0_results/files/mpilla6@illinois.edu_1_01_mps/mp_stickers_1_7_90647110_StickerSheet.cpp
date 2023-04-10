#include "StickerSheet.h"

// copy all private member variables
void StickerSheet::_copy(const StickerSheet &other)
{
        if(this == &other) return;
        // can just do stickers_ = other.stickers_ since both vectors are on the stack
         stickers_ = other.stickers_;
         pos_x = other.pos_x;
         pos_y = other.pos_y;

        empty_sheet = other.empty_sheet;
        
}


StickerSheet::StickerSheet (const StickerSheet &other)
{
    // copy constructor
    _copy(other);
}

StickerSheet::StickerSheet (const Image &picture, unsigned max)
{
        // constructor
        empty_sheet = picture;
        
        stickers_ = std::vector<Image*>(max, NULL);
        
        pos_x = std::vector<int>(max, 0);
        
        pos_y = std::vector<int>(max, 0);
        
}



const StickerSheet & StickerSheet::operator= (const StickerSheet &other)
{
    if(this == &other){
        return *this;
    }
    _copy(other);
    return *this;

}

int StickerSheet::addSticker (Image &sticker, int x, int y)
{
    // std::cout << "Sticker size: " << stickers_.size() << std::endl;
    for(unsigned int i = 0; i < stickers_.size(); ++i){
     
        if(stickers_.at(i) == nullptr){
            
            stickers_.at(i) = &sticker;

            pos_x.at(i) = x; // std::cout << __LINE__ << std::endl;
            pos_y.at(i) = y;// std::cout << __LINE__ << std::endl;

            return i;
        }

    }

     // if sticker sheet is full, add another layer   
    stickers_.push_back(&sticker);
    pos_x.push_back(x);
    pos_y.push_back(y);
    return stickers_.size() - 1;
}



void StickerSheet::removeSticker (unsigned index)
{
    if((stickers_.at(index) != nullptr) && (index < stickers_.size())){
        stickers_.at(index) = nullptr; 
        pos_x.at(index) = 0;
        pos_y.at(index) = 0;
    }
    
}



bool StickerSheet::translate (unsigned index, int x, int y)
{
    if((stickers_.at(index)==nullptr ) || (index >= stickers_.size())){
        return false;
    } 
    else {
    pos_x.at(index) = x;
    pos_y.at(index) = y;
    return true;
    }
}

int StickerSheet::layers () const
{
   return stickers_.size();
}

Image * StickerSheet::getSticker (unsigned index){
    if((stickers_[index] == NULL) || (index >= stickers_.size())){
        return NULL;
    }
    return stickers_.at(index);
}

int StickerSheet::setStickerAtLayer (Image &sticker, unsigned layer, int x, int y)
{
    if(layer >= stickers_.size() || layer < 0) return -1;
    
    stickers_[layer] = &sticker;
    pos_x.at(layer) = x;
    pos_y.at(layer) = y;
    
    return layer;
}

void StickerSheet::changeMaxStickers (unsigned max)
{
    // one case where max > current size. pushback just spaces
    // one case where max < current size
    std::vector<Image*> temp_stickers(max, NULL);
    std::vector<int> temp_pos_x(max, 0);
    std::vector<int> temp_pos_y(max, 0);
    for(unsigned int i = 0; i < max; i++){
        if(i < stickers_.size()){
            temp_stickers.at(i) = stickers_.at(i);
            temp_pos_x.at(i) = pos_x.at(i);
            temp_pos_y.at(i) = pos_y.at(i);

        }
    }
    stickers_ = temp_stickers;
    pos_x = temp_pos_x;
    pos_y = temp_pos_y;


}


Image StickerSheet::render () const{
    // create new image with new width and height
    // find coordinates of sticker, for each sticker. compare with coordinates of original image
    // check for biggest width, only want to rescale if the next sticker is farther away from image

    int new_width = empty_sheet.width();  // of image
    int new_height = empty_sheet.height(); // of image
    int negative_x = 0;
    int negative_y = 0;
    for(unsigned int i = 0; i < stickers_.size(); ++i){
        int sticker_xcoord = pos_x.at(i);
        int sticker_ycoord = pos_y.at(i);
        
        if(stickers_.at(i) != NULL){
            int sticker_width = stickers_.at(i)->width();
            int sticker_height = stickers_.at(i)->height();
            
            if(sticker_xcoord < negative_x){
                negative_x = empty_sheet.width() + std::abs(sticker_xcoord);
            }
            
            if(sticker_ycoord < negative_y){
                negative_y = empty_sheet.height() + std::abs(sticker_ycoord);
            }
            
            if((sticker_xcoord + sticker_width) > new_width){
                new_width = sticker_xcoord + sticker_width;
            }
            
            if((sticker_ycoord + sticker_height) > new_height){
                new_height = sticker_ycoord + sticker_height;
            }
        }
    }
    // generate a new blank Image with the new dimensions
    Image new_image(unsigned(new_width) + std::abs(negative_x), unsigned(new_height) + std::abs(negative_y));

    // copy old image onto the new image
    for(unsigned int i = std::abs(negative_x); i < empty_sheet.width() + std::abs(negative_x); ++i){
        for(unsigned int j = std::abs(negative_y); j < empty_sheet.height() + std::abs(negative_y); ++j ){
            new_image.getPixel(i, j) = empty_sheet.getPixel(i-negative_x, j-negative_y);
        }
    }


    for(unsigned int i = 0; i < stickers_.size(); ++i){
        if(stickers_.at(i) != NULL){
            int sticker_xcoord = pos_x.at(i) - negative_x;
            int sticker_ycoord = pos_y.at(i) - negative_y;
            int sticker_width = stickers_.at(i)->width();
            int sticker_height = stickers_.at(i)->height();

            // replace the pixels of the new_image with pixels of 
            for(int x = sticker_xcoord; x < sticker_xcoord+sticker_width; ++x){
                for(int y = sticker_ycoord; y < sticker_ycoord+sticker_height; ++y){
                    cs225::HSLAPixel &sticker_pixel = stickers_.at(i)->getPixel(x - sticker_xcoord, y - sticker_ycoord);
                    cs225::HSLAPixel &image_pixel = new_image.getPixel(x, y);
                    if(sticker_pixel.a != 0){
                        image_pixel = sticker_pixel;
                    }
                }
            }
        }
    }
    return new_image;
}