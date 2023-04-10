#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image cow;
  cow.readFromFile("../cow.png");
  StickerSheet s(cow, 4);

  Image i;
  i.readFromFile("../i.png");

  Image apple;
  apple.readFromFile("../apple.png");

  Image banana;
  banana.readFromFile("../banana.png");

  s.addSticker(i,10,10);
  s.addSticker(apple, 200, 150);
  s.addSticker(banana, 500, 600);

  Image myImage = s.render();
  myImage.writeToFile("../myImage.png");



  return 0;
}
