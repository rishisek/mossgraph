/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once

#include <math.h>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

class Image : public cs225::PNG {
    public:
        Image(); //Creates an empty Image. 
        Image(unsigned int width, unsigned int height); //Creates an Image of the specified dimensions. 
        
        void lighten(); //Lighten an Image by increasing the luminance of every pixel by 0.1. 
        void lighten(double amount); //Lighten an Image by increasing the luminance of every pixel by amount. 
        
        void darken(); //Darken an Image by decreasing the luminance of every pixel by 0.1. 
        void darken(double amount); //Darkens an Image by decreasing the luminance of every pixel by amount. 
        
        void saturate(); //Saturates an Image by increasing the saturation of every pixel by 0.1. 
        void saturate(double amount); //Saturates an Image by increasing the saturation of every pixel by amount. 
        
        void desaturate(); //Desaturates an Image by decreasing the saturation of every pixel by 0.1. 
        void desaturate(double amount); //Desaturates an Image by decreasing the saturation of every pixel by amount. 
        
        
        void grayscale(); //Turns the image grayscale. 
        
        void rotateColor(double degrees); //Rotates the color wheel by degrees. 
        void illinify(); //Illinify the image. 
        
        void scale(double factor); //Scale the Image by a given factor. 
        void scale(unsigned w, unsigned h); //Scales the image to fit within the size (w x h). 
         
};

