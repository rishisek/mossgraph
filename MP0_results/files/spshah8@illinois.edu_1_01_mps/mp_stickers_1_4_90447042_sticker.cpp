#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma;
  Image sticky_one;
  Image sticky_two;
  Image sticky_three;
  alma.readFromFile("../data/alma.png");
  sticky_one.readFromFile("../data/i.png");
  sticky_two.readFromFile("../data/penguin.png");
  sticky_three.readFromFile("../data/i.png");
  
  
  StickerSheet output(alma, 2);
  output.addSticker(sticky_one, 500, 70);
  output.addSticker(sticky_two, 500, 40);
  output.addSticker(sticky_three, 2000, 80);


  Image fin = output.render();
  fin.writeToFile("myImage.png");
  return 0;
}
