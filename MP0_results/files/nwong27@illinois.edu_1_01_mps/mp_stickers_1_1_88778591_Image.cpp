#include <cmath>
#include "Image.h"
#include "cs225/PNG.h"

using namespace cs225;

void Image::lighten() {
	unsigned int width_image = width();
	unsigned int height_image = height();
	for (unsigned int h = 0; h < height_image; h++) {
		for (unsigned int w = 0; w < width_image; w++) {
			HSLAPixel & pixel_cur = getPixel(w, h);
			pixel_cur.l += 0.1;
			if (pixel_cur.l > 1.0) {
                pixel_cur.l = 1.0;
            }
			if (pixel_cur.l < 0.0) {
                pixel_cur.l = 0.0;
            }
		}
	}
}

void Image::lighten(double amount) {
	unsigned int width_image = width();
	unsigned int height_image = height();
	for (unsigned int h = 0; h < height_image; h++) {
		for (unsigned int w = 0; w < width_image; w++) {
			HSLAPixel & pixel_cur = getPixel(w, h);
			pixel_cur.l += amount;
			if (pixel_cur.l > 1.0) {
                pixel_cur.l = 1.0;
            }
			if (pixel_cur.l < 0.0) {
                pixel_cur.l = 0.0;
            }
		}
	}
}

void Image::darken() {
	unsigned int width_image = width();
	unsigned int height_image = height();
	for (unsigned int h = 0; h < height_image; h++) {
		for (unsigned int w = 0; w < width_image; w++) {
			HSLAPixel & pixel_cur = getPixel(w, h);
			pixel_cur.l -= 0.1;
			if (pixel_cur.l < 0.0) {
                pixel_cur.l = 0.0;
            }
			if (pixel_cur.l > 1.0) {
                pixel_cur.l = 1.0;
            }
		}
	}
}

void Image::darken(double amount) {
	unsigned int width_image = width();
	unsigned int height_image = height();
	for (unsigned int h = 0; h < height_image; h++) {
		for (unsigned int w = 0; w < width_image; w++) {
			HSLAPixel & pixel_cur = getPixel(w, h);
			pixel_cur.l -= amount;
			if (pixel_cur.l < 0.0) {
                pixel_cur.l = 0.0;
            }
			if (pixel_cur.l > 1.0) {
                pixel_cur.l = 1.0;
            }
		}
	}
}

void Image::saturate() {
	unsigned int width_image = width();
	unsigned int height_image = height();
	for (unsigned int h = 0; h < height_image; h++) {
		for (unsigned int w = 0; w < width_image; w++) {
			HSLAPixel & pixel_cur = getPixel(w, h);
			pixel_cur.s += 0.1;
			if (pixel_cur.s > 1.0) {
                pixel_cur.s = 1.0;
            }
			if (pixel_cur.s < 0.0) {
                pixel_cur.s = 0.0;
            }
		}
	}
}

void Image::saturate(double amount) {
	unsigned int width_image = width();
	unsigned int height_image = height();
	for (unsigned int h = 0; h < height_image; h++) {
		for (unsigned int w = 0; w < width_image; w++) {
			HSLAPixel & pixel_cur = getPixel(w, h);
			pixel_cur.s += amount;
			if (pixel_cur.s > 1.0) {
                pixel_cur.s = 1.0;
            }
			if (pixel_cur.s < 0.0) {
                pixel_cur.s = 0.0;
            }
		}
	}
}

void Image::desaturate() {
	unsigned int width_image = width();
	unsigned int height_image = height();
	for (unsigned int h = 0; h < height_image; h++) {
		for (unsigned int w = 0; w < width_image; w++) {
			HSLAPixel & pixel_cur = getPixel(w, h);
			pixel_cur.s -= 0.1;
			if (pixel_cur.s < 0.0) {
                pixel_cur.s = 0.0;
            }
			if (pixel_cur.s > 1.0) {
                pixel_cur.s = 1.0;
            }
		}
	}
}

void Image::desaturate(double amount) {
	unsigned int width_image = width();
	unsigned int height_image = height();
	for (unsigned int h = 0; h < height_image; h++) {
		for (unsigned int w = 0; w < width_image; w++) {
			HSLAPixel & pixel_cur = getPixel(w, h);
			pixel_cur.s -= amount;
			if (pixel_cur.s < 0.0) {
                pixel_cur.s = 0.0;
            }
			if (pixel_cur.s > 1.0) {
                pixel_cur.s = 1.0;
            }
		}
	}
}

void Image::grayscale() {
	unsigned int width_image = width();
	unsigned int height_image = height();
	for (unsigned int h = 0; h < height_image; h++) {
		for (unsigned int w = 0; w < width_image; w++) {
			HSLAPixel & pixel_cur = getPixel(w, h);
			pixel_cur.s = 0.0;
		}
	}
}

void Image::rotateColor(double degrees) {
	unsigned int width_image = width();
	unsigned int height_image = height();
	for (unsigned int h = 0; h < height_image; h++) {
		for (unsigned int w = 0; w < width_image; w++) {
			HSLAPixel & pixel_cur = getPixel(w, h);
			pixel_cur.h += degrees;
			while (pixel_cur.h > 360.0) {
				pixel_cur.h -= 360.0;
			}
			while (pixel_cur.h < 0.0) {
				pixel_cur.h += 360.0;
			}
		}
	}
}

void Image::illinify() {
	unsigned int image_width = width();
	unsigned int image_height = height();
	for (unsigned int h = 0; h < image_height; h++) {
		for (unsigned int w = 0; w < image_width; w++) {
			HSLAPixel & cur_pixel = getPixel(w, h);
			if (cur_pixel.h >= 113.5 && cur_pixel.h < 293.5) {
                cur_pixel.h = 216;
            } else {
                cur_pixel.h = 11;
            }
		}
	}
}

void Image::scale(double factor) {
    if (factor == 1.0) {
		return;
	}
    Image copy = Image(*this);
    unsigned widthNew = width() * factor;
    unsigned heightNew = height() * factor;
    resize(widthNew, heightNew);
    for (unsigned x = 0; x < widthNew; x ++) {
        for (unsigned y = 0; y < heightNew; y ++) {
            HSLAPixel & pixelThis = getPixel(x, y);
            HSLAPixel & pixelCopy = copy.getPixel(x/factor, y/factor);
            pixelThis = pixelCopy;
        }
    }
}

void Image::scale(unsigned w, unsigned h) {
    double factorWidth = (1.0 * w) / width();
    double factorHeight = (1.0 * h) / height();
    double factor = std::min(factorWidth, factorHeight);
    scale(factor);
}