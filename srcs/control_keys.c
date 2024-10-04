#include "readline.h"

void	handle_backspace(t_line *l)
{
	if (l->current == l->initial)
		return ;
	l->current--;
	write_buffer(l);
}

void	handle_enter(t_line *l)
{
	(void)l;
	// write(1, "\n", 1);
}
