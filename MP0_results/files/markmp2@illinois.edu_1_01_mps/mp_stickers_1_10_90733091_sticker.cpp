#include "Image.h"
#include "StickerSheet.h"

int main() {
  
  Image sky, a, b, c;
  sky.readFromFile("Stickers/sky.png");
  a.readFromFile("Stickers/a.png");
  b.readFromFile("Stickers/b.png");
  c.readFromFile("Stickers/c.png");

  a.scale(0.5);
  b.scale(2);

  StickerSheet sheet(sky, 3);
  sheet.addSticker(a, 420,210);
  sheet.addSticker(b, 360,400);
  sheet.addSticker(c, 150,600);

  Image output = sheet.render();
  output.writeToFile("myImage.png");


  return 0;
}
