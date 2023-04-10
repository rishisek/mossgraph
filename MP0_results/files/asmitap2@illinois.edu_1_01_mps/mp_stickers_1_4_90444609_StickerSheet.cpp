#include "StickerSheet.h"
using namespace cs225;
using namespace std;
#include <string>
#include <algorithm>

StickerSheet::StickerSheet(const Image &picture,unsigned max_){
   // const Image & renderedImage;   
   //basePicture = new Image(picture);    // make a copy of the base image
   //renderedPicture = new Image();
   //for(unsigned int i=0;i<max_)
   maxsize = max_;
   pic=Image(picture);
   v.resize(max_);


}

StickerSheet::StickerSheet(const StickerSheet & other){
    copySticker(other);
}	
    //}

//StickerSheet::~StickerSheet(){
    //deleteMemory();
//}



int StickerSheet::addSticker(Image & sticker,int x,int y){
    for(unsigned int i=0;i<v.size();i++){
        if(v.at(i).stickerImage==NULL){
           v.at(i).stickerImage = &sticker;
           v.at(i).xCoord=x;
           v.at(i).yCoord=y;
           return i;}
    }
    StickerDetails s = {x, y, &sticker};
    v.push_back(s);
    maxsize++;
    return v.size()-1;
        }
    
  // StickerDetails s = {x, y, &sticker};
   //v.push_back(s);
    //max_++;
    //return max_-1;}
        
void StickerSheet::copySticker(const StickerSheet &other){
    maxsize=other.maxsize; //maximum num of layer of stickers
    //basePicture=new Image(*(other.basePicture)); //remember to delete
    //renderedPicture=new Image(*(other.renderedPicture));
    //count=other.count;
    pic=other.pic;
    v=other.v;
    //for(unsigned i=0; i<max_; i++){ 
        //v.at(i).xCoord=other.v.at(i).xCoord;
        //v.at(i).yCoord=other.v.at(i).yCoord;
       // v.at(i).stickerImage=new Image(*(other.v.at(i).stickerImage));
        //new Image(*(other.v.at(i).stickerImage)); 
    }


void StickerSheet::deleteMemory(){ v.clear();}



const StickerSheet & StickerSheet::operator=(const StickerSheet &other){
    if (this!= &other) {
        deleteMemory();
        copySticker(other);
    }
    return *this;}


bool StickerSheet::translate(unsigned index,int x,int y ){
   if(index<=maxsize && index>=0){
       if (v.at(index).stickerImage!=NULL){
           v.at(index).xCoord=x;
           v.at(index).yCoord=y;
            return true; }
        
   }
return false;
}		

int StickerSheet::setStickerAtLayer	(Image & sticker,unsigned layer,int x,int y){
    if(layer<v.size() && layer>=0){
        v.at(layer).xCoord=x;
        v.at(layer).yCoord=y;
        v.at(layer).stickerImage=&sticker;
        return layer;
    }
    return -1;
}	



int StickerSheet::layers() const{
    return v.size();
}


void StickerSheet::removeSticker(unsigned index){
    if(index<maxsize && index>=0){
    if(v.at(index).stickerImage!=NULL){
        v.at(index).stickerImage=NULL;
        v.at(index).xCoord=0;
        v.at(index).yCoord=0;
    }

}}

Image * StickerSheet::getSticker(unsigned index){
    if(index>maxsize && index<0 ){return NULL;}
    else{
        return v.at(index).stickerImage;
    }

}	

void StickerSheet::changeMaxStickers(unsigned newmax){
    v.resize(newmax);
    maxsize=newmax;
}

Image StickerSheet::render()const{
    int minY=0;
    int minX=0;
    unsigned int maxX=pic.width();
    unsigned int maxY=pic.height();

for(unsigned i=0;i<maxsize;i++){
    if (v.at(i).stickerImage != NULL) {
        if(v.at(i).yCoord<minY){
            minY=v.at(i).yCoord;}
        if(v.at(i).xCoord<minX){
            minX=v.at(i).xCoord;}
        if(v.at(i).stickerImage->width()+v.at(i).xCoord>maxX){
            maxX=v.at(i).stickerImage->width()+v.at(i).xCoord;}
        if(v.at(i).stickerImage->height()+v.at(i).yCoord>maxY){
            maxY=v.at(i).stickerImage->height()+v.at(i).yCoord;}
        }
    }


//resize the canvas
Image renderedPicture = Image(maxX-minX,maxY-minY);

int modx=(-1)*minX;
int mody=(-1)*minY;
for(unsigned i=modx;i<pic.width()+modx;i++){
    for(unsigned j=mody;j<pic.height()+mody;j++){
        renderedPicture.getPixel(i,j)=pic.getPixel(i-modx,j-mody);
    }
}



for(unsigned k=0;k<v.size();k++){
    if (v.at(k).stickerImage != NULL){
        unsigned limit1=(v.at(k).xCoord + modx) + v.at(k).stickerImage -> width();
        unsigned limit2=(v.at(k).yCoord + mody) + v.at(k).stickerImage -> height();
        for(unsigned a = v.at(k).xCoord + modx; a < limit1; a++){
            for(unsigned b = v.at(k).yCoord + mody; b < limit2; b++){
                if(v.at(k).stickerImage->getPixel(a - (v.at(k).xCoord + modx),b - (v.at(k).yCoord + mody)).a != 0) {
                    renderedPicture.getPixel(a,b) =  v.at(k).stickerImage->getPixel(a - (v.at(k).xCoord + modx),b - (v.at(k).yCoord + mody));
                }
            }
        }
    }   
}

return renderedPicture;}
// }


