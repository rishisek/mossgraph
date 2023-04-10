#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma, sticker1, sticker2, sticker3;

  alma.readFromFile("../data/alma.png");
  sticker1.readFromFile("../data/expected-2.png");
  sticker2.readFromFile("../data/expected-3.png");
  sticker3.readFromFile("../data/expected-4.png");

  StickerSheet sticker4(alma, 3); 
  sticker4.addSticker(sticker1, 100, 100); 
  sticker4.addSticker(sticker2, 300, 500); 
  sticker4.addSticker(sticker3, 600, 600); 

  Image result = sticker4.render(); 
  result.writeToFile("myImage.png"); 
  return 0;
}
