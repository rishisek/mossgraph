#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma;
  Image piplup;
  Image fondue;
  Image cat;

  alma.readFromFile("../data/alma.png");
  piplup.readFromFile("../data/piplup.png");
  fondue.readFromFile("../data/fondue.png");
  cat.readFromFile("../data/cat.png");

  StickerSheet partThree(alma);
  partThree.addSticker(piplup, 200, 300);
  partThree.addSticker(fondue, 50, 70);
  partThree.addSticker(cat, 100, 150);

  partThree.render().writeToFile("myImage.png");
  return 0;


  return 0;
}
