#include "readline.h"

void	insert_char(t_line *l, char c)
{
	size_t	len;
	size_t	i;

	len = str_len_rl(l->line);
	i = len;
	while (i > l->current - l->initial)
	{
		l->line[i] = l->line[i - 1];
		i--;
	}
	l->line[l->current - l->initial] = c;
	l->current++;
}

void	remove_char(t_line *l)
{
	size_t	len;
	size_t	i;

	len = str_len_rl(l->line) + l->initial;
	i = l->current - 1;
	while (i < len)
	{
		l->line[i - l->initial] = l->line[i + 1 - l->initial];
		i++;
	}
}

bool	alloc_handler(t_line *l)
{
	if (l->line == NULL)
	{
		l->line = ft_calloc(READLINE_BUFFER_SIZE, sizeof(char));
		if (!l->line)
			return (false);
		l->buffer_size = READLINE_BUFFER_SIZE;
	}
	else if (str_len_rl(l->line) == l->buffer_size - 1)
	{
		l->buffer_size += READLINE_BUFFER_SIZE;
		l->line = ft_realloc(l->line, l->buffer_size);
		if (!l->line)
			return (false);
	}
	return (true);
}

bool	line_handler(t_line *l, char *buffer)
{
	if (!alloc_handler(l))
		return (false);
	if (buffer[0] >= 32 && buffer[0] <= 126)
	{
		insert_char(l, buffer[0]);
	}
	else if (buffer[0] == 127)
		remove_char(l);
	return (true);
}
