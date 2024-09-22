#ifndef KEYS_H
# define KEYS_H

#include <stdio.h>
# define UP_TERMINAL "\e[A"
# define UP_START_TERMINAL "\e[F"
# define DOWN_TERMINAL "\e[B"
# define RIGHT_TERMINAL "\e[C"
# define LEFT_TERMINAL "\e[D"


// typedef struct s_key
// {
// 	char	*seq;
// 	void	(*func)(void);
// }	t_key;

// typedef struct s_keymap
// {
// 	t_key	*keys;
// 	int		size;
// }	t_keymap;

typedef enum e_keycodes
{
	PRINTABLE,
	ESC = 27,
	BACKSPACE = 127,
	ENTER = 10,
	CTRL_C = 3,
	CTRL_D = 4,
	UP = 65,
	DOWN = 66,
	RIGHT = 67,
	LEFT = 68,
}	t_keycodes;


#endif