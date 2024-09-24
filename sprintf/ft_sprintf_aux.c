/* #include "ft_sprintf.h"

int is_token_SP(char c, const char *tokens)
{
	int ctd;
	
	ctd = 0;
	while (tokens[ctd])
	{
		if (tokens[ctd] == c)
			return (1);
		ctd++;
	}
	return (0);
}

size_t ft_strlen_SP(const char *str)
{
	size_t len;
	
	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_insert_char_SP(char *str, char c, size_t pos)
{
	size_t	len;
	size_t	i;

	len = ft_strlen_SP(str);
	i = len;
	str[len + 1] = 0;
	while (i > pos && i > 0)
	{
		str[i] = str[i - 1];
		i--;
	}
	str[i] = c;
	return (1);
}

void ft_remove_char_SP(char *str, size_t pos)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (i >= pos)
			str[i] = str[i + 1];
		i++;
	}
} */