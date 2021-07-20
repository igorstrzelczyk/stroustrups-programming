/*
    Functions Header file

    Revision history:

        Originally written by Igor Strzelczyk
            (igor.strzelczyk@icloud.com) July 2021

    Following code contains forward declarations for user-defined and helper functions used in the game.
*/
#ifndef DEF_FUNC_H
#define DEF_FUNC_H

#include "actors.h"
#include "game_map.h"
#include "room.h"
#include <cstdlib>      // rand()
#include <iostream>     // cout
#include <sstream>      // ostringstream
#include <stdexcept>    // STL exceptions


int    random(int);
int    random(int, int);
Hazard generate_hazard();
bool   room_empty(const Room*);
Room*  wump_spawn(const Game_map&);
void   room_info(Room*, Room*);

#endif // DEF_FUNC_H
