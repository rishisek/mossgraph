#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma; alma.readFromFile("../data/alma.png");

  Image A;    A.readFromFile("../data/among.png");
	A.scale(.2);

  Image B;    B.readFromFile("../data/bernie.png");
  B.scale(0.5);
  Image S;    S.readFromFile("../data/sonic.png");
	S.scale(.3);


  StickerSheet sheet(alma, 5);
	sheet.addSticker(A, 0, 400);
	sheet.addSticker(B, 300, 200);
	sheet.addSticker(S, 650, 300);
	sheet.render().writeToFile("myImage.png");


  return 0;
}
