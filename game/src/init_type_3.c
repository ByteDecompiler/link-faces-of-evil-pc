#include "game.h"

void init_type_3(long sprite_idx, struct macro_def *def)
{
    register struct macro_def *mdef;

    init_type_1(sprite_idx, def);
    mdef = def;
    ((struct macro_b *)macros[sprite_idx])->alt3_chance = mdef->alt_chance;
    ((struct macro_b *)macros[sprite_idx])->b2a = mdef->alt_macro;
    ((struct macro_b *)macros[sprite_idx])->b2b = mdef->alt_repeat;
    if (mdef->alt_dir != 6 && mdef->alt_dir != 10 && mdef->alt_dir != 2)
        mdef->alt_dir = 2;
    ((struct macro_b *)macros[sprite_idx])->alt3_dir = mdef->alt_dir;
    ((struct macro_b *)macros[sprite_idx])->alt3_speed = mdef->alt_speed;
    if (((struct macro_b *)macros[sprite_idx])->alt3_speed < 1)
        ((struct macro_b *)macros[sprite_idx])->alt3_speed = 1;
    if (((struct macro_b *)macros[sprite_idx])->alt3_speed > 8)
        ((struct macro_b *)macros[sprite_idx])->alt3_speed = 8;
    if (music_paused && room_number == 4 && sprite_idx == 1) {
        macros[sprite_idx]->lo = def->x + 15;
        macros[sprite_idx]->hi = def->x + 16;
        if (macros[sprite_idx]->state == 6)
            macros[sprite_idx]->target = macros[sprite_idx]->lo;
        else
            macros[sprite_idx]->target = macros[sprite_idx]->hi;
        ((struct macro_b *)macros[sprite_idx])->alt3_chance = 10;
        ((struct macro_b *)macros[sprite_idx])->b2b = 8;
    }
}
