#include "Image.h"
#include "StickerSheet.h"
#include <iostream>

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image baseimage;
  baseimage.readFromFile("../data/bigbaseimage2.png");
  Image blackcat;
  blackcat.readFromFile("../data/blackcat2.png");
  Image textcat;
  textcat.readFromFile("../data/textcat2.png");
  Image whitecat;
  whitecat.readFromFile("../data/whitecat2.png");
  
  
  

  StickerSheet cats(baseimage, 3);
  cats.addSticker(blackcat, 20, 20);
  cats.addSticker(textcat, 1000, 500 );
  cats.addSticker(whitecat, 70, 1000);

  Image myImage = cats.render();
  myImage.writeToFile("myImage.png");
  return 0;
}
