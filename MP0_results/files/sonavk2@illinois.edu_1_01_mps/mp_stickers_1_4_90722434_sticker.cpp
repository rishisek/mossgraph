#include "Image.h"
#include "StickerSheet.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma;
  alma.readFromFile("alma.png");

  Image spongebob;
  spongebob.readFromFile("spongebob.png");

  Image bill;
  bill.readFromFile("bill.png");

  Image donkey;
  donkey.readFromFile("donkey.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(spongebob, 20, 30);
  sheet.addSticker(bill, 40, 50);
  sheet.addSticker(donkey, 60, 70);

  Image output = sheet.render();

  output.writeToFile("myImage.png");

  return 0;
}
