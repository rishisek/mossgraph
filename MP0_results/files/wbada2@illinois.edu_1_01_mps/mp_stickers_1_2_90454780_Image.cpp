#include "Image.h"

using namespace std;

Image::Image(){

    // creating a new image through the PNG class
    //PNG* image = new PNG();
    PNG image = PNG();

    image_ = image;

}

Image::Image(unsigned int width, unsigned int height){

    PNG image = PNG(width, height);
    image_ = image;
    // creating  new image with the dimentions of width and height that is passed in
    //PNG* image = new PNG(width,height);

}


void Image::darken(){

    for(unsigned int i=0; i < width(); i++){
        for(unsigned int j=0; j < height(); j++){
            
            HSLAPixel& pixel = getPixel(i,j);

            pixel.l = pixel.l - 0.1;

            if(pixel.l < 0){
                pixel.l = 0;
            }

            if(pixel.l > 1){
                pixel.l = 1;
            }
        }
    }

}

void Image::darken(double amount){

    for(unsigned int i=0; i < width(); i++){
        for(unsigned int j=0; j < height(); j++){

            HSLAPixel& pixel = getPixel(i,j);

            pixel.l = pixel.l - amount;

            if(pixel.l < 0){
                pixel.l = 0;
            }

            if(pixel.l > 1){
                pixel.l = 1;
            }
        }
    }

}

void Image::desaturate(){

    for(unsigned int i=0; i < width(); i++){
        for(unsigned int j=0; j < height(); j++){

            HSLAPixel& pixel = getPixel(i,j);

            pixel.s = pixel.s - 0.1;

            if(pixel.s < 0){
                pixel.s = 0;
            }

            if(pixel.s > 1){
                pixel.s = 1;
            }
        }
    }

}

void Image::desaturate(double amount){
      for(unsigned int i=0; i < width(); i++){
        for(unsigned int j=0; j < height(); j++){

            HSLAPixel& pixel = getPixel(i,j);

            pixel.s = pixel.s - amount;

            if(pixel.s < 0){
                pixel.s = 0;
            }

            if(pixel.s > 1){
                pixel.s = 1;
            }
        }
    }

}

void Image::grayscale(){
    
    for(unsigned int i=0; i < width(); i++){
        for(unsigned int j=0; j < height(); j++){

            HSLAPixel& pixel = getPixel(i,j);
            pixel.s = 0;
        }
    }


}

void Image::illinify(){


    for(unsigned int i=0; i < width(); i++){
        for(unsigned int j=0; j < height(); j++){

            HSLAPixel& pixel = getPixel(i,j);

            //double closeOrange = abs(pixel.h - 11);
            //double closeBlue = abs(pixel.h - 216);
            if(pixel.h < 0){
                pixel.h += 360;
            }
            else if(pixel.h > 360){
                pixel.h -= 360;
            }
            
            if(pixel.h >= 0 && pixel.h <= 113){
                pixel.h = 11; //makes orange
            }
            else if(pixel.h > 113 && pixel.h <= 293){
                pixel.h = 216; //makes blue
            }
            else if(pixel.h > 293 && pixel.h <= 360){
                pixel.h =11; //makes orange

            }




           /* if(closeOrange > closeBlue){
                pixel.h = 11;
            }
            else{
                pixel.h = 216;
            }*/
            
        
        }
    }

}

void Image::lighten(){

    for(unsigned int i=0; i < width(); i++){
        for(unsigned int j=0; j < height(); j++){

            HSLAPixel& pixel = getPixel(i,j);

            pixel.l = pixel.l + 0.1;

            if(pixel.l < 0){
                pixel.l = 0;
            }

            if(pixel.l > 1){
                pixel.l = 1;
            }
        }
    }

}

void Image::lighten(double amount){

    for(unsigned int i=0; i < width(); i++){
        for(unsigned int j=0; j < height(); j++){

            HSLAPixel& pixel = getPixel(i,j);

            pixel.l = pixel.l + amount;

            if(pixel.l < 0){
                pixel.l = 0;
            }

            if(pixel.l > 1){
                pixel.l = 1;
            }
        }
    }

}

void Image::rotateColor(double degrees){

    for(unsigned int i=0; i < width(); i++){
        for(unsigned int j=0; j < height(); j++){
            
            HSLAPixel& pixel = getPixel(i,j);

            if((pixel.h + degrees) > 360){
                double diff = (pixel.h + degrees)- 360;
                pixel.h = diff;
            }

            else if(pixel.h + degrees < 0){
                double sum = (pixel.h + degrees) + 360;
                pixel.h = sum;
            }

            else{
                pixel.h = pixel.h + degrees;
            }
        }
    }
    

}

void Image::saturate(){

    for(unsigned int i=0; i < width(); i++){
        for(unsigned int j=0; j < height(); j++){

            HSLAPixel& pixel = getPixel(i,j);

            pixel.s = pixel.s + 0.1;

            if(pixel.s < 0){
                pixel.s = 0;
            }

            if(pixel.s > 1){
                pixel.s = 1;
            }
        }
    }


}

void Image::saturate(double amount){
    for(unsigned int i=0; i < width(); i++){
        for(unsigned int j=0; j < height(); j++){

            HSLAPixel& pixel = getPixel(i,j);

            pixel.s = pixel.s + amount;

            if(pixel.s < 0){
                pixel.s = 0;
            }

            if(pixel.s > 1){
                pixel.s = 1;
            }
        }
    }


}

void Image::scale(double factor){
    //PNG copy = *this;

    Image copy = Image(*this);

    resize(factor * width(),factor * height());

    //nearest neigbor scaling algorithm
    for(unsigned int i=0; i < width(); i++){ // ask about using double in for loop
        for(unsigned int j=0; j < height(); j++){

            HSLAPixel pixel = copy.getPixel(i/factor, j/factor);
            getPixel(i,j) = pixel; 


        }
    }
}


void Image::scale(unsigned w, unsigned h){
 
    double widthFactor = ((double)w/(double)width());
    double heightFactor = ((double)h/(double)height());

    if (widthFactor > heightFactor){
        scale(heightFactor);
    }
    else if (widthFactor < heightFactor){
        scale(widthFactor);
    }
    else{
        scale(heightFactor);
    }




}