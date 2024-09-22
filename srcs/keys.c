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

void handle_enter(void)
{
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

void handle_up()
{
	write(1,"\e[A", 4);
}

void handle_down()
{

}
// void

void key_handler(char *buffer, int read_bytes, t_line *l)
{
	if (read_bytes == 3)
	{
		if (buffer[0] == 27 && buffer[1] == '[' && buffer[2] == 68)
			handle_left(l);
		if (buffer[0] == 27 && buffer[1] == '[' && buffer[2] == 67)
			handle_right(l);
		if (buffer[0] == 27 && buffer[1] == '[' && buffer[2] == 65)
			handle_up();
		if (buffer[0] == 27 && buffer[1] == '[' && buffer[2] == 66)
			printf("down\n");
	}
	else if (buffer[0] >= 32 && buffer[0] <= 126)
	{
		write_line(l);
	}
	else if (buffer[0] == BACKSPACE)
		handle_backspace(l);
	else if (buffer[0] == ENTER)
		handle_enter();
	// test_stuff(l);
}