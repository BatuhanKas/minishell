/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melihyil <melihyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:21:26 by melihyil          #+#    #+#             */
/*   Updated: 2023/11/09 14:21:56 by melihyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, char *sep)
{
	static char	*save;
	char		*tmp;
	int			i;

	if (str)
		save = str;
	if (!save)
		return (NULL);
	tmp = save;
	while (*tmp)
	{
		i = 0;
		while (sep[i])
		{
			if (*tmp == sep[i])
			{
				*tmp = '\0';
				save = tmp + 1;
				return (tmp);
			}
			i++;
		}
		tmp++;
	}
	return (save = NULL, tmp);
}
