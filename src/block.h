/**
 * File: block.h
 * Description: declaration of a null-terminated, doubly-linked list node class
 *              for CPSC 221 2023S PA1
 *
 *              THIS FILE WILL NOT BE MODIFIED
 */

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <vector>
#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"

using namespace std;
using namespace cs221util;

class Block {

private:
	vector<vector<HSLAPixel>> data;

public:
	/**
	 * Creates a square Block that is dimension x dimension pixels in size,
	 * starting at (x, y) on img. Assumes that the requested
	 * Block fits on the image (inputs are feasible)
	 */
	void Build(PNG& img, unsigned int x, unsigned int y, unsigned int dimension);

	/**
	 * Renders this Block onto img with its upper-left corner at (x, y).
	 * Assumes block fits on the image.
	 */
	void Render(PNG& img, unsigned int x, unsigned int y) const;

	/**
	 * Flips the Block's pixel data horizontally by a simple reflection
	 * across the vertical axis through its middle.
	 */
	void FlipHorizontal();

	/**
	 * Rotates the Block's pixel data 90 degrees counter-clockwise.
	 */
	void RotateCCW();

	/**
	 * Returns the dimension of the block (its width or height).
	 */
	unsigned int Dimension() const;
};

#endif