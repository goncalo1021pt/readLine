#include "readline.h"


int main() {
	char	*line;

	while(1)
	{
		line = ft_readline();
		printf("line: %s\n", line);
		history_rl(NULL, 2);
		if (!strcmp(line, "quit"))
			break;
		free(line);
	}
	free(line);
	history_rl(NULL, 1);
	return	0;
}
