#include "Image.h"


Image::Image() : cs225::PNG() { }

Image::Image(unsigned int width, unsigned int height) : cs225::PNG(width, height) { }

void Image::lighten() {
    for (unsigned int row = 0; row < height(); row++) {
        for (unsigned int col = 0; col < width(); col++) {
            if (getPixel(col, row).l + 0.1 <= 1) {
                getPixel(col, row).l += 0.1;
            } else {
                getPixel(col, row).l = 1;
            }
        }
    }
}

void Image::lighten(double amount) {
    for (unsigned int row = 0; row < height(); row++) {
        for (unsigned int col = 0; col < width(); col++) {
            if (getPixel(col, row).l + amount <= 1) {
                getPixel(col, row).l += amount;
            } else {
                getPixel(col, row).l = 1;
            }
        }
    }
}	

void Image::darken() {
    for (unsigned int row = 0; row < height(); row++) {
        for (unsigned int col = 0; col < width(); col++) {
            if (getPixel(col, row).l - 0.1 >= 0) {
                getPixel(col, row).l -= 0.1;
            } else {
                getPixel(col, row).l = 0;
            }
        }
    }
}

void Image::darken(double amount) {
    for (unsigned int row = 0; row < height(); row++) {
        for (unsigned int col = 0; col < width(); col++) {
            if (getPixel(col, row).l - amount >= 0) {
                getPixel(col, row).l -= amount;
            } else {
                getPixel(col, row).l = 0;
            }
        }
    }
}


void Image::saturate() {
    for (unsigned int row = 0; row < height(); row++) {
        for (unsigned int col = 0; col < width(); col++) {
            if (getPixel(col, row).s + 0.1 <= 1) {
                getPixel(col, row).s += 0.1;
            } else {
                getPixel(col, row).s = 1;
            }
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned int row = 0; row < height(); row++) {
        for (unsigned int col = 0; col < width(); col++) {
            if (getPixel(col, row).s + amount <= 1) {
                getPixel(col, row).s += amount;
            } else {
                getPixel(col, row).s = 1;
            }
        }
    }
}	

void Image::desaturate() {
    for (unsigned int row = 0; row < height(); row++) {
        for (unsigned int col = 0; col < width(); col++) {
            if (getPixel(col, row).s - 0.1 >= 0) {
                getPixel(col, row).s -= 0.1;
            } else {
                getPixel(col, row).s = 0;
            }
        }
    }
}

void Image::desaturate(double amount) {
    for (unsigned int row = 0; row < height(); row++) {
        for (unsigned int col = 0; col < width(); col++) {
            if (getPixel(col, row).s - amount >= 0) {
                getPixel(col, row).s -= amount;
            } else {
                getPixel(col, row).s = 0;
            }
        }
    }
}


void Image::grayscale() {
    for (unsigned int row = 0; row < height(); row++) {
        for (unsigned int col = 0; col < width(); col++) {
            getPixel(col, row).s = 0;
        }
    }
}

void Image::rotateColor(double degrees)	{
    for (unsigned int row = 0; row < height(); row++) {
        for (unsigned int col = 0; col < width(); col++) {
            if (getPixel(col, row).h + degrees <= 360 && getPixel(col, row).h + degrees >= 0) {
                getPixel(col, row).h += degrees;
            } else if (getPixel(col, row).h + degrees > 360) {
                getPixel(col, row).h = (getPixel(col, row).h + degrees) - 360; 
            } else {
                getPixel(col, row).h = (getPixel(col, row).h + degrees) + 360;
            }
        }
    }
}

void Image::illinify() {
    for (unsigned int row = 0; row < height(); row++) {
        for (unsigned int col = 0; col < width(); col++) { 
            double distOrange = fabs(getPixel(col, row).h - 11);
            double distBlue = fabs(getPixel(col, row).h - 216);
            if (distOrange < distBlue) {
                getPixel(col, row).h = 11.0;
            } else {
                getPixel(col, row).h = 216.0;
            }
        }
    }
}

void Image::scale(double factor) {
    Image copy = *this;
    if (factor != 1.0) {
        resize(width() * factor, height() * factor);
        for (unsigned int row = 0; row < height(); row++) {
            for (unsigned int col = 0; col < width(); col++) {
                getPixel(col, row) = copy.getPixel(col/factor, row/factor);
            }
        }
    }
}

void Image::scale(unsigned w, unsigned h) {
    double w_ratio = double(w)/double(width());
    double h_ratio = double(h)/double(height());
    if (w_ratio < h_ratio) {
        scale(w_ratio);
    } else  {
        scale(h_ratio);
    }
}


