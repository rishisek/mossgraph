#include "Image.h"
#include "StickerSheet.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

int main() {
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  Image alma;
  alma.readFromFile("alma.png");

  Image captainfalcon;
  captainfalcon.readFromFile("captainfalcon.png");

  Image basketball;
  basketball.readFromFile("basketball.png");

  Image rob;
  rob.readFromFile("rob.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(captainfalcon, 10, 20);
  sheet.addSticker(basketball, 50, 50);
  sheet.addSticker(rob, 70, 90);

  Image output = sheet.render();

  output.writeToFile("myImage.png");

  return 0;
}
