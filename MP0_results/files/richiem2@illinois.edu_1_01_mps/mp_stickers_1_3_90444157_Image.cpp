#include <string>
using std::string;

#include "Image.h"

//namespace cs225 {
            Image::Image(): PNG(){
            }
            Image::Image(unsigned int width, unsigned int height): PNG(width, height) {
            }

            void Image::darken(){
                for (unsigned int i = 0; i < this->width(); i++) {
                    for (unsigned int j = 0; j < this->height(); j++) {
                        cs225::HSLAPixel& tmp = this->getPixel(i, j);
                        if (tmp.l - 0.1 < 0) {
                            tmp.l = 0;
                        } else {
                            tmp.l = tmp.l - 0.1;
                        }
                    }
                }
            }
            void Image::darken(double amount){
                for (unsigned int i = 0; i < this->width(); i++) {
                    for (unsigned int j = 0; j < this->height(); j++) {
                        cs225::HSLAPixel& tmp = this->getPixel(i, j);
                        if (tmp.l - amount < 0) {
                            tmp.l = 0;
                        } else if (tmp.l - amount > 1.0) {
                            tmp.l = 1.0;
                        } else {
                            tmp.l = tmp.l - amount;
                        }
                    }
                }
            }
            
            void Image::desaturate(){
                for (unsigned int i = 0; i < this->width(); i++) {
                    for (unsigned int j = 0; j < this->height(); j++) {
                        cs225::HSLAPixel& tmp = this->getPixel(i, j);
                        if (tmp.s - 0.1 < 0) {
                            tmp.s = 0;
                        } else {
                            tmp.s = tmp.s - 0.1;
                        }
                    }
                }                
            }
            void Image::desaturate(double amount){
                for (unsigned int i = 0; i < this->width(); i++) {
                    for (unsigned int j = 0; j < this->height(); j++) {
                        cs225::HSLAPixel& tmp = this->getPixel(i, j);
                        if (tmp.s - amount < 0) {
                            tmp.s = 0;
                        } else if (tmp.s - amount > 1.0) {
                            tmp.s = 1.0;
                        } else {
                            tmp.s = tmp.s - amount;
                        }
                    }
                }                
            }
            
            void Image::grayscale(){
                for (unsigned int i = 0; i < this->width(); i++) {
                    for (unsigned int j = 0; j < this->height(); j++) {
                    cs225::HSLAPixel& tmp = this->getPixel(i, j);
                        tmp.s = 0;
                    }
                }                
            }
            
            void Image::illinify(){
                for (unsigned int i = 0; i < this->width(); i++) {
                    for (unsigned int j = 0; j < this->height(); j++) {
                        cs225::HSLAPixel& tmp = this->getPixel(i, j);
                        if (tmp.h >= 113.5 && tmp.h < 293.5) {
                            tmp.h = 216;
                        } else {
                            tmp.h = 11;
                        }
                    }
                }
            }

            void Image::lighten(){
                for (unsigned int i = 0; i < this->width(); i++) {
                    for (unsigned int j = 0; j < this->height(); j++) {
                        cs225::HSLAPixel& tmp = this->getPixel(i, j);
                        if (tmp.l + 0.1 > 1.0) {
                            tmp.l = 1.0;
                        } else {
                            tmp.l = tmp.l + 0.1;
                        }
                    }
                }
            }
            void Image::lighten(double amount){
                for (unsigned int i = 0; i < this->width(); i++) {
                    for (unsigned int j = 0; j < this->height(); j++) {
                        cs225::HSLAPixel& tmp = this->getPixel(i, j);
                        if (tmp.l + amount > 1.0) {
                            tmp.h = 1.0;
                        } else if (tmp.l + amount < 0.0) {
                            tmp.h = 0.0;
                        } else {
                            tmp.l = tmp.l + amount;
                        }
                    }
                }
            }

            void Image::rotateColor(double degrees){
                for (unsigned int i = 0; i < this->width(); i++) {
                    for (unsigned int j = 0; j < this->height(); j++) {
                        cs225::HSLAPixel& tmp = this->getPixel(i , j);
                        tmp.h = tmp.h + degrees;
                        while (tmp.h > 360.0) {
                            tmp.h = tmp.h - 360.0;
                        }
                        while (tmp.h < 0.0) {
                            tmp.h = tmp.h + 360.0;
                        }
                    }
                }
            }

            void Image::saturate(){
                for (unsigned int i = 0; i < this->width(); i++) {
                    for (unsigned int j = 0; j < this->height(); j++) {
                        cs225::HSLAPixel& tmp = this->getPixel(i, j);
                        if (tmp.s + 0.1 > 1.0) {
                            tmp.s = 1.0;
                        } else {
                            tmp.s = tmp.s + 0.1;
                        }
                    }
                }
            }
            void Image::saturate(double amount){
                for (unsigned int i = 0; i < this->width(); i++) {
                    for (unsigned int j = 0; j < this->height(); j++) {
                        cs225::HSLAPixel& tmp = this->getPixel(i, j);
                        if (tmp.s + amount > 1.0) {
                            tmp.s = 1.0;
                        } else if (tmp.s + amount < 0.0) {
                            tmp.s = 0.0;
                        } else {
                            tmp.s = tmp.s + amount;
                        }
                    }
                }
            }

            void Image::scale(double factor){
                unsigned int newX = this->width() * factor;
                unsigned int newY = this->height() * factor;
                Image* newCopy = new Image();
                *newCopy = *this;
                this->resize(newX, newY);
                
                for (unsigned int i = 0; i < this->width(); i++) {
                    for (unsigned int j = 0; j < this->height(); j++) {
                        cs225::HSLAPixel& tmp = this->getPixel(i, j);
                        cs225::HSLAPixel& toCopy = newCopy->getPixel(i / factor, j / factor);
                        tmp = toCopy;
                    }
                }
                delete newCopy;
            }
            
            void Image::scale(unsigned w, unsigned h){

                double wFac = double(w) / double(this->width());
                double hFac = double(h) / double(this->height());

                if (wFac  < hFac) {
                    scale(wFac);
                } else {
                    scale(hFac);
                }
            }
