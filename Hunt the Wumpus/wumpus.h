/*
    Wumpus Header file

    Revision history:

        Originally written by Igor Strzelczyk
            (igor.strzelczyk@icloud.com) July 2021

    Following code groups all lesser header files and contains forward declarations of main functions of the game.
*/
#ifndef WUMPUS_H
#define WUMPUS_H

#include "actors.h"
#include "command.h"
#include "def_func.h"
#include "game_map.h"
#include "room.h"
#include <iostream>     // cout
#include <limits>       // numeric_limits<T>
#include <stdexcept>    // STL exceptions
#include <vector>

void print_rules();
bool play_again();
void run_game();

#endif // WUMPUS_H
