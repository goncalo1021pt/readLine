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


void write_line(t_line *l)
{
	t_winsize	w;
	int 		line_size;
	int 		tmp;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
	write(1, "\r", 1);
	if (l->current % w.ws_col - 1 == 0)
		write(1, "\n", 1);
	if (w.ws_col > l->current)
	{
		write(1, l->prompt, str_len_rl(l->prompt));
		write(1, l->line, str_len_rl(l->line));
		write(1, " ", 1);
		get_back_to_pos(l);
	}
	else
	{
		tmp = l->current / w.ws_col;
		line_size = l->current - (tmp * w.ws_col);
		write(1, &l->line[tmp * w.ws_col - l->initial], line_size);
	}
}

void	handle_backspace(t_line *l)
{
	if (l->current == l->initial)
		return ;
	l->current--;
	write(1, "\b \b", 3);
	write_line(l);
}

void handle_enter(t_line *l)
{
	(void)l;
	write(1, "\n", 1);
}

void handle_left(t_line *l)
{
	t_winsize	w;

	if (l->current == l->initial)
		return ;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
	l->current--;
	if (l->current % w.ws_col == 0)
	{
		write(1, UP_TERMINAL, 3);
		if (l->current - w.ws_col < l->initial)
		{
			write(1, l->prompt, str_len_rl(l->prompt));
			write(1, l->line, str_len_rl(l->line));
		}
		write(1, &l->line[l->current - l->initial], w.ws_col - 1);
	}
	else
		write(1, LEFT_TERMINAL, 3);
}

void handle_right(t_line *l)
{
	write(1, &l->line[l->current - l->initial], 1);
	if (str_len_rl(l->line) + l->initial > l->current)
		l->current++;
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
}

void	key_handler(char *buffer, int read_bytes, t_line *l)
{
	int			key;

	key = get_key(buffer, read_bytes);
	if (key == PRINTABLE)
		write_line(l);
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
