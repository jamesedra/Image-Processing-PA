/**
 * File: chain.cpp
 * Description: student implementation for Chain functions
 *              for CPSC 221 2023S PA1
 *
 *              THIS FILE WILL BE SUBMITTED.
 */

#include <math.h>
#include <algorithm>
#include "chain.h"

/**
 * Constructs a Chain from an input image
 * Each Node will cover a nodedimension x nodedimension (in pixels)
 * region in the source image.
 * @param img the input image
 * @param nodedimension number of pixels along the width and height of the Block region
 * @pre input image's width and height are evenly divisible by nodedimension
 */
Chain::Chain(PNG& img, unsigned int nodedimension) {
	// create a starting node to point NW with it
	Block* start = new Block();
	start->Build(img, 0, 0, nodedimension);
	Node* startNode = new Node(*start);
	NW = startNode;
	SE = startNode;
	length_ = 1;

	// we use node dimension to actually divide the img to blocks of code, then we link them in a chain
	for (unsigned int height = 0; height < img.height(); height += nodedimension) {
		for (unsigned int width = 0; width < img.width(); width += nodedimension) {
			// since we built the starting node already
			if (!(height == 0 && width == 0)){
				Block* b = new Block();
				b->Build(img, width, height, nodedimension);
				InsertBack(*b);
			}
		}
	}
}

/**
 * Renders the Chain's pixel data into an output PNG.
 * The PNG should be sized according to the number of nodes
 * specified by the cols parameter.
 * It is possible that there may not be enough nodes to fill
 * the bottom row of the PNG. If this happens, just render
 * as many nodes as there are, from left to right, and leave
 * the rest of the row as opaque white pixels.
 * @pre this Chain is not empty
 * @param cols the number of Blocks to use for the width of the image
 */
PNG Chain::Render(unsigned int cols) {
	unsigned int dim = NW->data.Dimension();		// gets the dimension of one node
	unsigned int width = dim * cols;
	unsigned int height = dim * ceil(Length() / float(cols));

	PNG png(width, height);		

	Node* curr = NW; // create a pointer to traverse each node

	for (unsigned int h = 0; h < height; h+= dim) {
		for (unsigned int w = 0; w < width; w+= dim) {
			if (curr != nullptr) {
				curr->data.Render(png, w, h);
				curr = curr->next;
			}
		}
	}
	return png;
}

/**
 * Inserts a new Node containing ndata at the back of the Chain
 */
void Chain::InsertBack(const Block& ndata) {
	// we manipulate the pointer SE here, in which we assume is already at the current back of the chain
	SE->next = new Node(ndata); // add the new Node to the next of the current last
	(SE->next)->prev = SE;      // add the current last node to the next node as its previous
	(SE->next)->next = nullptr;
	SE = SE->next;				// move forward the SE pointer
	length_++;
}

/**
 * Reverses the structure of the list. This must be done by
 * pointer assignments. You may not deallocate or allocate any Nodes.
 * Example:
 *	before:	NW -> A <-> B <-> C <-> D <-> E <-> F <-> G <-> H <- SE
 *  
 *  after:	NW -> H <-> G <-> F <-> E <-> D <-> C <-> B <-> A <- SE
 */
void Chain::Reverse() {
	Node* curr = NW;
	Node* temp;
	while(curr != nullptr) {
		temp = curr->prev;
		curr->prev = curr->next;
		curr->next = temp;
		curr = curr->prev;
	}
	
	temp = NW;
	NW = SE;
	SE = temp; 
}

/**
 * Rearranges the Node structure and internal pixel data to be flipped over a vertical axis.
 * This must be done using pointer assignments.
 * You may not deallocate or allocate any Nodes.
 * Example, length = 6:
 *  before, flipping with 3 columns (2 rows):
 *
 *		NW -> A> <-> B> <-> C> <->
 *            D> <-> E> <-> F> <- SE
 * 
 *  after, visualized with 3 columns (2 rows):
 * 
 *		NW -> <C <-> <B <-> <A <->
 *            <F <-> <E <-> <D <- SE
 * 
 * @param cols number of Blocks to use for the initial width of the image
 * @pre length_ is divisible by cols (i.e. no "partially-filled" rows)
 */
