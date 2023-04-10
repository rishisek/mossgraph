#include <Image.h>

Image::Image() {




}




/*Creates Image of specified dimensions
width -- Width of new image
height -- Height of new image*/




Image::Image(unsigned int width, unsigned int height) {
  width_ = width;
  height_ = height;
}


/*
Lighten Image by increasing luminance of every pixel by 0.1
Function ensures that the luminance remains in the range [0,1]
*/
void Image::lighten() {
  for(unsigned int i = 0; i < width(); i++) {
      for(unsigned int j = 0; j < height(); j++) {
          HSLAPixel &p = getPixel(i,j);
          if(p.l + 0.1 <= 1) {
              p.l += 0.1;
          } else {
              p.l = 1;
          }
      }
  }
}

/*
Lightens Image by decreasing luminance of every pixel by amount
Function ensures luminance remains in rance [0,1]

amount -- Desired decrease in luminance
*/
void Image::lighten(double amount) {
  for(unsigned int i = 0; i < width(); i++) {
      for(unsigned int j = 0; j < height(); j++) {
          HSLAPixel &p = getPixel(i,j);
          if(p.l + amount <= 1) {
              p.l += amount;
          } else {
              p.l = 1;
          }
      }
  }
}

/*
Darken Image by decreasing luminance of every pixel by 0.1
Function ensures that luminance remains in the range [0,1]
*/
void Image::darken() {
  // loop through every pixel
  for(unsigned int i = 0; i < width(); i++) {
      for(unsigned int j = 0; j < height(); j++) {
          HSLAPixel &p = getPixel(i,j);
          if(p.l - 0.1 >= 0) {
              p.l -= 0.1;
          } else {
              p.l = 0;
          }
      }
  }
}

/*
Darkens Image by decreasing luminance of every pixel by amount
Function ensures luminance remains in rance [0,1] amount -- Desired decrease in luminance
*/
void Image::darken(double amount) {
  for(unsigned int i = 0; i < width(); i++) {
      for(unsigned int j = 0; j < height(); j++) {
          HSLAPixel &p = getPixel(i,j);
          if(p.l - amount >= 0) {
              p.l -= amount;
          } else {
              p.l = 0;
          }
      }
  }
}

/*
Saturates Image by increasing saturation of every pixel by 0.1
Function ensures saturation remains in range of [0,1]
*/
void Image::saturate() {
  for(unsigned int i = 0; i < width(); i++) {
      for(unsigned int j = 0; j < height(); j++) {
          HSLAPixel &p = getPixel(i,j);
          if(p.s + 0.1 <= 1) {
            p.s += 0.1;
          } else {
            p.s = 1;
          }
      }
  }
}

/*
Saturates Image by increasing saturation of every pixel by amount
Function ensures saturation remains in range of [0,1]
*/
void Image::saturate(double amount) {
  for(unsigned int i = 0; i < width(); i++) {
      for(unsigned int j = 0; j < height(); j++) {
          HSLAPixel &p = getPixel(i,j);
          if(p.s + amount <= 0) {
              p.s += amount;
          } else {
              p.s = 1;
          }
      }
  }
}

/*
Desaturates an Image by decreasing the saturation of every pixel by 0.1
Function ensures that the saturation remains in the range [0,1]
*/
void Image::desaturate() {
  // loop through every pixel
  for(unsigned int i = 0; i < width(); i++) {
      for(unsigned int j = 0; j < height(); j++) {
          HSLAPixel &p = getPixel(i,j);
          if(p.s - 0.1 >= 0) {
              p.s -= 0.1;
          } else {
              p.s = 0;
          }
      }
  }
}

/*
Desaturates an Image by decreasing saturation of every pixel by amount
Function ensures that the saturation remains in the range [0,1]
*/
void Image::desaturate(double amount) {
  for(unsigned int i = 0; i < width(); i++) {
      for(unsigned int j = 0; j < height(); j++) {
          HSLAPixel &p = getPixel(i,j);
          if(p.s - amount >= 0) {
              p.s -= amount;
          } else {
              p.s = 0;
          }
      }
  }
}

/*
Turns the image grayscale by decreasing saturation of every pixel to 0
*/
void Image::grayscale() {
  for(unsigned int i = 0; i < width(); i++) {
      for(unsigned int j = 0; j < height(); j++) {
          HSLAPixel &p = getPixel(i,j);
          p.s = 0;
      }
  }
}

/*
Rotates color whele by degrees




Positive direction increases degree of hue.
Function ensures that the hue remains in the range [0,360]
*/
void Image::rotateColor(double degrees) {
  for(unsigned int i = 0; i < width(); i++) {
      for(unsigned int j = 0; j < height(); j++) {
          // if increasing degree of hue exceeds 360
          // take excess above 360 and add that to the hue
          HSLAPixel &p = getPixel(i,j);
          if(degrees > 0 && (p.h + degrees) > 360) {
              p.h = (p.h + degrees) - 360;
          } else if (degrees > 0 && (p.h + degrees) <= 360) {
              p.h += degrees;
          } else if (degrees < 0 && (p.h - degrees) < 0) {
              // if decreasing degree of hue makes hue less than 0
              // take negative value (?) and subtract that from 360
              p.h = 360 - (degrees - getPixel(i,j).h);
          } else {
              p.h -= degrees;
          }
      }
  }
}

/*
To illinify image, change hue of every pixel to Illini Orange or Illini Blue

find distance of pixel from orange, find distance from pixel to blue
if distance from blue is smaller, change hue to 216
if distance from orange is smaller, change hue to 11

*/
void Image::illinify() {
  for(unsigned int i = 0; i < width(); i++) {
      for(unsigned int j = 0; j < height(); j++) {
          HSLAPixel &p = getPixel(i,j);
          // if the distance to orange is greater, change hue to 216
          if(std::abs(p.h - 11) > std::abs(p.h - 216)) {
              p.h = 216;
          } else {
              p.h = 11;
          }
      }
  }
}
 

// scales image by factor
void Image::scale(double factor) {
  unsigned int new_w =  width() * factor;
  unsigned int new_h = height() * factor;
  PNG * newImage = new PNG(*this);
  resize(new_w, new_h);

  for(unsigned int i = 0; i < new_w; i++) {
      for(unsigned int j = 0; j < new_h; j++) {
          HSLAPixel &p = newImage -> getPixel(i/factor, j/factor);
          HSLAPixel &a = getPixel(i,j);
          a = p;
      }
  }

  delete newImage;
}

// given new width and height, calculates
// scale factor 
void Image::scale(unsigned w, unsigned h) {
  if(((w/width()) > (h/height()))) {
      scale(h/height());
  } else {
      scale(w/width());
  }
}