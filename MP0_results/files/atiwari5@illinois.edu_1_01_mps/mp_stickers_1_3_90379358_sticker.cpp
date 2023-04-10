#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  // Image alma; 
  // alma.readFromFile("../data/alma.png");
  // Image i;    
  // i.readFromFile("../data/i.png");

  // StickerSheet sheet(alma, 5);  
  // sheet.addSticker(i, 20, 200);

  // Image expected;
  // expected.readFromFile("../data/expected.png");
  // sheet.render().writeToFile("../tests/myImage.png");
  // sheet.render();
  // bool result = sheet.render().writeToFile("../tests/myImage.png");

  // base image
  Image alma;
  alma.readFromFile("../data/sticker_5.png");
  // reading in stickers
  Image sticker_1;    
  sticker_1.readFromFile("../data/sticker_1.png");
  Image sticker_2;    
  sticker_2.readFromFile("../data/sticker_2.png");
  Image sticker_3;    
  sticker_3.readFromFile("../data/sticker_3.png");
  Image sticker_4;    
  sticker_4.readFromFile("../data/sticker_4.png");
  
  // creating sticker sheet
  StickerSheet sheet(alma, 5);
  // putting stickers in sticker sheet
  sheet.addSticker(sticker_1, 200, 500);
  sheet.addSticker(sticker_4, 1000, 1000);
  sheet.addSticker(sticker_2, 2000, 2000);
  sheet.addSticker(sticker_3, 20, 2000);
  sheet.render().writeToFile("../tests/myImage.png");
  sheet.render();

  return 0;
}
