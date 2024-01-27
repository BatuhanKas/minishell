/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melihyil <melihyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:07:19 by melihyil          #+#    #+#             */
/*   Updated: 2023/09/19 17:07:45 by melihyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	ft_atol(const char *str)
{
	long	i;
	long	neg;
	long	count;

	i = 0;
	neg = 1;
	count = 0;
	if ((str[i] >= '\001' && str[i] <= '\010'))
		return (0);
	while ((str[i] > 0 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		count *= 10;
		count += (str[i] - 48);
		i++;
	}
	return (count * neg);
}
