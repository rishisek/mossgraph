#include "Image.h"
#include <iostream>
#include "cs225/HSLAPixel.h"



    void Image::lighten() {
        for (unsigned int i = 0; i < width(); i++) {
            for (unsigned int j = 0; j < height(); j++) {
                // check if the range is between [0,1]
                    cs225::HSLAPixel & pointer = getPixel(i, j);
                    if (pointer.l + 0.1 <= 1.0) {
                        pointer.l += 0.1;
                    } else {
                        pointer.l = 1.0;
                    }
                    //use max function and compare 
                 // make sure pointer is being used correctly here
                //look up how to derefernce a pointer and make sure this is being done correctly
            }
        }
    }

    // void Image::lighten() {}
    // void Image::lighten(double amount) {}
    // void Image::darken() {}
    // void Image::darken(double amount) {}
    // void Image::saturate() {}
    // void Image::saturate(double amount) {}
    // void Image::desaturate() {}
    // void Image::desaturate(double amount) {}
    // void Image::grayscale() {}
    // void Image::rotateColor(double degrees) {}
    // void Image::illinify() {}
    // void Image::scale(double factor) {}
    // void Image::scale(unsigned w, unsigned h) {}

    void Image::lighten(double amount) {
        for (unsigned int i = 0; i < width(); i++) {
            for (unsigned int j = 0; j < height(); j++) {
                cs225::HSLAPixel & pointer = getPixel(i, j);
                if (pointer.l + amount <= 1.0) {
                    pointer.l += amount;
                } else {
                    pointer.l = 1.0;
                }
            }
        }
    }
    void Image::darken() {
        for (unsigned int i = 0; i < width(); i++) {
            for (unsigned int j = 0; j < height(); j++) {
                cs225::HSLAPixel & pointer = getPixel(i, j);
                if (pointer.l - 0.1 >= 0) {
                    pointer.l -= 0.1;
                } else {
                    pointer.l = 0;
                }
            }
        }
    }


    void Image::darken(double amount) {
        for (unsigned int i = 0; i < width(); i++) {
            for (unsigned int j = 0; j < height(); j++) {
                cs225::HSLAPixel & pointer = getPixel(i, j);
                if (pointer.l - amount >= 0) {
                    pointer.l -= amount;
                } else {
                    pointer.l = 0;
                }
            }
        }

    }
    void Image::saturate() {
        for (unsigned int i = 0; i < width(); i++) {
            for (unsigned int j = 0; j < height(); j++) {
                cs225::HSLAPixel & pointer = getPixel(i, j);
                if (pointer.s + 0.1 <= 1.0) {
                    pointer.s += 0.1;
                } else {
                    pointer.s = 1.0;
                }
            }
        }

    }
    void Image::saturate(double amount) {
         for (unsigned int i = 0; i < width(); i++) {
            for (unsigned int j = 0; j < height(); j++) {
                cs225::HSLAPixel & pointer = getPixel(i, j);
                if (pointer.s + amount <= 1) {
                    pointer.s += amount;
                } else {
                    pointer.s = 1.0;
                }
            }
        }

    }
    void Image::desaturate() {
        for (unsigned int i = 0; i < width(); i++) {
            for (unsigned int j = 0; j < height(); j++) {
                cs225::HSLAPixel & pointer = getPixel(i, j);
                if (pointer.s - 0.1 >= 0) {
                    pointer.s -= 0.1;
                } else {
                    pointer.s = 0;
                }
            }
        }
    }
    void Image::desaturate(double amount) {
        for (unsigned int i = 0; i < width(); i++) {
            for (unsigned int j = 0; j < height(); j++) {
                cs225::HSLAPixel & pointer = getPixel(i, j);
                if (pointer.s - amount >= 0) {
                    pointer.s -= amount;
                } else {
                    pointer.s = 0; 
                }
            }
        }

    }
    void Image::grayscale() {
        for (unsigned int i = 0; i < width(); i++) {
            for (unsigned int j = 0; j < height(); j++) {
                cs225::HSLAPixel & pointer = getPixel(i, j);
                pointer.s = 0.0;
            }
        }

    }
    void Image::rotateColor(double degrees) {
        for (unsigned int i = 0; i < width(); i++) {
            for (unsigned int j = 0; j < height(); j++) {
                cs225::HSLAPixel & pointer = getPixel(i, j);
                pointer.h += degrees;
                while (pointer.h > 360) {
                    pointer.h -= 360;
                }
                  while (pointer.h < 0) {
                    pointer.h += 360;
                }
            }
        }

 
    }
    void Image::illinify() {
          for (unsigned int i = 0; i < width(); i++) {
            for (unsigned int j = 0; j < height(); j++) {
                cs225::HSLAPixel & pointer = getPixel(i, j);
                if (pointer.h < 360 && pointer.h > 0) {
                    pointer.h = 11;
                }
            }
        }
    }

    void Image::scale(double factor) {
        // PNG::copy() 
        
        PNG copied = *this;
        this->resize(width() * factor, height() * factor);

        for (unsigned int i = 0; i < width(); i++) {
            for (unsigned int j = 0; j < height(); j++) {
                //figure out how to access the original array 
                this->getPixel(i,j) = copied.getPixel(i/factor, j/factor);

            }
        }
        //copy the original image using copy constructor
        //resize the current image -> nested for loop{
        }
        // iterate thru resize and map coordinates using factor division.

    
    void Image::scale(unsigned w, unsigned h) {

        double wfactor = (double) w / width();
        double hfactor = (double) h / height();
        if (wfactor < hfactor) {
            scale(wfactor);
        } else {
            scale(hfactor);
        }
    }

    