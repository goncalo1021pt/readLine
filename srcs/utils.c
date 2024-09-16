#include "readline.h"

int	str_len_rl(char *str)
{
	int	ctd;

	ctd = 0;
	while (str && str[ctd])
		ctd++;
	return (ctd);
}

void	try_free(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

char	*strdup_rl(char *str)
{
	char	*out;
	int		ctd;

	if (!str)
		return (NULL);
	out = malloc(str_len_rl(str) + 1);
	if (!out)
		return (NULL);
	ctd = -1;
	while (str[++ctd])
		out[ctd] = str[ctd];
	out[ctd] = 0;
	return (out);
}

char	*strjoin_rl(char *str1, char *str2, t_pos *p)
{
	char	*out;
	int		ctd;
	int		ctd2;

	ctd = 0;
	out = malloc(str_len_rl(str1) + str_len_rl(str2) + 1);
	if (!out)
		return (try_free(str1), try_free(str2), NULL);
	while (str1 && str1[ctd])
	{
		out[ctd] = str1[ctd];
		ctd++;
	}
	ctd2 = -1;
	while (str2 && str2[++ctd2])
	{
		out[ctd++] = str2[ctd2];
		p->current++;
	}
	out[ctd] = 0;
	return (try_free(str1), out);
}
