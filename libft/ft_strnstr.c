/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:12:33 by melihyil          #+#    #+#             */
/*   Updated: 2024/01/15 18:06:18 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	b;
	size_t	flen;
	char	*ptr;

	flen = ft_strlen(to_find);
	i = 0;
	ptr = (char *)str;
	if (to_find[i] == '\0' || flen == 0 || str == to_find)
		return (ptr);
	if (len == 0)
		return (0);
	while ((ptr[i] != '\0') && (i < len))
	{
		b = 0;
		while (ptr[i + b] && to_find[b]
			&& ptr[i + b] == to_find[b] && i + b < len)
			b++;
		if (b == flen)
			return (ptr + i);
		i++;
	}
	return (0);
}
