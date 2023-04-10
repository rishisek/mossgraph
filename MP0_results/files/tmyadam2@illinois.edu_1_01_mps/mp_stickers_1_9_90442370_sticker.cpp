#include "Image.h"
#include "StickerSheet.h"

int main() {
  Image alma;
  alma.readFromFile("../data/alma.png");
  Image pen;
  pen.readFromFile("../data/penguin.png");
  Image illinois;
  illinois.readFromFile("../data/i.png");
  //Image spiderman;
  //spiderman.readFromFile("../data/SpidermanMeme.png");

  StickerSheet beauty(alma,5);
  beauty.addSticker(alma, 20, 10);
  beauty.addSticker(illinois, 30,10);
  beauty.addSticker(pen, 10, 20);
  beauty.addSticker(pen, 30, 100);
  //beauty.addSticker(spiderman, 20, 30);
  Image a = beauty.render();
  a.writeToFile("Image.png");
  return 0;
}
