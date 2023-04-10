#include "Image.h"
#include "StickerSheet.h"

int main() {
Image gg;
  gg.readFromFile("../data/i.png");

  Image valorant;
  valorant.readFromFile("../data/i.png");
  Image alma;
  alma.readFromFile("../data/alma.png");
  Image penguin;
  penguin.readFromFile("../data/penguin.png");

StickerSheet sheet(gg, 3);
sheet.addSticker(valorant, 500, 500);
Image* cringe = sheet.getSticker(0);
if(*cringe == valorant){
  std::cout << 'y'<< std::endl;
}

  sheet.addSticker(alma, 25, 350);
  sheet.addSticker(penguin, 25, 25);

  Image img = sheet.render();
  img.writeToFile("myImage.png");

  return 0;
}
