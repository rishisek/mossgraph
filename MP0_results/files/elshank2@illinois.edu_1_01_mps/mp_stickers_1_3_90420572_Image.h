/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once

#include <iostream>
#include <string>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace std;
// how to make subclass of PNG???
// do i need private variables like width_ and length_ like that in PNG.h
class Image : public cs225::PNG{
    public:
        Image();
        Image(unsigned int width, unsigned int height);
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
        void scale(unsigned w, unsigned h);
    private:
    PNG * image_;
};