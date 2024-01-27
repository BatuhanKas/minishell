/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melihyil <melihyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:55:27 by melihyil          #+#    #+#             */
/*   Updated: 2023/09/03 15:18:30 by melihyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdarg.h>

static int	ft_formats(va_list *args, const char format)
{
	int	print_length;

	print_length = 0;
	if (format == 'c')
		print_length += ft_print_char(va_arg(*args, int));
	else if (format == 's')
		print_length += ft_print_str(va_arg(*args, char *));
	else if (format == 'p')
		print_length += ft_print_ptr(va_arg(*args, unsigned long long), 1);
	else if (format == 'd' || format == 'i')
		print_length += ft_print_int(va_arg(*args, int));
	else if (format == 'u')
		print_length += ft_print_unsint(va_arg(*args, unsigned int));
	else if (format == 'x' || format == 'X')
		print_length += ft_print_hex(va_arg(*args, unsigned int), format);
	else if (format == '%')
		print_length += ft_printpercent();
	return (print_length);
}

static int	ft_check_format(char str)
{
	if (str == 'c' || str == 'd' || str == 'i' || str == 'u' || str == '%'
		|| str == 's' || str == 'x' || str == 'X' || str == 'p')
		return (1);
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		leng;
	int		counter;
	int		tmp;

	counter = -1;
	leng = 0;
	va_start(args, str);
	while (str[++counter] != '\0')
	{
		if (str[counter] == '%' && ft_check_format(str[counter + 1]))
		{
			tmp = ft_formats(&args, str[++counter]);
			if (tmp == -1)
				return (-1);
			leng += tmp - 1;
		}
		else if (str[counter] == '%' && str[counter + 1] != '%')
			return (-1);
		else if (ft_print_char(str[counter]) == -1)
			return (-1);
		leng++;
	}
	va_end(args);
	return (leng);
}
