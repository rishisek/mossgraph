#include "StickerSheet.h"
#include <iostream>
#include <vector>

//using namespace cs225; 

StickerSheet::StickerSheet(const Image & picture, unsigned max){
    picture_ = Image(picture); 
    max_ = max; 
    layers_.resize(max); 
    for (unsigned i = 0; i<max_; i++){
        layer StructLayer = {0, 0, NULL};
        layers_.push_back(StructLayer); 
    }

}

StickerSheet::StickerSheet(const StickerSheet & other){
     copy(other); 

}

void StickerSheet::copy(const StickerSheet & obj){
    this->max_ = obj.max_; 
    this->picture_ = obj.picture_;
    layers_ = obj.layers_; 
    
}

// void StickerSheet::destroy() {
//     for (unsigned i = 0; i< max_; i++){
//          if (layers_.at(i).StructSticker)
//             delete layers_.at(i).StructSticker; 
//     }
// }

// StickerSheet::~StickerSheet(){
//     destroy(); 
// }
const StickerSheet & StickerSheet::operator=(const StickerSheet & other){
 
        //destroy(); 
        if(this!=&other){
            layers_.clear(); 
            copy(other);

        }
        
    
         return *this; 
}

void StickerSheet::changeMaxStickers(unsigned max){
    if (max == 0){
        layers_.clear();
        return; 
    }
    if(max >= layers_.size()) {
        max_ = max;
        layers_.resize(max); 
    }
    else {
        layers_.erase(layers_.begin() + max, layers_.end());
    }
}

int StickerSheet::addSticker(Image & sticker, int x, int y){
    
    for (unsigned i = 0; i< layers_.size(); i++){
        if (layers_.at(i).StructSticker == NULL){
            layers_.at(i).x = x; 
            layers_.at(i).y = y;
            layers_.at(i).StructSticker = &sticker;
            if(i +1 > max_)
                max_ = i+1; 
            return i; 
        }
    }
    std::cout<<"I made it through the for loop"<<std::endl; 
    layer newLayer = {x, y, &sticker}; 
    layers_.push_back(newLayer); 
    max_= layers_.size();  
    return (max_ - 1); 

}

int StickerSheet::setStickerAtLayer	(Image & sticker, unsigned layer, int x, int y){
    if(layer< max_ && layer>=0){
    layers_.at(layer).x = x; 
    layers_.at(layer).y = y; 
    layers_.at(layer).StructSticker = &sticker; 
    return layer; 
    }
    return -1; 


    
}	


bool StickerSheet::translate(unsigned index,int x,int y){
    if (index < layers_.size() && index >=0 && layers_.at(index).StructSticker!=NULL){
        layers_.at(index).x = x; 
        layers_.at(index).y = y; 
        return true; 
    }
    return false; 
}		

void StickerSheet::removeSticker (unsigned index){
    if (index < max_ && index >= 0)
        layers_.at(index).StructSticker = NULL; 
}

Image * StickerSheet::getSticker (unsigned index) const{
    
    if(index < layers_.size() && layers_.at(index).StructSticker!=NULL && index>=0)
        return layers_.at(index).StructSticker;
    return NULL;
}

int StickerSheet::layers () const{
    return max_; 
}

Image StickerSheet::render () const{
    if(layers_.size() == 0)
        return picture_; 

    Image base = picture_; 
    //return base; 
     int maxX = base.width(); //furthest
     int maxY = base.height(); 
     int negX = 0; //most negative
     int negY = 0; 
    int offsetX = 0; //offsets
    int offsetY = 0; 

    //Finding Offsets
   // std::cout<<__LINE__ << std::endl; 
    for(unsigned v = 0; v<layers_.size(); v++){
        //std::cout<<"enterting for loop"<<std::endl;
        //return base; 
        //if(layers_.at(v).StructSticker == NULL)
             //std::cout<<"NULL"<<std::endl;
        if(layers_.at(v).StructSticker!=NULL){
            //std::cout<<"valid"<<std::endl;
        /////find furthest X and Y on each side
        if (layers_.at(v).x < negX)
        {
            negX = layers_.at(v).x;
            
        }
         if (layers_.at(v).y < negY)
        {
            negY = layers_.at(v).y;
           
        }

        if((layers_.at(v).x + (int)layers_.at(v).StructSticker->width())>maxX){
            maxX = (layers_.at(v).x + layers_.at(v).StructSticker->width());
        }
             
        if((layers_.at(v).y  + (int)layers_.at(v).StructSticker->height())>maxY){
            maxY = (layers_.at(v).y + layers_.at(v).StructSticker->height());
        }
        //cout<<"Hi"<<endl;
        }
        
    }

    offsetX = 0 - negX; 
    offsetY = 0 - negY; 
   //std::cout<<"MaxX is: "<< maxX<<std::endl;
   //std::cout<<" NegXis: "<< negX<<std::endl;
  
   

    
    Image canvas((unsigned)(maxX - negX),(unsigned)( maxY - negY));  //blank canvas
    //std::cout<<"width is: "<< canvas.width()<<std::endl;
   //std::cout<<"height is: "<< canvas.height()<<std::endl;
    //std::cout<<__LINE__ << std::endl; 
    /// making base image blank canvas 
    for(unsigned i = 0; i<base.width(); i++){
        //std::cout<<__LINE__ << std::endl; 
        //std::cout<<"i for loop"<< std::endl;
        for(unsigned j = 0; j<base.height(); j++){
            //std::cout<<__LINE__ << std::endl; 
            //std::cout<<"j for loop"<< std::endl;
            canvas.getPixel(i+offsetX, j + offsetY) = picture_.getPixel(i,j);
            //std::cout<<__LINE__ << std::endl; 
            
            //std::cout<<__LINE__ << std::endl; 
        }
    }
    //std::cout<<__LINE__ << std::endl; 

    //put stickers on 
    for (unsigned int v = 0; v<max_; v++){

        //debugging
        //std::cout<<"entering sticker vector loop"<< std::endl;
        //std::cout<< layers_.at(v).x << std::endl;
        //if(layers_.at(v).StructSticker==NULL)
                   // std::cout<<"NULL "<< std::endl;
        if(layers_.at(v).StructSticker!=NULL){//check image exists, avoids seg fault
        for(unsigned int i = 0; i< layers_.at(v).StructSticker->width(); i++){
                //std::cout<<"i "<< std::endl;
            for(unsigned int j = 0; j<layers_.at(v).StructSticker->height(); j++){
                        HSLAPixel & p = canvas.getPixel(i + layers_.at(v).x+offsetX,j + layers_.at(v).y+offsetY);
                        if(layers_.at(v).StructSticker->getPixel(i, j).a!=0){
                            //std::cout<<"checks p.a "<< std::endl;
                        canvas.getPixel(i+layers_.at(v).x-negX, j+ layers_.at(v).y - negY)  = (layers_.at(v).StructSticker)->getPixel(i,j);
                    }
                }

            }
        }
    }

    

    return canvas;
}