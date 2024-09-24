#ifndef KEYS_H
# define KEYS_H

# define UP_TERMINAL "\e[A"
# define UP_START_TERMINAL "\e[F"
# define DOWN_TERMINAL "\e[B"
# define RIGHT_TERMINAL "\e[C"
# define LEFT_TERMINAL "\e[D"
# define CLEAR_TERMINAL "\e[2J\e[H"
# define THIN "\e[5 q"
# define BLOCK "\e[0 q"

typedef struct s_line	t_line;

typedef enum e_keycodes
{
	PRINTABLE,
	ESC,
	BACKSPACE,
	ENTER,
	CTRL_C,
	CTRL_D,
	UP,
	DOWN,
	RIGHT,
	LEFT,
}	t_keycodes;

#endif