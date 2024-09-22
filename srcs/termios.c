#include "readline.h"

struct termios	old_termios(void)
{
	static struct termios	old;
	static bool				init = false;

	if (!init)
	{
		tcgetattr(0, &old);
		init = true;
	}
	return (old);
}

void	set_termios(void)
{
	struct termios	new;

	new = old_termios();

	new.c_lflag &= ~(ICANON | ECHO);
	new.c_cc[VMIN] = 1;
	new.c_cc[VTIME] = 0;

	write(STDOUT_FILENO, "\e[5 q", 5);
	tcsetattr(0, TCSANOW, &new);
}

void	reset_termios(void)
{
	struct termios	old;

	old = old_termios();
	write(STDOUT_FILENO, "\e[0 q", 5);
	tcsetattr(0, TCSANOW, &old);
}

