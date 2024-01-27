/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melihyil <melihyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:20:10 by melihyil          #+#    #+#             */
/*   Updated: 2023/09/02 13:05:21 by melihyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	count;

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
