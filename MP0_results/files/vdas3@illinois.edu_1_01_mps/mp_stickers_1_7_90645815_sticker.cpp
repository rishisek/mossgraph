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
  StickerSheet s(alma, 2);
  s.addSticker(penguin, 0, 0);
  std::cout << s.layers() << std::endl;
  s.changeMaxStickers(6);
  // s.render().writeToFile("../data/agilan.png");
  std::cout << s.layers() << std::endl;
  s.changeMaxStickers(0);
  std::cout << s.layers() << std::endl;
  std::cout << s.getSticker(0) << std::endl;
  return 0;
}
