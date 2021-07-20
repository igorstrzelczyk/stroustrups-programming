/*
    Room Struct Source file

    Revision history:

        Originally written by Igor Strzelczyk
            (igor.strzelczyk@icloud.com) July 2021

    Following code contains definitions of Room Struct operators.
*/
#include "room.h"

std::ostream& operator<<(std::ostream& os, const Room& r)
{
    os << "[Room " << r.number << "]\nHazard: ";
    if (r.hazard == Hazard::None) os << "None\n";
    else if (r.hazard == Hazard::Bat) os << "Bat\n";
    else os << "Pit\n";
    os << "Tunnels to:";
    for (const auto& t : r.tunnels) os << ' ' << t->number;
    os << std::endl;
    return os;
}
