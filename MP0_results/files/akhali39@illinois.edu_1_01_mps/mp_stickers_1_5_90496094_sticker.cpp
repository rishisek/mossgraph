#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma;
  Image illini;
  Image penguin;

  penguin.readFromFile("../data/penguin.png");
  alma.readFromFile("../data/alma.png");
  illini.readFromFile("../data/i.png");

  StickerSheet sticker(alma, 3);
  sticker.addSticker(illini, 30, 70);
  sticker.addSticker(penguin, 100, 212);
    sticker.addSticker(alma, 500, 500);

    Image result = sticker.render();
    result.writeToFile("myImage.png");


  return 0;
}
