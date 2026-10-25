#include "game.h"

long check_screen_edges(void)
{
    register long steps;
    long delta;
    long moved;

    moved = 0;
    steps = link_target_y - link_screen_y;
    if (steps < 0)
        steps = -steps;
    for (; steps > 0; --steps) {
        if (link_screen_y > 45 && pf_y_px_max - 3 > pf_y_px) {
            --link_screen_y;
            --link_sprite_y;
            inc_pf_y();
            moved = 1;
        } else if (link_screen_y + 0 > 59) {
            --link_y;
            --link_screen_y;
            --link_sprite_y;
            moved = 1;
        } else if (link_screen_y < 22 && pf_y_px > 3) {
            ++link_screen_y;
            ++link_sprite_y;
            dec_pf_y();
            moved = 1;
        } else if (link_screen_y - 14 < 0) {
            delta = link_target_x - link_screen_x;
            link_x += delta;
            link_screen_x += delta;
            link_sprite_x += delta;
            delta = link_target_y - link_screen_y;
            link_y += delta;
            link_screen_y += delta;
            link_sprite_y += delta;
        }
    }
    steps = link_target_x - link_screen_x;
    if (steps < 0)
        steps = -steps;
    for (; steps > 0; --steps) {
        if (link_screen_x > 52 && pf_x_px_max - 3 > pf_x_px) {
            --link_screen_x;
            --link_sprite_x;
            inc_pf_x();
            moved = 1;
        } else if (link_screen_x + 9 > 103) {
            --link_x;
            --link_screen_x;
            --link_sprite_x;
            moved = 1;
        } else if (link_screen_x < 44 && pf_x_px > 3) {
            ++link_screen_x;
            ++link_sprite_x;
            dec_pf_x();
            moved = 1;
        } else if (link_screen_x - 9 < -8) {
            ++link_x;
            ++link_screen_x;
            ++link_sprite_x;
            moved = 1;
        }
    }
    return moved;
}
