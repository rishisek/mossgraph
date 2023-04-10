#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image classroom, student, penguin;
  classroom.readFromFile("../data/classroom.png");
  //student.readFromFile("../data/student.png");
  //penguin.readFromFile("../data/penguin.png");

  classroom.scale(4);
  penguin.scale(1);

  StickerSheet sheet(classroom, 5);
  //sheet.addSticker(student, 510,320);
  //sheet.addSticker(penguin, 550,350);
   

  Image output = sheet.render();
  output.writeToFile("myImage.png");
  return 0;
}
