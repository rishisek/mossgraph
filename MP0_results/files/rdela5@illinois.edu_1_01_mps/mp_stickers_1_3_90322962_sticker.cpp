#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma;
  alma.readFromFile("../data/alma.png");

  StickerSheet mySheet(alma, 3);
  Image i;
  i.readFromFile("../data/i.png");

  mySheet.addSticker(i, 0, 0);
  mySheet.addSticker(i, 1100, 1000);
  mySheet.addSticker(i, -60, 0);

  Image myImage = mySheet.render();
  myImage.writeToFile("myImage.png");

  return 0;
}
