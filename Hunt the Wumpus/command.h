/*
    Command Struct Header file

    Revision history:

        Originally written by Igor Strzelczyk
            (igor.strzelczyk@icloud.com) July 2021

    Following code contains definition of Command Struct and declaration of its operator overloads.
*/
#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <iostream>

// Data structure to create commands from user input; ex. "m2" means "move to room 2"
struct Command {
    char               action; // Type of command ['m' for "move"; 's' for "shoot"]
    std::vector<short> rooms;  // Action targets [Room number - 1 == Indices of Room objects for Room* dereference]
};

std::istream& operator>>(std::istream&, Command&);
std::ostream& operator<<(std::ostream&, const Command&);

#endif // COMMAND_H
