#include "Image.h"

Image::Image() : PNG() {}

Image::Image(unsigned int width, unsigned int height) : PNG(width, height) {}

void Image::lighten() {
    for (unsigned int x = 0; x < width(); ++x) {
        for (unsigned int y = 0; y < height(); ++y) {
            cs225::HSLAPixel& pixel = getPixel(x, y);
            pixel.l += 0.1;
            if (pixel.l > 1) {
                pixel.l = 1;
            }
        }
    }
}

void Image::lighten(double amount) {
    for (unsigned int x = 0; x < width(); ++x) {
        for (unsigned int y = 0; y < height(); ++y) {
            cs225::HSLAPixel& pixel = getPixel(x, y);
            pixel.l += amount;
            if (pixel.l > 1) {
                pixel.l = 1;
            }
        }
    }
} 

void Image::darken() {
    for (unsigned int x = 0; x < width(); ++x) {
        for (unsigned int y = 0; y < height(); ++y) {
            cs225::HSLAPixel& pixel = getPixel(x, y);
            pixel.l -= 0.1;
            if (pixel.l < 0) {
                pixel.l = 0;
            }
        }
    }
}

void Image::darken(double amount) {
    for (unsigned int x = 0; x < width(); ++x) {
        for (unsigned int y = 0; y < height(); ++y) {
            cs225::HSLAPixel& pixel = getPixel(x, y);
            pixel.l -= amount;
            if (pixel.l < 0) {
                pixel.l = 0;
            }
        }
    }
}

void Image::saturate() {
    for (unsigned int x = 0; x < width(); ++x) {
        for (unsigned int y = 0; y < height(); ++y) {
            cs225::HSLAPixel& pixel = getPixel(x, y);
            pixel.s += 0.1;
            if (pixel.s > 1) {
                pixel.s = 1;
            }
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned int x = 0; x < width(); ++x) {
        for (unsigned int y = 0; y < height(); ++y) {
            cs225::HSLAPixel& pixel = getPixel(x, y);
            pixel.s += amount;
            if (pixel.s > 1) {
                pixel.s = 1;
            }
        }
    }
}

void Image::desaturate() {
    for (unsigned int x = 0; x < width(); ++x) {
        for (unsigned int y = 0; y < height(); ++y) {
            cs225::HSLAPixel& pixel = getPixel(x, y);
            pixel.s -= 0.1;
            if (pixel.s < 0) {
                pixel.s = 0;
            }
        }
    }
}

void Image::desaturate(double amount) {
    for (unsigned int x = 0; x < width(); ++x) {
        for (unsigned int y = 0; y < height(); ++y) {
            cs225::HSLAPixel& pixel = getPixel(x, y);
            pixel.s -= amount;
            if (pixel.s < 0) {
                pixel.s = 0;
            }
        }
    }
}

void Image::grayscale() {
    for (unsigned int x = 0; x < width(); ++x) {
        for (unsigned int y = 0; y < height(); ++y) {
            cs225::HSLAPixel& pixel = getPixel(x, y);
            pixel.s = 0;
        }
    }
}

void Image::rotateColor(double degrees) {
    for (unsigned int x = 0; x < width(); ++x) {
        for (unsigned int y = 0; y < height(); ++y) {
            cs225::HSLAPixel& pixel = getPixel(x, y);
            pixel.h += degrees;
            if (pixel.h > 360) {
                pixel.h -= 360;
            }
            if (pixel.h < 0) {
                pixel.h += 360;
            }
        }
    }
}

void Image::illinify() {
    for (unsigned int x = 0; x < width(); ++x) {
        for (unsigned int y = 0; y < height(); ++y) {
            cs225::HSLAPixel& pixel = getPixel(x, y);
            if (pixel.h <= 281 || pixel.h > 101) {
                pixel.h = 216;
            } else { 
                pixel.h = 11;
            }
        }
    }
}

void Image::scale(double factor) {

    Image oldImg = Image(width(), height());
    for (unsigned int x = 0; x < width(); ++x) {
        for (unsigned int y = 0; y < height(); ++y) {
            cs225::HSLAPixel& pixel = getPixel(x, y);
            oldImg.getPixel(x, y) = pixel;
        }
    }

    // if (factor < 1) {
        resize(round(factor * width()), round(factor * height()));
        for (unsigned int x = 0; x < width(); ++x) {
            for (unsigned int y = 0; y < height(); ++y) {
                cs225::HSLAPixel& pixel = oldImg.getPixel(x * 1/factor, y * 1/factor);
                getPixel(x, y) = pixel; 
            }
        }
        // copy pixels over
    // } else {
    //     unsigned int oldHeight = height();
    //     unsigned int oldWidth = width();
    //     resize(factor * width(), factor * height());
    //     for (int x = oldWidth - 1; x >= 0; --x) {
    //         for (int y = oldHeight - 1; y >= 0; --y) {
    //             cs225::HSLAPixel& pixel = getPixel(x, y);
    //             for (unsigned int f = 0; f < factor; ++f) {
    //                 getPixel(width() - (factor * (oldWidth - x)) + f, height() - (factor * (oldHeight - y))) = pixel;
    //                 getPixel(width() - (factor * (oldWidth - x)) + f, height() - (factor * (oldHeight - y)) + 1) = pixel;
    //             }
    //         }
    //     }
    // }
}

void Image::scale(unsigned w, unsigned h) {
    double hFactor = (double)h / height();
    double wFactor = (double)w / width();
    if (hFactor > wFactor) {
        scale(wFactor);
    } else {
        scale(hFactor);
    }
}