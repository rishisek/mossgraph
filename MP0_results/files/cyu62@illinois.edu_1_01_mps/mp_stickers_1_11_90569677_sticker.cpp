#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image png;
  StickerSheet test(png, 0);
  StickerSheet nice(test);
  test = nice;
  test.changeMaxStickers(0);
  int num = test.addSticker(png, 0, 0);
  int five = test.setStickerAtLayer(png, 0, 0, 0);
  bool check = test.translate(0, 1, 2);
  test.removeSticker(0);
  Image* weird = test.getSticker(0);
  int afsd = test.layers();
  Image fasdf = test.render();

  return 0;
}
