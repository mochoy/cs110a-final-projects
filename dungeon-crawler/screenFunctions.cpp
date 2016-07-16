/*
 * Group Members: Hiroya Gojo, Zhongming Liao, Monty Choy, Ziling Yu, Amy Petrine
 */

// DO NOT CHANGE OR REMOVE THE FOLLOWING LINES
#ifndef __DEFINE_SCREEN_FUNCTIONS_CPP__
#define __DEFINE_SCREEN_FUNCTIONS_CPP__

#include <iostream>
using namespace std;

#include "playerFunctions.cpp"
#include "mapFunctions.cpp"
#include "interactionFunctions.cpp"
// DO NOT CHANGE OR REMOVE THE PRECEDING LINES

/*
 * SCREEN CONSTANTS AND SETTINGS
 */
const int SCREEN_MAP_RADIUS = 2; //Hiroya, Ziling
const int SCREEN_MAP_WIDTH_HEIGHT = SCREEN_MAP_RADIUS * 2 + 1;
const int SCREEN_INVENTORY_WIDTH = 15;

/*
 * FUNCTION PROTOTYPES
 */
void clearScreen();
void printScreen();
void printChar(const char, const int);

void clearScreen()
{
	for (int i = 0; i < 10; i++)
	{
		cout << endl;
	}
}

void printScreen()
{
	const int FRAME_WIDTH = 13;
	const int FRAME_ARRAY_LENGTH = FRAME_WIDTH + 1;
	
	const char FRAME_TOP_CORNER = ',';
	const char FRAME_BOTTOM_CORNER = '\'';
	const char FRAME_SIDE_HORIZONTAL = '-';
	const char FRAME_SIDE_VERTICAL = '|';

	// draw top of frame
	cout << FRAME_TOP_CORNER;
	printChar(FRAME_SIDE_HORIZONTAL, SCREEN_MAP_WIDTH_HEIGHT);
	cout << FRAME_TOP_CORNER;
	printChar(FRAME_SIDE_HORIZONTAL, SCREEN_INVENTORY_WIDTH);
	cout << FRAME_TOP_CORNER << endl;

	// draw frame, map, and inventory
	for (int row = 0; row < SCREEN_MAP_WIDTH_HEIGHT; row++)
	{
		cout << FRAME_SIDE_VERTICAL;
		printMapRow(playerX, playerY, row, SCREEN_MAP_WIDTH_HEIGHT, SCREEN_MAP_RADIUS, playerSymbol);
		cout << FRAME_SIDE_VERTICAL;
		if (!printInventoryRow(row, SCREEN_INVENTORY_WIDTH))
		{
			printChar(' ', SCREEN_INVENTORY_WIDTH);
		}
		cout << FRAME_SIDE_VERTICAL << endl;
	}

	// draw bottom of frame
	cout << FRAME_BOTTOM_CORNER;
	printChar(FRAME_SIDE_HORIZONTAL, SCREEN_MAP_WIDTH_HEIGHT);
	cout << FRAME_BOTTOM_CORNER;
	printChar(FRAME_SIDE_HORIZONTAL, SCREEN_INVENTORY_WIDTH);
	cout << FRAME_BOTTOM_CORNER << endl;

	// messaging below frame
	cout << endl << lastMessage.c_str() << endl << endl << "You are at (" << playerX << "," << playerY << "). Enter a command: ";
}

void printScreenMapSeparately()
{
	for (int row = playerY - SCREEN_MAP_RADIUS; row <= playerY + SCREEN_MAP_RADIUS; row++)
	{
		printMapRow(playerX, playerY, row, SCREEN_MAP_WIDTH_HEIGHT, SCREEN_MAP_RADIUS, playerSymbol);
		cout << endl;
	}
}

void printChar(const char c, const int times)
{
	for (int i = 0; i < times; i++)
	{
		cout << c;
	}
}

// DO NOT CHANGE OR REMOVE THE FOLLOWING LINE
#endif
// DO NOT CHANGE OR REMOVE THE PRECEDING LINE