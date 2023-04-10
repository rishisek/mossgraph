#include "Image.h"
#include "StickerSheet.h"
#include <iostream>

int main() {
  //
  // Reminder:
  // Before exiting main, save your creation to disk as myImage.png
  //

  Image alma;
  alma.readFromFile("../data/alma.png");
  
  Image penguin;
  penguin.readFromFile("../data/penguin.png");
 
  Image big_I;
  big_I.readFromFile("../data/i.png");

  StickerSheet s(alma, 3);
  
  s.addSticker(penguin, -50, -50);
  s.addSticker(big_I, 300, 500);
  s.addSticker(penguin, 900, 100);

  Image i = s.render();
  i.writeToFile("myImage.png");

  return 0;
}
