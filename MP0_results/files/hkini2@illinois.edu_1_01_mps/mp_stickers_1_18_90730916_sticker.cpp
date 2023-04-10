#include "Image.h"
#include "StickerSheet.h"
#include <iostream>

int main() 
{
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma;
  Image i;
  Image penguin;
  alma.readFromFile("alma.png");
  i.readFromFile("i.png");
  penguin.readFromFile("penguin.png");
  StickerSheet img(alma, 4);
  img.addSticker(i, 15, 15;
  img.addSticker(penguin, 10, 30);
  Image final = img.render();
  final.writeToFile("myImage.png");
  return 0;
}
