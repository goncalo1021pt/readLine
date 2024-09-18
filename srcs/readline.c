#include "readline.h"

void	exit_rl(t_line *l)
{
	if (l->line)
		free(l->line);
	l->line = NULL;
}

void	save_pointer(t_line *l)
{
	static t_line	*line;

	if (l)
		line = l;
	else
		exit_rl(line);
}

void	init_readline(t_line *l, char *prompt)
{
	l->line = NULL;
	l->buffer_size = 0;
	set_termios();
	l->initial = str_len_rl(prompt);
	l->current = l->initial;
	write(1, prompt, l->initial);
}

char	*ft_readline(char *prompt)
{
	t_line	l;
	char	buffer[10];
	int		read_bytes;

	init_readline(&l, prompt);
	while (true)
	{
		read_bytes = read(0, buffer, 10);
		if (read_bytes == -1)
			return (reset_termios(), try_free(l.line), NULL);
		if (read_bytes == 0)
			break ;
		buffer[read_bytes] = 0;
		if (!line_handler(&l, buffer))
			return (reset_termios(), try_free(l.line), NULL);
		key_handler(buffer, read_bytes, prompt, &l); 
		if (!l.line)
			return (reset_termios(), NULL);
		if (buffer[read_bytes - 1] == '\n' || buffer[read_bytes - 1] == '\4')
		{
			// l.line[str_len_rl(l.line) - 1] = 0;
			break ;
		}
	}
	reset_termios();
	if (!history_rl(l.line, 0))
		return (try_free(l.line), NULL);
	return (l.line);
}
