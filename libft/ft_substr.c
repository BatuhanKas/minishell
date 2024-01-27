/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:40:40 by melihyil          #+#    #+#             */
/*   Updated: 2024/01/15 18:06:21 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*ptr;

	j = 0;
	i = 0;
	if (!s)
		return (0);
	if (len >= ft_strlen(s))
		ptr = (char *)malloc(ft_strlen(s) + 1 * sizeof(char));
	else
		ptr = (char *)malloc(len + 1 * sizeof(char));
	if (!ptr)
		return (0);
	while (s[j] && i < len)
	{
		if (j >= start)
		{
			ptr[i] = s[j];
			i++;
		}
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}
