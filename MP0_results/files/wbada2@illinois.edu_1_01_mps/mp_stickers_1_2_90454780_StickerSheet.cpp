#include "StickerSheet.h"


StickerSheet::StickerSheet(const Image& picture, unsigned max){
    //PNG* imageCopy = new PNG();
    //base_ = picture;
    //stickerVector(max);
    base_ = picture;
    max_ = max;
    stickerVector_= vector<Image*>(max);
    x_comp_ = vector<int>(max);
    y_comp_ = vector<int>(max);
}

StickerSheet::StickerSheet(const StickerSheet & other){
        //vector<Image*> stickerVector;
        //vector<int> x_comp;
       // vector<int> y_comp;

       
        base_ = other.base_;
        max_ = other.max_;
        

        x_comp_ = other.x_comp_;
        y_comp_ = other.y_comp_;
        stickerVector_ = other.stickerVector_;
        

}

int StickerSheet::addSticker(Image& sticker, int x, int y){

    

        for (unsigned int i=0; i< (unsigned int)max_; i++){

            if(stickerVector_[i] == NULL){
                stickerVector_[i] = &sticker;
                x_comp_[i] = x;
                y_comp_[i] = y;

            return i;

            }
            
        }

        stickerVector_.push_back(&sticker);
        x_comp_.push_back(x);
        y_comp_.push_back(y);
        max_++;

        return stickerVector_.size() - 1;
}

void StickerSheet::changeMaxStickers(unsigned max){

    stickerVector_.resize(max);
    x_comp_.resize(max);
    y_comp_.resize(max);

    max_ = max;


        
}



Image* StickerSheet::getSticker(unsigned index){
    
    if (index > stickerVector_.size()){
        return NULL;
    }
    else{
        return stickerVector_[index];
    }

}

int StickerSheet::layers()const{

    //or max - size
    //nvm
    return max_;

}

const StickerSheet & StickerSheet::operator= (const StickerSheet& other){

        if (this == &other){
            return *this;
        }

        base_ = other.base_;
        max_ = other.max_;
        

        x_comp_ = other.x_comp_;
        y_comp_ = other.y_comp_;
        stickerVector_ = other.stickerVector_;

        return *this;



}

void StickerSheet::removeSticker(unsigned index){

    stickerVector_[index]= NULL;

}

Image StickerSheet::render()const{
    Image canvas;

    canvas = base_;

    Image cur_sticker;

    for (unsigned i=0; i<stickerVector_.size(); i++){
        if(stickerVector_[i] != NULL){
            cur_sticker = *stickerVector_[i];

        

        if((cur_sticker.width()+ x_comp_[i]) > canvas.width()){
            canvas.resize((cur_sticker.width() + x_comp_[i]), canvas.height());


        }

        if((cur_sticker.height() + y_comp_[i]) > canvas.height()){
            canvas.resize(canvas.width(), (cur_sticker.height() + y_comp_[i]));

        }


        if(x_comp_[i] < 0){
            canvas.resize((canvas.width() + abs(int(x_comp_[i]))), canvas.height());
        }

        if(y_comp_[i] < 0){
            canvas.resize(canvas.width(), (canvas.height() + abs(int(y_comp_[i]))));
        }

        for (unsigned j=0; j<cur_sticker.width(); j++){
            for(unsigned k=0; k<cur_sticker.height(); k++){

                if(cur_sticker.getPixel(j,k).a == 0) continue;
                canvas.getPixel(x_comp_[i]+j,(y_comp_[i])+k) = cur_sticker.getPixel(j,k);
                //canvas.getPixel((j),(k)) = sticker.getPixel(j,k);
            }

        }

   
    
    }
    }
    return canvas;


}


int StickerSheet::setStickerAtLayer(Image & sticker, unsigned layer, int x, int y){

    // if(layer > (unsigned int) max_){
    //     return -1;
    // }
    // else{
    //     stickerVector_[layer] = &sticker;
    //     x_comp_[layer] = x;
    //     y_comp_[layer] = y;

    //     return layer;
    // }

    if(layer < stickerVector_.size()){
        stickerVector_[layer] = &sticker;
        x_comp_[layer] = x;
        y_comp_[layer] = y;

        return layer;
    
    }
    else{
        return -1;
    }

}

bool StickerSheet::translate (unsigned index, int x, int y){
    // if(index > stickerVector_.size() && stickerVector_[index] == NULL ){
    //     return false;
    // }
    // else{
    //     stickerVector_[index] = stickerVector_[index];
    //     x_comp_[index] = x;
    //     y_comp_[index] = y;

    //     return true;
    // }

    if(index< stickerVector_.size() && stickerVector_[index] != NULL){
        x_comp_[index] = x;
        y_comp_[index] = y;
        return true;

    }
    else{
        return false;
    }


//|| (x_comp_[index] == NULL && y_comp_[index] == NULL)

}

//or (unsigned i=0; i<stickerVector_.size(); i++){
        