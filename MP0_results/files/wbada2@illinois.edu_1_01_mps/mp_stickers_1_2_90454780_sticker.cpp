#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
Image background; background.readFromFile("../entry/backgroundImage Small.png");
Image alImage; alImage.readFromFile("../entry/alImage 2.png");
Image s1; s1.readFromFile("../entry/s1Image 2.png");
Image lastImage; lastImage.readFromFile("../entry/lastImage Small.png");


StickerSheet sheet(background,3);

sheet.addSticker(alImage, 100, 600);
sheet.addSticker(lastImage, 1500,800);
sheet.addSticker(s1,400,800);


sheet.render().writeToFile("myImage.png");
  return 0;
}
