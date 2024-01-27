/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melihyil <melihyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:34:29 by bkas              #+#    #+#             */
/*   Updated: 2024/01/11 12:19:26 by melihyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_copy_and_append_char(char *dst, char *src, int c)
{
	int		i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i++] = c;
	dst[i] = '\0';
}

char	*ft_strjoin_char(char *s1, char c)
{
	int		cp;
	int		size;
	char	*ptr;

	cp = 0;
	size = ft_strlen(s1);
	ptr = (char *)malloc(sizeof(char) * (size + 2));
	if (!ptr)
		return (NULL);
	if (s1 && size)
		ft_copy_and_append_char(ptr, s1, c);
	else
	{
		ptr[cp] = c;
		ptr[cp + 1] = '\0';
	}
	return (ptr);
}
