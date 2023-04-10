#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>

void Image::lighten(){
  for (unsigned y = 0; y < this->height(); y++) {
    for (unsigned x = 0; x < this->width(); x++) {
      cs225::HSLAPixel& current_pixel = this->getPixel(x, y);

      if(current_pixel.l <= 0.9){
        current_pixel.l = current_pixel.l + 0.1;
      } else {
        current_pixel.l = 1.0;
      }
    }
  }
}

void Image::lighten(double amount){
  for (unsigned y = 0; y < this->height(); y++) {
    for (unsigned x = 0; x < this->width(); x++) {
      cs225::HSLAPixel& current_pixel = this->getPixel(x, y);

      current_pixel.l = current_pixel.l + amount;
      if(current_pixel.l >= 1){
        current_pixel.l = 1;
      }
    }
  }
}

void Image::darken(){
  for (unsigned y = 0; y < this->height(); y++) {
    for (unsigned x = 0; x < this->width(); x++) {
      cs225::HSLAPixel& current_pixel = this->getPixel(x, y);

      current_pixel.l = current_pixel.l - 0.1;
      if(current_pixel.l <= 0){
        current_pixel.l = 0;
      }
    }
  }
}

void Image::darken(double amount){
  for (unsigned y = 0; y < this->height(); y++) {
    for (unsigned x = 0; x < this->width(); x++) {
      cs225::HSLAPixel& current_pixel = this->getPixel(x, y);

      //Darken an image by a certain 'amount'
      current_pixel.l = current_pixel.l - amount;
      if(current_pixel.l <= 0){
        current_pixel.l = 0;
      }
    }
  }
}

void Image::saturate(){
  for (unsigned y = 0; y < this->height(); y++) {
    for (unsigned x = 0; x < this->width(); x++) {
      cs225::HSLAPixel& current_pixel = this->getPixel(x, y);

      current_pixel.s = current_pixel.s + 0.1;
      if(current_pixel.s >= 1){
        current_pixel.s = 1;
      }
    }
  }
}

void Image::saturate(double amount){
  for (unsigned y = 0; y < this->height(); y++) {
    for (unsigned x = 0; x < this->width(); x++) {
      cs225::HSLAPixel& current_pixel = this->getPixel(x, y);

      //Saturate an image by a certain 'amount'
      current_pixel.s = current_pixel.s + amount;
      if(current_pixel.s >= 1){
        current_pixel.s = 1;
      }
    }
  }
}

void Image::desaturate(){
  for (unsigned y = 0; y < this->height(); y++) {
    for (unsigned x = 0; x < this->width(); x++) {
      cs225::HSLAPixel& current_pixel = this->getPixel(x, y);

      current_pixel.s = current_pixel.s - 0.1;
      if(current_pixel.s <= 0){
        current_pixel.s = 0;
      }
    }
  }
}

void Image::desaturate(double amount){
  for (unsigned y = 0; y < this->height(); y++) {
    for (unsigned x = 0; x < this->width(); x++) {
      cs225::HSLAPixel& current_pixel = this->getPixel(x, y);

      current_pixel.s = current_pixel.s - amount;
      if(current_pixel.s <= 0){
        current_pixel.s = 0;
      }
    }
  }
}

void Image::grayscale(){
  for (unsigned y = 0; y < this->height(); y++) {
    for (unsigned x = 0; x < this->width(); x++) {
      cs225::HSLAPixel& current_pixel = this->getPixel(x, y);

      current_pixel.s = 0;
    }
  }
}

void Image::rotateColor(double degrees){
  for (unsigned y = 0; y < this->height(); y++) {
    for (unsigned x = 0; x < this->width(); x++) {
      cs225::HSLAPixel& current_pixel = this->getPixel(x, y);

      current_pixel.h = current_pixel.h + degrees;
      if (current_pixel.h <= 0){
        current_pixel.h = 360 - std::abs(current_pixel.h);
      } else if(current_pixel.h >= 360){
        current_pixel.h = current_pixel.h - 360;
      }
    }
  }
}

void Image::illinify(){
  for (unsigned y = 0; y < this->height(); y++) {
    for (unsigned x = 0; x < this->width(); x++) {
      cs225::HSLAPixel& current_pixel = this->getPixel(x, y);

      if (current_pixel.h <= 135 || 315 <= current_pixel.h) {
        current_pixel.h = 11;
      } else{
        current_pixel.h = 216;
      }
    }
  }
}

void Image::scale(double factor) {
  unsigned newWidth = this->width() * factor;
  unsigned newHeight = this->height() * factor;

  if (factor >= 1){
    this->resize(newWidth, newHeight);
    for (unsigned y = newHeight - 1; y != (unsigned) - 1; y--) {
      for (unsigned x = newWidth - 1; x != (unsigned) - 1; x--) {
        cs225::HSLAPixel& pixel_one = this->getPixel(x, y);
        cs225::HSLAPixel& pixel_two = this->getPixel((unsigned) (double) x / factor, (unsigned) (double) y / factor);
        pixel_one.h = pixel_two.h;
        pixel_one.s = pixel_two.s;
        pixel_one.l = pixel_two.l;
        pixel_one.a = pixel_two.a;
      }
    }
  } else {
    for (unsigned y = 0; y < newHeight; y++) {
      for (unsigned x = 0; x < newWidth; x++) {
        cs225::HSLAPixel& pixel_one = this->getPixel((unsigned) (double) x / factor, (unsigned) (double) y / factor);
        cs225::HSLAPixel& pixel_two = this->getPixel(x, y);
        pixel_two.h = pixel_one.h;
        pixel_two.s = pixel_one.s;
        pixel_two.l = pixel_one.l;
        pixel_two.a = pixel_one.a;
      }
    }

    this->resize(newWidth, newHeight);
  }
}

void Image::scale(unsigned w, unsigned h){

  double y = (double) h / (double) this->height();
  double x = (double) w / (double) this->width();

  if(x > y){
    scale(y);
  }
  else{
    scale(x);
  }
}