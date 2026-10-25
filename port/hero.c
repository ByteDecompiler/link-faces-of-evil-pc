#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pc.h"

#define PICS_SIZE 0x6000
#define HITS_SIZE 0x570
#define P(x) ((u8 *)(uintptr_t)(u32)(x))

extern s32 link_imagery, cmaps[], *sprite_frames, cur_sprite;
void display_message(const char *text);
void state_add(void *p, u32 size);

static u8 zelda_pics[PICS_SIZE], zelda_hits[HITS_SIZE], link_pics[PICS_SIZE], link_hits[HITS_SIZE];
static int have_zelda;
static int have_link;
static int hero_now;

static int zelda_startup_sector(void)
{
    static const struct { u32 size; int sector; } versions[] = {
        {134464, 0xaf}, {134292, 0xb0}, {134332, 0xae}, {134248, 0xb0},
    };
    u32 n;
    u8 *mod = disc_load_file("cdi_zelda", &n);
    if (!mod)
        return -1;
    u32 size = be32(mod + 4);
    free(mod);
    for (int i = 0; i < 4; i++)
        if (versions[i].size == size)
            return versions[i].sector;
    return -1;
}

static int read_zelda(void)
{
    u32 first, size;
    u8 raw[SECTOR_RAW];
    struct sector s;
    int sector = zelda_startup_sector(), pics = 0, hits = 0;
    if (sector < 0 || !disc_file("zdata.rtr", &first, &size))
        return 0;
    for (u32 n = (u32)sector; n * 2048 < size; n++) {
        if (!disc_read(first + n, raw))
            return 0;
        disc_parse(raw, &s);
        if (s.data && s.channel == 4 && pics + s.size <= PICS_SIZE) {
            memcpy(zelda_pics + pics, s.payload, s.size);
            pics += s.size;
        } else if (s.data && s.channel == 5 && hits < HITS_SIZE) {
            int k = s.size < HITS_SIZE - hits ? s.size : HITS_SIZE - hits;
            memcpy(zelda_hits + hits, s.payload, k);
            hits += k;
        }
        if (s.eor)
            break;
    }
    return be32(zelda_pics) == 0x50414330 && be32(zelda_pics + 8) == 0x6c && hits == HITS_SIZE;
}

void hero_init(void)
{
    char path[260];
    u32 first, size;
    disc_select(1);
    if (settings.zelda_disc[0] && disc_open(settings.zelda_disc) && disc_file("cdi_zelda", &first, &size))
        snprintf(path, sizeof path, "%s", settings.zelda_disc);
    else if (!disc_find("cdi_zelda", path, sizeof path))
        path[0] = 0;
    have_zelda = path[0] && read_zelda();
    disc_select(0);
    if (path[0])
        LOG("zelda disc: %s (%s)\n", path, have_zelda ? "her pictures read" : "couldn't read her pictures");
    state_add(&hero_now, sizeof hero_now);
}

static void put(int hero)
{
    u8 *pics = P(link_imagery);
    memcpy(pics, hero ? zelda_pics : link_pics, PICS_SIZE);
    memcpy(P(cmaps[0]), hero ? zelda_hits : link_hits, HITS_SIZE);
    if (sprite_frames)
        for (int i = 0; i < 24; i++) {
            s32 old = sprite_frames[i];
            sprite_frames[i] = link_imagery + 0x6c + (s32)be32(pics + 0x0c + 4 * i);
            if (cur_sprite == old)
                cur_sprite = sprite_frames[i];
        }
    hero_now = hero;
}

void port_hero_loaded(void)
{
    memcpy(link_pics, P(link_imagery), PICS_SIZE);
    memcpy(link_hits, P(cmaps[0]), HITS_SIZE);
    have_link = 1;
    hero_now = 0;
    if (settings.hero && have_zelda)
        put(1);
}

void hero_toggle(void)
{
    if (!have_zelda) {
        display_message("No Zelda disc found: put its .bin next to link.exe");
        return;
    }
    settings.hero = !settings.hero;
    if (have_link)
        put(settings.hero);
    settings_save();
}

const char *hero_text(void)
{
    if (!have_zelda)
        return "Link (no Zelda disc found)";
    return settings.hero ? "Zelda" : "Link";
}

void hero_after_load(void)
{
    if (have_link && hero_now != (settings.hero && have_zelda))
        put(settings.hero && have_zelda);
}
