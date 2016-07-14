/*
 * Group Members: Hiroya Gojo, Zhongming Liao, Monty Choy, Ziling Yu, Amy Petrine
 */

// DO NOT CHANGE OR REMOVE THE FOLLOWING LINES
#ifndef __DEFINE_PLAYER_FUNCTIONS_CPP__
#define __DEFINE_PLAYER_FUNCTIONS_CPP__

#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

#include "mapFunctions.cpp"
// DO NOT CHANGE OR REMOVE THE PRECEDING LINES

/*
 * PLAYER STATE CONSTANTS
 */
const char LOOKING_UP = '^';
const char LOOKING_DOWN = 'v';
const char LOOKING_LEFT = '<';
const char LOOKING_RIGHT = '>';
const int INVENTORY_INDEX_KEYS = 0;
const int INVENTORY_INDEX_PEBBLES = 1;
const int INVENTORY_INDEX_PLANK = 2;
const int INVENTORY_INDEX_ROPE = 3;
const int INVENTORY_INDEX_SLINGSHOT = 4;
const int INVENTORY_LENGTH = 5;
int INVENTORY_ARRAY[INVENTORY_LENGTH] = { 0, 0, 0, 0, 0 };

/*
 * PLAYER STATE
 */
char playerSymbol;
int playerX, playerY;

/*
 * FUNCTION PROTOTYPES
 */
int getLookingAtX(const int, const char);
int getLookingAtY(const int, const char);
void inventoryAdd(const char);
bool inventoryHas(const char);
bool inventoryUse(const char);
void inventorySet(const char[], const int[], const int);
bool printInventoryRow(const int, const int);
int convertMapSquareToInventoryIndex(const char);
char convertInventoryIndexToItemChar(const int);
int max(int, int);
int min(int, int);

int getLookingAtX(const int currentX, const char currentSymbol)
{
    switch(currentSymbol)
    {
        case LOOKING_UP:
        case LOOKING_DOWN:
            return currentX;
        case LOOKING_LEFT:
            return (currentX - 1);
        case LOOKING_RIGHT:
            return (currentX + 1);
    }
    return currentX;
}

int getLookingAtY(const int currentY, const char currentSymbol)
{
    switch(currentSymbol) //Hiroya 
    {
        case LOOKING_UP:
            return (currentY - 1);
        case LOOKING_DOWN:
            return (currentY + 1);
        case LOOKING_LEFT:
        case LOOKING_RIGHT:
            return currentY;
            
    }
    return currentY;
}

void inventoryAdd(const char item)
{
    int inventoryIndex = convertMapSquareToInventoryIndex(item);
    if (inventoryIndex >= 0)
    {
        switch(item)
        {
            //Hiroya 
            case MAP_SQUARE_KEY:
            case MAP_SQUARE_PEBBLE:
                INVENTORY_ARRAY[inventoryIndex] -= 1;
            case MAP_SQUARE_PEBBLES: 
                INVENTORY_ARRAY[inventoryIndex] += 1;
            case MAP_SQUARE_PLANK:
            case MAP_SQUARE_ROPE:
                INVENTORY_ARRAY[inventoryIndex] += 1;
                break;
            case MAP_SQUARE_SLINGSHOT:
                INVENTORY_ARRAY[inventoryIndex] = 1;
                break;
        }
    }
}

bool inventoryHas(const char item)
{
    int inventoryIndex = convertMapSquareToInventoryIndex(item);
    return (inventoryIndex >= 0 && INVENTORY_ARRAY[inventoryIndex] > 0);
}

bool inventoryUse(const char item)
{
    bool success = false;

    int inventoryIndex = convertMapSquareToInventoryIndex(item);
    if (inventoryIndex >= 0)
    {
        switch(inventoryIndex)
        {
            case INVENTORY_INDEX_KEYS:
            case INVENTORY_INDEX_PEBBLES:
            case INVENTORY_INDEX_PLANK:
            case INVENTORY_INDEX_ROPE:
                if (INVENTORY_ARRAY[inventoryIndex] > 0)
                {
                    INVENTORY_ARRAY[inventoryIndex] -= 1;
                    success = true;
                }
                break;
            case INVENTORY_INDEX_SLINGSHOT:
                if (INVENTORY_ARRAY[inventoryIndex] > 0)
                {
                    success = true;
                }
                break;
        }
    }

    return success;
}

void inventorySet(const char newInventoryItems[], const int newInventoryValues[], const int count)
{
    for (int i = 0; i < INVENTORY_LENGTH; i++)
    {
        bool itemIsInNewList = false;

        for (int j = 0; j < count; j++)
        {
            int index = convertMapSquareToInventoryIndex(newInventoryItems[j]);
            if (index == i)
            {
                INVENTORY_ARRAY[index] = newInventoryValues[j];
                itemIsInNewList = true;
                break;
            }
        }

        if (!itemIsInNewList)
        {
            INVENTORY_ARRAY[i] = 0;
        }
    }
}

