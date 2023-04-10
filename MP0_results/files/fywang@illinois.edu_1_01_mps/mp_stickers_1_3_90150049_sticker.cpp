#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //


  Image alma; alma.readFromFile("../data/alma.png");
  Image i;    i.readFromFile("../data/i.png");
  Image penguin;    penguin.readFromFile("../data/penguin.png");
  penguin.scale(0.9);

  StickerSheet sheet(alma, 5);

  sheet.addSticker(i, 330, 100);
  sheet.addSticker(penguin, 350, 0);

  (sheet.render()).writeToFile("myImage.png");

  return 0;
}
