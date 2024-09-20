#include "readline.h"


int main() {
	char	*line;

	while(1)
	{
		line = ft_readline("minishell$ ");
		printf("%s\n", line);
		if (line == NULL)
			break ;
		if (!strcmp(line, "quit"))
			break;
		free(line);
	}
	free(line);
	history_rl(NULL, 2);
	history_rl(NULL, 1);
	return	0;
}
