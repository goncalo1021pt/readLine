#include "readline.h"


int main() {
	char	*line;

	while(1)
	{
		line = ft_readline("minishell$ ");
		if (line == NULL)
		{
			write(1, "\nexit\n", 6);
			break ;
		}
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
