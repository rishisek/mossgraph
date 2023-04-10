#include <iostream>
#include "cs225/HSLAPixel.h"
#include "../src/Image.h"
using namespace cs225;
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma;
  Image monke;
  Image illini;
  Image penguin;
  
  monke.readFromFile("../data/monke.png");
  alma.readFromFile("../data/alma.png");
  illini.readFromFile("../data/i.png");
  penguin.readFromFile("../data/penguin.png");
  StickerSheet mysheet(alma, 4);
  //StickerSheet a_sheet = mysheet; //check


  
  mysheet.addSticker(illini, 100, 20);
  mysheet.addSticker(penguin, 30, 20);
  mysheet.addSticker(monke, 500, 500);
  Image final = mysheet.render();

  final.writeToFile("myImage.png");


  return 0;
}