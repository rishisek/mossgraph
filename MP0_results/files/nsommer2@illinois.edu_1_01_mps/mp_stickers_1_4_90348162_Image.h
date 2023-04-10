#pragma once

#include <string>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;

class Image : public PNG {

	public:

		void lighten();
		void lighten(double amount);
		void darken();
		void darken(double amount);
		void saturate();
		void saturate(double amount);
		void desaturate();
		void desaturate(double amount);
		void grayscale();
		void grayscale(double amount);
		void rotateColor(double degrees);
		void illinify();
		void scale(double factor);
		void scale(unsigned x, unsigned y);
};