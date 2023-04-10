#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma;     alma.readFromFile("../data/alma.png");
  Image i;        i.readFromFile("../data/i.png");

  StickerSheet s(alma, 10);
  s.addSticker(i, 100, 100);
  s.translate(0, 200, 200);
  s.render().writeToFile("myImage.png");

  return 0;
}
