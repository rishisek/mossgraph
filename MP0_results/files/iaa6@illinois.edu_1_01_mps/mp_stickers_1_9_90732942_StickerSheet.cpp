#include "StickerSheet.h"
using std::cout;
using std::endl;
StickerSheet::StickerSheet(const Image &picture, unsigned max)
{
    picture_ = new Image(picture);
    max_ = max;
    count_ = 0;
    stickers_ = new Image*[max];
    x_ = new int[max];
    y_ = new int[max];
    for (unsigned i= 0; i< max; i++)
    {
        stickers_[i] = NULL;
        x_[i] = 0;
        y_[i]=0;
    }

}

StickerSheet::StickerSheet(const StickerSheet &other)
{
    picture_ = new Image(*(other.picture_));
    max_ = other.max_;
    count_ = other.count_;
    stickers_ = new Image* [max_];
    x_ = new int[max_];
    y_ = new int [max_];
    for (unsigned i = 0; i < max_ ; i++) {
        if (other.stickers_[i] != NULL){
            stickers_[i] = new Image(*(other.stickers_[i]));
            x_[i] = other.x_[i];
            y_[i] = other.y_[i];
        } else{
            x_[i] = 0;
            y_[i] = 0;
            stickers_[i] = NULL;
        }
    }
}
/*
void StickerSheet::duplicate(const StickerSheet &other)
{
    picture_ = new Image(*(other.picture_));
    max_ = other.max_;
    count_ = other.count_;
    stickers_ = other.stickers_;
    x_ = other.x_;
    y_ = other.y_;
    layer_ = other.layer_;

}
*/


const StickerSheet & StickerSheet::operator=(const StickerSheet &other)
{
    if (this != &other)
    {
        picture_ = new Image(*(other.picture_));
        max_ = other.max_;
        count_ = other.count_;
        stickers_ = new Image* [max_];
        x_ = new int[max_];
        y_ = new int [max_];
        for (unsigned i = 0; i < max_ ; i++) {
            if (other.stickers_[i] != NULL){
                stickers_[i] = new Image(*(other.stickers_[i]));
                x_[i] = other.x_[i];
                y_[i] = other.y_[i];
            } else{
                x_[i] = 0;
                y_[i] = 0;
                stickers_[i] = NULL;
            }
        }
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max)
{
    unsigned temp = max_;
    max_ = max;

    Image **new_stickers_ = new Image*[max];
    int * new_x_ = new int[max];
    int * new_y_ = new int[max];

    for (unsigned i= 0; i< max; i++)
    {
        if (i<temp){
            new_stickers_[i] = stickers_[i];
            new_x_[i] = x_[i];
            new_y_[i] = y_[i];
        }
        
        else
        {
            new_stickers_[i] = NULL;
            new_x_[i] = 0;
            new_y_[i]=0;
        }
        
    }
    delete x_;
    delete y_;
    delete stickers_;
    x_ = new_x_;
    y_ = new_y_;
    stickers_ = new_stickers_;

}

int StickerSheet::addSticker(Image &sticker, int x, int y)
{
    int cunt;
    if (count_ < max_){
        cunt = count_;
    }
    else{
        cunt = max_;
        changeMaxStickers(max_+1);
        }    
        
    stickers_[cunt] = &sticker;
    x_[cunt] = x;
    y_[cunt] = y;
    count_ += 1;
    return count_-1;

    return -1;
    
}

int StickerSheet::setStickerAtLayer (Image &sticker, unsigned layer, int x, int y)
{
    unsigned i = 0;
    if (layer >= max_){return -1;}
    if (layer<0){return -1;}
    if (stickers_[layer]==NULL){count_+=1;}
    stickers_[layer] = &sticker;
    x_[layer] = x;
    y_[layer] = y;
    return layer;
}

bool StickerSheet::translate (unsigned index, int x, int y)
{
    unsigned i = 0;
    bool check = false;
    for (i = 0; i < count_; i++)
    {
        if(i == index)
        {
            check = true;
            x_[i]=x;
            y_[i]=y;
        }
    }
    return check;
}

void StickerSheet::removeSticker (unsigned index)
{
    if (index <0 or index>=max_){return;}
    unsigned j = index;
    stickers_[j] = NULL;
    x_[j] = 0;
    y_[j] = 0;
    count_-=1;
}

Image * StickerSheet::getSticker(unsigned index)
{
    if(index>count_){return NULL;}
    return stickers_[index];

}

int StickerSheet::layers() const
{   
    return max_;
}

Image StickerSheet::render() const
{
    Image *base = new Image(*picture_);
    int maxWidth = base->width();
    int maxHeight = base->height();
    int xneg = 0;
    int yneg = 0;
    for (unsigned i =0; i<max_; i++)
    {
        //cout<<"hi"<<endl;
        //cout<<stickers_[i]<<endl;
        if (stickers_[i]== NULL){continue;}
        
        
        int x = x_[i]+stickers_[i]->width();
        int y = y_[i]+stickers_[i]->height();

        if(x_[i]<xneg){
            xneg = x_[i];
        }
        if(y_[i]<yneg){
            yneg= y_[i];
            }
        //cout<<x_[i] <<' '<< x << " "<<y << " "<<y_[i]<<endl;
        if (x>maxWidth)
        {
            maxWidth = x;
        }
        if (y>maxHeight)
        {
            maxHeight = y;
        }
        
    }
    
    base->resize(maxWidth - xneg,maxHeight - yneg);

    //cout<<xneg<<yneg<<endl;
    for (unsigned i =0; i<max_; i++)
    {
        
        if (stickers_[i]==NULL) {continue;} 
        //cout<<"hi1"<<endl;
        Image sticker = *stickers_[i];
        int x = x_[i]+stickers_[i]->width();
        int y = y_[i]+stickers_[i]->height();
        //cout<<"hi2"<<endl;
        for (unsigned a =  x_[i]; a < x_[i]+sticker.width() ; a++)
        {
            for (unsigned b =  y_[i]; b < y_[i]+sticker.height() ; b++)
            {
                //cout<<"h31"<<endl;
                if (((&sticker.getPixel(a-x_[i],b-y_[i]))) -> a != 0){
                base->getPixel(a+xneg,b+yneg)=sticker.getPixel(a-x_[i],b-y_[i]);
                //cout<<"hi4"<<endl;
                /*
                    basepix -> h = sticky ->h;
                    basepix -> s = sticky ->s;
                    basepix -> l = sticky ->l;
                    basepix -> a = sticky ->a;
                */
                }
            }
        }
    }
    //cout<<"hi5"<<endl;
    Image output = *base;
    delete base;
    base =nullptr;
    return output;

}