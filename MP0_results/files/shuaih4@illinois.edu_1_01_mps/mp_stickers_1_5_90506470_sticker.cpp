#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma; alma.readFromFile("../data/alma.png");
  Image i;    i.readFromFile("../data/i.png");

  StickerSheet sheet(alma, 3);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 60, 200);
  sheet.addSticker(i, 100, 200);

  Image output = sheet.render();
  output.writeToFile("myImage.png");
  
  return 0;
}
