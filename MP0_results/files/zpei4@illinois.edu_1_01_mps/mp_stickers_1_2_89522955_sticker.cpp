#include <iostream>
#include "Image.h"
#include "StickerSheet.h"

int main() {

  Image photo1;
  photo1.readFromFile("photo1.png");
  Image photo2;
  photo2.readFromFile("photo2.png");
  Image photo3;
  photo3.readFromFile("photo3.png");

  StickerSheet mySticker(photo1, 3);
  mySticker.addSticker(photo1, 700, 350);
  mySticker.addSticker(photo2, 25, 350);
  mySticker.addSticker(photo3, 25, 25);

  Image pic = mySticker.render();
  pic.writeToFile("myImage.png");

  return 0;
}