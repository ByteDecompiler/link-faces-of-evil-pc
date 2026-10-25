#include <string.h>
#include "pc.h"

#define W SCREEN_W
#define H SCREEN_H

extern const u32 recolor_runs[];
extern const struct recolor_frame recolor_frames[];
extern const int recolor_count;

static u8 fix[H][W];
static const u8 (*result)[W];
static u32 frame_hash = 1;
static long frame_anim = -1;

const u8 (*cutscene_fix(long anim, const u8 img[H][W]))[W]
{
    u32 hash = 2166136261u;
    for (int y = 0; y < H; y++)
        for (int x = 0; x < W; x++)
            hash = (hash ^ img[y][x]) * 16777619u;
    if (hash != frame_hash || anim != frame_anim) {
        frame_hash = hash;
        frame_anim = anim;
        result = NULL;
        for (int i = 0; i < recolor_count; i++) {
            const struct recolor_frame *f = &recolor_frames[i];
            if (f->anim != anim || f->hash != hash)
                continue;
            memset(fix, 0, sizeof fix);
            for (u32 k = f->first; k < f->first + f->count; k++) {
                u32 r = recolor_runs[k], at = r >> 15, len = r >> 7 & 0xff;
                memset(&fix[0][0] + at, (int)(r & 0x7f), len);
            }
            result = (const u8(*)[W])fix;
            break;
        }
    }
    return result;
}
