#include "Image.h"
#include "StickerSheet.h"
#include <iostream> 

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image base; base.readFromFile("../data/base.png");
  Image i;    i.readFromFile("../data/i.png");
  Image hi;    hi.readFromFile("../data/hi.png");
  Image bye;    bye.readFromFile("../data/bye.png");

StickerSheet sheet(base, 5);
sheet.addSticker(i, 20, 20);
sheet.addSticker(hi, 5, 5);
sheet.addSticker(bye, 11, 19);

sheet.render().writeToFile("myImage.png");
//Image *i = new Image(180, 50); 
//i->scale(50,50);m
//std::cout<<i->width()<<" "<<i->height()<<std::endl;

 return 0;
}
