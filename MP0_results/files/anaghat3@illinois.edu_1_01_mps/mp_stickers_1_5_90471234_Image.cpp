#include "../lib/cs225/PNG.h"
#include "Image.h"
#include <cmath>
#include <iostream>
using namespace cs225;

// Image::Image () {
//     //Creates an empty Image. More...
//     PNG();
    
// }

    //Creates an Image of the specified dimensions. More...
// Image::Image (unsigned int width, unsigned int height) {
//     PNG(width, height);
// }

    //Lighten an Image by increasing the luminance of every pixel by 0.1. More...
void Image::lighten () {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            if (getPixel(w, h).l + 0.1 <= 1) {
                getPixel(w,h).l += 0.1;
            } else {
                getPixel(w,h).l = 1;
            }
            if (getPixel(w,h).l >= 0.95) {
                getPixel(w,h).l = 1;
            }
        }
    }
}

    //Lighten an Image by increasing the luminance of every pixel by amount. More...
void Image::lighten (double amount) {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            if ((getPixel(w, h).l + amount) <= 1) {
                getPixel(w,h).l += amount;
            } else {
                getPixel(w,h).l = 1;
            }
            if (getPixel(w,h).l >= 0.95) {
                getPixel(w,h).l = 1;
            }
        }
    }
}

    //Darken an Image by decreasing the luminance of every pixel by 0.1. More...
void Image::darken () {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            if (getPixel(w, h).l - 0.1 >= 0) {
                getPixel(w,h).l -= 0.1;
            } else {
                getPixel(w,h).l = 0;
            }
            if (getPixel(w,h).l <= 0.05) {
                getPixel(w,h).l = 0;
            }
        }
    }
    
}

    //Darkens an Image by decreasing the luminance of every pixel by amount. More...
void Image::darken (double amount) {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            if ((getPixel(w, h).l - amount) >= 0.0) {
                getPixel(w,h).l -= amount;
            } else {
                getPixel(w,h).l = 0;
            }
            if (getPixel(w,h).l <= 0.05) {
                getPixel(w,h).l = 0;
            }
        }
    }
}

    //Saturates an Image by increasing the saturation of every pixel by 0.1. More...
void Image::saturate () {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            if ((getPixel(w, h).s + 0.1) <= 1) {
                getPixel(w,h).s += 0.1;
            }
        }
    }
}

    //Saturates an Image by increasing the saturation of every pixel by amount. More...
void Image::saturate (double amount) {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            if ((getPixel(w, h).s + amount) <= 1) {
                getPixel(w,h).s += amount;
            }
        }
    }
}

    //Desaturates an Image by decreasing the saturation of every pixel by 0.1. More...
void Image::desaturate () {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            if ((getPixel(w, h).l - 0.1) >= 0) {
                getPixel(w,h).l -= 0.1;
            }
        }
    }
}

    //Desaturates an Image by decreasing the saturation of every pixel by amount. More...
void Image::desaturate (double amount) {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            if ((getPixel(w, h).l - amount) >= 0) {
                getPixel(w,h).l -= amount;
            }
        }
    }
}

    //Turns the image grayscale. More...
void Image::grayscale () {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            getPixel(w, h).s = 0;
        }
    }
}

    //Rotates the color wheel by degrees. More...
void Image::rotateColor (double degrees) {
    if (degrees == 0) {
        return;
    }
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            if (degrees > 0) {
                getPixel(w, h).h = fmod((getPixel(w, h).h + degrees), 360);
            } else {
                getPixel(w, h).h = 360 - (-1 * fmod(getPixel(w, h).h + degrees, 360));
                //getPixel(w, h).h = fmod(((getPixel(w, h).h + degrees) + 360), 360);
            }
            
        }
    }

}

    //Illinify the image. More...
void Image::illinify () {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            //orange = 11, blue = 216
            //if hue closer to or    
            if ((std::abs(getPixel(w, h).h - 11)) < std::abs(getPixel(w,h).h - 216)) {
                getPixel(w,h).h = 11;
            } else {
                getPixel(w,h).h = 216;
            }
        }
    }
}

    //Scale the Image by a given factor. More...
void Image::scale (double factor) {
    if (factor == 1.0) {
        return;
    }
    Image im2 = Image(*this); 
    resize(width() * factor, height() * factor);
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            HSLAPixel& scaledPixel = im2.getPixel(w/factor, h/factor);
            HSLAPixel& currPixel = this->getPixel(w, h);
            currPixel = scaledPixel;
        }
    }
}


    //Scales the image to fit within the size (w x h). More...
void Image::scale (unsigned w, unsigned h) {
    //if width bigger than argument
    /*
    a) keep the aspect ratio
    b) resultant image should have either, or both, of the input w/h
    c) resultant image should never be larger than the input parameters
    */
    double ratio = 0;
    if ((w * 1.0)/width() > (h * 1.0)/height()) {
        ratio = (h * 1.0)/height();
    } else { 
        ratio = (w * 1.0)/width();
    }
    scale(ratio);

}