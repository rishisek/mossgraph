#include "Image.h"
#include "StickerSheet.h"

int main() {

  Image backImage, elephantImage, tigerImage, pigImage;

  backImage.readFromFile("../cowBackImage.png");

  elephantImage.readFromFile("../elephant.png");

  tigerImage.readFromFile("../tiger.png");
  pigImage.readFromFile("../pig.png");

  StickerSheet sheet(backImage, 3);
  sheet.addSticker(elephantImage, 1000, 1000);
  sheet.addSticker(tigerImage,0,1000);
  sheet.addSticker(pigImage, 0,0);

  sheet.render().writeToFile("myImage.png");




  
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  


  return 0;
}
 