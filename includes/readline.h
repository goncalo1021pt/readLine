#ifndef READLINE_H
# define READLINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdbool.h>
# include <string.h>

# define READLINE_BUFFER_SIZE 4

typedef struct s_readline
{
	char				*line;
	struct s_readline	*next;
	struct s_readline	*prev;

}	t_readline;

// utils
int		str_len_rl(char *str);
void	try_free(void *ptr);
char	*strjoin_rl(char *str1, char *str2);
char	*strdup_rl(char *str);

// readline
void	set_termios(void);
void	reset_termios(void);
char	*ft_readline(void);

// history

/**
 * @brief Manages the history of commands.
 *
 * @param line The command line to be added to history.
 * @param func The function to perform:
 *             - 0: Add the line to history.
 *             - 1: Free the history.
 *             - 2: Print the history.
 * @return true if the operation was successful, false otherwise.
 */
bool	history_rl(char *line, int func);
// bool	add_history(char *line, t_readline **history);
// void	free_history(t_readline **history);
// void	print_history(t_readline *history);

#endif