#include <StickerSheet.h>

        StickerSheet::StickerSheet(const Image &picture, unsigned max) {
                this->base = picture;
                this->max_ = max;
                xcoordinate = std::vector<int>(max);
                ycoordinate = std::vector<int>(max);
                num_stickers = std::vector<Image*>(max, NULL);

        }
        StickerSheet::StickerSheet(const StickerSheet &other) {

                this->base = other.base;
                this->max_ = other.max_;
                num_stickers.resize(max_, NULL);
                xcoordinate.resize(max_);
                ycoordinate.resize(max_);
                xcoordinate = other.xcoordinate;
                ycoordinate = other.ycoordinate;
                num_stickers = other.num_stickers;
                

        }
        // StickerSheet::~StickerSheet(){
        //         // for (unsigned int i = 0; i < num_stickers.size(); i++) {
        //         //     delete num_stickers.at(i);q
        //         // }
        // }

        int StickerSheet::addSticker(Image & sticker, int x, int y){
            //Image* sticker_passed = &sticker;
            for (unsigned int i = 0; i < num_stickers.size(); i++) {
                if (num_stickers.at(i) == NULL) {
                        num_stickers.at(i) = &sticker;
                         xcoordinate.at(i) = x;
                         ycoordinate.at(i) = y;
                        //   xcoordinate.push_back(x);
                        //   ycoordinate.push_back(y);
                        //   num_stickers.push_back(&sticker);
                        return i;
                }
            }
                //resize vector?
                //max_ += 1;
                xcoordinate.push_back(x);
                ycoordinate.push_back(y);
                num_stickers.push_back(&sticker);
                return num_stickers.size() - 1;

                //maybe check how to update max here?
         }


        void StickerSheet::changeMaxStickers(unsigned max) {
            num_stickers.resize(max);
            xcoordinate.resize(max);
            ycoordinate.resize(max);
            // modify x and y coordinates
            //make sure this is correct
            
        }
        Image * StickerSheet::getSticker(unsigned index) {
            // Image some_image;
            // Image *something = &some_image;
            // return something;
            if (index < num_stickers.size()) {
                return num_stickers.at(index);
            } else {
                return NULL;
            }
        }



        int StickerSheet::layers() {
            return num_stickers.size();

        }


       const StickerSheet & StickerSheet::operator=(const StickerSheet & other) {
           if (this == &other) {
               return *this;
           } else {
                this->base = other.base;
                this->max_ = other.max_;
                num_stickers.resize(max_, NULL);
                xcoordinate.resize(max_);
                ycoordinate.resize(max_);
                xcoordinate = other.xcoordinate;
                ycoordinate = other.ycoordinate;
                num_stickers = other.num_stickers;
                
        }
        return *this;
       }


        void StickerSheet::removeSticker(unsigned index) {
            num_stickers.erase(num_stickers.begin() + index);
            ycoordinate.erase(ycoordinate.begin() + index);
            xcoordinate.erase(xcoordinate.begin() + index);
        }

        
    Image StickerSheet::render() {
            int smallest_x = 0;
            int biggest_x = base.width();
            int smallest_y = 0;
            int biggest_y = base.height();

            for (unsigned int i = 0; i < xcoordinate.size(); i++) {
                if (smallest_x >= xcoordinate.at(i)) {
                    smallest_x = xcoordinate.at(i);
                    // std::cout<<"this works" << std::endl;
                 } else if (biggest_x <=  xcoordinate.at(i) + (int) num_stickers.at(i)->width()) {
                    biggest_x = xcoordinate.at(i) + (int) num_stickers.at(i)->width();
                 }   
            }

         for (unsigned int j = 0; j < ycoordinate.size(); j++) {
            if (smallest_y >= ycoordinate.at(j)) {
                smallest_y = ycoordinate.at(j);
            } else if (biggest_y <=  ycoordinate.at(j) + (int) num_stickers.at(j)->height()) {
                biggest_y =  ycoordinate.at(j) +(int) num_stickers.at(j)->height();
             }
            }



            int newheight_ = biggest_y - smallest_y;
            int newwidth_ = biggest_x - smallest_x;
            Image answer_image(newwidth_, newheight_);
            

            // loop over base picture x vals
                // loop over base picture y vals
                        // set asnwer_image(x + offset, y + offset) = base_picture(x, y)
            for (unsigned i = 0; i < base.width(); i++) {
                for (unsigned j = 0; j < base.height(); j++) {
                        answer_image.getPixel(i - smallest_x, j - smallest_y) = base.getPixel(i, j);
                     }
                }


                       
            // loop over each sticker
                // loop over sticker x vals
                    // loop over sticker y vals
                            // if alpha > 0
                                // set asnwer_image(x + offset, y + offset) = base_picture(x, y)            
            
            for (unsigned t = 0; t < num_stickers.size(); t++) {
                if (num_stickers.at(t) != NULL) {
                    for (int i = 0; i < (int)num_stickers.at(t)->width(); i++) {
                        for (int j = 0; j < (int)num_stickers.at(t)->height(); j++) {
                            // answer_image.getPixel(i - smallest_x, j - smallest_y) = base.getPixel(i, j);
                            if (num_stickers.at(t) -> getPixel(i,j).a != 0) {
                            cs225::HSLAPixel &newpixel = num_stickers.at(t)->getPixel(i, j);
                            cs225::HSLAPixel &newpixel_1 = answer_image.getPixel(i + xcoordinate.at(t) - smallest_x, j + ycoordinate.at(t) - smallest_y);
                                    newpixel_1 = newpixel;
                        
                            }
                    }
                }
            }

              
            }
                return answer_image;

            }
               
               
               
               
            
            // Image answer_image = base;


            // Iterate through stickers vector to find the smallest and viggest x and y vals

           

            // make an empty image according to the new width and height

            // paste the base image with the proper offset with min x and y vals

            // paste the stickers with the triple for loop with the proper offsets




         
            


                    // if sticker is not null, add the width to max and same for y
                    //for min you do the min


        //right idea, i thjik u have the correct funciton 
        // extend it this way
        //say u have a sticker here 
        //calculate the index
        //num_stickers.at(i).width()


        int StickerSheet::setStickerAtLayer(Image & sticker, unsigned layer, int x, int y) {
            if (layer < max_) {
                num_stickers.at(layer) = (&sticker);
                xcoordinate.at(layer) = x;
                ycoordinate.at(layer) = y;
                return layer;
            }
                return -1;
        }

        
        bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
            if (num_stickers.at(index) != nullptr || num_stickers.size() <= index) {
                xcoordinate.at(index) = x;
                ycoordinate.at(index) = y;
                return true;
            }
            return false;
        
        }