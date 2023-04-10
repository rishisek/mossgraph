#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  // Image alma; alma.readFromFile("../data/alma.png");
  // Image i;    i.readFromFile("../data/i.png");

  // StickerSheet sheet(alma, 5);

  // {
  //   Image almaDuplicate = alma;

  //   StickerSheet sheetDuplicate(almaDuplicate, 5);
  //   sheet = sheetDuplicate;
  // }

  // sheet.addSticker(i, 800, 200);
  // sheet.addSticker(i, 50, 500);

  // sheet.changeMaxStickers(7);
  // sheet.removeSticker(1);
  // sheet.changeMaxStickers(4);

  // //sheet.render().writeToFile("tmp.png");

  // sheet.removeSticker(0);

  // sheet.addSticker(i, 20, 500);
  // sheet.changeMaxStickers(1);

  // //sheet.render().writeToFile("tmp.png");

  // sheet.removeSticker(0);
  // sheet.changeMaxStickers(2);

  // sheet.addSticker(i, 800, 200);
  // sheet.addSticker(i, -100, -500);

  // sheet.render().writeToFile("tmp.png");

 Image alma; alma.readFromFile("../data/alma.png");
  Image i;    i.readFromFile("../data/i.png");

  StickerSheet sheet(alma, 5);

  /**
   * For testing deep copy of base image
   * The {...} are used for a block statement
   * and are intentional
   */
  sheet.addSticker(i, 800, 200);
  sheet.addSticker(i, 50, 500);
  sheet.addSticker(i, 630, 300);

  sheet.render().writeToFile("myImage.png");

  return 0;
}
