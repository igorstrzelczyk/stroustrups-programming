/*
    Game_map Class Source file

    Revision history:

        Originally written by Igor Strzelczyk
            (igor.strzelczyk@icloud.com) July 2021

    Following code contains definitions of Game_map Class member functions.
*/
#include "game_map.h"

/* Constructor generating cave, in which the game takes place - a pointer to array of 25 Room objects allocated
    on free memory. The layout of the cave is fixed, with every room being connected with tunnels to three different
    ones. In most cases, one of the tunnel leads back to the room player came from. With this approach however,
    one of the rooms would always remain with only two possible routes. As such, Room 25 has a secret, one-way
    passage leading back to Room 9.
*/
Game_map::Game_map()
{
    const size_t last {size - 1}; // Index of last Room
    int bat_count {0},
        pit_count {0};

    // Initialising members of Room objects
    for (size_t i = 0; i < size; ++i) rooms[i].number = i + 1;                 // Numbers rooms
    for (Room* r = &rooms[last]; bat_count < max_bats || pit_count < max_pits; // Generates hazards until reached max
            r = &rooms[random(4, last)])                                       // First four rooms cannot be hazardous
    {
        Hazard h = generate_hazard();
        if (r->hazard == Hazard::None && h == Hazard::Bat && bat_count < max_bats)
        {
            r->hazard = Hazard::Bat;
            ++bat_count;
        }
        else if (r->hazard == Hazard::None && h == Hazard::Pit && pit_count < max_pits)
        {
            r->hazard = Hazard::Pit;
            ++pit_count;
        }
    }//end for

    // Fixed cave layout; tunnels between rooms
    rooms[0].tunnels[0] = &rooms[1];     // Room 1
    rooms[0].tunnels[1] = &rooms[2];
    rooms[0].tunnels[2] = &rooms[3];

    rooms[1].tunnels[0] = &rooms[0];     // Room 2
    rooms[1].tunnels[1] = &rooms[2];
    rooms[1].tunnels[2] = &rooms[4];

    rooms[2].tunnels[0] = &rooms[0];     // Room 3
    rooms[2].tunnels[1] = &rooms[1];
    rooms[2].tunnels[2] = &rooms[5];

    rooms[3].tunnels[0] = &rooms[0];     // Room 4
    rooms[3].tunnels[1] = &rooms[6];
    rooms[3].tunnels[2] = &rooms[7];

    rooms[4].tunnels[0] = &rooms[1];     // Room 5
    rooms[4].tunnels[1] = &rooms[10];
    rooms[4].tunnels[2] = &rooms[11];

    rooms[5].tunnels[0] = &rooms[2];     // Room 6
    rooms[5].tunnels[1] = &rooms[9];
    rooms[5].tunnels[2] = &rooms[10];

    rooms[6].tunnels[0] = &rooms[3];     // Room 7
    rooms[6].tunnels[1] = &rooms[7];
    rooms[6].tunnels[2] = &rooms[8];

    rooms[7].tunnels[0] = &rooms[3];     // Room 8
    rooms[7].tunnels[1] = &rooms[6];
    rooms[7].tunnels[2] = &rooms[8];

    rooms[8].tunnels[0] = &rooms[6];     // Room 9
    rooms[8].tunnels[1] = &rooms[7];
    rooms[8].tunnels[2] = &rooms[9];

    rooms[9].tunnels[0] = &rooms[5];     // Room 10
    rooms[9].tunnels[1] = &rooms[8];
    rooms[9].tunnels[2] = &rooms[12];

    rooms[10].tunnels[0] = &rooms[4];    // Room 11
    rooms[10].tunnels[1] = &rooms[5];
    rooms[10].tunnels[2] = &rooms[11];

    rooms[11].tunnels[0] = &rooms[4];    // Room 12
    rooms[11].tunnels[1] = &rooms[10];
    rooms[11].tunnels[2] = &rooms[12];

    rooms[12].tunnels[0] = &rooms[9];    // Room 13
    rooms[12].tunnels[1] = &rooms[11];
    rooms[12].tunnels[2] = &rooms[13];

    rooms[13].tunnels[0] = &rooms[12];   // Room 14
    rooms[13].tunnels[1] = &rooms[14];
    rooms[13].tunnels[2] = &rooms[15];

    rooms[14].tunnels[0] = &rooms[13];   // Room 15
    rooms[14].tunnels[1] = &rooms[15];
    rooms[14].tunnels[2] = &rooms[16];

    rooms[15].tunnels[0] = &rooms[13];   // Room 16
    rooms[15].tunnels[1] = &rooms[14];
    rooms[15].tunnels[2] = &rooms[16];

    rooms[16].tunnels[0] = &rooms[14];   // Room 17
    rooms[16].tunnels[1] = &rooms[15];
    rooms[16].tunnels[2] = &rooms[17];

    rooms[17].tunnels[0] = &rooms[16];   // Room 18
    rooms[17].tunnels[1] = &rooms[18];
    rooms[17].tunnels[2] = &rooms[19];

    rooms[18].tunnels[0] = &rooms[17];   // Room 19
    rooms[18].tunnels[1] = &rooms[19];
    rooms[18].tunnels[2] = &rooms[20];

    rooms[19].tunnels[0] = &rooms[17];   // Room 20
    rooms[19].tunnels[1] = &rooms[18];
    rooms[19].tunnels[2] = &rooms[20];

    rooms[20].tunnels[0] = &rooms[18];   // Room 21
    rooms[20].tunnels[1] = &rooms[19];
    rooms[20].tunnels[2] = &rooms[21];

    rooms[21].tunnels[0] = &rooms[20];   // Room 22
    rooms[21].tunnels[1] = &rooms[22];
    rooms[21].tunnels[2] = &rooms[23];

    rooms[22].tunnels[0] = &rooms[21];   // Room 23
    rooms[22].tunnels[1] = &rooms[23];
    rooms[22].tunnels[2] = &rooms[24];

    rooms[23].tunnels[0] = &rooms[21];   // Room 24
    rooms[23].tunnels[1] = &rooms[22];
    rooms[23].tunnels[2] = &rooms[24];

    rooms[24].tunnels[0] = &rooms[22];   // Room 25
    rooms[24].tunnels[1] = &rooms[23];
    rooms[24].tunnels[2] = &rooms[8];
}
