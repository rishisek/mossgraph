#include <iostream>
#include "Image.h"
#include "StickerSheet.h"

int main() {

  Image thebowl;
  thebowl.readFromFile("cs225git/mp_stickers/SuperBowl.png");

  Image greater;
  greater.readFromFile("cs225git/mp_stickers/GreaterThan.png");
  Image eagles;
  eagles.readFromFile("cs225git/mp_stickers/EaglesLogo.png");
  Image chiefs;
  chiefs.readFromFile("cs225git/mp_stickers/ChiefsLogo.png");

  StickerSheet image(thebowl, 3);
  image.addSticker(greater, 500, 500);
  image.addSticker(chiefs, 100, 500);
  image.addSticker(eagles, 750, 500);

  Image release = image.render();
  release.writeToFile("myImage.png");

  return 0;
}