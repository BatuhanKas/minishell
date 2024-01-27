/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkas <bkas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:54:00 by bkas              #+#    #+#             */
/*   Updated: 2024/01/27 14:38:41 by bkas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_charcount(const char *s, char c, int *in_quotes)
{
	int	count;

	count = 0;
	while (*s && (*s != c || *in_quotes))
	{
		if (*s == '\"' || *s == '\'')
			*in_quotes = !(*in_quotes);
		else if (*s == c && !(*in_quotes))
		{
			if (*(s + 1) == c || *(s + 1) == '\0')
				break ;
		}
		count++;
		s++;
	}
	return (count);
}

int	ft_strcount(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	if (s[i] == '\0')
		return (0);
	count = 1;
	while (s[i])
	{
		if (s[i + 1] != '\0' && s[i] == c && s[i + 1] != c)
			count++;
		i++;
	}
	return (count);
}

void	ft_fill_token(char **ptr, int x, const char **s, char c)
{
	int	y;
	int	in_quotes;

	in_quotes = 0;
	y = 0;
	ptr[x] = (char *)malloc(sizeof(char)
			* (ft_charcount(*s, c, &in_quotes) + 1));
	if (!ptr[x])
		ft_free_and_return(ptr);
	while (**s && (**s != c || in_quotes))
	{
		if (**s == '\"' || **s == '\'')
			in_quotes = !in_quotes;
		else if (ft_is_end_of_token(s, c, in_quotes))
			break ;
		if (**s != '\0')
			ptr[x][y++] = *(*s)++;
	}
	if (y == 0)
	{
		ptr[x] = NULL;
		free(ptr);
	}
	ptr[x][y] = '\0';
}

int	ft_syntax_continue(const char *s, char c, t_variable *var)
{
	if ((var->i == 0 || s[var->i - 1] == c) && s[var->i] != '|')
	{
		find_left_boundary(s, c, var->i, &var->left);
		var->has_command_before_pipe = has_valid_command(s, c, var->left);
	}
	else if ((s[var->i + 1] == c || s[var->i + 1] == '\0') && s[var->i] != c)
	{
		if (find_right_boundary(s, c, var->i, &var->right))
			return (1);
		var->has_command_after_pipe = has_valid_command(s, c, var->right);
	}
	return (0);
}

int	ft_check_pipe_syntax(const char *s, char c, t_variable *var)
{
	while (s[++var->i] != '\0')
	{
		if (is_quote(s[var->i]))
			var->in_quotes = !var->in_quotes;
		else if (s[var->i] == c && !var->in_quotes)
		{
			if (s[var->i + 1] == c || s[var->i + 1] == '\0')
			{
				if (var->has_command_before_pipe == 0
					|| var->has_command_after_pipe == 0)
					return (printf("minishell: syntax error\
	near unexpected token `|'\n"), 1);
				break ;
			}
		}
		if (!var->in_quotes)
		{
			if (ft_syntax_continue(s, c, var) == 1)
			{
				return (printf("minishell: syntax error\
	near unexpected token `|'\n"), 1);
			}
		}
	}
	return (0);
}
