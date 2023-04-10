#include "Image.h"
#include "StickerSheet.h"
//7:38PM@13th
int main() 
{
  Image adnan,sticker_1,sticker_2,sticker_3;
  adnan.readFromFile("Stickers/adnan.png");
  sticker_1.readFromFile("Stickers/sticker_1.png");
  sticker_2.readFromFile("Stickers/sticker_2.png");
  sticker_3.readFromFile("Stickers/sticker_3.png");

  
  sticker_1.scale(70, 80);
  sticker_2.scale(7.0);
  sticker_3.scale(0.25);

  StickerSheet output(adnan, 4);
  output.addSticker(sticker_1, 400, 60);
  output.addSticker(sticker_2, 400, 50);
  output.addSticker(sticker_3, 305, 50);

  Image final_output = output.render();
  final_output.writeToFile("myImage.png");
  
  return 0;
}

