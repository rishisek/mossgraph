
#include "StickerSheet.h"
#include <climits>

StickerSheet::StickerSheet(const Image &picture, unsigned max){
picture_ = picture; 
//max_ = max; 
//curr_sticker = 0; 
for (unsigned i = 0; i < max; i++) {
    image_.push_back(NULL); 
    coord_.push_back(make_pair(INT_MIN, INT_MIN)); 
}

}

StickerSheet::StickerSheet(const StickerSheet& other) {

picture_ = other.picture_; 
//max_ = other.max_;
//curr_sticker = other.curr_sticker; 
coord_ = other.coord_; 
image_ = other.image_; 


}
const StickerSheet& StickerSheet::operator= (const StickerSheet &other) {
if (this == &other) {
    return *this; 
}
picture_ = other.picture_; 
//max_ = other.max_;
//curr_sticker = other.curr_sticker; 
coord_ = other.coord_; 
image_ = other.image_; 


return *this; 
}
void StickerSheet::changeMaxStickers(unsigned max) {
 //if (max < max_) {
if (max > image_.size()) {
 for (unsigned i = image_.size(); i < max; i++) {
    image_.push_back(NULL);
    coord_.push_back(make_pair(INT_MIN, INT_MIN)); 
 }
} else if (max < image_.size()) {
    image_.erase(image_.begin() + max, image_.begin() + image_.size()); 
    coord_.erase(coord_.begin() + max, coord_.begin() + coord_.size());
    // x_ = 0;
    // y_ = 0;
    // for (unsigned index = 0; index < image_.size(); index++) {
    //     if (image_.at(index) != NULL) {
    //          if (coord_.at(index).first < x_) {
    //             x_ = coord_.at(index).first;
    //         }
    //          if (coord_.at(index).second < y_) {
    //             y_ = coord_.at(index).second;
    //         }
    //     }
    // }

//   if (coord_.at(index).first == x_) {
//         x_ = 0;
//        for (size_t i = 0; i < coord_.size(); i++) {
//         if (image_.at(i) != NULL) {
            
        }
}
       //}
   // }
      /*if (coord_.at(index).second == y_) {
        y_ = 0;
       for (size_t i = 0; i < coord_.size(); i++) {
        if (image_.at(i) != NULL) {
            if (coord_.at(i).second < x_) {
                x_ = coord_.at(i).second;
            }
        }
       }
    }
    }
    }*/
 

int StickerSheet::addSticker(Image &sticker, int x, int y) {
    const int w = picture_.width();
    const int h = picture_.height(); 
    
    /*if ((x < 0) && (y < 0)) {
     x_ = x_ - x; 
     y_ = y_ - y; 
     picture_.resize(w + x_, h+y_);
    } else if (x < 0) {
     x_ = x_ - x; 
    picture_.resize(w + x_, h);
    } else if (y < 0) {
    y_ = y_ -y;
    picture_.resize(w, h+y_);
    } else {

    }*/
    for (size_t i = 0; i < image_.size(); i++) {
        if (image_.at(i) == NULL) {
        image_.at(i) = &sticker; 
        coord_.at(i) = make_pair(x, y);
        return i; 
        }
    }
coord_.push_back(make_pair(x,y)); 
image_.push_back(&sticker); 
return coord_.size() - 1; 
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
    if ((layer < 0) || (layer >= image_.size())) {
        return -1; 
    }
coord_.at(layer) =  make_pair(x,y);
image_.at(layer) = &sticker;
return layer;
}
bool StickerSheet::translate(unsigned index, int x, int y) {
    if ((index < 0) || (index >= image_.size()) || (image_.at(index) == NULL)) {
        return false; 
    }
    coord_.at(index) = make_pair(x, y);
    return true; 
}

void StickerSheet::removeSticker(unsigned index) {
//coord_.at(index) = make_pair(0, 0);
if ((index < 0) || (index > image_.size()) || (image_.at(index) == NULL)) {
    return; 
} else {
    image_.at(index) = NULL; 
    // if (coord_.at(index).first == x_) {
    //     x_ = 0;
    //    for (size_t i = 0; i < coord_.size(); i++) {
    //     if (image_.at(i) != NULL) {
    //         if (coord_.at(i).first < x_) {
    //             x_ = coord_.at(i).first;
    //         }
    //     }
    //    }
    // }
    //   if (coord_.at(index).second == y_) {
    //     y_ = 0;
    //    for (size_t i = 0; i < coord_.size(); i++) {
    //     if (image_.at(i) != NULL) {
    //         if (coord_.at(i).second < y_) {
    //             y_ = coord_.at(i).second;
    //         }
    //     }
    //    }
    // }

}
}

Image * StickerSheet::getSticker(unsigned index) {
    if ((index < 0)||(index > image_.size())) {
        return NULL; 
    }
    return image_.at(index); 
}
int StickerSheet::layers() const {
return image_.size(); 
}

