/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once
#include "cs225/PNG.h"
using namespace std;

class Image: public cs225::PNG {
    public:
    Image(unsigned int width, unsigned int height);
    Image();
    void illinify();
    void lighten();
    void lighten(double amount);
    void darken();
    void darken(double amount);
    void saturate();
    void saturate(double amount);
    void desaturate();
    void desaturate(double amount);
    void grayscale();
    void rotateColor(double degrees);
    void scale(double factor);
    void scale(unsigned w, unsigned h);
};
