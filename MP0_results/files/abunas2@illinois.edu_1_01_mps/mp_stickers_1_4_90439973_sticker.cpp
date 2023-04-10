#include "Image.h"
#include "StickerSheet.h"

int main() {
  Image background_mp;
  Image pisa;
  Image runner;
  Image skier;
  Image surfboard;

  background_mp.readFromFile("../data/background_mp.png");
  pisa.readFromFile("../data/pisa.png");
  runner.readFromFile("../data/runner.png");
  skier.readFromFile("../data/skier.png");
  surfboard.readFromFile("../data/surfboard.png");

  pisa.saturate(0.03);
  skier.scale(0.75);
  runner.scale(0.5);
  surfboard.darken(0.2);
  surfboard.scale(0.4);
  //pisa.rotateColor(4);


  StickerSheet sheet(background_mp, 5);
  sheet.addSticker(pisa, 0, 0);
  sheet.addSticker(runner, 0, 1200);
  sheet.addSticker(skier, 1000, 1300);
  sheet.addSticker(surfboard, 0,1600);

  Image to_return = sheet.render();
  to_return.writeToFile("myImage.png");

  return 0;
}
