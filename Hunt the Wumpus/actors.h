/*
    Actor Class Header file

    Revision history:

        Originally written by Igor Strzelczyk
            (igor.strzelczyk@icloud.com) July 2021

    Following code contains definition of Actor, Player and Wumpus Classes.
*/
#ifndef ACTORS_H
#define ACTORS_H

#include "def_func.h"
#include "game_map.h"
#include "room.h"
#include <iostream>     // cout
#include <sstream>      // ostringstream
#include <stdexcept>    // STL exceptions
#include <string>
#include <vector>

class Game_map;

class Actor {
public:
    // Essential operations
    Actor(const Actor&) = delete;              // Does not allow copying
    Actor& operator=(const Actor&) = delete;
    virtual ~Actor() { }

    struct Invalid_spawn { std::string msg; }; // Constructor error handling

    // Modifying functions
    virtual void move(Room*);                  // Enters specified room
    void set_position(Room* new_position) { position = new_position; }
    void kill() { alive = false; }             // Kills Actor

    // Non-modifying functions
    Room* get_position() const { return position; }
    bool  is_alive()     const { return alive; }
protected:
    Actor(Room*);
private:
    Room* position;                            // Current position of Actor
    bool  alive {true};                        // Current status of Actor
};

std::vector<const Actor*>& actors();

class Wumpus : public Actor{
public:
    Wumpus(Room* spawn_point) : Actor{spawn_point} { }

    // Modifying functions
    void move(Room*) override;                    // Moves Wumpus to random adjoining Room
};

class Player : public Actor{
public:
    Player(Room* spawn_point) : Actor{spawn_point} { }

    // Modifying functions
    void shoot(const std::vector<Room*>&, Wumpus&);          // Shoots through up to three specified rooms
    friend void bat_met(Player&, const Game_map&);           // Changes position to a random, hazard-free room

    // Non-modifying functions
    short get_arrows() const { return arrows; }
private:
    short arrows {5};
};

#endif // ACTORS_H
