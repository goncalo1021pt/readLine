#include "readline.h"

size_t	str_len_rl(char *str)
{
	size_t	ctd;

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

char	*strjoin_rl(char *str1, char *str2, t_line *p)
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

void	*ft_realloc(void *ptr, size_t size)
{
	void	*out;

	out = ft_calloc(size, 1);
	if (!out)
		return (try_free(ptr), NULL);
	ft_memcpy(out, ptr, size);
	try_free(ptr);
	return (out);
}

void	ft_memcpy(void *dst, void *src, size_t size)
{
	size_t	ctd;

	ctd = 0;
	while (ctd < size)
	{
		((char *)dst)[ctd] = ((char *)src)[ctd];
		ctd++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*out;
	size_t	ctd;

	out = malloc(count * size);
	if (!out)
		return (NULL);
	ctd = 0;
	while (ctd < count * size)
	{
		((char *)out)[ctd] = 0;
		ctd++;
	}
	return (out);
}
