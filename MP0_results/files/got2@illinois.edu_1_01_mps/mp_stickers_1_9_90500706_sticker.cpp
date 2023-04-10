#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image space;
  space.readFromFile("../data/space.png");
  Image moon;
  moon.readFromFile("../data/moon.png");
  Image penguin;
  penguin.readFromFile("../data/penguin.png");

  Image myImage;
  StickerSheet sheet(space, 1);
  sheet.addSticker(moon, 160, 40);
  sheet.addSticker(penguin, 320, 300);
  myImage = sheet.render();

  myImage.writeToFile("myImage.png");
  
  return 0;
}
