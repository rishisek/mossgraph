#include "Image.h"
#include "StickerSheet.h"

#include <iostream>

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  

 Image alma;     alma.readFromFile("../data/alma.png");
  Image i;        i.readFromFile("../data/i.png");
  Image expected; expected.readFromFile("../data/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 0, 0);
  sheet.addSticker(i, 20, 50);
  sheet.addSticker(i, 40, 50);

  // std::cout << "made it here" << std::endl;
  

  sheet.render().writeToFile("myImage.png");

  


  return 0;
}
