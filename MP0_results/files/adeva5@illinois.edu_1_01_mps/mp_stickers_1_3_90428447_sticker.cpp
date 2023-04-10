#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image base;
  base.readFromFile("");
  Image s1;
  s1.readFromFile("");
  Image s2;
  s2.readFromFile("");
  Image s3;
  s3.readFromFile("");
  StickerSheet sheet(base, 3);
  sheet.addSticker(s1, 100, 100);
  sheet.addSticker(s2, 200, 200);
  sheet.addSticker(s3, 300, 300);
  Image render = sheet.render();
  render.writeToFile("myImage.png");

  return 0;
}
