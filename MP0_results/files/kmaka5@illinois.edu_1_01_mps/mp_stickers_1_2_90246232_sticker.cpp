#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma; alma.readFromFile("../data/alma.png");
  Image i;    i.readFromFile("../data/i.png");
  Image pen;    pen.readFromFile("../data/penguin.png");

  StickerSheet sheet(alma, 2);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 130, 500);
  sheet.addSticker(pen, 160, 300);

  Image res = sheet.render();

  res.writeToFile("/workspaces/cs225/cs225git/mp_stickers/entry/myImage.png");
  res.writeToFile("../visual/sticker.png"); //Testing purposes

  return 0;
}