void Chain::FlipHorizontal(unsigned int cols) {
    Node* curr = NW; //cursor pointer to move through the linked list
    
    // create a 2d vector of node pointers
    vector<vector<Node*>> temp(length_/cols, vector<Node*> (cols));

    for (int height = 0; height < length_/cols; height++) {
        // we start with the end of the width first to reverse per row
        for (int width = cols - 1; width >= 0; width--) {
            if (curr != nullptr) {
                curr->data.FlipHorizontal();
                temp[height][width] = curr;
                curr = curr->next;
            }
        }
    }

    curr = nullptr;

    for (unsigned int height = 0; height < length_/cols; height++) {
        for (unsigned int width = 0; width < cols; width++) {
            // if it's the top left or [0][0]
            if(height == 0 && width == 0) {
                temp[height][width]->prev = nullptr;
                temp[height][width]->next = temp[height][width+1];
            } 

            // if it's at the very start of the sub vector
            else if (height > 0 && width == 0) {
                temp[height][width]->prev = temp[height-1][cols-1];
                temp[height][width]->next = temp[height][width+1];
            }

            // if it's the end of the list
            else if (height == length_/cols - 1 && width == cols - 1) {
                temp[height][width]->prev = temp[height][width-1];
                temp[height][width]->next = nullptr;   
            }

            // if it's at the very end of the sub vector
            else if (width == cols - 1) {
                temp[height][width]->prev = temp[height][width-1];
                temp[height][width]->next = temp[height + 1][0];         
            }

            else {
                temp[height][width]->next = temp[height][width+1];
                temp[height][width]->prev = temp[height][width-1];
            }
        }
    }
    NW = temp[0][0];
    SE = temp[length_/cols-1][cols-1];
}



/**
 * Rearranges the Node structure and internal pixel data to be rotated counter-clockwise.
 * This must be done using pointer assignments.
 * You may not deallocate or allocate any Nodes.
 * Example, length = 6:
 *	before, rotating with 3 columns (2 rows):
 *            ^     ^     ^
 *      NW -> A <-> B <-> C <->
 *            ^     ^     ^
 *            D <-> E <-> F <- SE
 * 
 *  after, visualized with 2 columns (3 rows):
 * 
 *      NW -> <C <-> <F <->
 *            <B <-> <E <->
 *            <A <-> <D <- SE
 * 
 * @param cols number of Blocks to use for the initial width of the image
 * @pre length_ is divisible by cols (i.e. no "partially-filled" rows)
 */
void Chain::RotateCCW(unsigned int cols) {
    Node* curr = NW; //cursor pointer to move through the linked list
    vector<vector<Node*>> temp(cols);

    for (unsigned int width = 0; width < length_/cols; width++) {
        // we use the end of the height to put A at the bottom,
        // move height 1 up, and put B. That way we will have
        // height 0 - [C,F]
        // height 1 - [B,E]
        // height 2 - [A,D]
        for (int height = cols - 1; height >=0; height--) {
            if (curr != nullptr) {
                curr->data.RotateCCW();
                temp[height].push_back(curr);
                curr = curr->next;
            }
        }
    }
    curr = nullptr;

    // connect the pointers next and prev as mapped on the 2D vector
    for (unsigned int height = 0; height < cols; height++) {
        for (unsigned int width = 0; width < length_/cols; width++) {
            // if it's the top left or [0][0]
            if(height == 0 && width == 0) {
                temp[height][width]->prev = nullptr;
                temp[height][width]->next = temp[height][width+1];
            } 

            // if it's at the very start of the sub vector
            else if (height > 0 && width == 0) {
                temp[height][width]->prev = temp[height-1][cols-1];
                temp[height][width]->next = temp[height][width+1];
            }

            // if it's the end of the list
            else if (height == cols - 1 && width == length_/cols - 1) {
                temp[height][width]->prev = temp[height][width-1];
                temp[height][width]->next = nullptr;   
            }

            // if it's at the very end of the sub vector
            else if (width == length_/cols - 1) {
                temp[height][width]->prev = temp[height][width-1];
                temp[height][width]->next = temp[height + 1][0];         
            }

            else {
                temp[height][width]->next = temp[height][width+1];
                temp[height][width]->prev = temp[height][width-1];
            }
        }
    }
    // set the proper location for NW and SE
    NW = temp[0][0];
    SE = temp[cols-1][length_/cols-1];
}

/**
 * Destroys all dynamically allocated memory associated with
 * this Chain object. Called by destructor and operator=.
 * You must complete its implementation for PA1.
 */
void Chain::Clear() {
	// complete your implementation below

}

/**
 * Copies the parameter other Chain into the current Chain.
 * Does not free any memory. Called by copy constructor and
 * operator=.
 * You must complete its implementation for PA1.
 * @param other The Chain to be copied.
 */
void Chain::Copy(const Chain& other) {
	// complete your implementation below

}

/**
 * If you have declared any private helper functions in chain_private.h,
 * add your completed implementations below.
 */
