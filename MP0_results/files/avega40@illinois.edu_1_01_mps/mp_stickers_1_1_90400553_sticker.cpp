#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
Image background;
background.readFromFile("../data/White.png");
Image logoOne;
background.readFromFile("../data/LogoOne.png");
Image logoTwo;
background.readFromFile("../data/LogoTwo.png");
Image mucTechWhite;
background.readFromFile("../data/MucTechWhite.png");
Image mucTechColor;
background.readFromFile("../data/MucTechColor.png");
StickerSheet sheet(background, 4);
sheet.addSticker(logoOne,0,0);
sheet.addSticker(logoTwo,0,0);
sheet.addSticker(mucTechColor,0,0);
sheet.addSticker(mucTechWhite,0,0);
(sheet.render()).writeToFile("myImage.png");
return 0;
}