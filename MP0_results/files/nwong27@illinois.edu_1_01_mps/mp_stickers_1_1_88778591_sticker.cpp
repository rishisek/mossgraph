#include <iostream>
#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma, firststicker, secondsticker, thirdsticker, output;
  alma.readFromFile("alma.png");
  firststicker.readFromFile("thug.resized.png");
  secondsticker.readFromFile("corn.resized.png");
  thirdsticker.readFromFile("i.resized.png");

  StickerSheet mp1pic(alma, 4);
  mp1pic.addSticker(firststicker, 415, 35);
  mp1pic.addSticker(secondsticker, 295, 60);
  mp1pic.addSticker(secondsticker, 550, 60);
  mp1pic.addSticker(thirdsticker, 400, 140);
  output = mp1pic.render();
  output.writeToFile("myImage.png");

  return 0;
}