#include "readline.h"


char	*ft_readline(char *prompt)
{
	char				*line;
	t_pos				p;
	char				buffer[READLINE_BUFFER_SIZE + 1];
	int					read_bytes;

	line = NULL;
	set_termios();
	p.initial = str_len_rl(prompt);
	p.current = p.initial;
	write(1, prompt, p.initial);
	while (true)
	{
		read_bytes = read(0, buffer, READLINE_BUFFER_SIZE);
		if (read_bytes == -1)
			return (reset_termios(), try_free(line), NULL);
		if (read_bytes == 0)
			break ;
		buffer[read_bytes] = 0;
		if (read_bytes == 1 && buffer[0] >= 32 && buffer[0] <= 126)
			line = strjoin_rl(line, buffer, &p);
		key_handler(buffer, read_bytes, &line, &p); 
		if (!line)
			return (reset_termios(), NULL);
		if (buffer[read_bytes - 1] == '\n' || buffer[read_bytes - 1] == '\4')
		{
			// line[str_len_rl(line) - 1] = 0;
			break ;
		}
	}
	reset_termios();
	if (!history_rl(line, 0))
		return (try_free(line), NULL);
	return (line);
}
