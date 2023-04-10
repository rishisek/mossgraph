#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image almamater;
  almamater.readFromFile("../data/alma.png");
  Image illinois;
  illinois.readFromFile("../data/i.png");
  Image pen;
  pen.readFromFile("../data/penguin.png");

  StickerSheet almamaterpicture(almamater, 7);
  almamaterpicture.addSticker(illinois,10,10);
  almamaterpicture.addSticker(pen,20,15);

  Image output = almamaterpicture.render();

  output.writeToFile("myImage.png");


  return 0;
}
