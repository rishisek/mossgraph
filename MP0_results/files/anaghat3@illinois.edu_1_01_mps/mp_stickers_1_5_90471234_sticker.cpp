#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma; 
  alma.readFromFile("../data/alma.png");
  Image penguin; 
  penguin.readFromFile("../data/penguin.png");
  Image snowman; 
  snowman.readFromFile("../data/snowman.png");
  Image succulent; 
  succulent.readFromFile("../data/succulent.png");
  Image sun; 
  sun.readFromFile("../data/sun.png");
  Image uiuc; 
  uiuc.readFromFile("../data/uiuc.png");

  StickerSheet sheet(alma, 5);  
  sheet.addSticker(penguin, 20, 200);
    sheet.addSticker(snowman, 10, 5);
  sheet.addSticker(succulent, 500, 600);
  sheet.addSticker(sun, 90, 300);
  sheet.addSticker(uiuc, 400, 200);


  sheet.render().writeToFile("../tests/myImage.png");
  sheet.render();
  bool result = sheet.render().writeToFile("../tests/myImage.png");



  return 0;
}
