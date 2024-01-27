/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:44:12 by bkas              #+#    #+#             */
/*   Updated: 2024/01/08 16:59:44 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_first_pipe_control(const char *tmp, char c)
{
	int	i;

	i = 0;
	while (is_space(tmp[i]) && tmp[i] != '\0')
		i++;
	if (tmp[i] == c)
		return (1);
	return (0);
}

int	ft_last_pipe_control(const char *tmp, char sep)
{
	int	i;

	i = 0;
	while (tmp[i] != '\0')
		i++;
	i--;
	while (is_space(tmp[i]) && i > 0)
		i--;
	if (tmp[i] == sep)
		return (1);
	return (0);
}
