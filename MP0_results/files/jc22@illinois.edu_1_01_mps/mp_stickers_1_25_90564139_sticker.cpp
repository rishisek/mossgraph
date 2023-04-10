#include "Image.h"
#include "StickerSheet.h"
#include <fstream> 
#include <iostream>

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma; 
  alma.readFromFile("../alma.png"); 
  StickerSheet rabbitHole(alma, 3); 

  Image I; 
  I.readFromFile("../i.png");
  I.scale(0.2);
  
  rabbitHole.addSticker(I, 100, alma.height() - I.height());
  rabbitHole.render().writeToFile("../myImage.png");
  


  return 0;
}
