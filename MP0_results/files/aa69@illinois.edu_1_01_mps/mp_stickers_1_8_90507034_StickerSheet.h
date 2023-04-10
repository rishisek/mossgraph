/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h" 
#include <vector>
using namespace std;

namespace cs225 {
class StickerSheet {
	public:
    StickerSheet (const Image &picture, unsigned max); //done //max is the max number of stickers that can be placed on the stickersheet
	//picture is a constant reference. Image object as a constant reference 
	//to the StickerSheet constructor means that the image will remain unchange but Stickersheet can access the data and perform operations on it.

	StickerSheet (const StickerSheet &other); //done
	~StickerSheet();// done
	void copy(const StickerSheet &other);
	
	//copy constructor The other parameter 
	//is a constant reference to another StickerSheet object.
	//the const keyword means that the other object wont be modified the copy constructor
	
	const StickerSheet & operator= (const StickerSheet &other); //j

//An assignment operator is a member function that is used to 

// assign the value of one object to another object of the same type.
	
	void changeMaxStickers (unsigned max); // donej
	int setStickerAtLayer (Image &sticker, unsigned layer, int x, int y); //x
	int addSticker (Image &sticker, int x, int y); //donej
	bool translate (unsigned index, int x, int y); //donej
	void removeSticker (unsigned index); // donej
	Image * getSticker (unsigned index);  //donej
	int layers () const; // done
	Image render () const;// done
	

	private: 
	//Image pic;
	unsigned stick_max; // max number of stickers
	unsigned stick_obj; 
	Image base; // base picture
	struct Stit {
		int x_coord; 
		int y_coord;
		Image *new_img; };

	
	vector <Stit> vec; 

}; 
}
