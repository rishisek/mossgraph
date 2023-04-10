#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image myImage;
  Image alma; alma.readFromFile("../data/alma.png");
  Image i;    i.readFromFile("../data/i.png");
  Image penguin; penguin.readFromFile("/workspaces/cs225git/mp_stickers/data/penguin.png");

  StickerSheet sheet(alma, 2);
  sheet.addSticker(i, 420, 25);
  sheet.addSticker(penguin, 2,200);
  sheet.addSticker(penguin, 20,20);

  Image new_image = sheet.render();
  new_image.writeToFile("../build/myImage.png");

  return 0;
}
