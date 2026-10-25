#include "game.h"

long check_riding_box(short *box, long riding, long sprite_no)
{
    long rect[4];
    long x;
    long y;

    rect[0] = box[0];
    rect[1] = box[1];
    rect[2] = box[2];
    rect[3] = box[3];
    if (riding) {
        rect[0] = rect[0] + sprite_pos[sprite_no][2];
        rect[1] = rect[1] + sprite_draw_ys[sprite_no] + 7;
        rect[2] = rect[2] + sprite_pos[sprite_no][2];
        rect[3] = rect[3] + sprite_draw_ys[sprite_no] + 7;
    }
    x = link_x;
    y = link_y;
    return x >= rect[0] && y >= rect[1] && x <= rect[2] && y <= rect[3];
}
