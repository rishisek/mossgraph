#include "Image.h"
#include <stdexcept>
#include <cmath>

using namespace cs225;
using namespace std;

Image::Image() : PNG() {}

Image::Image(unsigned int width, unsigned int height) : PNG(width, height) {}

// Image::~Image() {
//   // delete this;
// }

void Image::darken() {
  for (unsigned int h = 0; h < height(); ++h) {
    for (unsigned int w = 0; w < width(); ++w) {
      if (getPixel(w, h).l - 0.1 < 0) {
        getPixel(w, h).l = 0;
      } else {
        getPixel(w, h).l -= 1;
      }
    }
  }
}

void Image::darken(double amount) {
  for (unsigned int h = 0; h < height(); ++h) {
    for (unsigned int w = 0; w < width(); ++w) {
      HSLAPixel& pixel = getPixel(w, h);
      if (pixel.l - amount < 0) {
        pixel.l = 0;
      } else {
        pixel.l -= amount;
      }
    }
  }
}

void Image::lighten() {
  for (unsigned int h = 0; h < height(); ++h) {
    for (unsigned int w = 0; w < width(); ++w) {
      HSLAPixel& pixel = getPixel(w, h);
      if (pixel.l + 0.1 > 1) {
        pixel.l = 1;
      } else {
        pixel.l += 0.1;
      }
    }
  }      
}
void Image::lighten(double amount) {
  for (unsigned int h = 0; h < height(); ++h) {
    for (unsigned int w = 0; w < width(); ++w) {
      HSLAPixel& pixel = getPixel(w, h);
      if (pixel.l + amount > 1) {
        pixel.l = 1;
      } else {
        pixel.l += amount;
      }
    }
  }         
}
void Image::saturate() {
  for (unsigned int h = 0; h < height(); ++h) {
    for (unsigned int w = 0; w < width(); ++w) {
      if (getPixel(w, h).s + 0.1 > 1) {
        getPixel(w, h).s = 1;
      } else {
        getPixel(w, h).s += 0.1;
      }
    }
  }         
}
void Image::saturate(double amount) {
  for (unsigned int h = 0; h < height(); ++h) {
    for (unsigned int w = 0; w < width(); ++w) {
      if (getPixel(w, h).s + amount > 1) {
        getPixel(w, h).s = 1;
      } else {
        getPixel(w, h).s += amount;
      }
    }
  }        
}
void Image::desaturate() {
  for (unsigned int h = 0; h < height(); ++h) {
    for (unsigned int w = 0; w < width(); ++w) {
      if (getPixel(w, h).s - 0.1 < 0) {
        getPixel(w, h).s = 0;
      } else {
        getPixel(w, h).s -= 0.1;
      }
    }
  }        
}
void Image::desaturate(double amount) {
  for (unsigned int h = 0; h < height(); ++h) {
    for (unsigned int w = 0; w < width(); ++w) {
      if (getPixel(w, h).s - amount < 0) {
        getPixel(w, h).s = 0;
      } else {
        getPixel(w, h).s -= amount;
      }
    }
  }        
}
void Image::grayscale() {
  for (unsigned int h = 0; h < height(); ++h) {
    for (unsigned int w = 0; w < width(); ++w) {
        getPixel(w, h).s = 0;
    }
  }        
}
void Image::scale(double factor) {
  unsigned int newW = width() * factor;
  unsigned int newH = height() * factor;

  Image newImg(newW, newH);

  for (unsigned h = 0; h < newH; ++h) 
  {
    for (unsigned w = 0; w < newW; ++w) 
    {
      newImg.getPixel(w, h) = getPixel(floor(w / factor), floor(h / factor));
    }
  }
  *this = newImg;
}

void Image::scale(unsigned w, unsigned h) {
  double newW = (double)(w);
  double newH = (double)(h);
  double ogW = (double)(width());
  double ogH = (double)(height());
  double ratioW = newW / ogW;
  double ratioH = newH / ogH;

  if (ratioH > ratioW)
  {
      scale(ratioW);
  } else if (ratioH == ratioW)
  {
      scale(ratioW);
  }
  else 
  {
      scale(ratioW);
  }
}

void Image::illinify() {
  for(unsigned int w = 0; w < width(); ++w)
  {
    for(unsigned int h = 0; h < height(); ++h)
    {
      if (abs(getPixel(w, h).h - 11) > abs(getPixel(w, h).h - 216)) {
        getPixel(w, h).h = 216;
      } else {
        getPixel(w, h).h = 11;
      }
    }
  }
}
void Image::rotateColor(double degrees) {
  for(unsigned int w = 0; w < width(); ++w)
  {
    for(unsigned int h = 0; h < height(); ++h)
    {
      if ((getPixel(w, h).h + degrees) > 360) {
        getPixel(w, h).h += degrees;
        while (getPixel(w, h).h > 360)
        {
          getPixel(w, h).h -= 360;
        }
      } else if ((getPixel(w, h).h + degrees) < 0) 
      {
        getPixel(w, h).h += (degrees + 360);
        while (getPixel(w, h).h > 360) 
        {
            getPixel(w, h).h -= 360;
        }         
      } else {
        getPixel(w, h).h += degrees;
      }
    }
  }      
}
