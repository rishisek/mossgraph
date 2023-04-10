#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image grad;
  grad.readFromFile("../alma.png");
  StickerSheet hmm(grad, 5);
  Image peng;
  peng.readFromFile("../penguin.png");
  peng.saturate(0.5);
  peng.darken(0.3);
  hmm.addSticker(peng, 50, 50);
  hmm.render().writeToFile("../myImage.png");


  return 0;
}
