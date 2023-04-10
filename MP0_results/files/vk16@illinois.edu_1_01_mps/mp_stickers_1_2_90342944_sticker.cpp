#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma;
  alma.readFromFile("../data/alma.png");
  Image i;    
  i.readFromFile("../data/i.png");
  Image peng;
  peng.readFromFile("../data/penguin.png");

  StickerSheet sheet(alma, 3);

  sheet.addSticker(i, 20, 200);
  sheet.addSticker(peng, 340, 350);
  sheet.addSticker(i, 650, 200);

  sheet.render().writeToFile("myImage.png");

  return 0;
}
