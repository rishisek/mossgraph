#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image base_img;
  base_img.readFromFile("../data/alma.png");
  StickerSheet test_img = StickerSheet(base_img, 5);

  Image stkr;
  stkr.readFromFile("../data/i.png");

  test_img.addSticker(stkr, 30, 140);
  test_img.addSticker(stkr, 70, 340);
  test_img.addSticker(stkr, 200, 14);

  Image output = test_img.render();
  output.writeToFile("../myImage.png");
  return 0;
}
