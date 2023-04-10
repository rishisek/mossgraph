#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image logo;
  logo.readFromFile("logo.png");
  Image illinois;
  illinois.readFromFile("illinois.png");
  Image dolphin;
  dolphin.readFromFile("dolphin.png");
  Image bird;
  bird.readFromFile("bird.png");

  StickerSheet mp1(logo, 3);
  mp1.addSticker(illinois, 700, 350);
  mp1.addSticker(dolphin, 25, 350);
  mp1.addSticker(bird, 25, 250);

  Image finalpic = mp1.render();
  finalpic.writeToFile("myImage.png");
  return 0;

 
}
