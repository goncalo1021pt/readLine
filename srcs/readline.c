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
	l->prompt = prompt;
	set_termios();
	l->initial = str_len_rl(prompt);
	l->current = l->initial;
	alloc_handler(l);
	write(1, prompt, l->initial);
}

char	*return_line(t_line *l)
{
	int	line_len;

	write(1, "\n", 1);
	if (l->line == NULL || *l->line == 0)
	{
		try_free(l->line);
		l->line = ft_calloc(1, 1);
		return (l->line);
	}
	line_len = str_len_rl(l->line);
	l->line = ft_realloc(l->line, line_len + 1);
	l->line[line_len] = 0;
	return (l->line);
}

t_winsize	test_stuff(t_line *l)
{
	(void)l;
	static t_winsize w;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
	printf("Rows: %d\n", w.ws_row);
	printf("Columns: %d\n", w.ws_col);
	printf("ws_xpixel: %d\n", w.ws_xpixel);
	printf("ws_ypixel: %d\n", w.ws_ypixel);
	return w;
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
		if (read_bytes == 0 || (buffer[read_bytes - 1] == '\4' && (l.line == NULL || *l.line == 0)))
			return (reset_termios(), try_free(l.line), write(1, "\n", 1), NULL);
		else if (buffer[read_bytes - 1] == '\4')
			continue ;
		buffer[read_bytes] = 0;
		if (read_bytes == -1 || !line_handler(&l, buffer))
			return (reset_termios(), try_free(l.line), write(1, "\n", 1), NULL);
		key_handler(buffer, read_bytes, &l);
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
