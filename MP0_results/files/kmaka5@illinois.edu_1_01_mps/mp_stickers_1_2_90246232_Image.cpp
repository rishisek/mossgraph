#include "Image.h"

void Image::darken() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            if (getPixel(x,y).l - 0.1 <= 0) {
                getPixel(x,y).l = 0;
            } else {
                getPixel(x,y).l -= 0.1;
            }
        }
    }
}//decrease luminance of every pixel by 0.1

void Image::darken(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            if (getPixel(x,y).l - amount <= 0) {
                getPixel(x,y).l = 0;
            } else {
                getPixel(x,y).l -= amount;
            }
        }
    }
}
void Image::desaturate() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            if (getPixel(x,y).s - 0.1 <= 0) {
                getPixel(x,y).s = 0;
            } else {
                getPixel(x,y).s -= 0.1;
            }
        }
    }
} //decrease saturation by .1

void Image::desaturate(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            if (getPixel(x,y).s - amount <= 0) {
                getPixel(x,y).s = 0;
            } else {
                getPixel(x,y).s -= amount;
            }
        }
    }
}

void Image::grayscale() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            getPixel(x,y).s = 0;
        }
    }
} //turns image grayscale (s=0)

void Image::illinify() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            unsigned hue = getPixel(x,y).h;
            if (abs((int)hue - 11) <= abs((int)hue - 216)) {
                getPixel(x,y).h = 11;
            } else {
                getPixel(x,y).h = 216;
            }
        }
    }
}

void Image::lighten() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            if (getPixel(x,y).l + 0.1 >= 1) {
                getPixel(x,y).l = 1;
            } else {
                getPixel(x,y).l += 0.1;
            }
        }
    }
} //increase luminance of every pixel by 0.1

void Image::lighten(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            if (getPixel(x,y).l + amount >= 1) {
                getPixel(x,y).l = 1;
            } else {
                getPixel(x,y).l += amount;
            }
        }
    }
}

void Image::rotateColor(double degrees) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            // getPixel(x,y).h = (static_cast<int>((double)getPixel(x,y).h + degrees)) % 360;
            int newH = (int) getPixel(x,y).h + (int) degrees;
            if (newH >= 0) {
                getPixel(x,y).h = (unsigned) (newH % 360);
            } else {
                getPixel(x,y).h = (unsigned) (360 + newH % 360);
            }
        }
    }
} //rotates color wheel by degrees in positive direction

void Image::saturate() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            if (getPixel(x,y).s + 0.1 >= 1) {
                getPixel(x,y).s = 1;
            } else {
                getPixel(x,y).s += 0.1;
            }
        }
    }
} //increase saturation by .1

void Image::saturate(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            if (getPixel(x,y).s + amount >= 1) {
                getPixel(x,y).s = 1;
            } else {
                getPixel(x,y).s += amount;
            }
        }
    }
}

void Image::scale(double factor) {
    if (factor == 1) {
        return;
    }
    //copy image
    // PNG old = *this;
    //starting pixel multiplied by factor
    
    //scale up
    if (factor > 1) {
        resize(width() * factor, height() * factor);
        for (int x = width() - 1; x >= 0; x--) {
            for (int y = height() - 1; y >= 0; y--) {
                cs225::HSLAPixel& oldp = getPixel((unsigned)x/factor,(unsigned)y/factor);
                cs225::HSLAPixel& newp = getPixel(x,y);
                newp = oldp;
            }
        }
    } else {
        for (unsigned x = 0; x < width() * factor; x++) {
            for (unsigned y = 0; y < height() * factor; y++) {
                cs225::HSLAPixel& oldp = getPixel((unsigned)x / factor, (unsigned)y / factor);
                cs225::HSLAPixel& newp = getPixel(x,y);
                newp = oldp;
            }
        }
        resize(width() * factor, height() * factor);
    }
} //1.0 scale doesn't change image, .5 results in half the width and height

void Image::scale(unsigned w, unsigned h) {
    // double ratio = (static_cast<double>(width())/static_cast<double>(height()));
    // unsigned newW = 0;
    // unsigned newH = 0;
    // if (abs((int)width() - (int)w) < abs((int)height()-(int)h)) {
    //     // newW = w;
    //     // newH = static_cast<int>((1.0/ratio) * newW);
    //     scale(w/width());
    // } else {
    //     // newH = h;
    //     // newW = static_cast<int>(ratio * newH);
    //     scale(h/height());
    // }
    double width_factor = (double)w/(double)width();
    double height_factor = (double)h/(double)height();
    if (width_factor <= height_factor) {
        scale(width_factor);
    } else {
        scale(height_factor);
    }
    // resize(newW, newH);
} //preserves aspect ratio of image 