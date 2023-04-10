#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image base;
  Image crane;
  Image minion;
  Image ian;
  base.readFromFile("../data/base.png");
  crane.readFromFile("../data/crane.png");
  minion.readFromFile("../data/minion.png");
  ian.readFromFile("../data/ian.png");
  
  //base.scale(900, 400);
  //crane.scale(200, 350);
  minion.scale(400,700);
  //ian.scale(200, 350);

  StickerSheet sheet(base, 3);

  sheet.addSticker(minion, -100, 35);
  sheet.addSticker(crane, 650, 25);
  sheet.addSticker(ian, 300, 25);

  sheet.render().writeToFile("myImage.png");  


  return 0;
}
