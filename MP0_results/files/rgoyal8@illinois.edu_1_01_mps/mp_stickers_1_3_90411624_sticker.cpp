#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma;
  Image ILL;



  //std::cout << "Using Image::lighten to create `lighten.png`..." << std::endl;
  alma.readFromFile("../data/alma.png");
  ILL.readFromFile("../data/i.png");
  StickerSheet sheet(alma, 5);
  sheet.addSticker(ILL, 20, 200);
  if(sheet.render() == alma){
    return 1;
  };



  return 0;
}
