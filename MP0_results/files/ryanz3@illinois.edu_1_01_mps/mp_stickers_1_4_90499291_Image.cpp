#include "Image.h"
#include <cmath>

using namespace std;

Image::Image() {
    PNG();
}
Image::Image(unsigned int width, unsigned int height) {
    PNG(width, height);
}
void Image::lighten() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
           if (getPixel(i,j).l + 0.1 <= 1) {
                getPixel(i,j).l += 0.1;
            } else {
                getPixel(i,j).l = 1;
            }
            
        }
    }
}
void Image::lighten(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            if (getPixel(i,j).l + amount <= 1) {
                getPixel(i,j).l += amount;
            } else {
                getPixel(i,j).l = 1;
            }
        }
    }
}
void Image::darken() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
           if (getPixel(i,j).l - 0.1 >= 0) {
                getPixel(i,j).l -= 0.1;
            } else {
                getPixel(i, j).l = 0;
            }
            
        }
    }

}
void Image::darken(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            if (getPixel(i,j).l - amount >= 0) {
                getPixel(i,j).l -= amount;
            } else {
                getPixel(i, j).l = 0;
            }
        }
    }

}
void Image::saturate() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            if (getPixel(i,j).s + 0.1 <= 1) {
                getPixel(i,j).s += 0.1;
            } else {
                getPixel(i,j).s = 1;
            }
        }
    }

}
void Image::saturate(double amount) {
     for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            if (getPixel(i,j).s + amount <= 1) {
                getPixel(i,j).s += amount;
            } else {
                getPixel(i,j).s = 1;
            }
        }
    }

}
void Image::desaturate() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            if (getPixel(i,j).s - 0.1 >= 0) {
                getPixel(i,j).s -= 0.1;
            } else {
                getPixel(i,j).s = 0;
            }
        }
    }
}
void Image::desaturate(double amount) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            if (getPixel(i,j).s - amount >= 0) {
                getPixel(i,j).s -= amount;
            } else {
                getPixel(i,j).s = 0;
            }
        }
    }
}
void Image::grayscale() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            getPixel(i,j).s = 0;
        }
    }
}
void Image::rotateColor(double degrees) {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            getPixel(i,j).h = std::fmod((getPixel(i,j).h + degrees), 360);
            if (getPixel(i,j).h < 0) {
                getPixel(i,j).h += 360;
            }
        }
    }
}
void Image::illinify() {
    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            if (std::fmod((getPixel(i,j).h - 216), 360) < std::fmod((getPixel(i,j).h - 11), 360)) {
                getPixel(i,j).h = 216;
            } else {
                getPixel(i,j).h = 11;
            }
        }
    }

}
void Image::scale(double factor) {
    unsigned int current_width = width();
    unsigned int current_height = height();
    
    PNG copy = PNG(current_width, current_height);

    for (unsigned int i = 0; i < current_width; i++) {
        for (unsigned int j = 0; j < current_height; j++) {
          copy.getPixel(i, j) = getPixel(i, j);
        }
    }
    
    resize(width() * factor, height() * factor);

    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
          getPixel(i, j) = HSLAPixel(0, 0, 1);
        }
    }



    for (unsigned int i = 0; i < current_width; i++) {
        for (unsigned int j = 0; j < current_height; j++) {
          getPixel(i * factor , j * factor) = copy.getPixel(i, j);
        }
    }

    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            if (getPixel(i, j) == HSLAPixel(0, 0, 1)) {
                getPixel(i, j) = copy.getPixel(i / factor, j / factor);
            }
        }
    }

    
}



void Image::scale(unsigned w, unsigned h) {
    double w_factor = double (w) / double (width());
    double h_factor = double (h) / double (height());

    unsigned int current_width = width();
    unsigned int current_height = height();
    

    double factor = w_factor;

    if (w_factor < 1 && h_factor < 1) {
        if (h_factor < w_factor) {
            factor = h_factor;
        }
    } else if (w_factor > 1 && h_factor > 1) {
        if (h_factor > w_factor) {
            factor = h_factor;
        }
    } else if (w_factor > 1 && h_factor < 1) {
        factor = h_factor;
    } else if ((w_factor == 1 && h_factor < 1) || (h_factor == 1 && w_factor > 1)) {
        factor = h_factor;
    } 

    PNG copy = PNG(current_width, current_height);

    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
          copy.getPixel(i, j) = getPixel(i, j);
        }
    }

    resize(width() * factor, height() * factor);

     for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
          getPixel(i, j) = HSLAPixel(0, 0, 1);
        }
    }



    for (unsigned int i = 0; i < current_width; i++) {
        for (unsigned int j = 0; j < current_height; j++) {
          unsigned int curr_w = i * factor;
          unsigned int curr_h = j * factor;

          if (curr_w >= width()) {
            curr_w = width() - 1;
          }

          if (curr_h >= height()) {
            curr_h = height() - 1;
          }

          getPixel(curr_w, curr_h) = copy.getPixel(i, j);
        }
    }

    for (unsigned int i = 0; i < width(); i++) {
        for (unsigned int j = 0; j < height(); j++) {
            if (getPixel(i, j) == HSLAPixel(0, 0, 1)) {
                getPixel(i, j) = copy.getPixel(i / factor, j / factor);
            }
        }
    }


    resize(w, h);


}