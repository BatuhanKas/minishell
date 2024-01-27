/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melihyil <melihyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:47:15 by melihyil          #+#    #+#             */
/*   Updated: 2023/09/03 14:08:33 by melihyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_print_hex(unsigned int d, char w)
{
	int	leng;
	int	tmp;

	leng = 0;
	if (d >= 16)
	{
		tmp = ft_print_hex(d / 16, w);
		if (tmp == -1)
			return (-1);
		leng += tmp;
	}
	if (w == 'X')
	{
		if (write(1, &"0123456789ABCDEF"[d % 16], 1) == -1)
			return (-1);
	}
	if (w == 'x')
	{
		if (write(1, &"0123456789abcdef"[d % 16], 1) == -1)
			return (-1);
	}
	return (leng + 1);
}
