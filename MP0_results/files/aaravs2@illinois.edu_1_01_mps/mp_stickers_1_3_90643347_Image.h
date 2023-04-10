/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once
#include "/workspaces/cs225/cs225git/mp_stickers/lib/cs225/PNG.h"

class Image : public cs225::PNG{
public:
    Image();
    Image (unsigned int width, unsigned int height);
    void lighten();
    void lighten(double amount);
    void darken(); 
    void darken(double amount);
    void saturate();
    void saturate(double amount);
    void desaturate();
    void desaturate(double amount);
    void greyscale();
    void rotateColor(double degrees);
    void illinify();
    void scale(double factor);
    void scale(unsigned w, unsigned h);
    
};