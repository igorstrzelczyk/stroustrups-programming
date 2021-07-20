/*
    Functions Source file

    Revision history:

        Originally written by Igor Strzelczyk
            (igor.strzelczyk@icloud.com) July 2021

    Following code contains definitions of user-defined and helper functions used in the game.
*/
#include "def_func.h"

int random(int max)
{
    return std::rand() % (max + 1);
}
int random(int starting_point, int max)
{
    return starting_point + std::rand() % (max - starting_point + 1);
}

// Helper function using rand() to generate and return type of hazard
Hazard generate_hazard()
{
    return static_cast<Hazard>(random(2));
}

// Helper function informing whether passed Room is empty by checking for hazard and (optionally) Actor presence
bool room_empty(const Room* checked_room)
{
    if (checked_room->hazard != Hazard::None) return false;
    for (const auto& a : actors())
        if (a->get_position() == checked_room) return false;
    return true;
}

/* Helper function generating Wumpus spawn point - pointer to a Room object fulfilling following requirements:
    Random number of [5, map.size] range
    No other Actor present
    No hazards present
    At least one of adjoining rooms is hazard-free
*/
Room* wump_spawn(const Game_map& map)
{
    Room* spawn {nullptr};
    for (bool ok = false; !ok; )
    {
        spawn = map.get_room(random(5, map.get_size()));
        for (const auto& r : spawn->tunnels)            // At least one of adjoining rooms is hazard-free
            if (r->hazard == Hazard::None) ok = true;
        if (!room_empty(spawn)) ok = false;
    }
    return spawn;
}

// Helper function changing location of the player to a random, hazard-free room upon meeting a bat
void bat_met(Player& p, const Game_map& map)
{
    if (p.get_position()->hazard != Hazard::Bat) throw std::logic_error("No bat at player position.");

    Room* destination      {p.get_position()};
    Room* old_bat_location {p.get_position()};

    std::cout << "Stumbled upon a bat. You are grabbed and taken into the dark...\n\n";

    // Changes position of player
    while (!room_empty(destination) || destination == p.get_position()) // Generates random, hazard-free location
        destination = map.get_room(random(1, 25));                      // different from the current one
    p.set_position(destination);

    // Changes position of the bat
    old_bat_location->hazard = Hazard::None;
    while (!room_empty(destination) || destination == old_bat_location)
        destination = map.get_room(random(1, 25));
    destination->hazard = Hazard::Bat;
}

// Function printing information about the current room
void room_info(Room* room_entered, Room* wump_location)
{
    std::ostringstream oss;
    // Prints hazard warnings
    for (const auto& adjoining_room : room_entered->tunnels)
    {
        if (adjoining_room->hazard == Hazard::Pit) oss << "I feel a breeze.\n";
        if (adjoining_room->hazard == Hazard::Bat) oss << "I hear a bat.\n";
        if (wump_location == adjoining_room)       oss << "I smell the Wumpus.\n";
    }

    oss << "\nYou are now in Room " << room_entered->number << ".\nThere are tunnels to rooms: "
        << room_entered->tunnels[0]->number << ", " << room_entered->tunnels[1]->number
        << " and " << room_entered->tunnels[2]->number;

    std::cout << oss.str() << std::endl;
}
