#include "Image.h"
#include "StickerSheet.h"

int main() {
  Image alma; 
  alma.readFromFile("../data/alma.png");
  Image i;    
  i.readFromFile("../data/i.png");

  StickerSheet sheet(alma, 2);
  sheet.addSticker(i, 20, 200);

  sheet.render().writeToFile("myImage.png");

  return 0;
}
