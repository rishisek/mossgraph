#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //



  Image background; background.readFromFile("../data/background.png");
  Image a;    a.readFromFile("../data/a.png");
  Image b;    b.readFromFile("../data/b.png");
  Image c;    c.readFromFile("../data/httd.png");
  a.scale(0.1);
  b.scale(0.52);
  c.scale(0.25);
  StickerSheet sheet(background, 1);
  sheet.addSticker(a, 590, 323);
  sheet.addSticker(b, 0, 339);
  sheet.addSticker(c, 225, 100);
  Image output = sheet.render();
  output.writeToFile("render.png");
  return 0;
}

