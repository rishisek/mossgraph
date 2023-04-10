#include "Image.h"


Image::Image(): PNG(){}

Image::Image (unsigned int width, unsigned int height): PNG(width, height)
{ 
 // creating an image using PNG
 // when calling constructor of another class within this class, use initializer list to initialize new class object simultaneously 
 // here calling PNG constructor inside the Image constructor
}

void Image::darken()
{
    // go through each pixel in the image, decrease each lum by 0.1, provided it is initially greater than 0.1
    for(unsigned int row = 0; row < height(); ++row){
        for(unsigned int col = 0; col < width(); ++col){
            cs225::HSLAPixel& pixel = getPixel(col, row);
            if(pixel.l >= 0.1){
                pixel.l -= 0.1;
            }
           else{
                pixel.l = 0.0;
           }
        }
    }
}

void Image::darken(double amount)
{
    // darken the lum of each pixel by given amount
    for(unsigned int row = 0; row < height(); ++row){
        for(unsigned int col = 0; col < width(); ++col){
            cs225::HSLAPixel& pixel = getPixel(col, row);
            if(pixel.l >= amount){
                pixel.l -= amount;
            }
            else{
                pixel.l = 0;
            }
            
        }
    }
}	

void Image::desaturate()
{
    // decrease saturation of each pixel by 0.1
    for(unsigned int row = 0; row < height(); ++row){
        for(unsigned int col = 0; col < width(); ++col){
            cs225::HSLAPixel& pixel = getPixel(col, row);
            if(pixel.s >= 0.1){
                pixel.s -= 0.1;
            }
            else{
                pixel.s = 0;
            }
            
        }
    }
}

void Image::desaturate(double amount)
{
    // decrease saturation of each pixel by 0.1
    for(unsigned int row = 0; row < height(); ++row){
        for(unsigned int col = 0; col < width(); ++col){
            cs225::HSLAPixel& pixel = getPixel(col, row);
            if(pixel.s >= amount){
                pixel.s -= amount;
            }
            else{
                pixel.s = 0;
            }
            
        }
    }
}

void Image::grayscale()
{
    // make each pixel's saturation = 0
    for(unsigned int row = 0; row < height(); ++row){
        for(unsigned int col = 0; col < width(); ++col){
            getPixel(col, row).s = 0;
        }
    }
}

void Image::lighten()
{
    // increase the lum by 0.1, as long as original lum <= 0.9
    for(unsigned int row = 0; row < height(); ++row){
        for(unsigned int col = 0; col < width(); ++col){
            cs225::HSLAPixel& pixel = getPixel(col, row);
            if(pixel.l <= 0.9){
                pixel.l += 0.1;
            }
            else{
                pixel.l = 1.0;
            }
            
        }
    }
}

void Image::lighten (double amount)
{
    // increase the lum by amount, as long as original lum <= 0.9
    for(unsigned int row = 0; row < height(); ++row){
        for(unsigned int col = 0; col < width(); ++col){
            cs225::HSLAPixel& pixel = getPixel(col, row);
            if(pixel.l <= (1.0 - amount)){
                pixel.l += amount;
            }
            else{
                pixel.l = 1.0;
            }
            
        }
    }
}

void Image::saturate()
{
    // increase saturation of every pixel by 0.1
    for(unsigned int row = 0; row < height(); ++row){
        for(unsigned int col = 0; col < width(); ++col){
            cs225::HSLAPixel& pixel = getPixel(col, row);
            if(pixel.s <= 0.9){
                pixel.s += 0.1;
            }
            else{
                pixel.s = 1.0;
            }
            
        }
    }
}

void Image::saturate(double amount)
{
    // increase saturation of every pixel by 0.1
    for(unsigned int row = 0; row < height(); ++row){
        for(unsigned int col = 0; col < width(); ++col){
            cs225::HSLAPixel& pixel = getPixel(col, row);
            if(pixel.s <= (1.0 - amount)){
                pixel.s += amount;
            }
            else{
                pixel.s = 1.0;
            }
            
        }
    }
}

void Image::rotateColor(double degrees)
{
    // increase hue of each pixel by degrees, keep within [0,360]
    for(unsigned int row = 0; row < height(); ++row){
        for(unsigned int col = 0; col < width(); ++col){
            cs225::HSLAPixel& pixel = getPixel(col, row);

            pixel.h += degrees;

            if(pixel.h < 0){
                pixel.h += 360;
            }
            else if(pixel.h > 360){
                pixel.h -= 360;
            }

        }
    }
}

void Image::illinify()
{
    // compare each pixel with orange hue and blue hue. assign whichever is closer
    for(unsigned int row = 0; row < height(); ++row){
        for(unsigned int col = 0; col < width(); ++col){
            int orange_comp = std::abs(getPixel(col, row).h - 11);
            int blue_comp = std::abs(getPixel(col, row).h - 216);

            if(orange_comp < blue_comp ){
                getPixel(col, row).h = 11;
            }
            else{
                getPixel(col, row).h = 216;
            }
        }
    }
} 



void Image::scale(double factor)
{
    // 1. create a new image of type Image with the new width and height(scaled)
    // 2. assign that new height and width to a varibale, for use in the for loop
    // 3. populate the new image
    // 4. each pixel from the original image is assigned to its corresponding pixelS in the resized newImage
    unsigned int newWidth = width() * factor;
    unsigned int newHeight = height() * factor;
    Image newImage(newWidth,  newHeight);
    // std::cout << "old width: "<< width() << "new width "<< newWidth << "old height: "<< height() << "new height "<< newHeight << std::endl;
    for(unsigned int row = 0; row < newHeight; ++row){
        for(unsigned int col = 0; col < newWidth; ++col){
            unsigned int scaled_col = std::floor((col / factor));
            unsigned int scaled_row = std::floor((row / factor));
            // cs225::HSLAPixel& old_pixel = this->getPixel(scaled_col, scaled_row);
            
            // cs225::HSLAPixel& new_pixel = newImage.getPixel(col, row);
           
            // new_pixel = old_pixel;

            newImage.getPixel(col, row) = getPixel(scaled_col, scaled_row);
          
        }

    }


    // now pointing new image to be the current image 
    *this = newImage;

}


void Image::scale (unsigned w, unsigned h)
{

    double scale_height = static_cast<double>(h);
    double orig_height = static_cast<double>(height());
    double scale_width = static_cast<double>(w);
    double orig_width = static_cast<double>(width());

    double height_factor = scale_height / orig_height;
    double width_factor = scale_width / orig_width;

    double scale_factor;
    height_factor < width_factor ? (scale_factor = height_factor) : (scale_factor = width_factor);
   

    unsigned int newWidth = width() * scale_factor;
    unsigned int newHeight = height() * scale_factor;
    Image newImage(newWidth,  newHeight);

    for(unsigned int row = 0; row < newHeight; ++row){
        for(unsigned int col = 0; col < newWidth; ++col){
            int scaled_col = (col /scale_factor);
            int scaled_row = (row / scale_factor);
            newImage.getPixel(col, row) = getPixel(scaled_col, scaled_row);
        }
    }

    // now pointing new image to be the current image 
    *this = newImage;

}