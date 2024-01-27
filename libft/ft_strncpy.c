/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 11:48:28 by melihyil          #+#    #+#             */
/*   Updated: 2024/01/15 18:06:15 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, char *src, size_t len)
{
	size_t	counter;
	char	*pointer_to_dest_start;
	size_t	src_len;

	pointer_to_dest_start = dst;
	src_len = ft_strlen(src);
	counter = 0;
	while (counter < len)
	{
		if (counter < src_len)
		{
			*dst = *src;
			src++;
		}
		else
			*dst = '\0';
		dst++;
		counter++;
	}
	return (pointer_to_dest_start);
}
