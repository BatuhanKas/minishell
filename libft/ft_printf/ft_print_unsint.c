/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melihyil <melihyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:32:24 by melihyil          #+#    #+#             */
/*   Updated: 2023/09/03 15:18:36 by melihyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <unistd.h>

int	ft_print_unsint(unsigned int nb)
{
	int	leng;
	int	tmp;

	leng = 0;
	if (nb >= 10)
	{
		tmp = ft_print_unsint(nb / 10);
		if (tmp == -1)
			return (-1);
		leng += tmp;
	}
	if (write(1, &"0123456789"[nb % 10], 1) == -1)
		return (-1);
	return (leng + 1);
}
