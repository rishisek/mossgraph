
#include "StickerSheet.h"



StickerSheet::StickerSheet (const Image &picture, unsigned max){
    //PNG* newImage = new PNG();
    base_ = picture;
    max_ = max;
   stickerVector_ = vector<Image*>(max);
   x_component_ =  vector<int>(max);
   y_component_ = vector<int>(max);
}

StickerSheet::StickerSheet(const StickerSheet & other){

    base_ = other.base_;
    max_ = other.max_; 

    x_component_ = other.x_component_;
    y_component_ = other.y_component_;
    stickerVector_ = other.stickerVector_;

    
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other){

    if (this == &other){
        return *this;
    } 

    base_ = other.base_;
    max_ = other.max_; 

    x_component_ = other.x_component_;
    y_component_ = other.y_component_;
    stickerVector_ = other.stickerVector_;

 
    return *this;
    

}


int StickerSheet::addSticker(Image & sticker, int x, int y){

    for(unsigned int i = 0; i< (unsigned int) max_; i++){

        if(stickerVector_[i] == NULL){
           stickerVector_[i] = &sticker;
            x_component_[i] = x;
            y_component_[i] = y; 
            return i;
        }

    }
   
 
        stickerVector_.push_back(&sticker);
        x_component_.push_back(x);
        y_component_.push_back(y);
        max_++;

    
   

    return stickerVector_.size() -1;

}

void StickerSheet::changeMaxStickers(unsigned max){

    stickerVector_.resize(max);
    x_component_.resize(max);
    y_component_.resize(max);

    max_ = max;
}

Image *StickerSheet::getSticker(unsigned index){
    if(index > stickerVector_.size()){
        return NULL;
    }
    else{
        return stickerVector_[index];
    }
     
}


int StickerSheet::layers() const{
    return max_;
}


void StickerSheet::removeSticker(unsigned index){
    stickerVector_[index]  = NULL;

}

Image StickerSheet::render() const{
   
   Image backgroundImage;

   backgroundImage = base_;

   Image currentSticker;

   for(unsigned k =0; k< stickerVector_.size(); k++){
        if(stickerVector_[k] != NULL){
            currentSticker = *stickerVector_[k];

            //resizing the image to incorporate all stickers

            if(currentSticker.width() + x_component_[k] > backgroundImage.width()){
                backgroundImage.resize((currentSticker.width() + x_component_[k]), backgroundImage.height());
            }


            if(currentSticker.height() + y_component_[k] > backgroundImage.height()){
                backgroundImage.resize(backgroundImage.width(), currentSticker.height() + y_component_[k]);
            }

            // if(x_component_[k] < 0 && y_component_[k] <0){
            //     backgroundImage.resize((abs((int)x_component_[k]) + backgroundImage.width()), (abs((int)y_component_[k]) + backgroundImage.height()));
                
            // }

            // if(y_component_[k] < 0){
            //     //  for(int c = 0; c< y_component_.size(); c++){
            //     //     if(y_component_[c] == 0){
            //     //         y_component_[c] += abs((int)y_component_[k]);
            //     //     }
            //     // }
            //     backgroundImage.resize(backgroundImage.width(), (abs((int)y_component_[k]) + backgroundImage.height()));
            // }
            // int originalX = 0;
            // int originalY = 0;
             if(x_component_[k] < 0){
                backgroundImage.resize((abs((int)x_component_[k]) + backgroundImage.width()),backgroundImage.height());
                //originalX = abs((int)x_component_[k]);
                
            }
            if(y_component_[k] < 0){
                backgroundImage.resize(backgroundImage.width(), (abs((int)y_component_[k]) + backgroundImage.height()));
               // originalY = abs((int)y_component_[k]); 
            }


            for(unsigned i=0; i< currentSticker.width(); i++){
                for(unsigned j = 0; j< currentSticker.height(); j++){

                    if(currentSticker.getPixel(i,j).a==0) continue;
                    // if(x_component_[k] < 0 && y_component_[k] <0){
                    //     backgroundImage.getPixel(i,j) = currentSticker.getPixel(i,j);
                    // //}
                    //else{

                        backgroundImage.getPixel(x_component_[k] +i,y_component_[k]+j) = currentSticker.getPixel(i,j);
                    //}
                    //backgroundImage.getPixel(i,j) = currentSticker.getPixel(i,j);
                }
            }
        

        }
   }
   return backgroundImage;


}

// Image StickerSheet::render() const{

