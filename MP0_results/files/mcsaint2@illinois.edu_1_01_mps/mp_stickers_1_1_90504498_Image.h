/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once

#include "workspace/cs225/cs225git/mp_stickers/lib/cs225/PNG.h"

using namespace std;

namespace cs225 {
    class Image : public PNG {
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
    };
};
