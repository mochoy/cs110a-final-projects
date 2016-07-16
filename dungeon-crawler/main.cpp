/*
 * Group Members: Hiroya Gojo, Zhongming Liao, Monty Choy, Ziling Yu, Amy Petrine
 */

// DO NOT CHANGE OR REMOVE THE FOLLOWING LINES
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

#include "interactionFunctions.cpp"
#include "mapFunctions.cpp"
#include "playerFunctions.cpp"
#include "screenFunctions.cpp"
// DO NOT CHANGE OR REMOVE THE PRECEDING LINES

/*
 * FUNCTION PROTOTYPES
 */
// none here yet

int main()
{
	doLoadDefaultGame(); //Hiroya, Ziling
	while (true)
	{
		clearScreen();
		printScreen();
		lastMessage = ""; //Hiroya
		char input = readCharacterInput();
		if (input == 'Q') //Hiroya
		{
			break;
		}
		doCommand(input);
	}

	return 0;
}