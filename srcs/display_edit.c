#include "readline.h"

void	clear_line(void)
{
	write(1, START_LINE, 4);
	write(1, CLEAR_LINE, 4);
}

void	clear_term(t_pos offset)
{
	// int	y;

	// y = y_offset;
	// while (y_offset > 0)
	// {
	// 	if (!(y_offset == y && (x_offset == 0 || x_offset == 1)))
	// 	{
	// 		clear_line();
	// 		write(1, UP_TERMINAL, 3);
	// 	}
	// 	y_offset--;
	// }
	// clear_line();
	while (offset.y > 0)
	{
		clear_line();
		write(1, UP_TERMINAL, 3);
		offset.y--;
	}
	clear_line();
}
