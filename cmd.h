#ifndef _COMMANDLINE_H
#define _COMMANDLINE_H

#include <stdbool.h>

char line[248];
extern volatile char lastest_c;
extern volatile bool line_done;

enum directions
{
    UP,
    DOWN,
    RIGHT,
    LEFT
};

void move_cursor(enum directions dir);

void cmd_init();


#endif
