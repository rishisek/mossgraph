/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
    @author haydenj2
 */

#pragma once

#include <string>
using std::string;

#include "../lib/cs225/PNG.h"

class Image : public cs225::PNG{
    public:

    Image();    //creates an empty Image
    
    /**
    Creates an Image of specified dimenstions
    @param width Width of the new image.
    @param height Height of the new image.
    */
    Image(unsigned int width, unsigned int height);

    void lighten();     //lightens the image, increases l by 0.1

    /**
    lightens the image, increases l by a specified amount
    @param amount the amount to increase the luminance
    */
    void lighten(double amount);

    void darken();  //darkens the Image, decreases l by 0.1

    /**
    darkens the image, decreases l by a specified amount
    @param amount the amount to decrease the luminance
    */
    void darken(double amount);

    void saturate();    //saturates the image, increases s by 0.1

    /**
    saturates the image, increases s by a specified amount
    @param amount the amount to increase the saturation
    */
    void saturate(double amount);

    void desaturate();  //desaturates the Image, decreases s by 0.1

    /**
    desaturates the image, decreases s by a specified amount
    @param amount the amount to decrease the saturation
    */
    void desaturate(double amount);

    void grayscale();   //turn the image grayscale

    /**
    rotates the color wheel a specified number of degrees
    @param degrees the number of degrees to rotate the color value
    */
    void rotateColor(double degrees);

    void illinify();    //illinifies the image

    /**
    scales the image by a specified amount
    @param factor the amount to scale the image
    */
    void scale(double factor);

    /**
    scales the image to fit within the size w x h
    @param w width to scale the image into
    @param h height to scale the image into
    */
    void scale(unsigned w, unsigned h);
};