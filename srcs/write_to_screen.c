#include "readline.h"

void	save_pos(char *buffer)
{
	int	i;
	int	ret;

	i = 0;
	write(1, "\e[6n", 4);
	while (1)
	{
		ret = read(0, &buffer[i], 1);
		if (ret == 0 || buffer[i] == 'R')
			break ;
		i++;
	}
	buffer[i] = 0;
}

void	get_cursor_position(int *rows, int *cols)
{
	char	buffer[255];
	int		i;

	i = 0;
	save_pos(buffer);
	if (buffer[0] == '\033' && buffer[1] == '[')
	{
		*rows = 0;
		*cols = 0;
		i = 2;
		while (buffer[i] != ';' && buffer[i] != '\0')
		{
			*rows = *rows * 10 + (buffer[i] - '0');
			i++;
		}
		i++;
		while (buffer[i] != 'R' && buffer[i] != '\0')
		{
			*cols = *cols * 10 + (buffer[i] - '0');
			i++;
		}
	}
	else
		*rows = *cols = -1;
}

void	move_cursor_to_position(int row, int col)
{
	char	buffer[32];
	int		len;

	len = snprintf(buffer, sizeof(buffer), "\033[%d;%dH", row, col);
	write(STDOUT_FILENO, buffer, len);
}

void	update_cursor(t_pos start)
{
	t_pos	current;

	get_cursor_position(&current.y, &current.x);
	while (current.y > start.y)
	{
		write(1, UP_TERMINAL, 3);
		current.y--;
	}
	while (current.x > start.x)
	{
		write(1, LEFT_TERMINAL, 3);
		current.x--;
	}
}

void	write_buffer(t_line *l)
{
	t_winsize	w;
	t_pos		offset;
	// t_pos		pos;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
	offset.y = (str_len_rl(l->prompt) + str_len_rl(l->line)) / w.ws_col;
	fprintf(stderr, "len: %zu\nw.ws_row: %d\n", str_len_rl(l->prompt) + str_len_rl(l->line), w.ws_col);
	// offset.y = l->initial / (w.ws_col);
	// offset.x = l->initial % (w.ws_col);
	// get_cursor_position(&pos.y, &pos.x);
	clear_term(offset);
	write(1, l->prompt, str_len_rl(l->prompt));
	write(1, l->line, str_len_rl(l->line));
	// update_cursor(pos);
	// printf("\033[%d;%dH", pos.y, pos.x);
}
