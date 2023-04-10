#include "Image.h"
#include <iostream>
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
using namespace cs225;



Image::Image() {
}


Image::Image (unsigned int width, unsigned int height) : PNG(width, height) {}

void Image::lighten() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & current_pixel_loc = getPixel(i,j);
            if (current_pixel_loc.l <= 1) {
                current_pixel_loc.l += 0.1;
                }
                if (current_pixel_loc.l > 1) {
                current_pixel_loc.l = 1; 
            }
        }
    }
}


void Image::lighten(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &current_pixel_loc = getPixel(i,j);
            if (current_pixel_loc.l <= 1) {
                current_pixel_loc.l += amount;
            }
            if (current_pixel_loc.l > 1) {
                current_pixel_loc.l = 1; 
            }
        }
    }

}



void Image::darken() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & current_pixel_loc = getPixel(i,j);
            if (current_pixel_loc.l <= 1) {
                current_pixel_loc.l -= 0.1;
                }
            if (current_pixel_loc.l < 0) {
                current_pixel_loc.l = 0; 
            }
        }
    }
}



void Image::darken(double amount) {
    // check if amount is between 0-1
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &current_pixel_loc = getPixel(i,j);
            if (current_pixel_loc.l <= 1) {
                current_pixel_loc.l -= amount;
            }
            if (current_pixel_loc.l < 0) {
                current_pixel_loc.l = 0; 
            }
        }
    }
}


void Image::saturate() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &current_pixel_loc = getPixel(i,j);
            if (current_pixel_loc.s <= 1) {
                current_pixel_loc.s += 0.1;
            }
            if (current_pixel_loc.s > 1) {
                current_pixel_loc.s = 1; 
            }
        }
    }

}


void Image::saturate(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &current_pixel_loc = getPixel(i,j);
            if (current_pixel_loc.s <= 1) {
                current_pixel_loc.s += amount;
            }
            if (current_pixel_loc.s > 1) {
                current_pixel_loc.s = 1; 
            }
        }
    }

}


void Image::desaturate() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &current_pixel_loc = getPixel(i,j);
            if (current_pixel_loc.s <= 1) {
                current_pixel_loc.s -= 1;
            }
            if (current_pixel_loc.s < 0) {
                current_pixel_loc.s = 0; 
            }
        }
    }
}


void Image::desaturate(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &current_pixel_loc = getPixel(i,j);
            if (current_pixel_loc.s <= 1) {
                current_pixel_loc.s -= amount;
            }
            if (current_pixel_loc.s < 0) {
                current_pixel_loc.s = 0; 
            }
        }
    }
}


void Image::grayscale() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &current_pixel_loc = getPixel(i,j);
            current_pixel_loc.s = 0;
        }
    }
}


void Image::rotateColor(double degrees) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &current_pixel_loc = getPixel(i,j);
            current_pixel_loc.h += degrees;
            // when adding makes degree larger than 360, subtract to go back 360 to spot
            while (current_pixel_loc.h > 360) {
                current_pixel_loc.h -= 360;
            }
            // if negative, add 360 to get to positive spot
            while (current_pixel_loc.h < 0) {
                current_pixel_loc.h += 360;
            }
        }
    }

}

// “Illini Orange” has a hue of 11 (degree of 11, 317) 
// if closer to orange, make orange
// “Illini Blue” has a hue of 216 (degree of 216, 576)
// if closer to blue, make blue
void Image::illinify() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &current_pixel_loc = getPixel(i,j);
            current_pixel_loc.h = 11; // orange
            if (current_pixel_loc.h > 11) {
                current_pixel_loc.h = 216; // blue
            }
        }
    }

}

// create copy = new PNG that has factor, this
void Image::scale(double factor) {
    unsigned int new_width = width() * factor;
    unsigned int new_height = height() * factor;
    // 
    Image new_img(*this); // empty image with scaled factor, do i delete at end?
    resize(new_width, new_height);

    //contents
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &current_pixel_loc = getPixel(i,j);
            current_pixel_loc = new_img.getPixel(i/factor,j/factor);
        }
    }
 }

// ex. (10, 20) --> (100, 100) -----> (10, 50)
void Image::scale (unsigned w, unsigned h) {
    double newW = (((double)w / width())); // 100 / 10
    double newH = (((double)h / height())); // 100 / 20
    double scale_input = std::min(newW, newH);
    // use previous scale function
    scale(scale_input);
}