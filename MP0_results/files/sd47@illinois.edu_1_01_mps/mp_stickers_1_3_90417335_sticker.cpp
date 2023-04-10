#include "Image.h"
#include "StickerSheet.h"
#include <iostream>
#include <fstream>

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image background;
  background.readFromFile("../data/carBackground2.png");
  
  Image sticker1;
  sticker1.readFromFile("../data/starSticker.png");

  Image sticker2;
  sticker2.readFromFile("../data/fireheadSticker.png");

  Image sticker3;
  sticker3.readFromFile("../data/burnoutSticker.png");

  StickerSheet sheet1(background, 4);
  sheet1.addSticker(sticker1, 0, 30);
  sheet1.addSticker(sticker2, -300, 30);
  sheet1.addSticker(sticker3, 700, 30);

  
  Image output = sheet1.render();
  output.writeToFile("myImage.png");

  return 0;
}
