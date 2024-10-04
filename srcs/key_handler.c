#include "readline.h"

void	print_key(t_line *l)
{
	write_buffer(l);
}

int	get_key(char *buffer, int read_bytes)
{
	if (read_bytes == 3)
	{
		if (buffer[0] == 27 && buffer[1] == '[' && buffer[2] == 68)
			return (LEFT);
		if (buffer[0] == 27 && buffer[1] == '[' && buffer[2] == 67)
			return (RIGHT);
		if (buffer[0] == 27 && buffer[1] == '[' && buffer[2] == 65)
			return (UP);
		if (buffer[0] == 27 && buffer[1] == '[' && buffer[2] == 66)
			return (DOWN);
	}
	else if (buffer[0] >= 32 && buffer[0] <= 126)
		return (PRINTABLE);
	else if (buffer[0] == 127)
		return (BACKSPACE);
	else if (buffer[0] == 10)
		return (ENTER);
	return (-1);
}

void	key_handler(char *buffer, int read_bytes, t_line *l)
{
	int	key;

	key = get_key(buffer, read_bytes);
	if (key == PRINTABLE)
		print_key(l);
	else if (key == LEFT)
		handle_left(l);
	else if (key == RIGHT)
		handle_right(l);
	else if (key == UP)
		handle_up(l);
	else if (key == DOWN)
		handle_down(l);
	else if (key == BACKSPACE)
		handle_backspace(l);
	else if (key == ENTER)
		handle_enter(l);
}
