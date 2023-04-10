#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
Image uiuc, computer, graingerlogo;
uiuc.readFromFile("uiuc.png");
computer.readFromFile("computer.png");
graingerlogo.readFromFile("grianderlogo.png");
StickerSheet my_sticker(uiuc,6);
my_sticker.addSticker(computer,555,578);
my_sticker.addSticker(graingerlogo,0,1);
my_sticker.addSticker(graingerlogo,999,765);

Image mywork=my_sticker.render();
mywork.writeToFile("myImage.png");
 return 0;
}