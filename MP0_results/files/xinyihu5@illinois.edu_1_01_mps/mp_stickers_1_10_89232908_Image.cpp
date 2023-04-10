   #include "Image.h"
    #include <iostream>
   
    Image::Image() {
        // width() = 0; 
        // height() = 0; 
    }
    Image::Image (unsigned int width, unsigned int height): PNG(width, height) {
        // PNG(width, height)
    }
    void Image::lighten() {
        //std::cout << "starting lighten" << std::endl;
        for (unsigned int i = 0; i < width(); i++) {
            for (unsigned int j = 0; j < height(); j++) {
                 cs225::HSLAPixel & p = getPixel(i, j);
                //  std::cout << p.l << std::endl;
                // p.l = 100;
                 if (p.l + 0.1 >= 1.0) {
                   p.l = 1.0; 
                 } else {
                    p.l += 0.1;
                  }
            }
        }
    }
    void Image::lighten(double amount) {
        for (unsigned int i = 0; i < width(); i++) {
            for (unsigned int j = 0; j < height(); j++) {
                 cs225::HSLAPixel & p = getPixel(i, j);
                 if (p.l + amount >= 1.0) {
                   p.l = 1.0; 
                 } else {
                    p.l = p.l + amount;
                 }
            }
        }

    }
    void Image::darken() {
        for (unsigned int i = 0; i < width(); i++) {
            for (unsigned int j = 0; j < height(); j++) {
                 cs225::HSLAPixel & p = getPixel(i, j);
                 if (p.l < 0.1) {
                   p.l = 0; 
                 } else {
                    p.l = p.l-0.1;
                 }
            }
        }
    }
    void Image::darken(double amount) {
        for (unsigned int i = 0; i < width(); i++) {
            for (unsigned int j = 0; j < height(); j++) {
                 cs225::HSLAPixel & p = getPixel(i, j);
                 if (p.l < amount) {
                   p.l = 0; 
                 } else {
                    p.l = p.l - amount;
                 }
            }
        }

    }
    void Image::saturate() {
        for (unsigned int i = 0; i < width(); i++) {
            for (unsigned int j = 0; j < height(); j++) {
                 cs225::HSLAPixel & p = getPixel(i, j);
                 if (p.s >= 1.0) {
                   p.s = 1.0; 
                 } else {
                    p.s = p.s + 0.1;
                 }
            }
        }
    }
    void Image::saturate(double amount) {
        for (unsigned int i = 0; i < width(); i++) {
            for (unsigned int j = 0; j < height(); j++) {
                 cs225::HSLAPixel & p = getPixel(i, j);
                 if (p.s >= 1.0) {
                   p.s = 1.0; 
                 } else {
                    p.s = p.s + amount;
                 }
            }
        }
    }
    void Image::desaturate() {
        for (unsigned int i = 0; i < width(); i++) {
            for (unsigned int j = 0; j < height(); j++) {
                 cs225::HSLAPixel & p = getPixel(i, j);
                 if (p.s < 0.1) {
                   p.s = 0; 
                 } else {
                    p.s = p.s-0.1;
                 }
            }
        }
    }
    void Image::desaturate(double amount) {
        for (unsigned int i = 0; i < width(); i++) {
            for (unsigned int j = 0; j < height(); j++) {
                 cs225::HSLAPixel & p = getPixel(i, j);
                 if (p.s < amount) {
                   p.s = 0; 
                 } else {
                    p.s = p.s- amount;
                 }
            }
        }
    }
    void Image::grayscale() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            cs225::HSLAPixel & p = getPixel(i, j);
            p.s = 0; 
        }
    }
    }
    void Image::rotateColor(double degrees) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            cs225::HSLAPixel & p = getPixel(i, j);
            p.h = p.h + degrees;
            while (p.h >= 360) {
                p.h -=360.0;
            }
            while (p.h < 0) {
                p.h += 360;
            }
        }}
    }
    void Image::illinify() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            cs225::HSLAPixel & p = getPixel(i, j);
            if (((p.h >= 11) && (p.h <= 113)) || (p.h >=293)) {
                p.h = 11; // orange
            } else {
                p.h = 216; //blue
            }
        }
     }

    }
    void Image::scale(double factor) { 
        cs225::PNG old_png_(*this); 
        //std::cout<<width()<<", "<<height()<<std::endl;
        resize(width() * factor, height() * factor);
        //std::cout<<width()<<", "<<height()<<std::endl;

        for (unsigned int i = 0; i < width(); i++) {
            for (unsigned int j = 0; j < height(); j++) {
                //if (factor >= 1.0) {
               cs225::HSLAPixel & p = old_png_.getPixel((int)(i/factor), (int)(j/factor));
               getPixel(i, j) = p; 
                //} else {
               // cs225::HSLAPixel & p = old_png_->getPixel((int)(i*factor), (int)(j*factor));
              // getPixel(i, j) = p; 
                }
            }
        }
       // if (factor < 1.0) {
    //width() = width() / factor; 
    //} else if (factor > 1.0)
    
    void Image::scale (unsigned w, unsigned h) {
    double f_width = ((double)(w)) / width();
    double f_height = ((double) (h)) / height();
    if (f_width < f_height) {
        scale(f_width); 
    } else {
        scale(f_height);
    }
    }
