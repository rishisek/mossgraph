#include "Image.h"
#include "StickerSheet.h"
#include <iostream>

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image alma; alma.readFromFile("alma.png");
  Image i;    i.readFromFile("i.png");
  
  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, alma.width()-50, 50);
  sheet.addSticker(i, 50, 50);
  sheet.addSticker(i, alma.width()/2, 100);
  Image expected = sheet.render();
  expected.writeToFile("myImage.png");


  

  return 0;
}
