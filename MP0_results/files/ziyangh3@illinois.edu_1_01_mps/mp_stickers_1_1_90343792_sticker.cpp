#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //


  Image alma; alma.readFromFile("../data/alma.png");
  Image a;    a.readFromFile("../data/path.png");
  Image b;    b.readFromFile("../data/blood.png");
  Image c;    c.readFromFile("../data/valk.png");
  a.scale(0.2);
  b.scale(0.35);
  c.scale(0.08);
  StickerSheet sheet(alma, 1);
  sheet.addSticker(a, 125, 240);
  sheet.addSticker(b, 500, 320);
  sheet.addSticker(c, 40, 40);
  Image output = sheet.render();
  output.writeToFile("render.png");
  return 0;
}
