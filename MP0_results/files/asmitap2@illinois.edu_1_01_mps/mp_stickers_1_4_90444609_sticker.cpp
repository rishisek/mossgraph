#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
 
    Image uiuc, one, two, three;
    uiuc.readFromFile("Stickers/uiuc.png");
    one.readFromFile("Stickers/one.png");
    one.scale(20,30);
    two.readFromFile("Stickers/two.png");
    two.scale(0.7);
    three.readFromFile("Stickers/three.png");
    three.scale(7);

    
   

    StickerSheet teststicker(one, 5);
    teststicker.addSticker(two, 430,300);
    teststicker.addSticker(three, 600,120);
    teststicker.addSticker(uiuc, 390,4400);
  

    Image output = teststicker.render();
    output.writeToFile("myImage.png");

    return 0;
}




