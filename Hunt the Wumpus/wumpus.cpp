/*
    Wumpus Source file

    Revision history:

        Originally written by Igor Strzelczyk
            (igor.strzelczyk@icloud.com) July 2021

    Following code contains definitions of main functions of the game.
*/
#include "wumpus.h"

// Function printing title of the game and its rules
void print_rules()
{
    std::cout << "\tHunt the Wumpus (v. 1.0) - game implementation by Igor Strzelczyk\n" << std::endl;
    std::cout << "\"Hunt the Wumpus\" (or just \"Wump\") is a simple (non-graphical) computer game "
              << "originally invented by Gregory Yob.\nThe basic premise is that a rather smelly monster "
              << "lives in a dark cave consisting of connected rooms. Your job is\nto slay the Wumpus using "
              << "bow and arrow. In addition to the Wumpus, the cave has two hazards: bottomless pits and\n"
              << "giant bats. If you enter a room with a bottomless pit, it's the end of the game for you. "
              << "If you enter a room with\na bat, the bat picks you up and drops you into another room. "
              << "If you enter the room with the Wumpus or he enters\nyours, he eats you. When you enter "
              << "a room you will be told if a hazard is nearby:\n\n\t\"I smell the Wumpus\": It's in an "
              << "adjoining room.\n\t\"I feel a breeze\": One of the adjoining rooms is a bottomless pit.\n\t"
              << "\"I hear a bat\": A giant bat is in an adjoining room.\n\nFor your convenience, rooms are "
              << "numbered. Every room is connected by tunnels to three other rooms. When entering\na room, "
              << "you are told something like \"You are in room 12; there are tunnels to rooms 1, 13, and 4; "
              << "move or shoot?\"\nPossible answers are m13 (\"Move to room 13\") and s13-4-3 (\"Shoot an arrow "
              << "through rooms 13, 4, and 3\"). The range\nof an arrow is three rooms. At the start of the game, "
              << "you have five arrows. The snag about shooting is that it\nwakes up the Wumpus and he moves to a "
              << "room adjoining the one he was in - that could be your room.\n" << std::endl;
}

// Function asking the user whether they want to play again
bool play_again()
{
    for (char c; std::cin >> c; )
    {
        if (std::cin.get() != '\n') std::cout << "\nOnly one character is expected.\n";
        else if (c == 'y' || c == 'Y') return true;
        else if (c == 'n' || c == 'N') break;
        else std::cout << "\nInvalid character \'" << c << "\'.\n";
        std::cout << "Please try again: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return false;
}

void run_game()
{
    print_rules();
    while (true)
    {
        // Game start
        Game_map cave;
        Player p(cave.get_room(1)); // Player always starts in Room 1
        Wumpus wump(wump_spawn(cave));

        // Player turn
        for (Command cmd; p.is_alive() && p.get_arrows() && wump.is_alive(); ) // Player input loop
        {
            room_info(p.get_position(), wump.get_position());
            std::cout << "Move or shoot?\n> ";

            try
            {
                std::cin >> cmd;
                if (std::cin)
                {
                    std::vector<Room*> target;
                    for (const auto& room : cmd.rooms) target.push_back(cave.get_room(room));
                    std::cout << cmd << "\n\n\n";
                    if (cmd.action == 'm') p.move(target[0]);
                    else p.shoot(target, wump);
                }
                else
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please try again.\n\n";
                }
                // Results of player actions
                if (p.get_position() == wump.get_position())
                {
                    std::cout << "You were killed by the Wumpus...\n\n";
                    p.kill();
                }
                if (p.get_position()->hazard == Hazard::Pit)
                {
                    std::cout << "You fell into bottomless pit...\n\n";
                    p.kill();
                }
                if (p.get_position()->hazard == Hazard::Bat) bat_met(p, cave);
            }//end try
            catch (std::exception& e)
            {
                std::cerr << e.what() << std::endl;
            }
        }//end Player input for

        // Game_Over
        // Checks the reason of game over and prints appropriate output
        if (!wump.is_alive()) std::cout << "Congratulations, you have slain the Wumpus!\n\n";
        else if (!p.get_arrows())
            std::cout << "You wander around the cave until you hear a strange noise. It's the Wumpus!\n\n"
                      << "Without any means of defending yourself, you stand no chance and are shortly killed "
                      << "by the beast.\n\n";

        std::cout << "Game Over. Would you like to play again [y/n]?: ";
        if (!play_again()) break;
        actors().clear();
    }//end gameplay loop while
    // Quit
    std::cout << "\n\tThank you for playing!" << std::endl;
}

