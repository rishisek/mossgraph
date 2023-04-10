#include "Image.h"
#include <cstdlib>

Image::Image(): PNG() {
}

Image::Image(unsigned int w, unsigned int h) : PNG(w, h){
}
    
void Image::darken() {
    for (unsigned w = 0; w < width(); w++) {
        for (unsigned h = 0; h < height(); h++) {
            if ( getPixel(w, h).l - 0.1 < 0) {
                 getPixel(w, h).l = 0;
            } else {
                 getPixel(w, h).l =  getPixel(w, h).l - 0.1;
            }
        }
    }
} //decrease luminance of every pixel by 0.1
    
void Image::darken(double amount) {
    for (unsigned w = 0; w <  width(); w++) {
        for (unsigned h = 0; h <  height(); h++) {
            if ( getPixel(w, h).l - amount < 0) {
                 getPixel(w, h).l = 0;
            } else {
                 getPixel(w, h).l =  getPixel(w, h).l - amount;
            }
        }
    }
}
    
void Image::desaturate() {
    for (unsigned w = 0; w <  width(); w++) {
        for (unsigned h = 0; h <  height(); h++) {
            if ( getPixel(w, h).s - 0.1 < 0) {
                 getPixel(w, h).s = 0;
            } else {
                 getPixel(w, h).s =  getPixel(w, h).s - 0.1;
            }
        }
    }
} //decrease saturation by .1
   
void Image::desaturate(double amount) {
    for (unsigned w = 0; w <  width(); w++) {
        for (unsigned h = 0; h <  height(); h++) {
            if ( getPixel(w, h).s - amount < 0) {
                 getPixel(w, h).s = 0;
            } else {
                 getPixel(w, h).s =  getPixel(w, h).s - amount;
            }
        }
    }
}
    
void Image::grayscale() {
    for (unsigned w = 0; w <  width(); w++) {
        for (unsigned h = 0; h <  height(); h++) {
             getPixel(w, h).s = 0;
        }
    }
} //turns image grayscale (s=0)
    
void Image::illinify() {
    for (unsigned w = 0; w <  width(); w++) {
        for (unsigned h = 0; h <  height(); h++) {
            if (abs((int)  getPixel(w, h).h - 11) <= abs((int)  getPixel(w, h).h - 216)) {
                 getPixel(w, h).h = 11;
            } else {
                 getPixel(w, h).h = 216;
            }
        }
    }
}
    
void Image::lighten() {
    for (unsigned w = 0; w <  width(); w++) {
        for (unsigned h = 0; h <  height(); h++) {
            if ( getPixel(w, h).l + 0.1 > 1) {
                 getPixel(w, h).l = 1;
            } else {
                 getPixel(w, h).l =  getPixel(w, h).l + 0.1;
            }
        }
    }
} //increase luminance of every pixel by 0.1
    
void Image::lighten(double amount) {
    for (unsigned w = 0; w <  width(); w++) {
        for (unsigned h = 0; h <  height(); h++) {
            if ( getPixel(w, h).l + amount > 1) {
                 getPixel(w, h).l = 1;
            } else {
                 getPixel(w, h).l =  getPixel(w, h).l + amount;
            }
        }
    }
}
    
void Image::rotateColor(double degrees) {
    for (unsigned w = 0; w <  width(); w++) {
        for (unsigned h = 0; h <  height(); h++) {
            int newHue = (int) getPixel(w, h).h + (int) degrees;
            if (newHue >= 0) {
                getPixel(w, h).h = (unsigned) (newHue % 360);
            } else {
                getPixel(w, h).h = (unsigned) ((360 + newHue) % 360);
            }
        }
    }
} //rotates color wheel by degrees in positive direction
    
void Image::saturate() {
    for (unsigned w = 0; w <  width(); w++) {
        for (unsigned h = 0; h <  height(); h++) {
            if ( getPixel(w, h).s + 0.1 > 1) {
                 getPixel(w, h).s = 1;
            } else {
                 getPixel(w, h).s =  getPixel(w, h).s + 0.1;
            }
        }
    }
} //increase saturation by .1
    
    
void Image::saturate(double amount) {
    for (unsigned w = 0; w <  width(); w++) {
        for (unsigned h = 0; h <  height(); h++) {
            if ( getPixel(w, h).s + amount > 1) {
                 getPixel(w, h).s = 1;
            } else {
                 getPixel(w, h).s =  getPixel(w, h).s + amount;
            }
        }
    }
}
    
void Image::scale(double factor) {
    unsigned int newWidth = width() * factor;
	unsigned int newHeight = height() * factor;

	Image * duplicate = new Image();
	*duplicate = *this;
	resize(newWidth, newHeight);

	for (unsigned int h = 0; h < newHeight; h++) {
		for (unsigned int w = 0; w < newWidth; w++) {
			HSLAPixel& curr = getPixel(w, h);
			HSLAPixel& cur_copy = duplicate->getPixel(w / factor, h / factor);
			curr = cur_copy;
		}
	}
	
	delete duplicate;
} //1.0 scale doesn't change image, .5 results in half the width and height

void Image::scale(unsigned w, unsigned h) {
    // if (abs((int) ( width() - w )) < abs((int) ( height() - h))) {
    //     scale(w/width());
    // } else {
    //     scale(h/height());
    // }
    double width_factor = (double)w/(double)width();
    double height_factor =(double)h/(double)height();
    if (width_factor <= height_factor) {
        scale(width_factor);
    } else {
        scale(height_factor);
    }
} //preserves aspect ratio of image 