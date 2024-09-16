#include "readline.h"

void handle_backspace(char *line, t_pos *p)
{
	if (p->current == p->initial)
		return ;
	remove_char(line, p->current - 1 - p->initial);
	p->current--;
	write(1, "\b \b", 3);
}

void handle_enter(void)
{
	write(1, "\n", 1);
}

void handle_left(char *line)
{
	(void)line;
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

void key_handler(char *buffer, int read_bytes, char **line, t_pos *p)
{
	if (read_bytes == 3)
	{
		if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 68)
			handle_left(*line);
		if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 67)
			handle_right();
		if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 65)
			printf("up\n");
		if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 66)
			printf("down\n");
	}
	else if (buffer[0] >= 32 && buffer[0] <= 126)
		write(1, buffer, read_bytes);
	else if (buffer[0] == BACKSPACE)
		handle_backspace(*line, p);
	else if (buffer[0] == ENTER)
		handle_enter();
}