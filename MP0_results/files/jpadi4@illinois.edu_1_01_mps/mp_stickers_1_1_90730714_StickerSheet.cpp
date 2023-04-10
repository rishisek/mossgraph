#include <StickerSheet.h>
#include <Image.h>
/*
Initializes StickerSheet with deep copy of base picture and ability to hold max # of stickers
w/ indices 0 through max-1
*/
StickerSheet::StickerSheet(const Image& picture, unsigned max) {
    //background = Image(bg);
    background = Image(picture);
    maxlayers = max;
}

/*
Copy constructor makes StickerSheet independent copy of source

The stickers array is an array of POINTERS That point to an image, not the image itself
*/
StickerSheet::StickerSheet(const StickerSheet& other) {
    background = other.background;
    maxlayers = other.maxlayers;

    // goes through all stickers in the sticker vector of the other sheet 
    // creates a new Image object pointer to copy the sticker
    // adds that sticker to the sticker vector of the new stickersheet
    for(Image* sticker : other.stickers) {
        // for each sticker pointer in the array
        Image *copiedSticker = new Image(*sticker);

        // add the pointer to the array
        stickers.push_back(copiedSticker);
    }
}

/*
Destructor for StickerSheet class
Goes through everything in the stickers vector, frees memory, and sets ptrs to NULL
*/
StickerSheet::~StickerSheet() {
    for(Image* sticker : stickers) {
        delete(sticker);
        sticker = NULL;
    }
}

/*
Adds sticker to StickerSheet, so top-left of sticker's Image is at (x,y) on sticker sheet
Sticker must be added to lowest possible layer available
If all layers are filled, new layer must be added

sticker -- image 
x -- x location of sticker
y -- y location of sticker

returns: zero-based layer index sticker was added to
*/
/*int StickerSheet::addSticker(Image &sticker, int x, int y) {
    // if all current layers are filled, change the max # of layers
    Image* newSticker = new Image(sticker);
    newSticker -> x = x;
    newSticker -> y = y;
    if(stickers.size() == maxlayers) {
        changeMaxStickers(maxlayers + 1);
        stickers.push_back(newSticker);
        return stickers.max_size();
    } else {
        stickers.push_back(newSticker);
        return stickers.max_size();
    }

    // creates a new Image object pointer
    // assigns coords of top left corner of image
    // adds the sticker to the top of the vector
}*/

int StickerSheet::addSticker(Image &sticker, int x, int y) {
    Image* image = &sticker;
    image->x = x;
    image->y = y;

    if (stickers.size() == maxlayers) {
        maxlayers++;
        stickers.resize(maxlayers);
        stickers.push_back(image);
        return maxlayers-1;
    } else {
        stickers.push_back(image);
        return stickers.size() - 1;
    }
   
}

/*
Modifies max number of stickers that are stored on sticker sheet without changing stickers' indices
if new max # is smaller, stickers with indices above max-1 are lost
*/
void StickerSheet::changeMaxStickers(unsigned max) {
    if(max < (this -> maxlayers)) {
        for(unsigned int i = max; i > this -> maxlayers; i--) {
            removeSticker(i);
        }
    } else {
        this -> maxlayers = max;
        stickers.resize(max);
    }
}

/*
Returns ptr to sticker at specified index
This way, user can modify Image

If index is invalid, return NULL
*/
Image* StickerSheet::getSticker(unsigned index) {
    if(index > stickers.max_size() || index < 0) {
        return NULL;
    } else {
        return stickers[index];
    }
}

/*
Returns total # of layers available
*/
int StickerSheet::layers() const {
    return maxlayers;
}

/*
Operator for StickerSheet class

other -- Other StickerSheet object to copy data from
return -- constant StickerSheet ref
*/
const StickerSheet& StickerSheet::operator=(const StickerSheet &other) {
    if(this == &other) {
        return *this;
    }

    background = other.background;
    maxlayers = other.maxlayers;
    (this->stickers).resize(maxlayers);

    for(Image* sticker : stickers) {
        delete(sticker);
    }

    for(Image* sticker : other.stickers) {
        Image* copied = new Image(*sticker);
        stickers.push_back(copied);
    }

    return *this;
}  

/*
Remove sticker at given index
Stickers don't change order
*/
void StickerSheet::removeSticker(unsigned index) {
    // new pointer to get to indexed sticker
    Image *toDelete = stickers[index];
    delete toDelete; // delete memory
    toDelete = NULL; // makes ptr null
}

/*
Renders whole StickerSheet on one Image and returns Image

Base is drawn first
Each sticker is drawn in order from layer 0

If pixel alpha channel is 0, no pixel is drawn for sticker at pixel
If alpha channel is non-zero, a pixel is drawn

Returned image includes full contents of the picture and all stickers
Should expand in each corresponding direction if stickers go beyond edge
*/
Image StickerSheet::render() const{ 
    Image* final = new Image(background);
    /*unsigned int widest = background.width();
    unsigned int tallest = background.height();

    // for loop to put the sticker on the image
    for(Image* sticker : stickers) {
       
    }*/

    return *final;
}
/*
Adds sticker to StickerSheet at layer so top-left of sticker's Image is at (x,y) on stickersheet

Returns layer index or -1 if layer does not exist
*/
int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
    if(layer < 0 || layer > stickers.max_size()) {
        return -1;
    } else {
        Image* newSticker = new Image(sticker);
        newSticker -> x = x;
        newSticker -> y = y;
        stickers.at(layer) = newSticker;
        return layer;
    }
}

/*
changes x and y coordinates of image in layer
if layer is invalid or doesn't contain sticker, return false
otherwise, true
*/
bool StickerSheet::translate(unsigned index, int x, int y) {
    if(index < 0 || index > stickers.size() || stickers[index] == NULL) {
        return false;
    } else {
        Image *sticker = stickers[index];
        sticker -> x = x;
        sticker -> y = y;
        return true;
    }
}