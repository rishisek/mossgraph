#include "Image.h"
#include "StickerSheet.h"

int main() {
    Image savanna, elephant, lion, giraffe;
    savanna.readFromFile("stickers/savanna.png");
    elephant.readFromFile("stickers/elephant.png");
    lion.readFromFile("stickers/lion.png");
    giraffe.readFromFile("stickers/giraffe.png");
    

    elephant.scale(0.5);
    lion.scale(0.5);
    giraffe.scale(0.5);

    StickerSheet sheet(savanna, 5);
    sheet.addSticker(elephant, 150,320);
    sheet.addSticker(lion, 500,150);
    sheet.addSticker(giraffe, 200,400);
    //sheet.addSticker(lion, 200,400);
    //sheet.addSticker(lion, 50, 50);

    Image output = sheet.render();
    output.writeToFile("myImage.png");

    return 0;
}


