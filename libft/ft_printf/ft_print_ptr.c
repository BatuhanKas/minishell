/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melihyil <melihyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 13:51:43 by melihyil          #+#    #+#             */
/*   Updated: 2023/09/03 14:08:10 by melihyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_print_ptr(unsigned long long ptr, int i)
{
	int	leng;
	int	tmp;

	leng = 0;
	if (i == 1)
	{
		if (write(1, "0x", 2) == -1)
			return (-1);
		i = 0;
		leng += 2;
	}
	if (ptr >= 16)
	{
		tmp = ft_print_ptr((ptr / 16), i);
		if (tmp == -1)
			return (-1);
		leng += tmp;
	}
	if (write(1, &"0123456789abcdef"[ptr % 16], 1) == -1)
		return (-1);
	return (leng + 1);
}
