

#include <Image.h>


Image::Image(){

}
Image::Image (unsigned int width, unsigned int height):cs225::PNG(width,height) {
  
}
void Image::lighten() {
    for (unsigned int w = 0; w < width(); w++) {
        for(unsigned int h = 0; h < height(); h++) {
            getPixel(w,h).l += 0.1;
            if (getPixel(w,h).l > 1) {
                getPixel(w,h).l = 1;
            }
        }
    }
}
void Image::lighten (double amount) {
    for (unsigned int w = 0; w < Image::width(); w++) {
        for(unsigned int h = 0; h < Image::height(); h++) {
            getPixel(w,h).l += amount;
            if (getPixel(w,h).l > 1) {
                getPixel(w,h).l = 1;
            }
        }
    }
}
void Image::darken() {
    for (unsigned int w = 0; w < width(); w++) {
        for(unsigned int h = 0; h < height(); h++) {
            getPixel(w,h).l -= 0.1;
            if (getPixel(w,h).l < 0) {
                getPixel(w,h).l = 0;
            }
        }
    }
}
void Image::darken(double amount) {
    for (unsigned int w = 0; w < width(); w++) {
        for(unsigned int h = 0; h < height(); h++) {
            getPixel(w,h).l -= amount;
            if (getPixel(w,h).l < 0) {
                getPixel(w,h).l = 0;
            }
        }
    }
}
void Image::saturate() {
    for (unsigned int w = 0; w < width(); w++) {
        for(unsigned int h = 0; h < height(); h++) {
            getPixel(w,h).s += 0.1;
            if (getPixel(w,h).s > 1) {
                getPixel(w,h).s = 1;
            }
        }
    }
}
void Image::saturate (double amount) {
    for (unsigned int w = 0; w < width(); w++) {
        for(unsigned int h = 0; h < height(); h++) {
            getPixel(w,h).s += amount;
            if (getPixel(w,h).s > 1) {
                getPixel(w,h).s = 1;
            }
        }
    }
}
void Image::desaturate() {
    for (unsigned int w = 0; w < width(); w++) {
        for(unsigned int h = 0; h < height(); h++) {
            getPixel(w,h).s -= 0.1;
            if (getPixel(w,h).s > 1) {
                getPixel(w,h).s = 1;
            }
        }
    }
}
void Image::desaturate (double amount) {
    for (unsigned int w = 0; w < width(); w++) {
        for(unsigned int h = 0; h < height(); h++) {
            getPixel(w,h).s -= amount;
            if (getPixel(w,h).s > 1) {
                getPixel(w,h).s = 1;
            }
        }
    }
}
void Image::grayscale() {
    for (unsigned int w = 0; w < width(); w++) {
        for(unsigned int h = 0; h < height(); h++) {
            getPixel(w,h).s = 0;
        }
    }
}
void Image::rotateColor (double degrees) {
    while (degrees < 0) {
        degrees += 360;
    }
    while (degrees > 360) {
        degrees -= 360;
    }
    for (unsigned int w = 0; w < width(); w++) {
        for(unsigned int h = 0; h < height(); h++) {
            getPixel(w,h).h += degrees;
            if (getPixel(w,h).h >= 360) {
                getPixel(w,h).h -= 360;
            }
        }
    }
}
void Image::illinify() {
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            if (getPixel(w,h).h >= 293.5 || getPixel(w,h).h <= 113.5) {
                getPixel(w,h).h = 11;
            } else {
                getPixel(w,h).h = 216;
            }
        }
    }
}

void Image::scale(double factor) {
    Image image;
    image.resize(factor*width(),factor*height());
    for (unsigned int w = 0; w < image.width(); w++) {
        for (unsigned int h = 0; h < image.height(); h++) {
            unsigned int i = w/factor;
            unsigned int j = h/factor;
            image.getPixel(w,h) = getPixel(i,j);
        }
    }
    resize(factor*width(),factor*height());
    for (unsigned int w = 0; w < width(); w++) {
        for (unsigned int h = 0; h < height(); h++) {
            getPixel(w,h) = image.getPixel(w,h);
        }
    }
}
void Image::scale (unsigned w, unsigned h) {
    double w2 = w + 0.0;
    double h2 = h + 0.0;
    double factor = w2/width();
    if (h2/height() < factor) {
        factor = h2/height();
    }
    scale(factor);
}