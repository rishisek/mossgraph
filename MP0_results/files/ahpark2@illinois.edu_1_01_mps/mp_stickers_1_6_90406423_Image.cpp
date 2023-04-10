#include <Image.h>
#include <cmath>
using namespace cs225;

Image::Image() {
}
Image::Image(unsigned int width, unsigned int height) {
    width_ = width;
    height_ = height;
}
void Image::lighten() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            HSLAPixel *pixel = &getPixel(x,y); 
            pixel->l += 0.1;
            if (pixel->l > 1) {
                pixel->l = 1;
            }
        }
    }
}
void Image::lighten(double amount) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            HSLAPixel *pixel = &getPixel(x,y); 
            pixel->l += amount;
            if (pixel->l > 1) {
                pixel->l = 1;
            }
        }
    }
}
void Image::darken() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            HSLAPixel *pixel = &getPixel(x,y); 
            pixel->l -= 0.1;
            if (pixel->l < 0) {
                pixel->l = 0;
            }
        }
    }
}
void Image::darken(double amount) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            HSLAPixel *pixel = &getPixel(x,y); 
            pixel->l -= amount;
            if (pixel->l < 0) {
                pixel->l = 0;
            }
        }
    }
}
void Image::saturate() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            HSLAPixel *pixel = &getPixel(x,y); 
            pixel->s += 0.1;
            if (pixel->s > 1) {
                pixel->s = 1;
            }
        }
    }
}
void Image::saturate(double amount) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            HSLAPixel *pixel = &getPixel(x,y); 
            pixel->s += amount;
            if (pixel->s > 1) {
                pixel->s = 1;
            }
        }
    }
}
void Image::desaturate() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            HSLAPixel *pixel = &getPixel(x,y); 
            pixel->s -= 0.1;
            if (pixel->s < 0) {
                pixel->s = 0;
            }
        }
    }
}
void Image::desaturate(double amount) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            HSLAPixel *pixel = &getPixel(x,y); 
            pixel->s -= amount;
            if (pixel->s < 0) {
                pixel->s = 0;
            }
        }
    }
}
void Image::grayscale() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            HSLAPixel *pixel = &getPixel(x,y); 
            pixel->s = 0;
        }
    }
}
void Image::rotateColor(double degrees) {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            HSLAPixel *pixel = &getPixel(x,y); 
            pixel->h += degrees;
            if (pixel->h < 0) {
                pixel->h += 360;
            }
            if (pixel->h > 360) {
                pixel->h -= 360;
            }
        }
    }
}
void Image::illinify() {
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            HSLAPixel *pixel = &getPixel(x,y); 
            if (pixel->h >= 113.5 || pixel->h < 276.5) {
                pixel->h = 214;
            } else {
                pixel->h = 11;
            }
        }
    }
}
void Image::scale(double factor) {
    Image *copy = new Image(width(), height());
    copy->resize(width(), height());
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            copy->getPixel(x,y) = getPixel(x,y);
        }
    }
    unsigned scaledWidth = width() * factor;
    unsigned scaledHeight = height() * factor;
    resize(scaledWidth, scaledHeight);
    for (unsigned int x = 0; x < scaledWidth; x++) {
        for (unsigned int y = 0; y < scaledHeight; y++) {
            HSLAPixel & currPixel = getPixel(x,y);
            HSLAPixel & copyPixel = copy->getPixel(x/factor, y/factor);
            currPixel = copyPixel;
        }
    }
    delete copy;
}
void Image::scale(unsigned w, unsigned h) {
    double widthFactor = (double)w / width();
    double heightFactor = (double)h / height(); 
    if (widthFactor > heightFactor) {
        scale(heightFactor);
    } else {
        scale(widthFactor);
    }
    
}