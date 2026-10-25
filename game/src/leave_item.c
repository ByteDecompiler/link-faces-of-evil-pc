#include "game.h"

void leave_item(long kind, long x, long y)
{
    long id;
    long item;
    long temporary;

    id = -1;
    switch (kind) {
    case 1:
        item = 2;
        temporary = 1;
        break;
    case 2:
        item = 3;
        temporary = 1;
        break;
    case 3:
        item = 4;
        temporary = 1;
        break;
    case 4:
        item = randomize() % 2 ? 2 : 3;
        temporary = 1;
        break;
    case 5:
        item = randomize() % 2 ? 3 : 4;
        temporary = 1;
        break;
    case 6:
        item = randomize() % 5 == 1 ? 4 : (randomize() % 2 ? 2 : 3);
        temporary = 1;
        break;
    case 7:
        item = 11;
        temporary = 1;
        break;
    case 8:
        item = 12;
        temporary = 1;
        break;
    case 9:
        id = 0x30;
        item = 14;
        temporary = 0;
        mark_experience(0x9a);
        break;
    case 10:
        id = 0x31;
        item = 13;
        temporary = 0;
        mark_experience(0x9b);
        break;
    case 11:
        id = 0x32;
        item = 16;
        temporary = 0;
        mark_experience(0x9c);
        break;
    case 12:
        id = 0x33;
        item = 19;
        temporary = 0;
        mark_experience(0x9d);
        break;
    case 13:
        id = 0x34;
        item = 20;
        temporary = 0;
        mark_experience(0x9e);
        break;
    case 14:
        id = 0x35;
        item = 21;
        temporary = 0;
        mark_experience(0x9f);
        break;
    case 15:
        id = 0x2d;
        item = 15;
        temporary = 0;
        mark_experience(0xa0);
        break;
    case 17:
        id = 5;
        item = 5;
        temporary = 0;
        mark_experience(0xa1);
        break;
    case 18:
        id = 6;
        item = 5;
        temporary = 0;
        mark_experience(0xa2);
        break;
    case 19:
        id = 7;
        item = 5;
        temporary = 0;
        mark_experience(0xa3);
        break;
    case 20:
        id = 8;
        item = 5;
        temporary = 0;
        mark_experience(0xa4);
        break;
    case 21:
        id = 9;
        item = 5;
        temporary = 0;
        mark_experience(0xa5);
        break;
    case 22:
        id = 10;
        item = 5;
        temporary = 0;
        mark_experience(0xa6);
        x = 0x70;
        y = 21;
        break;
    default:
        item = 4;
        temporary = 1;
        break;
    case 16:
        break;
    }
    if (!temporary)
        tool_spots[id].room = room_number;
    add_to_playfield_tools(temporary, id == -1 ? item : id, x + 7, y + 7, item, temporary == 0 ? 0 : 0x50);
}
