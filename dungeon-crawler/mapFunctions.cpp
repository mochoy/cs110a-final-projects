/*
 * Group Members: Hiroya Gojo, Zhongming Liao, Monty Choy, Ziling Yu, Amy Petrine
 */

// DO NOT CHANGE OR REMOVE THE FOLLOWING LINES
#ifndef __DEFINE_MAP_FUNCTIONS_CPP__
#define __DEFINE_MAP_FUNCTIONS_CPP__

#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;
// DO NOT CHANGE OR REMOVE THE PRECEDING LINES

/*
 * MAP CONSTANTS
 */
const char MAP_SQUARE_CHASM     = 'O';
const char MAP_SQUARE_EMPTY     = ' ';
const char MAP_SQUARE_KEY       = 'k';
const char MAP_SQUARE_LOCK      = '@';
const char MAP_SQUARE_PEBBLE    = '.';
const char MAP_SQUARE_PEBBLES   = ':';
const char MAP_SQUARE_PLANK     = '=';
const char MAP_SQUARE_PLANK_SET = 'I';
const char MAP_SQUARE_ROCK      = '#';
const char MAP_SQUARE_ROPE      = '&';
const char MAP_SQUARE_ROPE_TIED = '~';
const char MAP_SQUARE_SLINGSHOT = 'Y';
const char MAP_SQUARE_PLAYER_START = 'S';
const int MAP_MAX_WIDTH_HEIGHT = 255;

/*
 * MAP STATE
 */
string MAP;
int MAP_WIDTH;
int MAP_HEIGHT;

/*
 * FILE CONSTANTS
 */
const int FILE_INVENTORY_LENGTH = 10;
const char FILE_INVENTORY_ITEM_EMPTY = '\0';
const int FILE_INVENTORY_VALUE_EMPTY = 0;

/*
 * FILE STATE
 */
int FILE_START_LOCATION_AS_INDEX;
char FILE_START_LOOKING_DIRECTION;
char FILE_INVENTORY_ITEMS[FILE_INVENTORY_LENGTH];
int FILE_INVENTORY_VALUES[FILE_INVENTORY_LENGTH];

/*
 * FUNCTION PROTOTYPES
 */
void printMapRow(const int, const int, const int, const int, const int, const char);
char getMapSquare(const int, const int);
bool setMapSquare(const int, const int, const char, const char);
bool clearMapSquare(const int, const int, const char);
bool isOpenSpace(const int, const int);
bool loadMapFile(string);
bool loadGame(string fileName);
bool saveGame(string fileName, const int, const int, const char, const char[], const int[], const int);

/*
 * FUNCTION IMPLEMENTATIONS
 */

char getMapSquare(const int x, const int y)
{
    char result = MAP_SQUARE_ROCK;
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT)
    {
        result = MAP[x + y * MAP_WIDTH]; //Hiroya
    }
    return result;
}

bool setMapSquare(const int x, const int y, const char currentValue, const char newValue)
{
    bool result = false;

    if (x >= 0 && x < MAP_WIDTH &&
        y >= 0 && y < MAP_HEIGHT &&
        getMapSquare(x, y) == currentValue)
    {
        MAP[x + y * MAP_WIDTH] = newValue; //Hiroya
        result = true;
    }

    return result;
}

bool clearMapSquare(const int x, const int y, const char currentValue)
{
    return setMapSquare(x, y, currentValue, MAP_SQUARE_EMPTY);
}

bool isOpenSpace(const int x, const int y)
{
    char mapSquare = getMapSquare(x, y);
    return (mapSquare == MAP_SQUARE_EMPTY || mapSquare == MAP_SQUARE_PLANK_SET || mapSquare == MAP_SQUARE_ROPE_TIED); //Zhongming, Ziling 
}

void printMapRow(const int centerX, const int centerY, const int rowOffset, const int screenWidth, const int screenRadius, const char playerChar)
{
    const int row = centerY - screenRadius + rowOffset;
    for (int col = centerX - screenRadius; col <= centerX + screenRadius; col++)
    {
        if (row == centerY && col == centerX)
        {
            cout << playerChar;
        }
        else if (row >= 0 && row < MAP_HEIGHT && col >= 0 && col < MAP_WIDTH)
        {
            cout << MAP[row * MAP_WIDTH + col];
        }
        else
        {
            cout << MAP_SQUARE_ROCK; //Ziling, Zhongming
        }
    }
}

void openFile(ifstream& file, const char* fileName)
{
    //Monty Choy & Hiroya, Zhongming
    file.open(fileName);
}

