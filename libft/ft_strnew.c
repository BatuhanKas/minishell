/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melihyil <melihyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 17:34:15 by melihyil          #+#    #+#             */
/*   Updated: 2023/09/03 13:14:01 by melihyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*place;

	size++;
	place = malloc(size);
	if (place == NULL)
		return (NULL);
	ft_memset(place, '\0', size);
	return (place);
}
