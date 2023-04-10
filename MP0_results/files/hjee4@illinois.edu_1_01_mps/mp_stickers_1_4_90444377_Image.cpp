#include "Image.h"
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"

Image::Image() {
    PNG();
}

Image::Image(unsigned int width, unsigned int height) {
    PNG(width, height);
}

void Image::lighten() {
    for (unsigned int x = 0; x < this->width(); x++) {
        for (unsigned int y = 0; y < this->height(); y++) {

            cs225::HSLAPixel & temp = this -> getPixel(x, y);

            if (temp.l + 0.1 <= 1) {
                temp.l += 0.1;
            } else {
                temp.l = 1;
            }
        }
    }

}

void Image::lighten(double amount) {
    for (unsigned int x = 0; x < this->width(); x++) {
        for (unsigned int y = 0; y < this->height(); y++) {

            cs225::HSLAPixel & temp = this -> getPixel(x, y);

            if (temp.l + amount <= 1) {
                temp.l += amount;
            } else {
                temp.l = 1;
            }
        }
    }

}

void Image::darken() {
    for (unsigned int x = 0; x < this->width(); x++) {
        for (unsigned int y = 0; y < this->height(); y++) {

            cs225::HSLAPixel & temp = this -> getPixel(x, y);

            if (temp.l - 0.1 >= 0) {
                temp.l -= 0.1;
            } else {
                temp.l = 0;
            }
        }
    }

}

void Image::darken(double amount) {
    for (unsigned int x = 0; x < this->width(); x++) {
        for (unsigned int y = 0; y < this->height(); y++) {

            cs225::HSLAPixel & temp = this -> getPixel(x, y);

            if (temp.l - amount >= 0) {
                temp.l -= amount;
            } else {
                temp.l = 0;
            }
        }
    }

}

void Image::saturate() {
    for (unsigned int x = 0; x < this->width(); x++) {
        for (unsigned int y = 0; y < this->height(); y++) {

            cs225::HSLAPixel & temp = this -> getPixel(x, y);

            if (temp.s + 0.1 <= 1) {
                temp.s += 0.1;
            } else {
                temp.s = 1;
            }
        }
    }

}

void Image::saturate(double amount) {
    for (unsigned int x = 0; x < this->width(); x++) {
        for (unsigned int y = 0; y < this->height(); y++) {

            cs225::HSLAPixel & temp = this -> getPixel(x, y);

            if (temp.s + amount <= 1) {
                temp.s += amount;
            } else {
                temp.s = 1;
            }
        }
    }

}

void Image::desaturate() {
    for (unsigned int x = 0; x < this->width(); x++) {
        for (unsigned int y = 0; y < this->height(); y++) {

            cs225::HSLAPixel & temp = this -> getPixel(x, y);

            if (temp.s - 0.1 >= 0) {
                temp.s -= 0.1;
            } else {
                temp.s = 0;
            }
        }
    }

}

void Image::desaturate(double amount) {
    for (unsigned int x = 0; x < this->width(); x++) {
        for (unsigned int y = 0; y < this->height(); y++) {

            cs225::HSLAPixel & temp = this -> getPixel(x, y);

            if (temp.s - amount >= 0) {
                temp.s -= amount;
            } else {
                temp.s = 0;
            }
        }
    }

}

void Image::grayscale() {
    for (unsigned int x = 0; x < this->width(); x++) {
        for (unsigned int y = 0; y < this->height(); y++) {

            cs225::HSLAPixel & temp = this -> getPixel(x, y);

            temp.s = 0;
        }
    }   

}

void Image::rotateColor(double degrees) {
    for (unsigned int x = 0; x < this->width(); x++) {
        for (unsigned int y = 0; y < this->height(); y++) {

            cs225::HSLAPixel & temp = this -> getPixel(x, y);
            double a = temp.h + degrees;

            if(a > 360.0) {
                temp.h = a - 360.0;
            } else if (a < 0.0) {
                temp.h = a + 360.0;
            } else {
                temp.h = a;
            }
        }
    }
}

void Image::illinify() {
    for (unsigned int x = 0; x < this->width(); x++) {
        for (unsigned int y = 0; y < this->height(); y++) {

            cs225::HSLAPixel & temp = this -> getPixel(x, y);

            int orange_hue = std::abs(temp.h - 11);
            int blue_hue = std::abs(temp.h - 216);

            if (orange_hue > blue_hue) {
                temp.h = 216;
            } else {
                temp.h = 11;
            }
        }
    }
}

void Image::scale(double factor) {
    unsigned new_w = this -> width();
    unsigned new_h = this -> height();

    Image *temp = new Image(*this);

    this -> resize(new_w * factor, new_h * factor);

    for (unsigned int x = 0; x < this -> width(); x++) {
        for (unsigned int y = 0; y < this -> height(); y++) {
            double og_xcoor = x / factor;
            double og_ycoor = y / factor;
            getPixel(x,y) = temp -> getPixel(og_xcoor, og_ycoor);
        }
    }

    delete temp;

}

void Image::scale(unsigned w, unsigned h) {
    double factor_w = double(w) / this->width();
    double factor_h = double(h) / this->height();
    double factor = 0;
    
    if (factor_w <= factor_h) {
        factor = factor_w;
    } else if (factor_h < factor_w) {
        factor = factor_h;
    } 

    scale(factor);

}