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
  alma.readFromFile("../data/alma.png");
  Image i;
  i.readFromFile("../data/i.png");
  Image happyfeet;
  happyfeet.readFromFile("../data/penguin.png");

  StickerSheet laflame(alma, 4);
 


  laflame.addSticker(alma, 10, 10);
  laflame.addSticker(i, 200, 20);
  laflame.addSticker(happyfeet, 50, 20);

  Image answer = laflame.render();

  answer.writeToFile("myImage.png");


  return 0;
}
