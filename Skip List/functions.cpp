/*
    Functions Source file

    Revision history:

        Originally written by Igor Strzelczyk
            (igor.strzelczyk@icloud.com) July 2021

    Following code contains definitions of user-defined functions used in the program.
*/
#include "functions.h"

// Function generating height of new element of the list
size_t generate_height()
{
    size_t height {1};
    while (rand() % 2) // "Coin toss" - generates 0 or 1
        ++height;

    return height;
}
