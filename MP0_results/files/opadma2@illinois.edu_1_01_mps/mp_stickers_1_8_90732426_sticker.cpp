#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  //
  //board,dog,fish,note
  Image b;     b.readFromFile("board.png");
  Image i;        i.readFromFile("dog.png");
  Image a;        a.readFromFile("fish.png");
  Image c;        c.readFromFile("note.png");

  StickerSheet sheet(b, 3);
  sheet.addSticker(i, 40, 30);
  sheet.addSticker(a, 400, 40);
  sheet.addSticker(c, -1000, -1000);
  Image * x = sheet.render()
  x.writeToFile("customPhoto5.png");
  //delete x;
  return 0;
}
