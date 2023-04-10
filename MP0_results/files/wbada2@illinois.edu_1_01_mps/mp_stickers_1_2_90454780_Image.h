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

        Image();
            //creates an empty image


        Image(unsigned int width, unsigned int height);
            //creates an image of the specified dimenions


        void darken();
            //darken an image by decreasing the luminance of everyh pixel by 0.1


        void darken(double amount);
            //darkens an image by decreasing the luminance of every pixel by amount (remains in range [0,1])


        void desaturate();
            //desaturates an image by decreasing the saturation of every pixel by 0.1


        void desaturate(double amount);
            //desaturates an image by decreasing the saturation of every pixel by amount (remains in range [0,1])


        void grayscale();
            //turns the image grayscale


        void illinify();
            //illinify the image


        void lighten();
            //lighten the image by increasing the luminance of every pixel by 0.1


        void lighten(double amount);
            //lighten the image by increasing the luminance of every pixel by amount (remains in the range [0,1])


        
        void rotateColor(double degrees);
            //rotates the color wheel by degrees
            //rotating in the positive direction increases the hue
            //remains in the range [0,360]

        void saturate();
            //saturates the image by increasing the saturation of every pixel by 0.1


        void saturate(double amount);
            //saturates the image by increasing the saturation of every pixel by amount (remains in range [0,1])

        
        void scale(double factor);
            //scale the image by a given factor
            //a factore of 0.5 results in an image with half the width and half the height

        void scale(unsigned w, unsigned h);
            //scales the image to fit within the size (wxh)


};
