#include "game.h"

char mem_space[60];

void decode_mem_space(void)
{
    register unsigned char *src;
    long i;

    src = (unsigned char *)mem_space;
    initial_item_quantity();
    for (i = 0; i < 32; ++i)
        experiences[i] = *src++;
    for (i = 0; i < 21; ++i)
        item_counts[i] = *src++;
    rubies = *src++ << 8;
    rubies |= *src++;
    for (i = 22; i <= 26; ++i)
        item_counts[i] = *src++;
    selected_item = 99;
    initial_areas();
    for (i = 0x8b; i <= 0x96; ++i)
        if (check_experience(i))
            open_up_area(i - 0x80, 0);
}
