#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image dababy;
  Image almapic;

  almapic.readFromFile("../data/alma.png");
  dababy.readFromFile("../data/penguin.png");
  dababy.scale(0.5);
  StickerSheet a(almapic,1);
  a.addSticker(dababy,400,10);
  Image b = a.render();
  b.writeToFile("myImage.png");
  return 0;
}
