#include "readline.h"

void insert_char(char *line, char c, t_pos *p)
{
	size_t	len;
	size_t	i;

	len = str_len_rl(line);
	i = len;
	while (i > p->current)
	{
		line[i] = line[i - 1];
		i--;
	}
	line[p->current] = c;
	p->current++;
}

void remove_char(char *line, size_t pos)
{
	size_t	len;
	size_t	i;

	len = str_len_rl(line);
	i = pos;
	while (i < len)
	{
		line[i] = line[i + 1];
		i++;
	}
}