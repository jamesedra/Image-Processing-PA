/**
 * File: main.cpp
 * Description: entry point for test program
 *              for CPSC 221 2023S PA1
 *
 *              Add or modify test code as needed.
 * 
 *              THIS FILE WILL NOT BE SUBMITTED.
 */

#include <iostream>

#include "chain.h"

using namespace std;
using namespace cs221util;

/**
 * Test function declarations
 */

void TestChainRender();
void TestChainReverse();
void TestChainFlipHorizontal();
void TestChainRotateCCW();

/**
 * Program entry point
 */
int main(void) {

	// add or remove calls to testing functions as needed
	TestChainRender();
	cout << "TestChainRender completed.\n" << endl;
	TestChainReverse();
	cout << "TestChainReverse completed.\n" << endl;
	TestChainFlipHorizontal();
	cout << "TestChainFlipHorizontal completed.\n" << endl;
	TestChainRotateCCW();
	cout << "TestChainRotateCCW completed.\n" << endl;

	return 1;
}

/**
 * Test function implementations
 */

void TestChainRender() {
	cout << "Entered TestChainRender." << endl;
	// load a PNG file
	PNG alphabetpng;
	alphabetpng.readFromFile("images-original/alphabet-240x40.png");

	cout << "Creating a Chain from PNG... ";
	Chain c(alphabetpng, 40);
	cout << "done." << endl;

	cout << "Rendering Chain to output PNG with 2 columns... ";
	PNG alphabet2 = c.Render(2);
	cout << "done." << endl;

	cout << "Writing output PNG to file... ";
	alphabet2.writeToFile("images-output/alphabet-240x40-render2.png");
	cout << "done." << endl;

	cout << "Rendering Chain to output PNG with 3 columns... ";
	PNG alphabet3 = c.Render(3);
	cout << "done." << endl;

	cout << "Writing output PNG to file... ";
	alphabet3.writeToFile("images-output/alphabet-240x40-render3.png");
	cout << "done." << endl;

	cout << "Rendering Chain to output PNG with 4 columns... ";
	PNG alphabet4 = c.Render(4);
	cout << "done." << endl;

	cout << "Writing output PNG to file... ";
	alphabet4.writeToFile("images-output/alphabet-240x40-render4.png");
	cout << "done." << endl;

	cout << "Leaving TestChainReverse..." << endl;
}

void TestChainReverse() {
	cout << "Entered TestChainReverse." << endl;

	// load a PNG file
	PNG alphabetpng;
	alphabetpng.readFromFile("images-original/alphabet-240x40.png");

	cout << "Creating a Chain from PNG... ";
	Chain c(alphabetpng, 40);
	cout << "done." << endl;

	cout << "Calling Reverse... ";
	c.Reverse();
	cout << "done." << endl;

	cout << "Rendering reversed Chain to output PNG with 6 columns... ";
	PNG alphabetreversed = c.Render(6);
	cout << "done." << endl;

	cout << "Writing output PNG to file... ";
	alphabetreversed.writeToFile("images-output/alphabet-240x40-reverse-render6.png");
	cout << "done." << endl;

	cout << "Leaving TestChainReverse..." << endl;
}

void TestChainFlipHorizontal() {
	cout << "Entered TestChainFlipHorizontal." << endl;
	// load a PNG file
	PNG alphabetpng;
	alphabetpng.readFromFile("images-original/alphabet-240x40.png");

	cout << "Creating a Chain from PNG... ";
	Chain c(alphabetpng, 40);
	cout << "done." << endl;

	cout << "Calling FlipHorizontal with 3 columns... ";
	c.FlipHorizontal(3);
	cout << "done." << endl;

	cout << "Rendering flipped Chain to output PNG with 3 columns... ";
	PNG alphabetflipped = c.Render(3);
	cout << "done." << endl;

	cout << "Writing output PNG to file... ";
	alphabetflipped.writeToFile("images-output/alphabet-240x40-flip3-render3.png");
	cout << "done." << endl;

	cout << "Leaving TestChainFlipHorizontal..." << endl;
}

void TestChainRotateCCW() {
	cout << "Entered TestChainRotateCCW." << endl;
	// load a PNG file
	PNG alphabetpng;
	alphabetpng.readFromFile("images-original/alphabet-240x40.png");

	cout << "Creating a Chain from PNG... ";
	Chain c(alphabetpng, 40);
	cout << "done." << endl;

	cout << "Calling RotateCCW with 3 columns... ";
	c.RotateCCW(3);
	cout << "done." << endl;

	cout << "Rendering rotated Chain to output PNG with 2 columns... ";
	PNG alphabetrotated = c.Render(2);
	cout << "done." << endl;

	cout << "Writing output PNG to file... ";
	alphabetrotated.writeToFile("images-output/alphabet-240x40-rotate3-render2.png");
	cout << "done." << endl;

	cout << "Leaving TestChainRotateCCW..." << endl;
}