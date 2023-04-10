/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <cmath>
#include <cstdlib>

class Image: public cs225::PNG{
    public:
            Image();
        	Image (unsigned int width, unsigned int height);
            void 	darken ();
            void 	darken (double amount);
            void 	desaturate ();
            void 	desaturate (double amount);
            void 	grayscale ();
            void 	lighten ();
            void 	lighten (double amount);
            void 	saturate ();
            void 	saturate (double amount);
            void 	rotateColor (double degrees);
            void 	illinify ();
            void 	scale (double factor);
            void 	scale (unsigned w, unsigned h);
    private:
        // int height_;
        // int width_;
        // double amount_;
        // double degrees_;
        // double factor_;
        // unsigned w_;
        // unsigned h_;

};