Image StickerSheet::render() const {
    //if sticker is bigger change size of base image call scale 
    //int w = picture_.width();
    //int h = picture_.height();
    
    //const int w = pic_.width();
    //const int h = pic_.height();
    //x_ = 0;
    //y_ = 0;
    int x_ = 0;
    int y_ = 0; 
     for (unsigned index = 0; index < image_.size(); index++) {
        if (image_.at(index) != NULL) {
             if (coord_.at(index).first < x_) {
                x_ = coord_.at(index).first;
            }
             if (coord_.at(index).second < y_) {
                y_ = coord_.at(index).second;
            }
        }
    }
    Image temp = picture_; 
    unsigned int w = temp.width();
    unsigned int h = temp.height(); 
   // Image img(w, h); 
    if (x_ < 0) {
        w = w - x_;
    }
    if (y_ < 0) {
        h = h - y_;
    }
    Image img(w, h);
    for (unsigned int i = 0; i < temp.width(); i++) {
        for (unsigned int j = 0; j < temp.height(); j++) {
            cs225::HSLAPixel & p = temp.getPixel(i, j); 
            img.getPixel(-x_ + i, -y_ + j) = p;
        }
    }
   // 
    unsigned int new_w = img.width();
    unsigned int new_h = img.height(); 
    for (size_t i = 0; i < image_.size(); i++) {
        if (image_.at(i) != NULL) {
        if (image_.at(i)->width() + coord_.at(i).first - x_> new_w) {
           new_w = image_.at(i)->width() + coord_.at(i).first - x_; 
        } 
        if (image_.at(i)->height() + coord_.at(i).second - y_> new_h) {
           new_h = image_.at(i)->height() + coord_.at(i).second -y_; 
        } 
    }
    }
    img.resize(new_w, new_h); 
    //const int w = img.width(); 
    //const int h = img.height(); 
   // if ((x_ == 0) && (y_ == 0))
   /*Image pic_ = picture_;
    for (size_t i = 0; i < pic_.width(); i++) {
        for (size_t j = 0; j < pic_.height(); j++) {
            cs225::HSLAPixel & p = pic_.getPixel(i, j); 
            img.getPixel(-x_ + i,-y_ + j) = p;  
            if ((-x_ + i)>= img.width()) {
             std::cout<<"line 142"<<std::endl; }
        }
    }*/
    //addSticker(&picture_, -x_, -y_); 

    for (size_t a = 0; a < image_.size(); a++) {
        //img._copy(image_.at(a)); 
        if (image_.at(a) != NULL) {
        for (unsigned int i = 0; i < image_.at(a)->width(); i++) {
           for (unsigned int j = 0; j < image_.at(a)->height(); j++) {
           // if ((i + coord_.at(a).first -x_ )> img.width()) {
             //std::cout<<"line 163"<<std::endl; }
            cs225::HSLAPixel & p = image_.at(a)->getPixel(i, j); 
            if (p.a == 0) {
                continue; 
            } 
            //unsigned int x_offset = 
            //if (coord_.at(a).first < 0) {
                
            //}
            img.getPixel(-x_ + i + coord_.at(a).first, -y_ + j + coord_.at(a).second) = p;
            }
    }
    
} 
}return img;
}
           //  std::cout << coord_.at(a).first << std::endl; 
            //  std::cout << i  << std::endl; 
           // if ((i + coord_.at(a).first) < 0) 
           // std::cout << i + coord_.at(a).first << std::endl; 
            //std::cout<<i - coord_.at(a).first<<std::endl; 
       
       /* if ((coord_.at(a).first < 0) && (coord_.at(a).second < 0)){
            if ((i - coord_.at(a).first) >= img.width()) {
                std::cout<<"line 178"<<std::endl;
            }
         img.getPixel(i - coord_.at(a).first, j - coord_.at(a).second) = p;
         } else if (coord_.at(a).first < 0) {
             if ((i - coord_.at(a).first) >= img.width()) {
                std::cout<<"line 183"<<std::endl;  }
         img.getPixel(i - coord_.at(a).first, j + coord_.at(a).second) = p; 
         } else if (coord_.at(a).second < 0) {
             if ((i + coord_.at(a).first -x_ )>= img.width()) {
             std::cout<<"line 177"<<std::endl; }
         img.getPixel(i + coord_.at(a).first, j - coord_.at(a).second) = p;
         } else {
            if ((i + coord_.at(a).first -x_ )>= img.width()) {
                std::cout<<i<<std::endl;
                std::cout<<-x_<<std::endl;
                std::cout<<coord_.at(a).first<<std::endl;
                std::cout<<img.width()<<std::endl;
                
            
            }
        img.getPixel(i + coord_.at(a).first, j + coord_.at(a).second) = p;
    }
        }*/
        //img.resize(img.width() + 1, img.height()); 
   // cs225::HSLAPixel & p = image_.at(i)->getPixel(image_.at(i)->width(), image_.at(i)->height());
     
    // picture_.l = p.l; 
    // picture_.s = p.s; 
    // picture_.h = p.h; 
    // }
    //return img; 

//vif (coord_.at(a).first < 0)
            /*if ((coord_.at(a).first < 0) && (coord_.at(a).second < 0)) {
                if (((image_.at(a)->width() - coord_.at(a).first > img.width())) 
                && (image_.at(a)->height() - coord_.at(a).second > img.height())) {
                 img.resize(image_.at(a)->width() - coord_.at(a).first, 
                 image_.at(a)->height() - coord_.at(a).second);
            } else if (image_.at(a)->width() - coord_.at(a).first > img.width())
                //&& (image_.at(a)->height() - coord_.at(a).second > img.height())) 
                { img.resize(image_.at(a)->width() - coord_.at(a).first, 
                 img.height());
            }
            }*/
           // if(coord_.at(a).first > 0) && ()
          /*  if (((image_.at(a)->width() + coord_.at(a).first > img.width())) 
            && (image_.at(a)->height() + coord_.at(a).second > img.height())) {
                 img.resize(image_.at(a)->width() + coord_.at(a).first, 
                 image_.at(a)->height()+coord_.at(a).second);
            } else if (image_.at(a)->height()+coord_.at(a).second > img.height()) {
               img.resize(img.width(), image_.at(a)->height()+coord_.at(a).second);
            } else if (image_.at(a)->width() + coord_.at(a).first > img.width()) {
              img.resize(image_.at(a)->width() + coord_.at(a).first, img.height());
            } else {

            }*/