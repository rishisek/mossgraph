// /**
//  * @file StickerSheet.h
//  * Contains your declaration of the interface for the StickerSheet class.
//  */
// #pragma once

// #include "Image.h"
// #include <vector>

// using namespace cs225;

// class StickerSheet {
// 	public:
// 		StickerSheet(const Image& picture, unsigned max); 
// 		StickerSheet(const StickerSheet& other);          
// 		const StickerSheet& operator=(const StickerSheet & other);   
//         ~StickerSheet();   
// 		void changeMaxStickers(unsigned max);
// 		int addSticker(Image & sticker, unsigned x, unsigned y);
//         int setStickerAtLayer(Image &sticker, unsigned layer, int x, int y);
// 		bool translate(unsigned index, unsigned x, unsigned y);
// 		void removeSticker(unsigned index);
// 		Image * getSticker(unsigned index) const;
//         int layers() const;
// 		Image render () const;
    
// 	//private:
// 		Image* base_;             // base image
//    		Image** sheet_;           // image of base with stickers
//   		unsigned* x_;            // pointer x array
//    		unsigned* y_;            // pointer y array
//    		unsigned max_, count_;
  
//   		void _copy(const StickerSheet& other);
//   		void _delete();
// };



/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"
#include <vector>

class StickerSheet {
	public:
		StickerSheet(const Image & picture, unsigned max);
		StickerSheet(const StickerSheet & other);
		~StickerSheet();
		const StickerSheet & operator=(const StickerSheet & other);
		void changeMaxStickers(unsigned max);
		int addSticker(Image & sticker, unsigned x, unsigned y);
		bool translate(unsigned index, unsigned x, unsigned y);
		void removeSticker(unsigned index);
		Image * getSticker(unsigned index) const;
		Image render ();

		int layers() const;
		int setStickerAtLayer(Image &sticker, unsigned layer, int x, int y);

	private:
		unsigned capacity, count;
		Image * base;
		Image ** sheet;
		unsigned * x_array;
		unsigned * y_array;
		void copy_(const StickerSheet & other);
		void delete_();
};