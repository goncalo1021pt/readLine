#include "readline.h"

void get_back_to_pos(t_line *l)
{
	size_t i;

	i = l->current - l->initial;
	while (i < str_len_rl(l->line) + 1)
	{
		write(1, "\b", 1);
		i++;
	}
}


// void write_line(t_line *l)
// {
// 	t_winsize	w;
// 	int 		line_size;
// 	int 		tmp;

// 	ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
// 	write(1, "\r", 1);
// 	if (l->current % w.ws_col - 1 == 0)
// 		write(1, "\n", 1);
// 	if (w.ws_col > l->current)
// 	{
// 		write(1, l->prompt, str_len_rl(l->prompt));
// 		write(1, l->line, str_len_rl(l->line));
// 		write(1, " ", 1);
// 		get_back_to_pos(l);
// 	}
// 	else
// 	{
// 		tmp = l->current / w.ws_col;
// 		line_size = l->current - (tmp * w.ws_col);
// 		write(1, &l->line[tmp * w.ws_col - l->initial], line_size);
// 	}
// }

void clear_line(void)
{
	write(1, START_LINE, 4);
	write(1, CLEAR_LINE, 4);
}

void clear_term(int y_offset, int x_offset)
{
	int y;

	y = y_offset;
	while (y_offset > 0)
	{
		if (!(y_offset == y && (x_offset == 0 || x_offset == 1)))
		{
			clear_line();
			write(1, UP_TERMINAL, 3);
		}
		y_offset--;
	}
	clear_line();
}


void write_buffer(t_line *l)
{
	t_winsize	w;
	int 		y_offset;
	int 		x_offset;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
	y_offset = l->current / (w.ws_col);
	x_offset = l->current % (w.ws_col);
	clear_term(y_offset, x_offset);
	write(1, l->prompt, str_len_rl(l->prompt));
	write(1, l->line, str_len_rl(l->line));
}

void	handle_backspace(t_line *l)
{
	if (l->current == l->initial)
		return ;
	l->current--;
	write_buffer(l);
}

void handle_enter(t_line *l)
{
	(void)l;
	write(1, "\n", 1);
}

void handle_left(t_line *l)
{
	t_winsize	w;
	int 		y_offset;
	int 		x_offset;

	// if (l->current == l->initial)
	// 	return ;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
	l->current--;
	y_offset = l->current / (w.ws_col);
	x_offset = l->current % (w.ws_col);
	fprintf(stderr, "y_offset: %d\n", y_offset);
	if (x_offset == 0 && w.ws_col > 0)
	{
		write(1, UP_TERMINAL, 3);
		while (w.ws_col >= 0)
		{
			write(1, RIGHT_TERMINAL, 3);
			w.ws_col--;
		}
	}
	else
		write(1, LEFT_TERMINAL, 3);
}

void handle_right(t_line *l)
{
	t_winsize	w;

	if (l->current == str_len_rl(l->line) + l->initial)
		return ;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
	l->current++;
	write(1, RIGHT_TERMINAL, 3);
}

void handle_up(t_line *l)
{
	(void)l;
	write(1,"\e[A", 4);
}

void handle_down(t_line *l)
{
	(void)l;
	write(1,"\e[B", 4);
}

int get_key(char *buffer, int read_bytes)
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
	int			key;

	key = get_key(buffer, read_bytes);
	if (key == PRINTABLE)
		write_buffer(l);
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
