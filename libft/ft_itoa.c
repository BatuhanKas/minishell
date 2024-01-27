/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melihyil <melihyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:28:15 by melihyil          #+#    #+#             */
/*   Updated: 2023/09/02 13:06:44 by melihyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	get_digits(int n)
{
	size_t	i;
	long	num;

	num = n;
	i = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		num = -num;
		i++;
	}
	while (num > 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str_num;
	size_t	digits;
	long	num;

	num = n;
	digits = get_digits(n);
	str_num = (char *)malloc(sizeof(char) * (digits + 1));
	if (!str_num)
		return (NULL);
	str_num[digits] = '\0';
	if (num < 0)
	{
		str_num[0] = '-';
		num = -num;
	}
	if (num == 0)
		str_num[0] = '0';
	while (digits > 0 && num > 0)
	{
		digits--;
		str_num[digits] = (num % 10) + '0';
		num /= 10;
	}
	return (str_num);
}
