/* #ifndef FT_SPRINTF_H
# define FT_SPRINTF_H

#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

#define SPRINTF_TOKENS "cspdiuxX%"

int put_token(char *str, char *format, int ctd, va_list *ap);
int is_token_SP(char c, const char *tokens);
size_t ft_strlen_SP(const char *str);
int	ft_insert_char_SP(char *str, char c, size_t pos);
void ft_remove_char_SP(char *str, size_t pos);
char *ft_itoa(int n);
int ft_sprintf(char *str, const char *format, ...);


#endif */