/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:20:17 by bkas              #+#    #+#             */
/*   Updated: 2024/01/08 17:02:12 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_quote(char c)
{
	return (c == '\"' || c == '\'');
}

int	has_valid_command(const char *s, char c, int start)
{
	return (s[start] == c && s[start + 1] != '\0' && s[start + 1] != c);
}

int	check_space_between_pipes(const char *s, char c, int position)
{
	int	i;

	i = position;
	i++;
	while (is_space(s[i]) && s[i] != '\0')
		i++;
	if (s[i] == c)
		return (1);
	return (0);
}

void	find_left_boundary(const char *s, char c, int position, int *boundary)
{
	int	left;

	left = position;
	while (left > 0 && s[left] != c && s[left] != '\0')
		left--;
	*boundary = left;
}

int	find_right_boundary(const char *s, char c, int position, int *boundary)
{
	int	right;

	right = position;
	while (s[right] != c && s[right] != '\0')
		right++;
	*boundary = right;
	if (s[right] == c)
		if (check_space_between_pipes(s, c, right))
			return (1);
	return (0);
}
