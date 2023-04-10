#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image bunnygirl; bunnygirl.readFromFile("../data/bunnygirl.png");
  Image mai;    mai.readFromFile("../data/mai.png");
  Image sakuta;    sakuta.readFromFile("../data/sakuta.png");
  Image title;    title.readFromFile("../data/title.png");
  Image vin;    vin.readFromFile("../data/diesel.png");
  StickerSheet sheet(bunnygirl, 3);
  sheet.addSticker(title, 0, 1080);
  sheet.addSticker(mai, -600, 100);
  sheet.addSticker(sakuta, -450, 125);
  sheet.addSticker(vin, 1630, 300);
  (sheet.render()).writeToFile("myImage.png");
  return 0;
}
