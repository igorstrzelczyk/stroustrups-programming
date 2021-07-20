/*
    Room Struct Header file

    Revision history:

        Originally written by Igor Strzelczyk
            (igor.strzelczyk@icloud.com) July 2021

    Following code contains definition of Hazard Enumaration class and Room Struct.
*/
#ifndef ROOM_H
#define ROOM_H

#include <iostream>

enum class Hazard : char { None, Bat, Pit };

struct Room {
    short  number     {0};
    Hazard hazard     {Hazard::None};
    Room*  tunnels[3] {nullptr};
};

std::ostream& operator<<(std::ostream&, const Room&);

#endif // ROOM_H
