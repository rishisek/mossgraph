#include "Image.h"

Image::Image() { // Creates an empty Image.
  PNG();
}

Image::Image (unsigned int width, unsigned int height) { // Creates an Image of the specified dimensions.
  PNG(width, height);
}

//////////////////////////////////

void Image::lighten() { // Lighten an Image by increasing the luminance of every pixel by 0.1.
  for (unsigned int i = 0; i < width(); i++) {
    for (unsigned int j = 0; j < height(); j++) {
      if (getPixel(i, j).l + 0.1 > 1.0) {
        getPixel(i, j).l = 1.0;
      } else {
        getPixel(i, j).l += 0.1;
      }
    }
  }
}

void Image::lighten (double amount) { // Lighten an Image by increasing the luminance of every pixel by amount.
  for (unsigned int i = 0; i < width(); i++) {
    for (unsigned int j = 0; j < height(); j++) {
      if (getPixel(i, j).l + amount > 1.0) {
        getPixel(i, j).l = 1.0;
      } else {
        getPixel(i, j).l += amount;
      }
    }
  }
}

//////////////////////////////////

void Image::darken() { // Darken an Image by decreasing the luminance of every pixel by 0.1.
  for (unsigned int i = 0; i < width(); i++) {
    for (unsigned int j = 0; j < height(); j++) {
      if (getPixel(i, j).l - 0.1 < 0.0) {
        getPixel(i, j).l = 0.0;
      } else {
        getPixel(i, j).l -= 0.1;
      }
    }
  }
}

void Image::darken(double amount) { // Darkens an Image by decreasing the luminance of every pixel by amount.
  for (unsigned int i = 0; i < width(); i++) {
    for (unsigned int j = 0; j < height(); j++) {
      if (getPixel(i, j).l - amount < 0.0) {
        getPixel(i, j).l = 0.0;
      } else {
        getPixel(i, j).l -= amount;
      }
    }
  }
}

//////////////////////////////////

void Image::saturate() { // Saturates an Image by increasing the saturation of every pixel by 0.1.
  for (unsigned int i = 0; i < width(); i++) {
    for (unsigned int j = 0; j < height(); j++) {
      if (getPixel(i, j).s + 0.1 <= 1) {
        getPixel(i, j).s += 0.1;
      }
    }
  }
}

void Image::saturate(double amount) { // Saturates an Image by increasing the saturation of every pixel by amount.
  for (unsigned int i = 0; i < width(); i++) {
    for (unsigned int j = 0; j < height(); j++) {
      if (getPixel(i, j).s + amount <= 1) {
        getPixel(i, j).s += amount;
      }
    }
  }
}

//////////////////////////////////

void Image::desaturate() { // Desaturates an Image by decreasing the saturation of every pixel by 0.1.
  for (unsigned int i = 0; i < width(); i++) {
    for (unsigned int j = 0; j < height(); j++) {
      if (getPixel(i, j).s - 0.1 >= 0) {
        getPixel(i, j).s -= 0.1;
      }
    }
  }
}

void Image::desaturate(double amount) { // Desaturates an Image by decreasing the saturation of every pixel by amount.
  for (unsigned int i = 0; i < width(); i++) {
    for (unsigned int j = 0; j < height(); j++) {
      if (getPixel(i, j).s - amount >= 0) {
        getPixel(i, j).s -= amount;
      }
    }
  }
}

//////////////////////////////////

void Image::grayscale() { // Turns the image grayscale.
  for (unsigned int i = 0; i < width(); i++) {
    for (unsigned int j = 0; j < height(); j++) {
      getPixel(i, j).s = 0;
    }
  }
}

//////////////////////////////////

void Image::rotateColor(double degrees) { // Rotates the color wheel by degrees.
  for (unsigned int i = 0; i < width(); i++) {
    for (unsigned int j = 0; j < height(); j++) {
      if (getPixel(i, j).h + degrees > 360.0) {
        getPixel(i, j).h = ((getPixel(i, j).h + degrees) - 360);
      } else if (getPixel(i, j).h + degrees < 0.0) {
        getPixel(i, j).h = (360 + (getPixel(i, j).h + degrees));
      } else {
        getPixel(i, j).h += degrees;
      }
    }
  }
}

//////////////////////////////////

void Image::illinify() { // Illinify the image.
  for (unsigned int i = 0; i < width(); i++) {
    for (unsigned int j = 0; j < height(); j++) {
      if (std::abs(getPixel(i, j).h - 11.0) > std::abs(getPixel(i, j).h - 216.0)) {
        getPixel(i, j).h = 216.0;
      } else {
        getPixel(i, j).h = 11.0;
      }
    }
  }
}

//////////////////////////////////

void Image::scale(double factor) { // Scale the Image by a given factor.

  Image current = Image(*this);

  resize(width() * factor, height() * factor);

  for (unsigned int i = 0; i < width(); i++) {
    for (unsigned int j = 0; j < height(); j++) {
      cs225::HSLAPixel & oldPixel = getPixel(i, j);
      cs225::HSLAPixel & newPixel = current.getPixel(i / factor, j / factor);
      oldPixel = newPixel;
    }
  }
}

void Image::scale(unsigned w, unsigned h) { // Scales the image to fit within the size (w x h).

  Image current = Image(*this);
  
  double x_factor = w / (double) width();
  double y_factor = h / (double) height();

  double factor = 1.0;

  if (x_factor < y_factor) {
    factor = x_factor;
  } else {
    factor = y_factor;
  }

  scale(factor);
}

//////////////////////////////////