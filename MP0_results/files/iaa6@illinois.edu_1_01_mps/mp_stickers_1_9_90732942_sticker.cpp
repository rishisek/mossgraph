#include "Image.h"
#include "StickerSheet.h"

#include "StickerSheet.h"
#include "Image.h"
using std::cout;
using std::endl;

int main (){
    Image alma; 
    alma.readFromFile("../data/alma.png");
    Image i;    
    i.readFromFile("../data/i.png");
    StickerSheet sheet(alma, 5);
    sheet.addSticker(i, 20, 200);
    (sheet.render()).writeToFile("myImage.png");
    cout<<"hejn"<<endl;
    return 0;
}