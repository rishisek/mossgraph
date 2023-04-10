/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once

#include "cs225/PNG.h" 
#include <string>

using namespace cs225; // as given in the png.h file
class Image : public PNG  // inheritance 
{  
    public : 
    Image(); // creating public member functions
    Image(unsigned int width, unsigned int height); 
    void lighten(); 
    void lighten (double amount);
    void darken ();
    void darken(double amount);
    void saturate ();
    void saturate(double amount);
    void desaturate();
    void desaturate(double amount);
    void grayscale();
    void rotateColor(double degrees);
    void illinify();
    void scale(double factor); 
    void scale(unsigned w, unsigned h);

}; 