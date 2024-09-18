#include "readline.h"

void	handle_backspace(t_line *l)
{
	if (l->current == l->initial)
		return ;
	l->current--;
	write(1, "\b \b", 3);
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

void handle_right()
{
	write(1, "\a", 1);
}

void handle_up()
{
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
			handle_right();
		if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 65)
			printf("up\n");
		if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 66)
			printf("down\n");
	}
	else if (buffer[0] >= 32 && buffer[0] <= 126)
	{
		write(1, "\r", 1);
		write(1, prompt, str_len_rl(prompt));
		write(1, l->line, str_len_rl(l->line));
	}
	else if (buffer[0] == BACKSPACE)
		handle_backspace(l);
	else if (buffer[0] == ENTER)
		handle_enter();
}