/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once
#include "../lib/cs225/PNG.h"
using namespace cs225;

class Image : public PNG {
    private:
        unsigned int width_;
        unsigned int height_;

    public:
        Image();
        Image(unsigned int w, unsigned int h); 
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
        void illinify();
        void scale(double factor);
        void scale(unsigned width, unsigned height);

        unsigned int x;
        unsigned int y;

};