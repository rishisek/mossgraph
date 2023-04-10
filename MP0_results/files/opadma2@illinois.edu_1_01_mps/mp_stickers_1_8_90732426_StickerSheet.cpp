#include "StickerSheet.h"

StickerSheet::~StickerSheet(){
    destroy();
}
void StickerSheet::destroy(){
    /*
    for(int i =0;i<int(numStickers);i++){
        if(sheet_[i] != NULL && sheet_[i] != nullptr){
            delete sheet_[i];
        }
        sheet_[i] = NULL;
    }
    */
    //delete[] sheet_;
    numStickers = 0;
    max_ = 0;
    sheet_.clear();
    x_.clear();
    y_.clear();
    //if(base != NULL && base != nullptr){
    delete base;
    //}
    base = NULL;
}
StickerSheet::StickerSheet(const Image &picture, unsigned max){
    max_ = max;
    sheet_.resize(max);
    base = new Image(picture);
    numStickers=0;
    x_.resize(max);
    y_.resize(max);
}

StickerSheet::StickerSheet(const StickerSheet &other){
    max_ = other.max_;
    sheet_.resize(max_);
    numStickers = other.numStickers;
    base = new Image(*(other.base));
    //base = other.base;
    x_.resize(max_);
    y_.resize(max_);
    for(unsigned int i=0;i<other.sheet_.size();i++){
        Image * temp = other.sheet_[i];
        sheet_[i]= temp;
        x_[i]=other.x_[i];
        y_[i]=other.y_[i];
    }
    

}

const StickerSheet & StickerSheet::operator= (const StickerSheet &other){
    destroy();
    max_ = other.max_;
    sheet_.resize(max_);
    numStickers = other.numStickers;
    base = new Image(*(other.base));
    //base = other.base;
    x_.resize(max_);
    y_.resize(max_);
    for(unsigned int i=0;i<other.sheet_.size();i++){
        Image * temp = other.sheet_[i];
        sheet_[i]= temp;
        x_[i]=other.x_[i];
        y_[i]=other.y_[i];
    }
    return *this;

}
void StickerSheet::changeMaxStickers (unsigned max){
    if(max < numStickers){
        /*
        for(unsigned int i =max;i < numStickers;i++){
            delete sheet_[i];
            sheet_[i] = NULL;
        }
        */
        
        numStickers = max;
    }
    
    if(max < max_){
        sheet_.erase(sheet_.begin()+max, sheet_.end());
    }
    else{
        sheet_.resize(max);
    }
    x_.resize(max);
    y_.resize(max);
    max_ = max;
}
int StickerSheet::addSticker (Image &sticker, int x, int y){
    Image* s = &sticker;
    if(numStickers == max_){
        sheet_.resize(max_+1);
        y_.resize(max_+1);
        x_.resize(max_+1);
    }
    sheet_[numStickers] = s;
    x_[numStickers] = x;
    y_[numStickers] = y;
    numStickers = numStickers +1;
    return numStickers - 1;
}
int StickerSheet::setStickerAtLayer (Image &sticker, unsigned layer, int x, int y){
    if(layer >= max_ || layer <0){
        return -1;
    }
    Image * s = &sticker;
    sheet_[layer] = s;
    x_[layer] = x;
    y_[layer] = y;
    return layer;
}
bool StickerSheet::translate (unsigned index, int x, int y){
    if(index >= max_ || index <0 || index >=numStickers){
        return false;
    }
    x_[index] = x;
    y_[index] = y;
    return true;
}
void StickerSheet::removeSticker (unsigned index){
    if(index < max_ && index >=0){
        //delete sheet_[index];
        sheet_[index] = NULL;
        sheet_.erase(sheet_.begin()+index);
        x_.erase(x_.begin()+index);
        y_.erase(y_.begin()+index);
    }
    numStickers = numStickers -1;
}
Image * StickerSheet::getSticker (unsigned index){
    if(index >= max_ || index <0){
        return NULL;
    }
    return sheet_[index];
}
int StickerSheet::layers () const{
    return sheet_.size();
}
Image StickerSheet::render () const{
    //Image * rendered;
    int minw = 0;
    int maxw = base->width();
    int maxh = base->height();
    int minh = 0;
    for(unsigned int i =0;i<numStickers;i++){
        if(x_[i]<minw){
            minw = x_[i];
        }
        if((x_[i] + int(sheet_[i]->width()))>maxw){
            maxw = x_[i] + sheet_[i]->width();
        }
        if(y_[i] + int(sheet_[i]->height())>maxh){
            maxh = y_[i] + sheet_[i]->height();
        }
        if(y_[i] < minh){
            minh = y_[i];
        }
    }
    /*
    if((minw!=0)||(maxw!=(int(base->width())))||(minh!=0)||(maxh!=int(base->height()))){
        int newWidth = maxw - minw;
        int newHeight = maxh - minh;
        int minworig = 0 - minw;
        int maxworig = minworig + base->width();
        int minhorig = 0-minh;
        int maxhorig = minhorig+base->height();
        rendered = new Image(newWidth,newHeight);
        for(int w=0;w<newWidth;w++){
            for(int h=0;h<newHeight;h++){
                if(w>=minworig && w<maxworig && h>=minhorig && h<maxhorig){
                    //store base image back
                    cs225::HSLAPixel & pix = rendered->getPixel(w,h);
                    cs225::HSLAPixel & pBase = base->getPixel(w-minworig,h-minhorig);
                    pix = pBase;
                }
                else{
                    //store white pixel
                    cs225::HSLAPixel & pix = rendered->getPixel(w,h);
                    pix.l = 1;
                }
            }
        }
    }
    else{
        rendered = new Image(*base);
    }
    */
    int newWidth = maxw - minw;
    int newHeight = maxh - minh;
    int minworig = 0 - minw;
    int maxworig = minworig + base->width();
    int minhorig = 0-minh;
    int maxhorig = minhorig+base->height();
    //Image * rendered = new Image(newWidth,newHeight);
    Image rendered = Image(newWidth,newHeight);
    for(int w=0;w<newWidth;w++){
        for(int h=0;h<newHeight;h++){
            if(w>=minworig && w<maxworig && h>=minhorig && h<maxhorig){
                //store base image back
                cs225::HSLAPixel & pix = rendered.getPixel(w,h);
                cs225::HSLAPixel & pBase = base->getPixel(w-minworig,h-minhorig);
                pix = pBase;
            }
            else{
                //store white pixel
                cs225::HSLAPixel & pix = rendered.getPixel(w,h);
                pix.l = 1;
            }
        }
    }
    for(unsigned int i =0;i<numStickers;i++){
         for(unsigned int w = x_[i]+minworig;w<(x_[i]+minworig+sheet_[i]->width());w++){
            for(int h =y_[i]+minhorig;h<(y_[i]+minhorig+int(sheet_[i]->height()));h++){
                cs225::HSLAPixel & p = rendered.getPixel(w,h);
                cs225::HSLAPixel & pSticker = sheet_[i]->getPixel(w-x_[i]-minworig,h-y_[i]-minhorig);
                if(pSticker.a == 1){
                    p = pSticker;
                }
            }
         }
    }
    return rendered;
    //delete rendered;
}