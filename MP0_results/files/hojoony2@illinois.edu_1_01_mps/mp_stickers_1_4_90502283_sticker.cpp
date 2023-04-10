#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image alma; alma.readFromFile("../data/alma.png");
  Image i; i.readFromFile("../data/i.png");

  StickerSheet sheet(alma, 3);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 140, 150);
  sheet.addSticker(i, 100, 120);
  sheet.addSticker(i, 110, 200);
  sheet.addSticker(i, 130, 150);

  sheet.render().writeToFile("myImage.png");
  
  return 0;
}
