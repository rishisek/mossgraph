#include "Image.h"
#include "cs225/HSLAPixel.h"

using namespace cs225; 

void Image::lighten() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel & pix = getPixel(i, j);
            pix.l += 0.1;
            if (pix.l > 1) {
                pix.l = 1;
            }
            if (pix.l < 0) {
                pix.l = 0;
            }
        }
    }
}

void Image::lighten(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &pix = getPixel(i, j);
            pix.l += amount;
            if (pix.l > 1) {
                pix.l = 1;
            }
            if (pix.l < 0) {
                pix.l = 0;
            }
        }
    }
}

void Image::darken() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &pix = getPixel(i, j);
            pix.l -= 0.1;
            if (pix.l > 1) {
                pix.l = 1;
            }
            if (pix.l < 0) {
                pix.l = 0;
            }
        }
    }
}

void Image::darken(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &pix = getPixel(i, j);
            pix.l -= amount;
            if (pix.l > 1) {
                pix.l = 1;
            }
            if (pix.l < 0) {
                pix.l = 0;
            }
        }
    }
}

void Image::saturate() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &pix = getPixel(i, j);
            pix.s += 0.1;
            if (pix.s > 1) {
                pix.s = 1;
            }
            if (pix.s < 0) {
                pix.s = 0;
            }
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &pix = getPixel(i, j);
            pix.s += amount;
            if (pix.s > 1) {
                pix.s = 1;
            }
            if (pix.s < 0) {
                pix.s = 0;
            }
        }
    }
}

void Image::desaturate() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &pix = getPixel(i, j);
            pix.s -= 0.1;
            if (pix.s > 1) {
                pix.s = 1;
            }
            if (pix.s < 0) {
                pix.s = 0;
            }
        }
    }
}

void Image::desaturate(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &pix = getPixel(i, j);
            pix.s -= amount;
            if (pix.s > 1) {
                pix.s = 1;
            }
            if (pix.s < 0) {
                pix.s = 0;
            }
        }
    }
}

void Image::grayscale() { //saturation makes gray
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &pix = getPixel(i, j);
            pix.s = 0;
        }
    }
}

void Image::rotateColor(double degrees) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &pix = getPixel(i, j);
            // while (degrees > 360) {
            //     degrees -= 360;
            // } 
            // while (degrees < 0) {
            //     degrees += 360;
            // }
            pix.h += degrees;
            while (pix.h > 360) {
                pix.h -= 360;
            }
            while (pix.h < 0) {
                pix.h += 360;
            }
        }
    }
}

void Image::illinify() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            HSLAPixel &pix = getPixel(i, j);
            int orange = int(11 - pix.h);
            int blue = int(216 - pix.h);
            if (abs(orange) < abs(blue)) {
                pix.h = 11;
            } else {
                pix.h = 216;
            }
        }
    }
}

void Image::scale(double factor) {
    unsigned int nwid = (unsigned int)(this -> width() * factor);
    unsigned int nheight = (unsigned int)(this -> height() * factor);
    
    Image oldimage = (*this);
    this -> resize(nwid, nheight);
    for (unsigned int i = 0; i < nwid; i++) {
        for (unsigned int j = 0; j < nheight; j++) {
            HSLAPixel &tocopy = oldimage.getPixel((int)i/factor, (int)j/factor);
            this -> getPixel(i, j) = tocopy;
            // HSLAPixel &newpix = newimage -> getPixel(i/factor, j/factor);
        }
    }
    
}

void Image::scale(unsigned w, unsigned h) {
    double scalew = (double) w / width();
    double scaleh = (double) h / height();
    if (scalew < scaleh) {
        scale(scalew);
    } else {
        scale(scaleh);
    }
}




   