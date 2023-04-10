#include "Image.h"
#include "StickerSheet.h"
#include <iostream>

using namespace std;

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma;     alma.readFromFile("../data/alma.png");
  Image i;        i.readFromFile("../data/i.png");
  Image expected; expected.readFromFile("../data/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 240, 200);
  sheet.addSticker(i, 480, 200);

  sheet.render().writeToFile("./myImage.png");

  cout << "Printed" << endl;

  return 0;
}
