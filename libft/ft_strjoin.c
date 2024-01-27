/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 19:30:20 by melihyil          #+#    #+#             */
/*   Updated: 2024/01/15 18:06:07 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int			c1;
	int			c2;
	int			cp;
	char		*ptr;

	c1 = 0;
	c2 = 0;
	cp = 0;
	if (!s1)
		return (ft_strdup(s2));
	ptr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1 * sizeof(char));
	if (!ptr)
		return (0);
	while (*s1 && s1 && s1[c1])
	{
		ptr[cp] = s1[c1];
		c1++;
		cp++;
	}
	if (!s2)
		return (ptr[cp] = '\0', ptr);
	while (s2[c2])
		ptr[cp++] = s2[c2++];
	return (ptr[cp] = '\0', ptr);
}
