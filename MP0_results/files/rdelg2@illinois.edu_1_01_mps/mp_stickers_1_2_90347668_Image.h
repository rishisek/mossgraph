/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once
#include "cs225/PNG.h"

using namespace std;
using namespace cs225;


class Image : public PNG {
    public:
        Image();
        Image(unsigned int x, unsigned int y);
        void darken();
        void darken(double amount);
        void desaturate();
        void desaturate(double amount);
        void grayscale();
        void illinify();
        void lighten();
        void lighten(double amount);
        void rotateColor(double degrees);
        void saturate();
        void saturate(double amount);
        void scale(double factor);
        void scale(unsigned int w, unsigned int h);
};
