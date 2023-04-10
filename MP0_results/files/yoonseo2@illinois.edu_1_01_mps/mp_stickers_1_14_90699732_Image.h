/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#include "cs225/PNG.h"

using namespace cs225;

#pragma once

class Image : public PNG {
  public:
    Image();
    Image(unsigned int width, unsigned int height);
    void darken();
    void darken(double amount);
    void lighten();
    void lighten(double amount);
    void saturate();
    void saturate(double amount);
    void desaturate();
    void desaturate(double amount);
    void grayscale();
    void scale(double factor);
    void scale(unsigned w, unsigned h);
    void illinify();
    void rotateColor(double degrees);

};