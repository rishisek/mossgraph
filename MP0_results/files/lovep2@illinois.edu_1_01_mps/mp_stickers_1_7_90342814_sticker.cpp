#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  
  Image uiuc;   uiuc.readFromFile("../data/UIUC.png");
  Image man_saluting;  man_saluting.readFromFile("../data/Man_Saluting.png");
  Image ece;  ece.readFromFile("../data/ECE.png");
  Image nfl;  nfl.readFromFile("../data/nfl.png");
  uiuc.scale(10);
  ece.scale(1.8);
  nfl.scale(1.5);
  man_saluting.scale(0.5);
  StickerSheet sheet(uiuc, 4);
  sheet.addSticker(ece, 0, 0);
  sheet.addSticker(man_saluting, 2940, 0);
  sheet.addSticker(nfl, 1500, 1080);
  sheet.render().writeToFile("myImage.png");
  return 0;
}
