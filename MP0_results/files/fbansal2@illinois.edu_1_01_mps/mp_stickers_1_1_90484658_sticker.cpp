#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image alma;    alma.readFromFile("../data/alma.png");
  Image i;       i.readFromFile("../data/i.png");
  Image penguin; penguin.readFromFile("../data/penguin.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);

  i = penguin;

  std::cout<< sheet.render().writeToFile("myImage.png");
  return 0;
}
