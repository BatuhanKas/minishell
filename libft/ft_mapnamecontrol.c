/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapnamecontrol.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melihyil <melihyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:51:34 by melihyil          #+#    #+#             */
/*   Updated: 2023/09/05 15:21:27 by melihyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_mapnamecontrol(char *str, char dot)
{
	int	i;
	int	three;

	three = 3;
	i = ft_strlen(str);
	if (dot != '\0')
	{
		while (three > 0)
		{
			i--;
			three--;
		}
	}
	if (str[i] != 'b')
		return (1);
	return (0);
}
