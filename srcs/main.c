#include "readline.h"

int	try_free1(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
	return (1);
}

int main() {
	char	*line;

	while(1)
	{
		line = ft_readline("minishell$ ");
		if (line == NULL)
		{
			write(1, "exit\n", 6);
			break ;
		}
		if (line[0] == 0 && try_free1(line))
			continue ;
		printf("%s\n", line);
		if (!strcmp(line, "quit"))
			break;
		free(line);
	}
	free(line);
	// history_rl(NULL, 2);
	history_rl(NULL, 1);
	return	0;
}
