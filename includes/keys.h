#ifndef KEYS_H
# define KEYS_H

#include <stdio.h>

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
	ESC = 27,
	BACKSPACE = 127,
	ENTER = 10,
	CTRL_C = 3,
	CTRL_D = 4,
	UP = 65,
	DOWN = 66,
	RIGHT = 67,
	LEFT = 68,
} t_keycodes;

typedef void (*KeyAction)(char *line, size_t *len);

typedef struct {
    t_keycodes	code;
    KeyAction	action;
} KeyHandler;


#endif