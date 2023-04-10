/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once

#include "Image.h"
#include "cs225/PNG.h"
#include <iostream>
using namespace std;
class Image: public cs225::PNG
{
public:
  Image(unsigned width, unsigned height) : cs225::PNG(width, height) {}; //done
  Image() : cs225::PNG() {}; //done
  void lighten(); //done
  void lighten(double amount); //done
  void darken(); // done
  void darken(double amount); //done
  void grayScale(); //done
  void illinify(); //done
  void desaturate(); //done
  void desaturate(double amount); //done
  void rotateColor(double degrees); //done
  void saturate(); //done
  void saturate(double amount); //done
  void scale(double factor); //done
  void scale(unsigned w, unsigned h); //done

private:

};