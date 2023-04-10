#include "Image.h"
#include "StickerSheet.h"

int main() {
  Image alma;
  Image sticker;
  alma.readFromFile("../data/alma.png");
  StickerSheet stickerman(alma, 5);
  sticker.readFromFile("../data/i.png");
  stickerman.addSticker(sticker, 0, 0);
  stickerman.addSticker(sticker, 5, 0);
  stickerman.addSticker(sticker, 10, 0);
  stickerman.addSticker(sticker, 15, 0);
  stickerman.addSticker(sticker, 20, 0);
  stickerman.addSticker(sticker, 25, 0);
  stickerman.addSticker(sticker, 30, 0);
  stickerman.addSticker(sticker, 40, 0);
  stickerman.addSticker(sticker, 45, 0);
  stickerman.addSticker(sticker, 50, 0);
  stickerman.addSticker(sticker, 55, 0);
  stickerman.addSticker(sticker, 60, 0);
  stickerman.render().writeToFile("myImage.png");
  return 0;
}
