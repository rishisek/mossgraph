#include "Image.h"

using namespace std;

Image::Image(){
    PNG image =  PNG();
    image_ = image;

}

Image::Image(unsigned int width, unsigned int height){
   PNG image =  PNG(width, height);
   image_ = image;

}


void Image::darken(){
    for(unsigned int i=0; i< width(); i++){
        for(unsigned int j=0; j<height();j++){
            HSLAPixel& pixel =  getPixel(i,j);
            pixel.l = pixel.l - 0.1;

            if(pixel.l < 0){
                pixel.l =0;
            }

            if(pixel.l > 1){
                pixel.l =1 ;
            }

        }
    }

}

void Image::darken(double amount){
      for(unsigned int i=0; i< width(); i++){
        for(unsigned int j =0; j<height();j++){

            HSLAPixel& pixel =  getPixel(i,j);
            pixel.l = pixel.l - amount;

            if(pixel.l < 0){
                pixel.l =0;
            }

            if(pixel.l > 1){
                pixel.l =1;
            }

        }
    }
}

void Image::desaturate(){
    for(unsigned int i=0; i< width(); i++){
        for(unsigned int j =0; j<height();j++){
            HSLAPixel& pixel =  getPixel(i,j);
            pixel.s = pixel.s- 0.1;

            if(pixel.s < 0){
                pixel.s =0;
            }

            if(pixel.s > 1){
                pixel.s =1;
            }

        }
    }
}

void Image::desaturate(double amount){
    for(unsigned int i=0; i< width(); i++){
        for(unsigned int j =0; j<height();j++){
            HSLAPixel& pixel =  getPixel(i,j);
            pixel.s = pixel.s- amount;

            if(pixel.s < 0){
                pixel.s =0;
            }

            if(pixel.s > 1){
                pixel.s =1;
            }

        }
    }
}

void Image::lighten(){
    for(unsigned int i=0; i< width(); i++){
        for(unsigned int j =0; j<height();j++){
            HSLAPixel& pixel =  getPixel(i,j);
            pixel.l = pixel.l + 0.1;

            if(pixel.l < 0){
                pixel.l =0;
            }

            if(pixel.l > 1){
                pixel.l =1;
            }

        }
    }

}

void Image::lighten(double amount){
    for(unsigned int i=0; i< width(); i++){
        for(unsigned int j =0; j<height();j++){
            HSLAPixel& pixel =  getPixel(i,j);
            pixel.l = pixel.l + amount;

            if(pixel.l < 0){
                pixel.l =0;
            }

            if(pixel.l > 1){
                pixel.l =1;
            }

        }
    }

}

void Image::saturate(){
    for(unsigned int i=0; i< width(); i++){
        for(unsigned int j =0; j<height();j++){
            HSLAPixel& pixel =  getPixel(i,j);
            pixel.s = pixel.s + 0.1;

            if(pixel.s < 0){
                pixel.s =0;
            }

            if(pixel.s > 1){
                pixel.s =1;
            }

        }
    }

}

   
void Image::saturate(double amount){
     for(unsigned int i=0; i< width(); i++){
        for(unsigned int j =0; j<height();j++){
            HSLAPixel& pixel =  getPixel(i,j);
            pixel.s = pixel.s + amount;

            if(pixel.s < 0){
                pixel.s =0;
            }

            if(pixel.s > 1){
                pixel.s =1;
            }

        }
    }

}

void Image::grayscale(){
     for(unsigned int i=0; i< width(); i++){
        for(unsigned int j =0; j<height();j++){
            HSLAPixel& pixel =  getPixel(i,j);
            pixel.s = 0; 

        }
    }
}

void Image::rotateColor(double degrees){
    for(unsigned int i=0; i< width(); i++){
        for(unsigned int j =0; j<height();j++){

            HSLAPixel& pixel =  getPixel(i,j);

            if((pixel.h + degrees) > 360){
                double diff = (pixel.h + degrees) - 360;
                pixel.h = diff;
            }
            else if((pixel.h + degrees) < 0){
                double sum = (pixel.h + degrees) + 360;
                pixel.h = sum;

            }
            else{
               pixel.h =  pixel.h + degrees; 
            }

        }
    }
}

void Image::illinify(){

     for(unsigned int i=0; i< width(); i++){
        for(unsigned int j =0; j< height();j++){
            HSLAPixel& pixel =  getPixel(i,j);

            if(pixel.h < 0){
                pixel.h += 360;
            }
            else if(pixel.h > 360){
                pixel.h -= 360;
            }

            if(pixel.h >= 0 && pixel.h <= 113){
                pixel.h = 11;
            }
            else if(pixel.h > 113 && pixel.h <=293){
                pixel.h = 216;
            }
            else if(pixel.h > 293 && pixel.h <= 360){
                pixel.h = 11; 
            }


        }
    }
}

void Image::scale(double factor){
    //PNG copy = *this;
    //resize the image

    Image copy = Image(*this);

    resize(factor * width(), factor * height());

   for(unsigned int i=0; i< width(); i++){
        for(unsigned int j =0; j< height();j++){
            HSLAPixel& pixel =  copy.getPixel(i/factor, j/factor);
            getPixel(i,j) = pixel;
        }
    }
}

void Image::scale(unsigned  w, unsigned  h){


    double width_Factor = ((double)w/(double)width());
    double height_Factor = ((double)h/(double)height());
    
   if(width_Factor > height_Factor){
    scale(height_Factor);
   }
   else if(width_Factor < height_Factor){
    scale(width_Factor);
   }
   else{
    scale(height_Factor);
   }

}


