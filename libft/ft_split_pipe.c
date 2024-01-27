/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:42:17 by bkas              #+#    #+#             */
/*   Updated: 2024/01/27 14:26:10 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	init_variable(t_variable *var)
{
	var->left = 0;
	var->right = 0;
	var->in_quotes = 0;
	var->has_command_before_pipe = 0;
	var->has_command_after_pipe = 0;
	var->i = -1;
}

int	ft_run_pipe(const char *s, char c)
{
	t_variable	var;
	int			ret;

	ret = 0;
	init_variable(&var);
	ret = ft_check_pipe_syntax(s, c, &var);
	return (ret);
}

int	pipe_check(const char *s, char c)
{
	if (c == '|' && ((ft_first_pipe_control(s, c))
			|| (ft_last_pipe_control(s, c))))
		return (1);
	return (0);
}

int	full_space_control(const char *s)
{
	int	i;

	i = 0;
	while (is_space(s[i]))
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}

char	**ft_split_pipe(const char *s, char c)
{
	char	**ptr;
	int		x;

	if (full_space_control(s))
		return (NULL);
	if (pipe_check(s, c))
		return (printf("Syntax error: near unexpected token `|'\n"), NULL);
	ptr = (char **)ft_calloc(sizeof(char *), (ft_strcount(s, c) + 1));
	if (!ptr)
		return (NULL);
	x = -1;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			if (c == '|' && ft_run_pipe(s, c) == 1)
				return (ft_full_free(ptr));
			ft_fill_token(ptr, ++x, &s, c);
		}
	}
	if (x == -1)
		return (ptr[0] = NULL, free(ptr), NULL);
	return (ptr[++x] = NULL, ptr);
}