bool printInventoryRow(const int row, const int displayWidth)
{
    bool success = false;

    const int symbolWidth = max(0, min(2, displayWidth));
    const int numberWidth = max(0, min(2, displayWidth - symbolWidth));
    const int nameWidth = max(0, displayWidth - (numberWidth + symbolWidth));

    switch(row)
    {
        case 0:
        {
            int itemIndex = INVENTORY_INDEX_KEYS;
            int count = INVENTORY_ARRAY[itemIndex];
            if (count > 0)
            {
                //Monty Choy & Hiroya 
                cout << left << setw(symbolWidth) << convertInventoryIndexToItemChar(itemIndex)
                    << left << setw(nameWidth) << "Key"
                    << right << setw(numberWidth) << count;
                success = true;
            }
            break;
        }
        case 1:
        {
            int itemIndex = INVENTORY_INDEX_ROPE;
            int count = INVENTORY_ARRAY[itemIndex];
            if (count > 0)
            {
                //Monty Choy & Hiroya 
                cout << left << setw(symbolWidth) << convertInventoryIndexToItemChar(itemIndex)
                    << left << setw(nameWidth) << "Rope"
                    << right << setw(numberWidth) << count;
                success = true;
            }
            break;
        }
        case 2:
        {
            int itemIndex = INVENTORY_INDEX_PLANK;
            int count = INVENTORY_ARRAY[itemIndex];
            if (count > 0)
            {
                //Monty Choy & Hiroya 
                cout << left << setw(symbolWidth) << convertInventoryIndexToItemChar(itemIndex)
                    << left << setw(nameWidth) << "Wood Plank"
                    << right << setw(numberWidth) << count;
                success = true;
            }
            break;
        }
        case 3:
        {
            break;
        }
        case 4:
        {
            bool hasSlingshot = INVENTORY_ARRAY[INVENTORY_INDEX_SLINGSHOT] > 0;
            int itemIndex = INVENTORY_INDEX_PEBBLES;
            int count = INVENTORY_ARRAY[itemIndex];
            //Monty Choy & Hiroya 
            if (hasSlingshot)
            {
                 itemIndex = INVENTORY_INDEX_SLINGSHOT;
                 cout << left << setw(symbolWidth) << convertInventoryIndexToItemChar(itemIndex) 
                    << left << setw(nameWidth) << "Slingshot"
                    << right << setw(numberWidth) << count << left;
                    success = true;
            } 
            else if (!hasSlingshot && count > 0)
            {
                 cout << left << setw(symbolWidth) << convertInventoryIndexToItemChar(itemIndex) 
                    << left << setw(nameWidth) << "Pebble"
                    << right << setw(numberWidth) << count << left;
                    success = true;
            }
            break;
        }
    }

    return success;
}

int convertMapSquareToInventoryIndex(const char mapSquare)
{
    switch(mapSquare)
    {
        case MAP_SQUARE_KEY:
            return INVENTORY_INDEX_KEYS;
        case MAP_SQUARE_PEBBLE:
        case MAP_SQUARE_PEBBLES:
            return INVENTORY_INDEX_PEBBLES;
        case MAP_SQUARE_PLANK:
            return INVENTORY_INDEX_PLANK;
        case MAP_SQUARE_ROPE:
            return INVENTORY_INDEX_ROPE;
        case MAP_SQUARE_SLINGSHOT:
            return INVENTORY_INDEX_SLINGSHOT;
    }
    return -1;
}

char convertInventoryIndexToItemChar(const int index)
{
    switch(index)
    {
        case INVENTORY_INDEX_KEYS:
            return MAP_SQUARE_KEY;
        case INVENTORY_INDEX_PEBBLES:
            return MAP_SQUARE_PEBBLE;
        case INVENTORY_INDEX_PLANK:
            return MAP_SQUARE_PLANK;
        case INVENTORY_INDEX_ROPE:
            return MAP_SQUARE_ROPE;
        case INVENTORY_INDEX_SLINGSHOT:
            return MAP_SQUARE_SLINGSHOT;
    }
    return ' ';
}

int max(int a, int b)
{
    return (a > b ? a : b);        //Monty Choy
}

int min(int a, int b)
{
    return (a > b ? b : a);        //Monty Choy
}

// DO NOT CHANGE OR REMOVE THE FOLLOWING LINE
#endif
// DO NOT CHANGE OR REMOVE THE PRECEDING LINE