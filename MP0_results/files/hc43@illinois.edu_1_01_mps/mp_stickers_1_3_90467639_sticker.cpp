#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
 Image uiuc, computer, smile,happy;
 uiuc.readFromFile("uiuc.png");
 computer.readFromFile("computer.png");
smile.readFromFile("smile.png");
happy.readFromFile("happy.png");
StickerSheet my_sticker(uiuc,6);
my_sticker.addSticker(computer,123,231);
my_sticker.addSticker(smile,444,555);
my_sticker.addSticker(happy,999,999);

Image mywork=my_sticker.render();
mywork.writeToFile("myImage.png");
 return 0;
}
