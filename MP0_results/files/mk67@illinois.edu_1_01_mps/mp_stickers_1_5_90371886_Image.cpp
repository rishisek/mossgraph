#include <Image.h>
#include <cmath>
using namespace cs225;

void Image::lighten() {
    for (unsigned w = 0; w < this->width(); w++) {
        for (unsigned h = 0; h < this->height(); h++) {
           HSLAPixel &pix = this->getPixel(w,h);
           pix.l += 0.1;
           if (pix.l > 1) pix.l = 1; 
        }
    }
}
void Image::lighten(double amount) {
   for (unsigned w = 0; w < this->width(); w++) {
        for (unsigned h = 0; h < this->height(); h++) {
           HSLAPixel &pix = this->getPixel(w,h);
           pix.l += amount;
           if (pix.l > 1) pix.l = 1; 
        }
    }
}
void Image::darken() {
    for (unsigned w = 0; w < this->width(); w++) {
        for (unsigned h = 0; h < this->height(); h++) {
           HSLAPixel &pix = this->getPixel(w,h);
           pix.l -= 0.1;
           if (pix.l < 0) pix.l = 0; 
        }
    }
}
void Image::darken(double amount) {
    for (unsigned w = 0; w < this->width(); w++) {
        for (unsigned h = 0; h < this->height(); h++) {
           HSLAPixel &pix = this->getPixel(w,h);
           pix.l -= amount;
           if (pix.l < 0) pix.l = 0; 
        }
    }
}
void Image::saturate() {
    for (unsigned w = 0; w < this->width(); w++) {
        for (unsigned h = 0; h < this->height(); h++) {
           HSLAPixel &pix = this->getPixel(w,h);
           pix.s += 0.1;
           if (pix.s > 1) pix.s = 1; 
        }
    }
}
void Image::saturate(double amount) {
    for (unsigned w = 0; w < this->width(); w++) {
        for (unsigned h = 0; h < this->height(); h++) {
           HSLAPixel &pix = this->getPixel(w,h);
           pix.s += amount;
           if (pix.s > 1) pix.s = 1; 
        }
    }
}
void Image::desaturate() {
    for (unsigned w = 0; w < this->width(); w++) {
        for (unsigned h = 0; h < this->height(); h++) {
           HSLAPixel &pix = this->getPixel(w,h);
           pix.s -= 0.1;
           if (pix.s < 0) pix.s = 0; 
        }
    }
}
void Image::desaturate(double amount) {
    for (unsigned w = 0; w < this->width(); w++) {
        for (unsigned h = 0; h < this->height(); h++) {
           HSLAPixel &pix = this->getPixel(w,h);
           pix.s -= amount;
           if (pix.s < 0) {
               pix.s = 0; 
           }
        }
    }
}
void Image::grayscale() {
    for (unsigned w = 0; w < this->width(); w++) {
        for (unsigned h = 0; h < this->height(); h++) {
           HSLAPixel &pix = this->getPixel(w,h);
           pix.s = 0;
        }
    }
}
void Image::rotateColor(double degrees) {
    for (unsigned w = 0; w < this->width(); w++) {
        for (unsigned h = 0; h < this->height(); h++) {
            if(getPixel(w,h).h + degrees > 360 || getPixel(w,h).h + degrees < 0) {
                if (getPixel(w,h).h + degrees > 360) {
                    getPixel(w,h).h = getPixel(w,h).h + degrees - 360;
                } else {
                    getPixel(w,h).h = 360 + getPixel(w,h).h + degrees;
                }
            } else {
                getPixel(w,h).h += degrees;
            } 
        }
    }
}
// Illini orange HUE = 11
// Illini blue HUE = 216
void Image::illinify() {
    int ill_o = 11;
    int ill_b = 216;
    for (unsigned w = 0; w < this->width(); w++) {
        for (unsigned h = 0; h < this->height(); h++) {
            HSLAPixel &pix = this->getPixel(w,h);
            // calculate distance 
            int o_dist = std::abs(pix.h - ill_o); 
            int b_dist = std::abs(pix.h - ill_b);
            if (o_dist > b_dist) { // blue dist closer
                pix.h = ill_b;
            } else { // orange dist closer
                pix.h = ill_o;
            }
        }
    }
}
void Image::scale(double factor) {
    if (factor == 1.0) {
        return;
    }
    unsigned int new_width = this->width() * factor;
    unsigned int new_height = this->height() * factor;

    PNG *image = new PNG(new_width, new_height);
    for (unsigned int i = 0; i < new_width; i++) {
        for (unsigned int j = 0; j < new_height; j++) {
            image->PNG::getPixel(i,j).h = this->PNG::getPixel(floor(i / factor), floor(j / factor)).h;
            image->PNG::getPixel(i,j).s = this->PNG::getPixel(floor(i / factor), floor(j / factor)).s;
            image->PNG::getPixel(i,j).l = this->PNG::getPixel(floor(i / factor), floor(j / factor)).l;
            image->PNG::getPixel(i,j).a = this->PNG::getPixel(floor(i / factor), floor(j / factor)).a;
        }
    }
    this->resize(new_width, new_height);

    for (unsigned int i = 0; i < new_width; i++) {
        for (unsigned int j = 0; j < new_height; j++) {
            this->PNG::getPixel(i, j).h = image->PNG::getPixel(i,j).h;
            this->PNG::getPixel(i, j).s = image->PNG::getPixel(i,j).s;
            this->PNG::getPixel(i, j).l = image->PNG::getPixel(i,j).l;
            this->PNG::getPixel(i, j).a = image->PNG::getPixel(i,j).a;
        }
    }
    delete image;
    image = nullptr;
}

void Image::scale(unsigned w, unsigned h) {
    double width_weight = ((double) w) / ((double) this->width());
    double height_weight = ((double) h) / ((double) this->height());

    PNG *image = new PNG(w, h);

    if (width_weight <= height_weight) {
        scale(width_weight);
    } else {
        scale(height_weight);
    }
    delete image;
    image = nullptr;
}    