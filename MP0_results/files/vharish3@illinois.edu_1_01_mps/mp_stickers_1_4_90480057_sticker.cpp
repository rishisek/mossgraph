#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image alma,sticker1,sticker2,sticker3;
  alma.readFromFile("../data/alma.png");
  sticker1.readFromFile("../data/penguin.png");
  sticker2.readFromFile("../data/i.png");
  sticker3.readFromFile("../data/penguin.png");
  
  
  StickerSheet output(alma, 2);
  output.addSticker(sticker1, 300, 80);
  output.addSticker(sticker2, 600, 60);
  output.addSticker(sticker3, 4000, 40);
  output.setStickerAtLayer(sticker2, 1, 60, 200);


  Image finalImage_ = output.render();
  finalImage_.writeToFile("myImage.png");
  
  return 0;
}
