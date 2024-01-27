/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melihyil <melihyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:52:59 by melihyil          #+#    #+#             */
/*   Updated: 2023/10/20 20:47:03 by melihyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t		dst_i;
	size_t		src_i;
	size_t		len;

	if (size == 0)
		return (ft_strlen(src));
	else if (size < ft_strlen(dest))
		return (ft_strlen(src) + size);
	else
		len = ft_strlen(src) + ft_strlen(dest);
	dst_i = 0;
	while (dest[dst_i] != '\0')
		dst_i++;
	src_i = 0;
	while (src[src_i] != '\0' && dst_i + 1 < size)
	{
		dest[dst_i] = src[src_i];
		src_i++;
		dst_i++;
	}
	dest[dst_i] = '\0';
	return (len);
}
