#include "game.h"

char file_name[16];
char host_name[16];

void create_file_and_host_names(long slot_number)
{
    file_name[9] = slot_number + '0';
    host_name[14] = slot_number + '0';
}
