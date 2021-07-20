/*
    Game_map Class Header file

    Revision history:

        Originally written by Igor Strzelczyk
            (igor.strzelczyk@icloud.com) July 2021

    Following code contains definition of Game_map Class.
*/
#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "def_func.h"
#include "room.h"
#include <cstddef>      // size_t
#include <stdexcept>    // STL exceptions

class Game_map {
public:
    // Essential operations
    Game_map();
    Game_map(const Game_map&) = delete;             // Does not allow copying
    Game_map& operator=(const Game_map&) = delete;
    ~Game_map() { delete[] rooms; }

    // Non-modifying functions
    size_t get_size()      const { return size; }
    Room*  get_room(short) const;                   // Returns pointer to Room object of specified number (not index)
private:
    size_t size     {25};
    short  max_bats {7};
    short  max_pits {5};
    Room*  rooms    {new Room[size]};
};

// Member function returning pointer to a Room of specified number
inline
Room* Game_map::get_room(short room_number) const
{
    if (room_number < 1 || room_number > size)
        throw std::out_of_range("Room of this number does not exist.");
    return &rooms[room_number - 1];
}

#endif // GAME_MAP_H
