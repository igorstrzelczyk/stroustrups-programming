/*
    "Hunt the Wumpus" game implementation

    Revision history:

        Revised by Igor Strzelczyk; 19/07/2021 - Minor code cleanup and division among several translation units
        Originally written by Igor Strzelczyk
            (igor.strzelczyk@icloud.com) June 2021

    Following code is a proposed solution to exercise 12 of chapter 18 from
    Bjarne Stroustrup's "Programming -- Principles and Practice Using C++".

    It contains "Hunt the Wumpus" game implementation. It is a non-graphical computer game originally invented
    by Gregory Yob, where player is tasked with killing a monster living in a cave of connected rooms using only his
    bow and arrows.
    At the start of every turn, player is informed of their position (number of the room), rooms they are able
    to enter and possible hazards ahead. Apart from the Wumpus, there are also endless pits and giant bats. Player has
    the possibility of shooting one of their five arrows at any time to try and hunt the monster. The range of the bow
    is three rooms. Whenever a shot is made however, Wumpus awakes and moves to one of the adjoining rooms.
    When the Wumpus enters the room player is currently in or vice versa the player is killed. The game also ends
    when the player falls into the endless pit or runs out of arrows. Entering a room with a giant bat makes
    the animal grab the player and move each of them to a random room.

    For more detailed description, please open README.md file.

    Player interacts with the game by inputting commands on the computer's keyboard and receiving results of their
    actions by output displayed on the screen, in the program's console.
*/

#include "wumpus.h"
#include <cstdlib>      // rand()
#include <ctime>        // time()
#include <iostream>     // cout, cerr
#include <stdexcept>    // STL exceptions

int main()
{
    try
    {
        std::srand(std::time(nullptr)); // Seeds rand()
        run_game();
        return 0;
    }
    catch (Player::Invalid_spawn& e)
    {
        std::cerr << "Failed to construct Player object. " << e.msg << std::endl;
        return 1;
    }
    catch (Wumpus::Invalid_spawn& e)
    {
        std::cerr << "Failed to construct Wumpus object. " << e.msg << std::endl;
        return 1;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 2;
    }
    catch (...)
    {
        std::cerr << "Something went wrong." << std::endl;
        return 3;
    }
}
