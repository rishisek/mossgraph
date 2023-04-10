/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once

#include <string> 
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225; 

class Image : public PNG {
    public:
        Image() : PNG() {};
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
        void setStart(unsigned x, unsigned y) {
            start_x = x;
            start_y = y;
        };
        unsigned getStartX() {
            return start_x;
        };
        unsigned getStartY() {
            return start_y;
        };
    private:
        unsigned start_x = 0;
        unsigned start_y = 0;
};