#include "Image.h"
#include <algorithm> 
#include <cmath> 

Image::Image(unsigned int width, unsigned int height) : PNG(width,height) {}

std::vector<unsigned> SetInterval(unsigned start, unsigned end, unsigned number) {
    unsigned diff = end - start;
    double interval = (float)diff/(float)number;
    std::vector<unsigned> to_return;
    for(unsigned i = 0; i < number; i++) {
        unsigned add = std::floor(interval*i);
        to_return.push_back(add);
    }

    
    return to_return;
}

void Image::lighten() { 
    for (unsigned int i = 0; i < height(); i++) {
        for (unsigned int j = 0; j < width(); j++) {
            HSLAPixel &curr_pixel = getPixel(j, i);
            curr_pixel.l += 0.1;
            if (curr_pixel.l > 1.0) {
                curr_pixel.l = 1.0; 
            } else if (curr_pixel.l < 0.0) {
                curr_pixel.l = 0.0; 
            }
        }
    }
}

void Image::lighten(double amount) {
    for (unsigned int i = 0; i < height(); i++) {
        for (unsigned int j = 0; j < width(); j++) {
            HSLAPixel &curr_pixel = getPixel(j, i);
            curr_pixel.l += amount;
            if (curr_pixel.l > 1.0) {
                curr_pixel.l = 1.0; 
            } else if (curr_pixel.l < 0.0) {
                curr_pixel.l = 0.0; 
            }
        }
    }
}

void Image::darken() {
    for (unsigned int i = 0; i < height(); i++) {
        for (unsigned int j = 0; j < width(); j++) {
            HSLAPixel &curr_pixel = getPixel(j, i);
            curr_pixel.l -= 0.1;
            if (curr_pixel.l < 0.0) {
                curr_pixel.l = 0.0; 
            } else if (curr_pixel.l > 1.0) {
                curr_pixel.l = 1.0; 
            }
        }
    }
}

void Image::darken(double amount) {
    for (unsigned int i = 0; i < height(); i++) {
        for (unsigned int j = 0; j < width(); j++) {
            HSLAPixel &curr_pixel = getPixel(j, i);
            curr_pixel.l -= amount;
            if (curr_pixel.l < 0.0) {
                curr_pixel.l = 0.0; 
            } else if (curr_pixel.l > 1.0) {
                curr_pixel.l = 1.0; 
            }
        }
    }
}

void Image::saturate() {
    for (unsigned int i = 0; i < height(); i++) {
        for (unsigned int j = 0; j < width(); j++) {
            HSLAPixel &curr_pixel = getPixel(j, i);
            curr_pixel.s += 0.1;
            if (curr_pixel.s > 1.0) {
                curr_pixel.s = 1.0; 
            } else if (curr_pixel.s < 0.0) {
                curr_pixel.s = 0.0; 
            }
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned int i = 0; i < height(); i++) {
        for (unsigned int j = 0; j < width(); j++) {
            HSLAPixel &curr_pixel = getPixel(j, i);
            curr_pixel.s += amount;
            if (curr_pixel.s > 1.0) {
                curr_pixel.s = 1.0; 
            } else if (curr_pixel.s < 0.0) {
                curr_pixel.l = 0.0; 
            }
        }
    }
}

void Image::desaturate() {
    for (unsigned int i = 0; i < height(); i++) {
        for (unsigned int j = 0; j < width(); j++) {
            HSLAPixel &curr_pixel = getPixel(j, i);
            curr_pixel.s -= 0.1;
            if (curr_pixel.s < 0.0) {
                curr_pixel.s = 0.0; 
            } else if (curr_pixel.s > 1.0) {
                curr_pixel.l = 1.0; 
            }
        }
    }
}

void Image::desaturate(double amount) {
    for (unsigned int i = 0; i < height(); i++) {
        for (unsigned int j = 0; j < width(); j++) {
            HSLAPixel &curr_pixel = getPixel(j, i);
            curr_pixel.s -= amount;
            if (curr_pixel.s < 0.0) {
                curr_pixel.s = 0.0; 
            } else if (curr_pixel.s > 1.0) {
                curr_pixel.l = 1.0; 
            }
        }
    }
}

void Image::grayscale() {
    for (unsigned int i = 0; i < height(); i++) {
        for (unsigned int j = 0; j < width(); j++) {
            HSLAPixel &curr_pixel = getPixel(j, i);
            curr_pixel.s = 0.0;
        }
    }
}

void Image::rotateColor(double degrees) {
    for (unsigned int i = 0; i < height(); i++) {
        for (unsigned int j = 0; j < width(); j++) {
            HSLAPixel &curr_pixel = getPixel(j, i); 
            double temp = curr_pixel.h + degrees; 
            if (temp > 360) {
                while (temp > 360) {
                    temp -= 360;
                }
            }
            if (temp < 0) {
                while (temp < 0) {
                    temp += 360; 
                }
            }
            curr_pixel.h = temp; 
        }
    }
}

void Image::illinify() {
    for (unsigned int i = 0; i < height(); i++) {
        for (unsigned int j = 0; j < width(); j++) {
            HSLAPixel &curr_pixel = getPixel(j, i);
            if (curr_pixel.h >= 113.5 && curr_pixel.h < 293.5) {
                curr_pixel.h = 216;
            } else {
                curr_pixel.h = 11; 
            }
        }
    }
}

void Image::scale(double factor) {
    unsigned int new_width = width() * factor; 
    unsigned int new_height = height() * factor;

    Image *copy_image = new Image(); 
    *copy_image = *this; 
    resize(new_width, new_height); 

    for (unsigned int i = 0; i < new_height; i++) {
        for (unsigned int j = 0; j < new_width; j++) {
            HSLAPixel &curr_pixel = getPixel(j, i); 
            HSLAPixel &curr_copy_pixel = copy_image->getPixel(j/ factor, i / factor);
            curr_pixel = curr_copy_pixel;
        }
    }
    delete copy_image; 
}

void Image::scale(unsigned w, unsigned h) {
    float factor; 
    float width_s = (float)w / (float)width(); 
    float height_s = (float)h / (float)height(); 

    if (height() * width_s < h) {
        factor = width_s; 
    } else {
        factor = height_s; 
    }
    scale(factor); 
}

// void Image::scale(unsigned w, unsigned h) {
//     double new_width = w / width(); 
//     double new_height = h / height();

//     Image *copy_image = new Image(); 
//     *copy_image = *this; 
//     resize(w, h); 

//     for (unsigned int i = 0; i < h; i++) {
//         for (unsigned int j = 0; j < w; j++) {
//             HSLAPixel &curr_pixel = getPixel(j, i); 
//             HSLAPixel &curr_copy_pixel = copy_image->getPixel(j/ new_width, i / new_height);
//             curr_pixel = curr_copy_pixel;
//         }
//     }
//     delete copy_image; 
// }