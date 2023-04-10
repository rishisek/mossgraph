#include "Image.h"
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

  StickerSheet sheet(alma, 2);

  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 60, 200);
  sheet.addSticker(i, 100, 200);
  sheet.addSticker(i, 1300 - i.width(), 1000 - i.height());
  sheet.addSticker(i, -400, -400);

  alma = sheet.render();

  alma.writeToFile("sticker.png");

  return 0;
}
