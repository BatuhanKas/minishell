/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melihyil <melihyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:03:57 by melihyil          #+#    #+#             */
/*   Updated: 2024/01/11 13:38:10 by melihyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	int	i;

	if (str == NULL || str == 0 || str[0] == 0)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}
