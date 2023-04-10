/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once
#include "cs225/PNG.h"
#include <cmath>
using namespace cs225;

class Image : public cs225::PNG {

    public:

    PNG image_;
    
    // creates an empty Image
    Image();

    //creates an Image of the specified dimensions
    Image(unsigned int width, unsigned int height);

    

    //Darken an Image by decreasing the luminance of every pixel by 0.1
    void darken();

    //Darkens an Image by decreasing the luminance of every pixel by amount
    void darken(double amount);

    //Desaturates an Image by decreasing the saturation of every pixel by 0.1
    void desaturate();

    //Desaturates an Image by decreasing the saturation of every pixel by amount
    void desaturate(double amount);

    //Turns the image grayscale 
    void grayscale();

    //Illinify the image 
    void illinify();


    //ligthen an image by increasing the luminance of every pixel by 0.1
    void lighten();

    //Lighten an image by increasing the luminace of every pixel by amount
    void lighten(double amount);

    //Rotates the color wheel by degrees
    void rotateColor(double degrees);

    //Saturates an Image by increasing the saturation of every pixel by 0.1
    void saturate();

    //Saturates an Image by increasing the saturation of every pixel by amount
    void saturate(double amount);

    //Scale the image by a given factor
    void scale(double factor);

    //Scales the image to fit within the size (w,h)
    void scale(unsigned w, unsigned h);


};

