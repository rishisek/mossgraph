#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image yahoo;
  yahoo.readFromFile("../yahoo.png");

  Image guy1;
  guy1.readFromFile("../guy1.png");
  guy1.scale(300,300);

  Image guy2;
  guy2.readFromFile("../guy2.png");
  guy2.scale(100, 100);

  Image guy4;
  guy4.readFromFile("../guy4.png");
  guy4.scale(250,250);


  StickerSheet background(yahoo, 10);
  background.addSticker(guy1, 0, 30);
  background.addSticker(guy2, 50,50);
  background.addSticker(guy4, 70,70);
  background.render();
  background.render().writeToFile("../myImage.png");
  return 0;
}
