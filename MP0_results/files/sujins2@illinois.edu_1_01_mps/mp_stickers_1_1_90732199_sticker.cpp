#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image alma;
  alma.readFromFile("../data/alma.png");

  Image penguin;
  penguin.readFromFile("../data/penguin.png");

  Image bigI;
  penguin.readFromFile("../data/i.png");

  

  StickerSheet sheet(alma, 3);
  sheet.addSticker(penguin, 100, 100);
  sheet.addSticker(penguin, 0, 0);
  sheet.addSticker(bigI, 20, 20);

  Image result;
  result.writeToFile("../build/myImage.png");

  return 0;
}
