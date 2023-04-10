#include "Image.h"
#include <iostream>
#include "cs225/HSLAPixel.h"
using namespace std;
using namespace cs225;


void Image::lighten() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & pixel = getPixel(i, j);
            if (pixel.l <= 1.0) {
                pixel.l += 0.1;
            }
            if (pixel.l < 0.0) {
                pixel.l = 0.0;
            }
            if (pixel.l > 1.0) {
                pixel.l = 1.0;
            }
        }
    }
}
void Image::lighten(double amount) {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & pixel = getPixel(i, j);
            pixel.l += amount;
            if (pixel.l > 1.0) {
                pixel.l = 1.0;
            }
            if (pixel.l < 0.0) {
                pixel.l = 0.0;
            }
        }
    }
}
void Image::darken() {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & pixel = getPixel(i, j);
            if (pixel.l >= 0.1 && pixel.l <= 1.1) {
                pixel.l -= 0.1;
            } else {
                if (pixel.l < 0.1) {
                    pixel.l = 0.0;
                }
                if (pixel.l > 1.1) {
                    pixel.l = 1.0;
                }
            }
        }
    }
}
void Image::darken(double amount) {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & pixel = getPixel(i, j);
            pixel.l -= amount;
            if (pixel.l < 0.0) {
                pixel.l = 0.0;
            }
            if (pixel.l > 1.0) {
                pixel.l = 1.0;
            }
        }
    }
}
void Image::saturate() {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & pixel = getPixel(i, j);
            
            if (pixel.s <= 1.0) {
                pixel.s += 0.1;
            }
            if (pixel.s < 0.0) {
                pixel.s = 0.0;
            }
            if (pixel.s > 1.0) {
                pixel.s = 1.0;
            }
        }
    }
}
void Image::saturate(double amount) {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & pixel = getPixel(i, j);
            pixel.s += amount;
            if (pixel.s > 1.0) {
                pixel.s = 1.0;
            }
            if (pixel.s < 0.0) {
                pixel.s = 0.0;
            }
        }
    }
}
void Image::desaturate() {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & pixel = getPixel(i, j);
            if (pixel.s >= 0.1 && pixel.s <= 1.1) {
                pixel.s -= 0.1;
            } else {
                if (pixel.s < 0.1) {
                    pixel.s = 0.0;
                }
                if (pixel.s > 1.1) {
                    pixel.s = 1.0;
                }
            }
        }
    }
}
void Image::desaturate(double amount) {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & pixel = getPixel(i, j);
            pixel.s -= amount;
            if (pixel.s < 0.0) {
                pixel.s = 0.0;
            }
            if (pixel.s > 1.0) {
                pixel.s = 1.0;
            }
        }
    }
}
void Image::grayscale() {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & pixel = getPixel(i, j);
            pixel.s = 0;
        }
    }
}
void Image::rotateColor(double degrees) {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & pixel = getPixel(i, j);
            pixel.h += degrees;
            if (pixel.h > 360) {
                while (pixel.h > 360) {
                    pixel.h -=360;
                }
            } else if (pixel.h < 0) {
                while (pixel.h < 0) {
                    pixel.h += 360;
                }
            }
        }
    }
}
void Image::illinify() {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & pixel = getPixel(i, j);
            if (pixel.h >= 114 && pixel.h <= 243) {
                pixel.h = 216;
            } else {
                pixel.h = 11;
            }
        }
    }
}
void Image::scale(double factor) {
unsigned newWidth = (width() * factor);
unsigned newHeight = (height() * factor);

Image copy(*this);
resize(newWidth, newHeight);

double inverse = 1.0 / factor;
unsigned i = 0;
while (i < newWidth) {
  unsigned j = 0;
  while (j < newHeight) {
    HSLAPixel curr_copy = copy.getPixel(i * inverse, j * inverse);
    HSLAPixel & curr = getPixel(i, j);
    curr = curr_copy;
    j++;
  }
  i++;
}
}
void Image::scale(unsigned w, unsigned h) {
    double newWidth = (double)w / (double)width();
    double newHeight = (double)h / (double)height();
    if (newHeight < newWidth) {
        scale(newHeight);
    }  else {
        scale(newWidth);
    }
}
