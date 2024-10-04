#include "readline.h"

void	handle_left(t_line *l)
{
	t_winsize	w;
	int			y_offset;
	int			x_offset;
	(void)y_offset;

	if (l->current == l->initial)
		return ;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
	l->current--;
	y_offset = l->current / (w.ws_col);
	x_offset = l->current % (w.ws_col);
	// fprintf(stderr, "y_offset: %d\n", y_offset);
	if (x_offset == 0 && w.ws_col > 0)
	{
		write(1, UP_TERMINAL, 3);
		while (w.ws_col > 0)
		{
			write(1, RIGHT_TERMINAL, 3);
			w.ws_col--;
		}
	}
	else
		write(1, LEFT_TERMINAL, 3);
}

void	handle_right(t_line *l)
{
	t_winsize	w;

	if (l->current == str_len_rl(l->line) + l->initial)
		return ;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
	l->current++;
	write(1, RIGHT_TERMINAL, 3);
}

void	handle_up(t_line *l)
{
	(void)l;
	// write(1,"\e[A", 4);
}

void	handle_down(t_line *l)
{
	(void)l;
	// write(1,"\e[B", 4);
}
