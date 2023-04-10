#include "StickerSheet.h" 
#include "Image.h"


#include <vector>

using namespace std;
namespace cs225 {


StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    stick_obj = 0;
    base = Image(picture);
    stick_max = max; 
    cout<<"this is max inside constructor "<<stick_max<<endl;
    for(unsigned i =0; i< stick_max; i++) { 
        
        
        Stit new_stit = {0,0,NULL}; 
        
        vec.push_back(new_stit);
        //stick_max++;
        //stick_obj = stick_max;
        
    }

    
}



StickerSheet::~StickerSheet() {
    return;
}

void StickerSheet::copy(const StickerSheet &other) {
    
    stick_max = other.stick_max;
    base = other.base;
    vec = other.vec;
    //stick_obj = other.stick_obj;
}




StickerSheet::StickerSheet (const StickerSheet &other) {  
   copy(other);
}






const StickerSheet & StickerSheet::operator = (const StickerSheet &other) {
    if(this != &other) {
    
    vec.clear(); 

    copy(other);
    


        
    }
    
    return *this;
}








int StickerSheet::addSticker ( Image & sticker, int x,int y )	{ 
    for(unsigned int j  = 0 ; j< stick_max ; j++) {
        if(vec.at(j).new_img == NULL) {
            vec.at(j).new_img = &sticker;
            //if you access a wrong index, it's easier to debug.
            vec.at(j).x_coord = x;
            vec.at(j).y_coord = y;
            stick_obj++;
            cout<<"This is my stick_obj"<< stick_obj << endl;
            cout<<"This is my stick_max"<< stick_max << endl;
            return j;

        }
    }
    Stit new_st = {x,y,&sticker};
    vec.push_back(new_st);
    stick_max++;
    stick_obj = stick_max;
    return stick_max-1;
} 

void StickerSheet::changeMaxStickers(unsigned max)	{
    vec.resize(max);
    stick_max = max;

}

bool StickerSheet::translate(unsigned index, int x,int 	y){
    

    
    if(index < stick_max && vec.at(index).new_img != NULL && index >= 0) {
       
            vec.at(index).x_coord = x;
            vec.at(index).y_coord = y;
            return true; 
        
    }
    else 
    {return false;}

}

void StickerSheet::removeSticker(unsigned index) { 
    if (index < vec.size() && vec.at(index).new_img !=NULL ) {
        //delete vec.at(index).new_img;
        vec.at(index).new_img = NULL;
        vec.at(index).x_coord= 0;
        vec.at(index).y_coord= 0;
        
    } 




}

Image* StickerSheet::getSticker(unsigned index) {
    
    if( index >=0 && index < stick_max && vec.at(index).new_img != NULL) {

        return vec.at(index).new_img;
    }

    return NULL;

}


Image StickerSheet::render()const { 
    cout << __LINE__ << endl;
    unsigned max_width = base.width();           
    unsigned max_height = base.height();           
    

    //Find the maximum width and height of the final image by checking the width and height of each sticker
    //Image tmp = base;       
    cout << __LINE__ << "   THIS IS MY STICK_OBJ: " << stick_obj <<  endl;
    
     
        for(unsigned m = 0; m<stick_obj; m++) {                                  cout<<__LINE__<<endl;
        unsigned cur_wid = vec.at(m).new_img->width() + vec.at(m).x_coord;       cout<<"this is curwid "<<cur_wid<<endl;
    
    // If the current width is greater than the current maximum width, update the maximum width
        if(cur_wid > max_width) { 
            max_width = cur_wid; }
    
    // Calculate the current height of the sticker// Calculate the current height of the sticker
        unsigned cur_hei = vec.at(m).new_img->height() + vec.at(m).y_coord;
        if(cur_hei > max_height) {
            max_height = cur_hei; }
        
    // Create an Image object to store the final image
    }
    
    Image get = Image(max_width,max_height); // run the resize of the base image
    // Resize the Image object to the maximum width and height found in the previous loop
    
   
    
   // Copy the base image to the final Image object
   
    for(unsigned i = 0; i < base.width();i++) {
        for(unsigned j =0; j<base.height();j++) {
            get.getPixel(i,j) = base.getPixel(i,j);
        }
    }
    // Loop through each sticker and add it to the final Image object
    //cout<<"stick_obj is "<< stick_obj<<endl;
    for(unsigned m = 0; m<stick_obj; m++) { 
        // Loop through each pixel in the sticker
        for(unsigned i=0; i< vec.at(m).new_img->width();i++) {
            for(unsigned j = 0;  j < vec.at(m).new_img->height();j++) { 
                // If the current pixel is not transparent (alpha value is not 0), add it to the final Image object
                if(vec.at(m).new_img->getPixel(i,j).a != 0) {
                    get.getPixel(i + vec.at(m).x_coord, j + vec.at(m).y_coord) = vec.at(m).new_img->getPixel(i,j);
                }
            }
        }
    
    }  

    
    

   
   //return the final image object
    return get;

}


int StickerSheet::setStickerAtLayer (Image &sticker, unsigned layer, int x, int y) {
    if(layer>=0 && layer<stick_max) {
       
            vec.at(layer).new_img = &sticker;
            vec.at(layer).x_coord = x;
            vec.at(layer).y_coord = y;
            return layer;

    }

    else {
        return -1 ;
        }
}

int StickerSheet::layers()const {
    return stick_max; 
}

}



































