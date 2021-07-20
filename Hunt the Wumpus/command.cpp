/*
    Command Struct Source file

    Revision history:

        Originally written by Igor Strzelczyk
            (igor.strzelczyk@icloud.com) July 2021

    Following code contains definitions of Command Struct operators.
*/
#include "command.h"

std::istream& operator>>(std::istream& is, Command& cmd)
{
    constexpr char delim {'-'}; // Delimiting char when inputting more than one room number

    char c;

    is.get(c);
    if (c != 'm' && c!= 'M' && c != 's' && c != 'S')
    {
        is.unget();
        is.clear(std::ios_base::failbit);
        return is;
    }

    char action_t {tolower(c)}; // cmd.action
    std::vector<short> rooms;   // cmd.rooms

    while (is.get(c) && c != '\n')
    {
        // Vector capacity met (movement range is 1 Room, bow range is 3 Rooms) - no extra chars
        // should have been extracted at this point
        if ( (action_t == 'm' && rooms.size() == 1) ||
             (action_t == 's' && rooms.size() == 3) ) is.clear(std::ios_base::failbit);

        if (isdigit(c))
        {
            is.unget();
            short index;
            is >> index;
            rooms.push_back(index);
        }
        else if (c != delim || (c == delim && is.peek() == '\n')) // Input must not end with delim char
            is.clear(std::ios_base::failbit);
    }//end while
    if (is.good())
        cmd = Command {action_t, rooms};
    return is;
}

std::ostream& operator<<(std::ostream& os, const Command& cmd)
{
    os << "Command: ";
    if (cmd.action == 'm') return os << "Move to room " << cmd.rooms.front();
    os << "Shoot ";
    if (cmd.rooms.size() == 1) os << "into room " << cmd.rooms.front();
    else if (cmd.rooms.size() == 2) os << "through rooms " << cmd.rooms[0] << " and " << cmd.rooms[1];
    else os << "through rooms " << cmd.rooms[0] << ", " << cmd.rooms[1] << " and " << cmd.rooms[2];
    return os;
}
