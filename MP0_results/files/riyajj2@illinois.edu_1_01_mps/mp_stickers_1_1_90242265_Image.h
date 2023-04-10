/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once

#include "../lib/cs225/PNG.h"
using namespace cs225;

class Image : public cs225::PNG {
 public:
    Image();
    Image(unsigned int, unsigned int);
    void darken(); //decrease luminance of every pixel by 0.1
    void darken(double amount);
    void desaturate(); //decrease saturation by .1
    void desaturate(double amount);
    void grayscale(); //turns image grayscale (s=0)
    void illinify();
    void lighten(); //increase luminance of every pixel by 0.1
    void lighten(double amount);
    void rotateColor(double degrees); //rotates color wheel by degrees in positive direction
    void saturate(); //increase saturation by .1
    void saturate(double amount);
    void scale(double factor); //1.0 scale doesn't change image, .5 results in half the width and height
    void scale(unsigned w, unsigned h); //preserves aspect ratio of image 
    
};   
