#include "StickerSheet.h"
#include "Image.h"
#include <vector>
using namespace std;
//7:24pm@13th

StickerSheet::StickerSheet(const Image & picture, unsigned max){
    base_image = picture; // setting the base image for this sticker sheet
    max_ = max; // setting the maximum number of stickers on this sticker sheet
    for (unsigned i = 0; i < max; i++){ // this for loop's pushbacks remove the need for us to have layersv.resize(max)
        layerstruct basestruct; // declaring a default struct to fill our vectors
        basestruct.sticker = NULL; // setting values of default structs (sticker will point to null in every case)
        basestruct.x = 0;
        basestruct.y = 0;
        layersv.push_back(basestruct);
    } // now there are NO empty spots in the vector... all are filled with structs containing a null sticker pointer
}


StickerSheet::StickerSheet(const StickerSheet & other){ // your copy constructor  -> needs a destructor and an assignment operator
    copy(other);
} 

StickerSheet & StickerSheet::operator=(const StickerSheet & other){

    // do we need to reject if other is the same object?
    layersv.clear(); // clearing all elements
    copy(other);
    return *this; // correct, only overloaded operators can return a "this" pointer
}

////////////////////////////////////////////////////////////////////////////////////////////////
int StickerSheet::addSticker(Image & sticker, int x, int y){
    
    for (unsigned i = 0; i < layersv.size(); i++){
        if(layersv.at(i).sticker == NULL){
            layersv.at(i).sticker = &sticker;
            layersv.at(i).x = x;
            layersv.at(i).y = y;
            // test case over here?
            return i;
        }
    }

    layerstruct newstruct; // declaring a newstruct struct to add at the end
    newstruct.sticker = &sticker; // setting values of new struct
    newstruct.x = x;
    newstruct.y = y;
    layersv.push_back(newstruct);
    max_++; // setting new max
    return layersv.size() - 1;
}
//////////////////////////////////////////////////////////////////////////////////////////////

void StickerSheet::changeMaxStickers(unsigned max){
    layersv.resize(max); // I am assuming this does the deletion for us?
    max_ = max; // set new max
}


Image* StickerSheet::getSticker(unsigned index){ // the compiler will detect a wrong argument for us, right?
    if (index < 0 || index >= layersv.size() ){
        return NULL;
    }
    return layersv.at(index).sticker; // return address of sticker at index
}

int StickerSheet::layers() const{
    return max_;
}

/***************************************************************************************/
void StickerSheet::removeSticker(unsigned index){
    if (index < 0 || index >= layersv.size() || layersv.at(index).sticker == NULL){
        return; // just exit and don't do anything
    }
    layersv.at(index).sticker = NULL;
}
/***************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Image StickerSheet::render() const{
    
    unsigned int max_height = base_image.height();
    unsigned int max_width = base_image.width();
    int min_height = 0;
    int min_width = 0;

    for (unsigned i = 0; i < max_; i++){

        if (layersv.at(i).sticker != NULL){
            if (layersv.at(i).x + layersv.at(i).sticker->width() > max_width){
                max_width = layersv.at(i).x + layersv.at(i).sticker->width(); 
            }

            if (layersv.at(i).y + layersv.at(i).sticker->height() > max_height){
                max_height = layersv.at(i).y + layersv.at(i).sticker->height();
            }

            if (layersv.at(i).x < min_width){
                min_width = layersv.at(i).x;
            }

            if (layersv.at(i).y < min_height){
                min_height = layersv.at(i).y;
            }
        }
    }

    Image rendered_version = Image(max_width - min_width, max_height - min_height); // you have your new image with the altered width and height
    
    int negated_offsetx = -1 * min_width; // we are taking the absolute of min width here... if the min_width is 0, it won't even matter
    int negated_offsety = -1* min_height;
    
    // Loading the original image onto the new image depending on our offsets
    for (unsigned i = negated_offsetx; i < base_image.width() + negated_offsetx; i++){ // so now I am saying that my base image will be printed from pixels where the original had its start at (0,0) which is now negatedxoffset up till negatedxoffset plus width of original, and they will be put into pixels starting from (0,0) for the main canvas now
        for (unsigned j = negated_offsety; j < base_image.height() + negated_offsety; j++){
            rendered_version.getPixel(i, j) = base_image.getPixel(i - negated_offsetx, j - negated_offsety); // we are loading all pixels from the previous image onto the new image

        }
    }

    for (size_t v = 0; v < layersv.size(); v++){ // iterating through my vector
        if(layersv.at(v).sticker != NULL){ // where they exist
            for (unsigned x = negated_offsetx + layersv.at(v).x; x < negated_offsetx + layersv.at(v).x + layersv.at(v).sticker->width(); x++){
                for (unsigned y = negated_offsety + layersv.at(v).y; y < negated_offsety + layersv.at(v).y + layersv.at(v).sticker->height(); y++){
                        if (layersv.at(v).sticker->getPixel(x - (negated_offsetx + layersv.at(v).x),y - (negated_offsety + layersv.at(v).y)).a != 0){
                            rendered_version.getPixel(x,y) = layersv.at(v).sticker->getPixel(x - (negated_offsetx + layersv.at(v).x),y - (negated_offsety + layersv.at(v).y));
                        }
                }
            }
    }    
    }

    return rendered_version;
    
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int StickerSheet::setStickerAtLayer(Image & sticker, unsigned layer, int x, int y){
    if (layer < 0 || layer >= layersv.size()){
        return -1;
    }

    
    layersv.at(layer).sticker = &sticker;
    layersv.at(layer).x = x;
    layersv.at(layer).y = y;
    return layer;

}

bool StickerSheet::translate(unsigned index, int x, int y){
    if (index < 0 || index >= layersv.size() || layersv.at(index).sticker == NULL){
        return false;
    }

    layersv.at(index).x = x;
    layersv.at(index).y = y;
    return true;
}

void StickerSheet::copy(const StickerSheet & other){

    base_image = other.base_image; // copies base image
    max_ = other.max_; // copies max number of layers
    layersv = other.layersv; // does this just work?    
}

