/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_roundspc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:47:23 by melihyil          #+#    #+#             */
/*   Updated: 2024/01/19 11:46:43 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_roundspc(char *str, int index, char c)
{
	int		i;
	char	*new;

	new = malloc(ft_strlen(str) + 3);
	if (!new)
		return (NULL);
	i = 0;
	while (str[i] && i < index)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = c;
	while (str[i])
	{
		new[i + 1] = str[i];
		i++;
	}
	new[i + 1] = '\0';
	return (new);
}
