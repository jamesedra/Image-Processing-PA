/**
 * File: block.cpp
 * Description: student implementation for Block functions
 *              for CPSC 221 2023S PA1
 *
 *              THIS FILE WILL BE SUBMITTED.
 */

#include "block.h"

/**
 * Creates a square Block that is dimension x dimension pixels in size,
 * starting at (x, y) on img. Assumes that the requested
 * Block fits on the image (inputs are feasible)
 */
void Block::Build(PNG& img, unsigned int x, unsigned int y, unsigned int dimension) {
	// the vector goes pixel to pixel to accumulate on data like this:
	// | | | | | | | | | |
	// | | | | | | | | | |
	// | | | | | | | | | |
	// | | | | | | | | | |
	// | | | | | | | | | |
	// v v v v v v v v v v
	// in order to get something from the data by data[width][height]
	for (unsigned width = 0; width < dimension; width++) {
		// create a temporary vector
		vector<HSLAPixel> temp;
		for (unsigned height = 0; height < dimension; height++) {
			// for each pixel starting from the x and y coordinates
			HSLAPixel* p = img.getPixel(x + width, y + height);
			// add it to the vector
			temp.push_back(*p);
		}
		// add the temporary vector to data
		data.push_back(temp);
	}
}

/**
 * Renders this Block onto img with its upper-left corner at (x, y).
 * Assumes block fits on the image.
 */
void Block::Render(PNG& img, unsigned int x, unsigned int y) const {
	// this method is to overwrite the existing image with the block
	for (unsigned width = 0; width < data.size(); width++) {
		for (unsigned height = 0; height < data[width].size(); height++) {
			// create a pointer from the image
			HSLAPixel* p = img.getPixel(x + width, y + height);
			// since pointer p is currently pointing to thepixel in the image
			// overwrite the value of the image from data[width][height]
			*p = data[width][height];
		}
	}
}

/**
 * Flips the Block's pixel data horizontally by a simple reflection
 * across the vertical axis through its middle.
 */
void Block::FlipHorizontal() {
	// for each vector inside data, we plan to iterate through half of its size
	// to flip the values
	for (unsigned width = 0; width < data.size() / 2; width++) {
		// for the nested loop, since we are flipping horizontally, we need the size of every sub vector
		for (unsigned height = 0; height < data[width].size(); height++) {
			HSLAPixel* p = &data[width][height];
			HSLAPixel* a = &data[data.size() - width - 1][height]; // get the mirrored pixel to be used
			HSLAPixel temp = *p; 								   // store the data in a temporary HSLAPixel
			*p = *a;
			*a = temp;
		}
	}
}

/**
 * Rotates the Block's pixel data 90 degrees counter-clockwise.
 */
void Block::RotateCCW() {

	// if we start from this block

	//  1, 6,11,16,21			we want to move 1 to 5				21, 6,11,16,25
	//  2, 7,12,17,22						   5 to 25				 2, 7,12,17,22
	//  3, 8,13,18,23						  25 to 21				 3, 8,13,18,23
	//  4, 9,14,19,24						   21 to 1				 4, 9,14,19,24
	//  5,10,15,20,25												 1,10,15,20, 5

	// then move to the next loop
	// we will only iterate through half of the rows and columns of data to not repeat swapping values
	for (unsigned width = 0; width < data.size()/2; width++) {
		for (unsigned height = 0; height < data[width].size()/2; height++) {
			// since the block has equal width and height, we can swap four pixels 
			// per each iteration to rotate the image
			unsigned int xWidth = data.size() - width - 1; // position based from the end of the width
			unsigned int yHeight = data[width].size() - height - 1; // position based from the end of the height
			// four values to swap, we will swap a->b, b->c, c->d, d->a
			HSLAPixel* a = &data[width][height];
			HSLAPixel* b = &data[height][xWidth];
			HSLAPixel* c = &data[xWidth][yHeight];
			HSLAPixel* d = &data[yHeight][width];

			HSLAPixel temp = *a;
			*a = *d;
			*d = *c;
			*c = *b;
			*b = temp;
		}
	}
}

/**
 * Returns the dimension of the block (its width or height).
 */
unsigned int Block::Dimension() const {
	return data.size();
}