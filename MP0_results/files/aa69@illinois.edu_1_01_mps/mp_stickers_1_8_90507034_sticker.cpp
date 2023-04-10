#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
Image alma, rashford, garnacho, bruno;

alma.readFromFile("../data/alma.png");
rashford.readFromFile("../data/penguin.png");
garnacho.readFromFile("../data/penguin.png");

StickerSheet degea(alma,4);
degea.addSticker(rashford, 400, 350);
degea.addSticker(garnacho, 35, 350);
degea.addSticker(bruno, 65, 55);

Image no = degea.render();
no.writeToFile("myImage.png");

  

return 0;
}
