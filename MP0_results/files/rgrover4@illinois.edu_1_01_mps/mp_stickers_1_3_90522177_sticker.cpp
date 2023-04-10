#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image penguin;
  Image alma;
  Image temp;
  Image temp2;
  penguin.readFromFile("../penguin.png");
  alma.readFromFile("../alma.png");
  temp.readFromFile("../temp.png");
  temp2.readFromFile("../temp2.png");
  StickerSheet complete(penguin, 4);
  complete.addSticker(alma, 100, 100);
  complete.addSticker(temp, 150, 150);
  complete.addSticker(temp2, 200, 200);
  Image retVal = complete.render();
  retVal.writeToFile("../MyImage.png");

  return 0;
}