void openFile(ofstream& file, const char* fileName)
{
    //Monty Choy & Hiroya, Zhongming
    file.open(fileName);
}

bool loadGame(string fileName)
{
    //Monty Choy & Hiroya 
    bool success = false;

    ifstream file;
    openFile(file, fileName.c_str());
    if (!file.fail())
    {
        int mapWidth, mapHeight, playerLocationAsIndex;
        char lookingDirection;
        file >> mapWidth >> mapHeight >> playerLocationAsIndex >> lookingDirection;
		file.ignore(200, '\n');
        if (mapWidth > 0 && mapHeight > 0)
        {
            const int charsToWriteIncludingNullTerminator = mapWidth + 1;
            char buffer[MAP_MAX_WIDTH_HEIGHT + 1];
            string mapText = "";

			for (int i = 0; i < MAP_MAX_WIDTH_HEIGHT + 1; i++)
			{
				buffer[i] = '\0';
			}

            //load map in file into mapText
            for (int i = 0; i < mapWidth * mapHeight; i++)
            {
				file.get(buffer[i]);
				if (buffer[i] == '\n')
				{
					i--;
					continue;
				}
                if (file.fail())
                {
                    break;
                }
                else if (buffer[0] == '\0')
                {
                    i--;
                    continue;
                }
                mapText = buffer;
            }
			//Debugging
			//cout << mapWidth << endl << mapHeight << endl << playerLocationAsIndex << endl << lookingDirection << endl << buffer;
            if (mapText.length() == mapWidth * mapHeight)
            {
                MAP = mapText;
                MAP_WIDTH = mapWidth;
                MAP_HEIGHT = mapHeight;
                FILE_START_LOCATION_AS_INDEX = playerLocationAsIndex;
                FILE_START_LOOKING_DIRECTION = lookingDirection;

                if (!file.fail())
                {
                    char item;
                    int value;

                    for (int i = 0; i < FILE_INVENTORY_LENGTH; i++)
                    {
                        if (file.fail())
                        {
                            FILE_INVENTORY_ITEMS[i] = FILE_INVENTORY_ITEM_EMPTY;
                            FILE_INVENTORY_VALUES[i] = FILE_INVENTORY_VALUE_EMPTY;
                            continue;
                        }

                        file >> item;
                        if (file.fail())
                        {
                            i--;
                            continue;
                        }

                        file >> value;
                        if (file.fail())
                        {
                            i--;
                            continue;
                        }

                        FILE_INVENTORY_ITEMS[i] = item;
                        FILE_INVENTORY_VALUES[i] = value;
                    }
                }

                success = true;
            }        //if
        }        //if
    }        //if !file.fail()

    file.close();

    return success;
}

bool saveGame(string fileName, const int playerX, const int playerY, const char lookingDirection, const char inventoryItems[], const int inventoryValues[], const int inventoryLength)
{
    bool success = false;

    ofstream file;
    openFile(file, fileName.c_str());
    if (!file.fail())
    {
        // write map dimensions and player location
        int playerSymbolIndex = playerX + playerY * MAP_WIDTH; //Hiroya 
        file << MAP_WIDTH << ' ' << MAP_HEIGHT << ' ' << playerSymbolIndex << ' ' << lookingDirection << endl;

        // write map
        for (int i = 0; i < MAP_HEIGHT; i++)
        {
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				file << MAP[j + i * MAP_WIDTH]; //Hiroya 
			}
			file << endl;
        }

        // write inventory
        for (int i = 0; i < inventoryLength; i++)
        {
            file << inventoryItems[i] << ' ' << inventoryValues[i] << endl;
        }

        success = !file.fail();
    }

    file.close();

    return success;
}

void loadDefaultMap()
{
    //Hiroya, Ziling
    for (int i = 0; i < FILE_INVENTORY_LENGTH; i++)
    {
	    FILE_INVENTORY_ITEMS[0] = FILE_INVENTORY_ITEM_EMPTY;
	    FILE_INVENTORY_VALUES[0] = FILE_INVENTORY_VALUE_EMPTY;
    }
    MAP = "&.@:=     OYO k";
    MAP_WIDTH = 5;
    MAP_HEIGHT = 3;
    FILE_START_LOCATION_AS_INDEX = 7;
    FILE_START_LOOKING_DIRECTION = '>';
}

// DO NOT CHANGE OR REMOVE THE FOLLOWING LINE
#endif
// DO NOT CHANGE OR REMOVE THE PRECEDING LINE