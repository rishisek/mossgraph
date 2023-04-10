#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
Image base;
  base.readFromFile("../data/basejpg.png");

Image star_sticker;
  star_sticker.readFromFile("../data/stick1jpg.png");
Image cloud_sticker;
  cloud_sticker.readFromFile("../data/stick2png.png");
Image ball_sticker;
  ball_sticker.readFromFile("../data/stick3png.png");

StickerSheet sheet(base, 3);
sheet.addSticker(star_sticker, 500, 500);
Image* a = sheet.getSticker(0);
if(*a == star_sticker){
  std::cout << 'y'<< std::endl;
}

  sheet.addSticker(cloud_sticker, 900, 300);
  sheet.addSticker(ball_sticker, 25, 425);

  Image img = sheet.render();
  img.writeToFile("myImage.png");

  return 0;
}
