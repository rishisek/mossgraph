#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image ash, grass, pikachu, charizard, infernape, greninja, lucario, sceptile;
    ash.readFromFile("ash.png");
    grass.readFromFile("grass.png");
    pikachu.readFromFile("pikachu.png");
    charizard.readFromFile("charizard.png");
    infernape.readFromFile("infernape.png");
    greninja.readFromFile("greninja.png");
    lucario.readFromFile("lucario.png");
    sceptile.readFromFile("sceptile.png");

    grass.scale(2.5);
    ash.scale(0.7);

    StickerSheet sheet(grass, 5);
    sheet.addSticker(ash, 510,300);
    sheet.addSticker(pikachu, 520,310);
    sheet.addSticker(charizard, 530,320);
    sheet.addSticker(infernape, 540,330);
    sheet.addSticker(greninja, 550,340);
    sheet.addSticker(lucario, 560,350);
    sheet.addSticker(sceptile, 570,360);

    Image output = sheet.render();
    output.writeToFile("myImage.png");

  return 0;
}
