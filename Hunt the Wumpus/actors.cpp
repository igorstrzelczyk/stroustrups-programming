/*
    Actor Class Source file

    Revision history:

        Originally written by Igor Strzelczyk
            (igor.strzelczyk@icloud.com) July 2021

    Following code contains definitions of functions of Actor, Player and Wumpus Classes.
*/
#include "actors.h"

// Vector of constant pointers to Actor objects; used to keep track of position and count of all Actors
std::vector<const Actor*>& actors()
{
    static std::vector<const Actor*> actors;
    return actors;
}

// Actor Class Member functions

// Constructor
Actor::Actor(Room* spawn_point) : position{spawn_point}
{
    if (spawn_point == nullptr) throw Invalid_spawn{"Null pointer passed."};
    if (spawn_point->hazard != Hazard::None)
        throw Invalid_spawn{"Invalid spawn location - hazard present."};
    for (const auto& a : actors())
        if (a->get_position() == spawn_point)
            throw Invalid_spawn{"Invalid spawn location - another Actor present in Room."};
    actors().push_back(this);
}

// Member function moving Actor to passed Room, provided it is possible
void Actor::move(Room* destination)
{
    if (destination == nullptr) throw std::invalid_argument("Passed destination is a null pointer.");
    for (const auto& tunnel : position->tunnels)
        if (tunnel == destination)
        {
            position = destination;
            return;
        }
    // Invalid room number
    std::ostringstream oss;
    oss << "You cannot get to room " << destination->number << " from current position.";
    throw std::invalid_argument(oss.str());
}

// Wumpus Class Member functions

// Member function moving the Wumpus to random adjoining, hazard-free room
void Wumpus::move(Room*)
{
    Room* destination {get_position()->tunnels[random(2)]};
    while (destination->hazard != Hazard::None)
        destination = get_position()->tunnels[random(2)];
    set_position(destination);
}

// Player Class Member functions

// Member function checking whether rooms from the command are valid, adjoining to the one player is currently in
// and shooting the arrow through them afterwards
void Player::shoot(const std::vector<Room*>& arrow_trajectory, Wumpus& wump)
{
    Room* arrow = get_position();
    for (const auto& checked : arrow_trajectory)
    {
        bool match_found = false;
        for (const auto& adjoining : arrow->tunnels)
        {
            if (adjoining == checked)             // Correct trajectory - room traversal possible
            {
                match_found = true;
                arrow = adjoining;
                if (arrow == wump.get_position()) // Wumpus hit with the arrow
                {
                    std::cout << "You hear a screech.\n";
                    wump.kill();
                    return;
                }
                break;
            }
        }//end arrow->tunnels for
        if (!match_found) // Invalid input - Room in arrow_trajectory matches no adjoining rooms
        {
            std::ostringstream oss;
            oss << "Invalid input. Cannot reach room " << checked->number << " from room " << arrow->number
                << ", as it only leads to rooms " << arrow->tunnels[0]->number << ", " << arrow->tunnels[1]->number
                << " and " << arrow->tunnels[2]->number << '.';
            throw std::invalid_argument(oss.str());
        }
    }//end arrow_trajectory for

    // Valid trajectory - rooms input by the user were present in "tunnels" array of each corresponding room
    // The arrow was shot successfully but did not hit the Wumpus
    --arrows;
    std::ostringstream oss;
    oss << "You missed. There ";
    switch (arrows)
    {
    case 0:
        oss << "are no arrows left.\n";
        break;
    case 1:
        oss << "is only 1 arrow left.\n";
        break;
    default:
        oss << "are " << arrows << " arrows left.\n";
        break;
    }
    oss << "Running Wumpus can be heard...\n";
    std::cout << oss.str() << std::endl;
    wump.move(nullptr);
}
