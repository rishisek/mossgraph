#include <iostream>
#include"StickerSheet.h"

using namespace std;
using namespace cs225;

StickerSheet::StickerSheet(const Image &stickerture, unsigned max)
{
    num_ = 0;
    max_ = max;
    baseImage = stickerture;
    stickers = new Image*[max];
    x_ = new unsigned[max];
    y_ = new unsigned[max];
}
StickerSheet::StickerSheet(const StickerSheet &other)
{
    copy_(other);
}
const StickerSheet& StickerSheet::operator=(const StickerSheet &other)
{
    clear_();
    copy_(other);
    return *this;
}
void StickerSheet::changeMaxStickers(unsigned max)
{
    Image** temp = new Image *[num_];
	unsigned* tempx = new unsigned[num_];
	unsigned* tempy = new unsigned[num_];
	for (unsigned i = 0; i < num_; i++) 
    {
		temp[i] = stickers[i];
		tempx[i] = x_[i];
		tempy[i] = y_[i];
	}
	delete[] stickers;
	delete[] x_;
	delete[] y_;
	stickers = new Image * [max];
	x_ = new unsigned[max];
	y_ = new unsigned[max];

	if (max < num_) 
    {
		for (unsigned i = max; i < num_; i++) 
        {
			delete temp[i];
			temp[i] = NULL;
		}
		num_ = max;
		for (unsigned i = 0; i < num_; i++) 
        {
			stickers[i] = temp[i];
			x_[i] = tempx[i];
			y_[i] = tempy[i];
		}
	}
	else 
    {
		for (unsigned i = 0; i < num_; i++) 
        {
			stickers[i] = temp[i];
			x_[i] = tempx[i];
			y_[i] = tempy[i];
		}
	}
	max_ = max;
	delete[] temp;
	delete[] tempx;
	delete[] tempy;
}
int StickerSheet::addSticker(Image &sticker, int x, int y)
{
    if(num_ == max_)
    {
        max_++;
    }
    for (unsigned int i = 0; i < max_; i++) 
    {
		if (i == num_) 
        {
			stickers[i] = new Image(sticker);
			x_[i] = x;
			y_[i] = y;
			num_++;
			return i;
		}
	}
	return -1;
}
int StickerSheet::setStickerAtLayer (Image &sticker, unsigned layer, int x, int y)
{
    if(layer >= max_ || layer < 0) 
    {
        return -1;
    }
    stickers[layer] = &sticker;
    x_[layer] = x;
    y_[layer] = y;
    return layer;
}
bool StickerSheet::translate(unsigned index, int x, int y)
{
    if(index >= num_)
    {
        return false;
    }
    else
    {
        x_[index] = x;
        y_[index] = y;
        return true;
    }
}
void StickerSheet::removeSticker(unsigned index)
{
    delete stickers[index];
	for (unsigned i = index; i < max_-1; i++) 
    {
		stickers[i] = stickers[i + 1];
		x_[i] = x_[i + 1];
		y_[i] = y_[i + 1];
	}
    num_--;
	stickers[max_-1] = NULL;
	x_[max_-1] = 0; 
	y_[max_-1] = 0; 
}
Image* StickerSheet::getSticker(unsigned index)
{
    if(index >= num_)
    {
        return NULL;
    }
    return stickers[index];
}
int StickerSheet::layers () const
{
    return max_;
}
Image StickerSheet::render() const
{
    Image out(baseImage);
	for (unsigned i = 0; i < num_; i++) 
    {
		unsigned w = stickers[i]->width();
		unsigned h = stickers[i]->height();
		if ((w + x_[i]) > out.width()) 
        {
			out.resize(w + x_[i], out.height());
		}
		if ((h + y_[i]) > out.height()) 
        {
			out.resize(out.width(), h + y_[i]);
		}
		for (unsigned x = 0; x < w; x++) 
        {
			for (unsigned y = 0; y < h; y++) 
            {
                HSLAPixel& ipix = stickers[i]->getPixel(x, y);
				HSLAPixel& opix = out.getPixel(x_[i] + x,y_[i] + y);
				if (ipix.a != 0) 
                {
					opix = ipix;
				}
			}
		}
	}
	return out;
}
void StickerSheet::copy_(const StickerSheet & other)
{
  max_ = other.max_;
  baseImage = other.baseImage;
  num_ = other.num_;
  x_ = new unsigned[max_];
  y_ = new unsigned[max_];
  stickers = new Image* [max_];
  for (unsigned i = 0; i < max_; i++)
  {
    stickers[i] = NULL;
  }
  for (unsigned i = 0; i < num_; i++)
  {
      stickers[i] = new Image();
      *stickers[i] = *other.stickers[i];
      x_[i] = other.x_[i];
      y_[i] = other.y_[i];
  }
}
void StickerSheet::clear_()
{
  for(unsigned i = 0; i < num_; i++)
  {
    delete stickers[i];
  }
  delete[] stickers;
  delete[] x_;
  delete[] y_;
}