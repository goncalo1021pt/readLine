#include "readline.h"

bool	add_history(char *line, t_readline **history)
{
	t_readline	*new;
	t_readline	*tmp;

	new = malloc(sizeof(t_readline));
	if (!new)
		return (false);
	new->line = strdup_rl(line);
	if (!new->line)
		return (try_free(new), false);
	new->next = NULL;
	new->prev = NULL;
	if (!history)
		history = &new;
	if (!*history)
	{
		*history = new;
		return (true);
	}
	tmp = *history;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return (true);
}

void	free_history(t_readline **history)
{
	t_readline	*tmp;

	while (*history)
	{
		tmp = *history;
		*history = (*history)->next;
		try_free(tmp->line);
		try_free(tmp);
	}
}

void	print_history(t_readline *history)
{
	while (history)
	{
		printf("%s\n", history->line);
		history = history->next;
	}
}

bool	history_rl(char *line, int func)
{
	static t_readline	*history = NULL;

	if (func == 0)
	{
		if (!add_history(line, &history))
			return (false);
		return (true);
	}
	else if (func == 1 && history)
	{
		free_history(&history);
		return (true);
	}
	else if (func == 2 && history)
	{
		print_history(history);
		return (true);
	}
	return (false);
}
