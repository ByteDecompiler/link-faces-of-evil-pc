#include "game.h"

char initial_area_tab[16];

void initial_areas(void)
{
    long i;

    for (i = 0; i < 16; ++i)
        areas[i] = initial_area_tab[i];
}
