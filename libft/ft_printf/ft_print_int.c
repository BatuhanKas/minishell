/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melihyil <melihyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:01:18 by melihyil          #+#    #+#             */
/*   Updated: 2023/09/03 15:18:47 by melihyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <unistd.h>

int	ft_print_int(int nb)

{
	int	leng;
	int	tmp;

	leng = 0;
	if (nb == 0)
		return (write(1, "0", 1));
	if (nb == -2147483648)
		return (write(1, "-2147483648", 11));
	if (nb < 0)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		leng++;
		nb *= -1;
	}
	if (nb >= 10)
	{
		tmp = ft_print_int(nb / 10);
		if (tmp == -1)
			return (-1);
		leng += tmp;
	}
	if (write(1, &"0123456789"[nb % 10], 1) == -1)
		return (-1);
	return (leng + 1);
}
