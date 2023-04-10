#include <cmath>
#include "Image.h"

using namespace cs225;

void Image::lighten() {
    for (unsigned w = 0; w < width(); w++) {
        for (unsigned h = 0; h < height(); h++) {
            HSLAPixel& pixel = getPixel(w, h);
            pixel.l += 0.1;
            if (pixel.l > 1.0) pixel.l = 1.0;      // ensures that the luminance remains in the range [0, 1]
        }
    }
}
        
void Image::lighten(double amount) {
    for (unsigned w = 0; w < width(); w++) {
        for (unsigned h = 0; h < height(); h++) {
            HSLAPixel& pixel = getPixel(w, h);
            pixel.l += amount;
            if (pixel.l > 1.0) pixel.l = 1.0;       // ensures that the luminance remains in the range [0, 1]
        }
    }
}
       
void Image::darken() {
    for (unsigned w = 0; w < width(); w++) {
        for (unsigned h = 0; h < height(); h++) {
            HSLAPixel& pixel = getPixel(w, h);
            pixel.l -= 0.1;
            if (pixel.l < 0) pixel.l = 0.0;        // ensures that the luminance remains in the range [0, 1]
        }
    }
}
       
void Image::darken(double amount) {
    for (unsigned w = 0; w < width(); w++) {
        for (unsigned h = 0; h < height(); h++) {
            HSLAPixel& pixel = getPixel(w, h);
            pixel.l -= amount;
            if (pixel.l < 0) pixel.l = 0.0;        // ensures that the luminance remains in the range [0, 1]
        }
    }
}
        
void Image::saturate() {
    for (unsigned w = 0; w < width(); w++) {
        for (unsigned h = 0; h < height(); h++) {
            HSLAPixel& pixel = getPixel(w, h);
            pixel.s += 0.1;
            if (pixel.s > 1.0) pixel.s = 1.0;      // ensures that the saturation remains in the range [0, 1]
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned w = 0; w < width(); w++) {
        for (unsigned h = 0; h < height(); h++) {
            HSLAPixel& pixel = getPixel(w, h);
            pixel.s += amount;
            if (pixel.s > 1.0) pixel.s = 1.0;      // ensures that the saturation remains in the range [0, 1]
        }
    }
}
        
void Image::desaturate() {
    for (unsigned w = 0; w < width(); w++) {
        for (unsigned h = 0; h < height(); h++) {
            HSLAPixel& pixel = getPixel(w, h);
            pixel.s -= 0.1;
            if (pixel.s < 0) pixel.s = 0.0;        // ensures that the saturation remains in the range [0, 1]
        }
    }
}
        
void Image::desaturate(double amount) {
    for (unsigned w = 0; w < width(); w++) {
        for (unsigned h = 0; h < height(); h++) {
            HSLAPixel& pixel = getPixel(w, h);
            pixel.s -= amount;
            if (pixel.s < 0) pixel.s = 0.0;        // ensures that the saturation remains in the range [0, 1]
        }
    }
}
        
void Image::grayscale() {
    for (unsigned w = 0; w < width(); w++) {
        for (unsigned h = 0; h < height(); h++) {
            HSLAPixel& pixel = getPixel(w, h);
            pixel.s = 0.0;
        }
    }
}
        
void Image::rotateColor(double degrees) {
    for (unsigned w = 0; w < width(); w++) {
        for (unsigned h = 0; h < height(); h++) {
            HSLAPixel& pixel = getPixel(w, h);
            pixel.h += degrees;
            // ensures that the hue remains in the range [0, 360]
            while (pixel.h > 360) {
                pixel.h -= 360.0;
            }
            while (pixel.h < 0) {
                pixel.h += 360.0;
            }
            // 300 + 90 = 390 == 30 = (390 - 360)
            // 90 + (-150) = 300 == -60 = (360 - 60)
        }
    }
}
        
void Image::illinify() {
    for (unsigned w = 0; w < width(); w++) {
        for (unsigned h = 0; h < height(); h++) {
            HSLAPixel& pixel = getPixel(w, h);
            if ((pixel.h >= 113.5) && (pixel.h <= 293.5)) {
                pixel.h = 216;
            } else {
                pixel.h = 11;
            }
        }
    }
}
        
void Image::scale(double factor) {
    if (factor != 1) {
        Image original = Image(*this);                  // store copy of original image

        unsigned originalWidth = width();
        unsigned originalHeight = height();
        unsigned newWidth = width() * factor;       // determine new image width by multiplying with resizing factor
        unsigned newHeight = height() * factor;     // determine new image height by multiplying with resizing factor

        resize(newWidth, newHeight);                      // resize image to new dimensions

        for (unsigned w = 0; w < newWidth; w++) {
            for (unsigned h = 0; h < newHeight; h++) {
                HSLAPixel& newPixel = getPixel(w, h);
                HSLAPixel& originalPixelScaled = original.getPixel((w * originalWidth / newWidth), (h * originalHeight / newHeight)); // attempt at scaling
                newPixel = originalPixelScaled;
            }
        }
    }
}
        
void Image::scale(unsigned w, unsigned h) {
    double wid = ((double)(w)) / (width());
    double hei = ((double)(h)) / (height());

    if (hei >= wid) {
        scale(hei);
    }
    else {
        scale(wid);
    }
}