//     Image backgroundImage;
//     backgroundImage = base_;

//     int rightmostX = *max_element(x_component_.begin(), x_component_.end()); //p.x
//     int leftmostX = *min_element(x_component_.begin(), x_component_.end()); //n.x

//     for(int i=0; i< stickerVector_.size(); i++){
//         if(stickerVector_[i]!=NULL){
//             if(x_component_[i] + stickerVector_[i]->width() > backgroundImage.width()){
//                 backgroundImage.width() = x_component_[i] + stickerVector_[i]->width() 
//             }
//             if(y_component_[i] + stickerVector_[i]->height() > backgroundImage.height()){
//                 backgroundImage.height() = y_component_[i] + stickerVector_[i]->height() 
//             }
//         }
//     }

//     int indexofRM;

//     for(unsigned int i = 0; i< x_component_.size(); i++){
//         if(x_component_[i] == rightmostX){
//             indexofRM = i;
//         }
//     }

//     int widthRightSticker = stickerVector_[indexofRM]->width(); // width of the rightmost sticker
//     int w = base_.width();

//     if(leftmostX < 0){
//          w += abs(leftmostX);
//     }
//     if(rightmostX + widthRightSticker > (int) base_.width()){
//          w += (rightmostX + widthRightSticker) - base_.width();
//     }
    


//     int bottommostY = *max_element(y_component_.begin(), y_component_.end());
//     int topmostY = *min_element(y_component_.begin(), y_component_.end());

//     int indexofBM;
//     for(unsigned int i = 0; i< y_component_.size(); i++){
//         if(y_component_[i] == bottommostY){
//              indexofBM = i;
//         }
//     }

//     int heightBottomSticker = stickerVector_[indexofBM]->height(); //width of the bottommost sticker
//    // int h = topmostY + abs(bottommostY) + abs(widthBottomSticker); 

//     int h = base_.height();

//     if(bottommostY < 0){
//          h += abs(bottommostY);
//     }
//     if(rightmostX + heightBottomSticker > (int)base_.height()){
//          h += (topmostY + heightBottomSticker) - base_.height();
//     }


//     printf("width: %d, height: %d\n", w, h);
//     Image sheet((unsigned)w, (unsigned)h);
//     sheet.resize((unsigned)w, (unsigned)h);

//      for (unsigned int i=0; i<base_.width(); i++){
//             for(unsigned int j=0; j<base_.height(); j++) {
//                 //how to get the x and y of base
//                 int widthShift = w - base_.width(); 
//                 int heightShift = h - base_.height();
//                 // HSLAPixel& p1 = sheet.getPixel(widthShift + i,heightShift + j);
//                 // HSLAPixel p2 = base_.getPixel(i, j);
//                 // *(p1) = p2;
//                 sheet.getPixel(widthShift + i,heightShift + j) = base_.getPixel(i, j);
//             }
//         }

//     //puts stickers on the image
//     for(unsigned int k = 0; k< stickerVector_.size(); k++){
//         for (unsigned int i=0; i<stickerVector_[k]->width(); i++){
//             for(unsigned int j=0; j<stickerVector_[k]->height(); j++) {
//                 //HSLAPixel& p1 = sheet.getPixel(x_component_[k] + i, y_component_[k] + j);
//                 //HSLAPixel p2 = stickerVector_[k]->getPixel(i, j);
//                 //*(p1) = p2;
//                 //if(stickerVector_[k]!=NULL){
//                     sheet.getPixel(x_component_[k] + i, y_component_[k] + j) = stickerVector_[k]->getPixel(i, j);
//                 //}
//             }
//         }
//     }

//     return sheet;

// }
    

int StickerSheet::setStickerAtLayer(Image & sticker, unsigned layer, int x, int y){

    // if(layer > (unsigned int) max_ ){
    //     return -1;
    // }
    // else{
    //     stickerVector_[layer] = &sticker;
    //     x_component_[layer] =  x;
    //     y_component_[layer]  = y;

    //     return layer;
        if(layer < stickerVector_.size()){
            stickerVector_[layer] = &sticker;
            x_component_[layer] =  x;
            y_component_[layer]  = y;
            
            return layer;
        }
        else{
            return -1;
        }

    }
   


bool StickerSheet::translate(unsigned index, int x, int y){

    if(index < stickerVector_.size() && stickerVector_[index] != NULL){
        x_component_[index] = x;
        y_component_[index] = y;
        return true;
    }
    else{
        return false;
    }
}
  

