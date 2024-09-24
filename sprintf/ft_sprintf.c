/* #include "ft_sprintf.h"

int put_token(char *str, char *format, int ctd, va_list *ap)
{
	int ret;
	char *tmp;
	
	ret = 0;
	if (*format == 'c')
		ret += ft_insert_char_SP(str, va_arg(*ap, int), ctd);
	else if (*format == 's')
	{
		tmp = va_arg(*ap, char *);
		while (tmp[ret])
			ret += ft_insert_char_SP(str, va_arg(*ap, int), ctd++);
	}
	else if (*format == 'd' || *format == 'i')
	{
		tmp = ft_itoa(va_arg(*ap, int));
		while (tmp[ret])
			ret += ft_insert_char_SP(str, tmp[ret], ctd++);
		free(tmp);
	}
	else if (*format == '%')
		ret += ft_insert_char_SP(str, '%', ctd);
	return (ret);
}

int ft_sprintf(char *str, const char *format, ...)
{
	va_list ap;
	int ctd;
	
	va_start(ap, format);
	ctd = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (is_token_SP(*format, SPRINTF_TOKENS))
				ctd += put_token(str, format, ctd, &ap);
		}
		else
			str[ctd++] = *format;
		format++;
	}
	va_end(ap);
	return (ctd);
} */