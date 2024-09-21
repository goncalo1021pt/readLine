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

char *return_line(t_line *l)
{
	int line_len;

	if (l->line == NULL || *l->line == 0)
	{
		exit_rl(l);
		return (NULL);
	}
	line_len = str_len_rl(l->line);
	l->line = ft_realloc(l->line, line_len + 1);
	l->line[line_len] = 0;
	return (l->line);
}

void	test_stuff(t_line *l)
{
	(void)l;
}

char	*ft_readline(char *prompt)
{
	t_line	l;
	char	buffer[10];
	int		read_bytes;

	init_readline(&l, prompt);
	test_stuff(&l);
	while (true)
	{
		read_bytes = read(0, buffer, 10);
		if (read_bytes == 0 || (buffer[read_bytes - 1] == '\4' && (l.line == NULL || *l.line == 0)))
			break;
		else if (buffer[read_bytes - 1] == '\4')
			continue;
		buffer[read_bytes] = 0;
		if (read_bytes == -1 || !line_handler(&l, buffer))
			return (reset_termios(), try_free(l.line), NULL);
		key_handler(buffer, read_bytes, prompt, &l);
		if (!l.line)
			return (reset_termios(), NULL);
		if (buffer[read_bytes - 1] == '\n')
			break ;
	}
	reset_termios();
	if (!history_rl(l.line, 0))
		return (try_free(l.line), NULL);
	return (return_line(&l));
}
