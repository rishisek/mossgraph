#include "Image.h"

Image::Image() {
    PNG();
}

Image::Image(unsigned int width, unsigned int height) {
    PNG(width, height);
}

void Image::lighten() {
    for (unsigned int row = 0; row < height(); row++) {
        for (unsigned int col = 0; col < width(); col++) {
            HSLAPixel& pixel = getPixel(col,row);
            pixel.l += 0.1;
            if (pixel.l > 1) pixel.l = 1;
        }
    }
}

void Image::lighten(double amount) {
    for (unsigned int row = 0; row < height(); row++) {
        for (unsigned int col = 0; col < width(); col++) {
            HSLAPixel& pixel = getPixel(col,row);
            pixel.l += amount;
            if (pixel.l > 1) pixel.l = 1;
            if (pixel.l < 0) pixel.l = 0;
        }
    }
}

void Image::darken() {
    for (unsigned int row = 0; row < height(); ++row) {
        for (unsigned int col = 0; col < width(); ++col) {
            HSLAPixel& pixel = getPixel(col,row);
            pixel.l -= 0.1;
            if (pixel.l < 0) pixel.l = 0;
        }
    }    
}

void Image::darken(double amount) {
    for (unsigned int row = 0; row < height(); ++row) {
        for (unsigned int col = 0; col < width(); ++col) {
            HSLAPixel& pixel = getPixel(col,row);
            pixel.l -= amount;
            if (pixel.l > 1) pixel.l = 1; 
            if (pixel.l < 0) pixel.l = 0;
        }
    }    
}

void Image::saturate() {
    for (unsigned int row = 0; row < height(); ++row) {
        for (unsigned int col = 0; col < width(); ++col) {
            HSLAPixel& pixel = getPixel(col,row);
            pixel.s += 0.1;
            if (pixel.s > 1) pixel.s = 1;
        }
    }       
}

void Image::saturate(double amount) {
    for (unsigned int row = 0; row < height(); ++row) {
        for (unsigned int col = 0; col < width(); ++col) {
            HSLAPixel& pixel = getPixel(col,row);
            pixel.s += amount;
            if (pixel.s > 1) pixel.s = 1;
            if (pixel.s < 0) pixel.s = 0;
        }
    }       
}

void Image::desaturate() {
    for (unsigned int row = 0; row < height(); ++row) {
        for (unsigned int col = 0; col < width(); ++col) {
            HSLAPixel& pixel = getPixel(col,row);
            pixel.s -= 0.1;
            if (pixel.s < 0) pixel.s = 0;
        }
    }       
}

void Image::desaturate(double amount) {
    for (unsigned int row = 0; row < height(); ++row) {
        for (unsigned int col = 0; col < width(); ++col) {
            HSLAPixel& pixel = getPixel(col,row);
            pixel.s -= amount;
            if (pixel.s > 1) pixel.s = 1;
            if (pixel.s < 0) pixel.s = 0;
        }
    }       
}

void Image::grayscale() {
    for (unsigned int row = 0; row < height(); ++row) {
        for (unsigned int col = 0; col < width(); ++col) {
            HSLAPixel& pixel = getPixel(col,row);
            pixel.s = 0;
        }
    } 
}

void Image::rotateColor(double degrees) {
    for (unsigned int row = 0; row < height(); ++row) {
        for (unsigned int col = 0; col < width(); ++col) {
            HSLAPixel& pixel = getPixel(col,row);
            pixel.h += degrees;
            while (pixel.h >= 360) {
                pixel.h -= 360;
            }
            while (pixel.h < 0) {
                pixel.h += 360;
            }
        }
    } 
}


void Image::illinify() {
    for (unsigned int row = 0; row < height(); ++row) {
        for (unsigned int col = 0; col < width(); ++col) {
            HSLAPixel& pixel = getPixel(col,row);
            if (pixel.h >= 113.5 && pixel.h <=293.5) {
                pixel.h = 216;
            } else {
                pixel.h = 11;
            }
        }
    } 
}

void Image::scale(double factor) {
    unsigned int scaledwidth = width()* factor;
    unsigned int scaledheight = height() * factor;
    Image* copy = new Image(*this);
    resize(scaledwidth, scaledheight);
    for (unsigned int row = 0; row < scaledheight; ++row) {
        for (unsigned int col = 0; col < scaledwidth; ++col) {
            HSLAPixel& pixel = getPixel(col,row);
            HSLAPixel& copypixel = copy->getPixel(col/factor, row/factor);
            pixel = copypixel;
        }
    }
    delete copy;
}

void Image::scale(unsigned w, unsigned h) {
    double xfactor = (double) w/ (double) width();
    double yfactor = (double) h/ (double) height();   
    if (xfactor < yfactor) scale(xfactor);
        else scale(yfactor);
}


