#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  StickerSheet myImage = new StickerSheet("../data/alma.png", 3);
  myImage.addSticker("../data/i.png", 69, 69);
  myImage.addSticker("../data/i.png", 420, 69);
  myImage.addSticker("../data/penguin.png", 69, 420);

  

  return 0;
}
