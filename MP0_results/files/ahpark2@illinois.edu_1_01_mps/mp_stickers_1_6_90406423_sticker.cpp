#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image basePicture;
  basePicture.readFromFile("../data/background.png");
  Image Spongebob;
  Spongebob.readFromFile("../data/spongebobwow.png");
  Image Gary;
  Gary.readFromFile("../data/garythesnail.png");
  Image Patrick;
  Patrick.readFromFile("../data/patrick.png");
  Image Amongus;
  Amongus.readFromFile("../data/amongus.png");
  
  StickerSheet sheet(basePicture, 4); 
  sheet.addSticker(Patrick, 260, 430);
  Patrick.scale(0.55);
  sheet.addSticker(Spongebob,900, 600);
  Spongebob.scale(1.3);
  sheet.addSticker(Gary, 1570, 420);
  Gary.scale(0.25);
  sheet.addSticker(Amongus, 1433, 713);
  Amongus.scale(0.025);
  Amongus.darken(0.1);
  Amongus.desaturate(0.15);
  Image render = sheet.render();
  render.writeToFile("../data/myImage.png");
  return 0;
}
