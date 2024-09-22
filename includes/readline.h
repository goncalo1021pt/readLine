#ifndef READLINE_H
# define READLINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdbool.h>
# include <string.h>
# include <termios.h>
# include <sys/ioctl.h>
# include "keys.h"

# define READLINE_BUFFER_SIZE 1024

typedef struct s_readline
{
	char				*line;
	struct s_readline	*next;
	struct s_readline	*prev;

}	t_readline;

typedef struct s_line
{
	size_t	initial;
	size_t	current;
	size_t	buffer_size;
	char	*prompt;
	char	*line;
}	t_line;

typedef struct s_winsize
{
	unsigned short	ws_row;
	unsigned short	ws_col;
	unsigned short	ws_xpixel;
	unsigned short	ws_ypixel;
}	t_winsize;

// utils
size_t		str_len_rl(char *str);
void		try_free(void *ptr);
char		*strjoin_rl(char *str1, char *str2, t_line *p);
char		*strdup_rl(char *str);
void		*ft_realloc(void *ptr, size_t size);
void		ft_memcpy(void *dst, void *src, size_t size);
void		*ft_calloc(size_t count, size_t size);

// string
bool		line_handler(t_line *l, char *buffer);
void		insert_char(t_line *l, char c);
void		remove_char(t_line *l);
bool		alloc_handler(t_line *l);

// readline
void		set_termios(void);
void		reset_termios(void);
char		*ft_readline(char *promt);
t_winsize	test_stuff(t_line *l);

// keys
void		key_handler(char *buffer, int read_bytes, t_line *l);

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