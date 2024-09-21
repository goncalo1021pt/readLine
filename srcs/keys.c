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


void write_line(t_line *l, char *prompt)
{
	t_winsize w;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
	write(1, "\r", 1);
	if (w.ws_col >= l->current)
	{
		write(1, prompt, str_len_rl(prompt));
		write(1, l->line, str_len_rl(l->line));
		write(1, " ", 1);
		get_back_to_pos(l);
	}
	else
		write(1, l->line, str_len_rl(l->line) - w.ws_col + str_len_rl(prompt));
}

void	handle_backspace(t_line *l, char *prompt)
{
	if (l->current == l->initial)
		return ;
	l->current--;
	write(1, "\b \b", 3);
	write_line(l, prompt);
}

void handle_enter(void)
{
	write(1, "\n", 1);
}

void handle_left(t_line *l)
{
	if (l->current == l->initial)
		return ;
	l->current--;
	write(1, "\b", 1);
}

void handle_right(t_line *l)
{
	write(1, &l->line[l->current - l->initial], 1);
	if (str_len_rl(l->line) + l->initial > l->current)
		l->current++;
}

void handle_up()
{
	printf("\033[A");
	fflush(STDIN_FILENO);
}

void handle_down()
{

}
// void

void key_handler(char *buffer, int read_bytes, char *prompt, t_line *l)
{
	if (read_bytes == 3)
	{
		if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 68)
			handle_left(l);
		if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 67)
			handle_right(l);
		if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 65)
			handle_down();
		if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 66)
			printf("down\n");
	}
	else if (buffer[0] >= 32 && buffer[0] <= 126)
	{
		write_line(l, prompt);
	}
	else if (buffer[0] == BACKSPACE)
		handle_backspace(l, prompt);
	else if (buffer[0] == ENTER)
		handle_enter();
	// test_stuff(l);
}