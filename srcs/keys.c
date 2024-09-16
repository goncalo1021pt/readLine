#include "readline.h"

void handle_backspace(char *line, size_t *len)
{
	if (*len == 0)
		return;
	write(1, "\b \b", 3);
	line[*len] = 0;
	(*len)--;
}

void handle_enter(char *line, size_t *len)
{
    line[*len] = '\0';
}

// void

// void key_handler (char *buffer, int read_bytes)
// {
	
// }