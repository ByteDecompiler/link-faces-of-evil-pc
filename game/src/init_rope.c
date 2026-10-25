#include "game.h"

void init_rope(void)
{
    get_sprite_block(link_x, link_y, &jump_info);
    if ((jump_info.floor || jump_info_solid || jump_info.track || jump_info.climb_b || jump_info.climb_a)
            && !jump_info.deadly && !jump_info.right && !jump_info.left) {
        if (jump_info.climb_b && old_get_sprite_block(link_x, link_y - 1) == 25)
            return;
        if (jump_info.climb_a && old_get_sprite_block(link_x, link_y - 1) == 48)
            return;
        rope_out = 1;
        rope_x = link_x;
        rope_top = rope_bottom = link_y - 10;
        old_link_dir = link_dir;
        link_dir = 2;
        link_sprite_x = link_screen_x - 8;
        link_thrusting = 0;
        go_find_hero_action(15);
        anim_frame_idx = 0;
        cur_sprite = sprite_frames[hero_actions[hero_action].frames[anim_frame_idx]];
        link_moved = 1;
        link_anim_step = 0;
    }
}
