#include "readline.h"


int main() {
	char	*line;
	char	*line2;

	line = readLine();
	line2 = readLine();
	printf("line: %s\n", line);
	printf("line2: %s\n", line2);
	history(NULL, 2);
	free(line2);
	free(line);
	free_history(NULL);
	return	0;
}
