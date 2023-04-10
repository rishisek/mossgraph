#include "StickerSheet.h"

// constructors
StickerSheet::StickerSheet(const Image &picture, unsigned max)
{
    base_ = new Image(picture); 
    maxstickers_ = max;
}

StickerSheet::StickerSheet(const StickerSheet &other)
{
    this->clear();
    base_ = new Image(*other.base_);
    maxstickers_ = other.maxstickers_;
    for (unsigned int i = 0; i < other.stickers_.size(); i++)
    {
        stickers_.push_back(other.stickers_.at(i));
        cord.push_back(other.cord.at(i));
    }
}

StickerSheet::~StickerSheet()
{
    clear();
}

// functions
void StickerSheet::clear()
{
    /*for (unsigned int i = 0; i < maxstickers_; i++)
    {
        if (stickers_[i] != NULL)
        {
            delete stickers_[i];
            stickers_[i] = NULL;
        }
    }*/
    delete base_;
    stickers_.clear();
    cord.clear();
}

const StickerSheet &StickerSheet::operator=(const StickerSheet &other)
{
    if (this == &other)
    {
        return *this;
    }

    clear();

    base_ = new Image(*other.base_);
    maxstickers_ = other.maxstickers_;

    for (unsigned int i = 0; i < other.stickers_.size(); i++)
    {
        stickers_.push_back(other.stickers_.at(i));
        cord.push_back(other.cord.at(i));
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max)
{
    while(stickers_.size() > max){
        stickers_.pop_back();
        cord.pop_back();
    }
    maxstickers_ = max;
}

// done
int StickerSheet::addSticker(Image &sticker, int x, int y)
{
    stickers_.push_back(&sticker);
    cord.push_back(make_pair(x, y));
    if (stickers_.size() > maxstickers_)
    {
        maxstickers_++;
    }
    return stickers_.size() - 1;
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y)
{
    if (layer < maxstickers_)
    {
        stickers_[layer] = &sticker;
        cord[layer] = make_pair(x, y);
        return layer;
    }
    return -1;
}

//done
bool StickerSheet::translate(unsigned index, int x, int y)
{
    if (index >= stickers_.size() || stickers_.at(index) == NULL)
    {
        return false;
    }
    cord.at(index).first = x;
    cord.at(index).second = y;
    return true;
}

// done
void StickerSheet::removeSticker(unsigned index)
{
    if (index < maxstickers_)
    {
        stickers_.erase(stickers_.begin() + index);
        cord.erase(cord.begin() + index);
    }
}

// done
Image *StickerSheet::getSticker(unsigned index)
{
    if(index >= stickers_.size() || stickers_.at(index) == NULL){
        return NULL;
    }
    return stickers_.at(index);
}

int StickerSheet::layers() const
{
    return maxstickers_;
}

Image StickerSheet::render() const
{
    unsigned int maxw = base_->width();
    unsigned int maxh = base_->height();
    int xNegMax = 0;
    int yNegMax = 0;

    for (unsigned int i = 0; i < stickers_.size(); i++){ 
        if (stickers_[i] != nullptr){
            if (cord.at(i).first < xNegMax){
                xNegMax = cord.at(i).first;
            }
            if (stickers_[i]->width() + cord.at(i).first > maxw){
                maxw = stickers_[i]->width() + cord.at(i).first;
            }
            if (cord.at(i).second < yNegMax){
                yNegMax = cord.at(i).second;
            }
            if (stickers_[i]->height() + cord.at(i).second > maxh){
                    maxh = stickers_[i]->height() + cord.at(i).second;
            }
        }
    }
    Image result (*base_);
    result.resize(maxw + abs(xNegMax), maxh + abs(yNegMax));

    for (unsigned int x = 0; x < result.width(); x++){
        for (unsigned int y = 0; y < result.height(); y++){
            result.getPixel(x - xNegMax, y - yNegMax) = result.getPixel(x,y);
        }
    }

    for (unsigned i = 0; i < stickers_.size(); i++){
        if (stickers_[i] != nullptr){
            for (unsigned x = 0; x < stickers_[i]->width(); x++){
                for (unsigned y = 0; y < stickers_[i]->height(); y++){
                    if (stickers_[i]->getPixel(x, y).a != 0)
                    {
                        //cs225::HSLAPixel resultp = copy.getPixel(x + xNegMax, y + yNegMax);
                        cs225::HSLAPixel &pixel = result.getPixel( x + cord.at(i).first - xNegMax, y + cord.at(i).second - yNegMax);
                        pixel = stickers_[i]->getPixel(x, y);
                    }
                }
            }
        }
    }
    return result;
}