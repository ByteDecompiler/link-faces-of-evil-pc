#include "game.h"

void check_map_while_walking(long dir)
{
    move_1_block(0, dir, 0);
    if (!jump_info_solid) {
        if (walk_toggle)
            link_anim_step = 1;
        else
            link_anim_step = 0;
        walk_toggle = 1 - walk_toggle;
    }
}
