#ifndef READLINE_H
# define READLINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdbool.h>
# include <string.h>
# include <termios.h>
# include "keys.h"

# define READLINE_BUFFER_SIZE 4

typedef struct s_readline
{
	char				*line;
	struct s_readline	*next;
	struct s_readline	*prev;

}	t_readline;

typedef struct s_pos
{
	size_t	initial;
	size_t	current;
}	t_pos;

// utils
int		str_len_rl(char *str);
void	try_free(void *ptr);
char	*strjoin_rl(char *str1, char *str2, t_pos *p);
char	*strdup_rl(char *str);

// string
void	insert_char(char *line, char c, t_pos *p);
void	remove_char(char *line, size_t pos);

// readline
void	set_termios(void);
void	reset_termios(void);
char	*ft_readline(char *promt);

// keys
void	key_handler(char *buffer, int read_bytes, char **line, t_pos *p);

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