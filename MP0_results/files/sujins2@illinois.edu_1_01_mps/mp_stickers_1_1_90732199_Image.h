/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once

#include "../lib/cs225/PNG.h"
#include <string>

using namespace std;
using namespace cs225;

class Image : public PNG {
    public:
    Image();
    Image(unsigned, unsigned);

    void darken();
    void darken(double);

    void desaturate();
    void desaturate(double);

    void grayscale();

    void illinify();

    void lighten();
    void lighten(double);

    void rotateColor(double);
    
    void saturate();
    void saturate(double);

    void scale(double);
    void scale(unsigned, unsigned);
};