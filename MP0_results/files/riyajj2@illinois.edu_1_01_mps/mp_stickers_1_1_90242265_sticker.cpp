#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma; alma.readFromFile("../data/alma.png");
   Image penguin;    penguin.readFromFile("../data/penguin.png");
   Image neon; neon.readFromFile("../data/neon.png");

  StickerSheet sheet(neon, 3);
  sheet.addSticker(penguin, 200, 800);
  sheet.addSticker(penguin, 550, 500);
  sheet.addSticker(penguin, 900, 800);

  Image res = sheet.render();

  res.writeToFile("../visual/sticker.png");

  res.writeToFile("../visual/sticker.png");

  return 0;
}
